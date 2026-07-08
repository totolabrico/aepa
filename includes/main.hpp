#ifndef MAIN_HPP

#define MAIN_HPP

#include "/usr/include/alsa/asoundlib.h"
#include <array>
#include <iostream>
#include <fstream>
#include <pthread.h>

namespace PcmSetting
{
    constexpr unsigned int CHANNELS = 1;
    constexpr unsigned int FRAME_RATE = 44100;
    constexpr snd_pcm_uframes_t FRAME_LEN = 128;
    constexpr size_t BUFFER_LEN = FRAME_LEN * CHANNELS;
    typedef std::array<float, PcmSetting::BUFFER_LEN> AudioBuffer;
};

class Reverb;

typedef struct s_env
{
    Reverb *reverb;
    bool running;
} t_env;

void *input_routine(void *addr);

#endif