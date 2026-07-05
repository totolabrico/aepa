#include "../includes/AudioIn.hpp"
#include <iostream>

AudioIn::AudioIn() {}

AudioIn::~AudioIn() {}

void AudioIn::PlugIn(AudioOut const &src)
{
    auto it = std::find(_buffers.begin(), _buffers.end(), &src.GetBuffer());
    if (it == _buffers.end())
        _buffers.push_back(&src.GetBuffer());
}

void AudioIn::UnPlugIn(AudioOut const &src)
{
    auto it = std::find(_buffers.begin(), _buffers.end(), &src.GetBuffer());
    if (it != _buffers.end())
        _buffers.erase(it);
}

void AudioIn::SumSignalsIn(PcmSetting::AudioBuffer &buffer)
{
    std::fill(buffer.begin(), buffer.end(), 0);
    size_t len = _buffers.size();
    for (const auto &ref : _buffers)
    {
        const auto &buf = *ref;
        for (size_t i = 0; i < buffer.size(); ++i)
            buffer[i] += buf[i] / len;
    }
}
