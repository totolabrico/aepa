#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "../includes/main.hpp"
#include "../includes/Reverb.hpp"

char read_key()
{
    char c;
    termios old, current;

    tcgetattr(STDIN_FILENO, &old);
    current = old;
    current.c_lflag &= ~(ICANON | ECHO); // mode non canonique + pas d'affichage
    tcsetattr(STDIN_FILENO, TCSANOW, &current);
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return c;
}

void *input_routine(void *addr)
{
    t_env *env = reinterpret_cast<t_env *>(addr);
    Reverb *reverb = env->reverb;
    std::string cmd;
    float value;

    while (true)
    {
        reverb->print();
        char key = read_key();
        if (key == 'o')
            reverb->IncDuration(0.1);
        else if (key == 'l')
            reverb->IncDuration(-0.1);
        else if (key == 'p')
            reverb->IncLayerSize(1);
        else if (key == 'm')
            reverb->IncLayerSize(-1);
        else if (key == 'q')
            break;
    }
    env->running = false;
    return NULL;
}