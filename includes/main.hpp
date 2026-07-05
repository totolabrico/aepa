#ifndef MAIN_HPP

#define MAIN_HPP

#include "/usr/include/alsa/asoundlib.h"
#include <array>

namespace PcmSetting
{
    constexpr unsigned int CHANNELS = 1;
    constexpr unsigned int FRAME_RATE = 44100;
    constexpr snd_pcm_uframes_t FRAME_LEN = 32;
    constexpr size_t BUFFER_LEN = FRAME_LEN * CHANNELS;
    typedef std::array<float, PcmSetting::BUFFER_LEN> AudioBuffer;
};

#endif