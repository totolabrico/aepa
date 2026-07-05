#ifndef REVERB_HPP

#define REVERB_HPP

#include "AudioIn.hpp"
#include "AudioOut.hpp"
#include <pthread.h>

class Reverb : public AudioIn, public AudioOut
{

private:
    float _duration; // second
    size_t _layer_size;
    size_t _buffer_size;
    std::vector<std::vector<float>> _buffers;
    size_t _head;
    size_t _head_layer;
    std::vector<float> _layer_coef;
    pthread_mutex_t _mutex;

public:
    Reverb();
    ~Reverb();
    void SetDuration(float value);
    void SetLayerSize(size_t value);
    void Process();
};

#endif