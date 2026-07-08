#include "../includes/Reverb.hpp"
#include <iostream>
#include <math.h>

Reverb::Reverb() : _head(0), _head_layer(0)
{
    pthread_mutex_init(&_mutex, NULL);
    SetLayerSize(10);
    SetDuration(0.1);
}

Reverb::~Reverb()
{
    pthread_mutex_destroy(&_mutex);
}

size_t Reverb::GetLayerSize() const
{
    return _layer_size;
}

float Reverb::GetDuration() const
{
    return _duration;
}

void Reverb::SetLayerSize(size_t value)
{
    _layer_size = value;
    _buffers.resize(_layer_size);
    _layer_coef.resize(_layer_size);
    float coef = 0;
    // float inc = 1.0 / (_layer_size + 1);
    float coef = 1 / pow(2, static_cast<float>(_layer_size));
    for (size_t i = 0; i < _layer_size; i++)
    {
        // coef += inc;
        _layer_coef[i] = coef;
        coef *= 2;
        // std::cout << "Layer " << i << " coef: " << _layer_coef[i] << std::endl;
    }
    if (_head_layer >= _layer_size)
        _head_layer = 0;
    SetDuration(_duration);
}

void Reverb::IncLayerSize(int value)
{
    pthread_mutex_lock(&_mutex);
    if (!(value < 0 && _layer_size <= static_cast<size_t>(-value)))
        SetLayerSize(_layer_size + value);
    pthread_mutex_unlock(&_mutex);
}

void Reverb::SetDuration(float value)
{
    _duration = value;
    _buffer_size = static_cast<size_t>(PcmSetting::FRAME_RATE * _duration);
    for (auto &buffer : _buffers)
    {
        if (buffer.size() != _buffer_size)
            buffer.resize(_buffer_size, 0.0);
    }
    if (_head > _buffer_size)
        _head = 0;
}

void Reverb::IncDuration(float value)
{
    float v;
    pthread_mutex_lock(&_mutex);
    v = _duration + value;
    if (v < 0.1)
        v = 0.1;
    SetDuration(v);
    pthread_mutex_unlock(&_mutex);
}

void Reverb::Process()
{
    pthread_mutex_lock(&_mutex);
    float input_len = static_cast<float>(AudioIn::_buffers.size());
    size_t current_layer;
    for (size_t i = 0; i < PcmSetting::BUFFER_LEN; i++)
    {
        AudioOut::_buffer[i] = 0;
        for (size_t j = 0; j < _layer_size; j++)
        {
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

void Reverb::print() const
{
    std::cout << "\r[ " << _duration << " ]" << "\t\t\t\t[ " << _layer_size << " ]\t\t\t\t\t" << std::flush;
}
