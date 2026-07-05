#ifndef AUDIOOUT_HPP

#define AUDIOOUT_HPP

#include "main.hpp"

class AudioOut
{

protected:
    PcmSetting::AudioBuffer _buffer;

public:
    AudioOut();
    ~AudioOut();
    PcmSetting::AudioBuffer const &GetBuffer() const;
};

#endif