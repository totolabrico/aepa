#include "../includes/AudioOut.hpp"

AudioOut::AudioOut() {}

AudioOut::~AudioOut() {}

PcmSetting::AudioBuffer const &AudioOut::GetBuffer() const
{
    return _buffer;
}