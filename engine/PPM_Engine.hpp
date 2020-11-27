#ifndef __PPM_ENGINE_HPP__
#define __PPM_ENGINE_HPP__

#include "./Engine.hpp"

#include <cmath>
#include <iostream>
#include <fstream> 
#include <algorithm>
#include <vector>

struct PPM_Engine : public Engine 
{

    PPM_Engine(int width, int height, unsigned int toProduce=1);
    ~PPM_Engine()=default;

    bool isRunning() const override;
    void execute() override;

    // output file type
    using File = std::ofstream;

private:

    static unsigned long NUM_EXPECTED;

    unsigned int toProduce;
    std::vector<File> files;

};

#endif