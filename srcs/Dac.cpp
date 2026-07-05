#include "../includes/Dac.hpp"

Dac::Dac(std::string const &device) : Pcm(device, SND_PCM_STREAM_PLAYBACK)
{
}

void Dac::Process()
{
    AudioIn::SumSignalsIn(_buffer);
    int rc;
    rc = snd_pcm_writei(Pcm::_handle, _buffer.data(), PcmSetting::FRAME_LEN);
    if (rc < 0)
        std::cout << "Write Error: " << snd_strerror(rc) << std::endl;
    if (rc == -EPIPE)
        snd_pcm_prepare(Pcm::_handle);
}