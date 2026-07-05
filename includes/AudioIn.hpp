#ifndef AUDIOIN_HPP

#define AUDIOIN_HPP

#include "main.hpp"
#include "AudioOut.hpp"
#include <vector>
#include <algorithm>

class AudioIn
{

protected:
    std::vector<PcmSetting::AudioBuffer const *> _buffers;

public:
    AudioIn();
    ~AudioIn();
    void PlugIn(AudioOut const &src);
    void UnPlugIn(AudioOut const &src);
    void SumSignalsIn(PcmSetting::AudioBuffer &buffer);
};

#endif