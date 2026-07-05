#include "../includes/Adc.hpp"

Adc::Adc(std::string const &device) : Pcm(device, SND_PCM_STREAM_CAPTURE)
{
}

void Adc::Process()
{
    int rc;

    rc = snd_pcm_readi(Pcm::_handle, AudioOut::_buffer.data(), PcmSetting::FRAME_LEN);
    if (rc < 0)
        std::cout << "Read Error: " << snd_strerror(rc) << std::endl;
    if (rc == -EPIPE)
        snd_pcm_prepare(Pcm::_handle);
}