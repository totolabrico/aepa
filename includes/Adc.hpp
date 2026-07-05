#ifndef ADC_HPP

#define ADC_HPP

#include "Pcm.hpp"
#include "AudioOut.hpp"

class Adc : public Pcm, public AudioOut
{
public:
    Adc(std::string const &device);
    void Process() override;
};

#endif