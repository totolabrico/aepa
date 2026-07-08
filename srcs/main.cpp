#include "../includes/main.hpp"
#include "../includes/Adc.hpp"
#include "../includes/Dac.hpp"
#include "../includes/Reverb.hpp"

void print_header()
{
    std::ifstream logo("logo.txt");
    std::string line;
    std::cout << "\033[31m";
    while (getline(logo, line))
        std::cout << line << std::endl;
    std::cout << std::endl;
    std::cout << "\033[34m";
    std::cout << "DURATION (O | L)\t\tLAYER SIZE (P | M)" << std::endl;
    std::cout << "\033[0m" << std::endl;
}

int run(t_env *env, Adc &adc, Dac &dac, Reverb &reverb)
{
    while (env->running)
    {
        adc.Process();
        reverb.Process();
        dac.Process();
    }
    return 0;
}

void init_env(t_env *env, Reverb *reverb)
{
    env->reverb = reverb;
    env->running = true;
}

int main(int argc, char **argv)
{
    print_header();
    std::string in = "default";
    std::string out = "default";
    if (argc > 1)
        in = argv[1];
    if (argc > 2)
        out = argv[2];
    Adc adc(in);
    Dac dac(out);
    Reverb reverb;
    t_env env;
    init_env(&env, &reverb);
    reverb.PlugIn(adc);
    dac.PlugIn(adc);
    dac.PlugIn(reverb);
    pthread_t cmd_thread;
    if (pthread_create(&cmd_thread, NULL, &input_routine, reinterpret_cast<void *>(&env)) != 0)
        exit(1);
    return run(&env, adc, dac, reverb);
}