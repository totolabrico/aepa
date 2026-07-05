#include "../includes/Adc.hpp"
#include "../includes/Dac.hpp"
#include "../includes/Reverb.hpp"
#include <pthread.h>

void *input_routine(void *addr)
{
    Reverb *reverb = reinterpret_cast<Reverb *>(addr);
    std::string cmd;
    float value;
    while (1)
    {
        if (getline(std::cin, cmd).fail())
            break;
        std::cout << "cmd: " << cmd << std::endl;
        if (cmd.size() > 4 && cmd.find("rev") != std::string::npos)
        {
            cmd = cmd.substr(4, cmd.size());
            try
            {
                value = std::stof(cmd);
            }
            catch (...)
            {
                continue;
            }
            std::cout << "reverb cmd: " << value << std::endl;
            reverb->SetDuration(value);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    std::string in = "default";
    std::string out = "default";
    if (argc > 1)
        in = argv[1];
    if (argc > 2)
        out = argv[2];
    Adc adc(in);
    Dac dac(out);
    Reverb reverb;
    reverb.PlugIn(adc);
    dac.PlugIn(adc);
    dac.PlugIn(reverb);
    pthread_t cmd_thread;
    if (pthread_create(&cmd_thread, NULL, &input_routine, reinterpret_cast<void *>(&reverb)))
        exit(1);
    while (1)
    {
        adc.Process();
        reverb.Process();
        dac.Process();
    }
    return 0;
}