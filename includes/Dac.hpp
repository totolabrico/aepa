#ifndef DAC_HPP

#define DAC_HPP

#include "Pcm.hpp"
#include "AudioIn.hpp"

class Dac : public Pcm, public AudioIn
{
protected:
    PcmSetting::AudioBuffer _buffer;

public:
    Dac(std::string const &device);
    void Process() override;
};

#endif