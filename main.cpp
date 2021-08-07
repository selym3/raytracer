#include <iostream>

#include "gui/Engine.hpp"

int main(int argc, char** argv)
{

    Engine e(600, 600, 1);

    while (e.is_running())
    {
        e.update();
    }

    return 0;
}