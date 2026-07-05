#include "../includes/Reverb.hpp"
#include <iostream>
#include <math.h>

Reverb::Reverb() : _head(0), _head_layer(0)
{
    pthread_mutex_init(&_mutex, NULL);
    SetLayerSize(20);
    SetDuration(10.0);
}

Reverb::~Reverb()
{
    pthread_mutex_destroy(&_mutex);
}

void Reverb::SetLayerSize(size_t value)
{
    _layer_size = value;
    _buffers.resize(_layer_size);
    _layer_coef.resize(_layer_size);
    float coef = 1 / pow(2, static_cast<float>(_layer_size));
    for (size_t i = 0; i < _layer_size; i++)
    {
        _layer_coef[i] = coef;
        coef *= 2;
    }
    if (_head_layer >= _layer_size)
        _head_layer = 0;
}

void Reverb::SetDuration(float value)
{
    std::cout << "Reverb set duration to " << value << std::endl;
    _duration = value;
    _buffer_size = static_cast<size_t>(PcmSetting::FRAME_RATE * _duration / _layer_size);
    for (auto &buffer : _buffers)
        buffer.resize(_buffer_size, 0.0);
    if (_head > _buffer_size)
        _head = 0;
}

void Reverb::Process()
{
    pthread_mutex_lock(&_mutex);
    float input_len = static_cast<float>(AudioIn::_buffers.size());
    size_t current_layer;
    for (size_t i = 0; i < PcmSetting::BUFFER_LEN; i++)
    {
        AudioOut::_buffer[i] = 0;
        float total = 0;
        for (size_t j = 0; j < _layer_size; j++)
        {
            total += _layer_coef[j];
            current_layer = (_head_layer + j) % _layer_size;
            AudioOut::_buffer[i] += _buffers[current_layer][_head] * _layer_coef[j];
        }
        _buffers[_head_layer][_head] = 0;
        for (const auto &ref : AudioIn::_buffers)
        {
            const auto buf = *ref;
            _buffers[_head_layer][_head] += buf[i] / input_len;
        }
        _head++;
        if (_head == _buffer_size)
        {
            _head_layer = (_head_layer + 1) % _layer_size;
            _head = 0;
        }
    }
    pthread_mutex_unlock(&_mutex);
}
