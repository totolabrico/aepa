#ifndef PCM_HPP

#define PCM_HPP

#include "/usr/include/alsa/asoundlib.h"
#include <iostream>
#include <string>
#include "main.hpp"

class Pcm
{
private:
    static constexpr _snd_pcm_format PCM_FORMAT = SND_PCM_FORMAT_FLOAT;
    static constexpr _snd_pcm_access PCM_ACCESS = SND_PCM_ACCESS_RW_INTERLEAVED;
    static constexpr unsigned int SOFT_RESAMPLE = 1;
    static constexpr unsigned int LATENCY = 10000;

protected:
    snd_pcm_t *_handle;
    virtual void Process() = 0;

public:
    Pcm(std::string const &device, snd_pcm_stream_t stream);
    ~Pcm();
};

#endif