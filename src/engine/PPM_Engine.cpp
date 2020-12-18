#include "../../engine/PPM_Engine.hpp"

#include <string>

unsigned long PPM_Engine::NUM_EXPECTED = 0;

static std::vector<PPM_Engine::File> getOutputFiles(
    unsigned int toProduce,
    unsigned int id
) 
{
    std::vector<PPM_Engine::File> out;

    auto base = "./untitled-";
    auto extension = ".ppm";

    for (;toProduce>0;--toProduce)
        out.push_back(
            std::ofstream(
                base + std::to_string(toProduce+id) + extension,
                std::ios::out | std::ios::binary
            )
        );

    return out;
}

PPM_Engine::PPM_Engine(int w, int h, Camera camera, unsigned int toProduce) : 
    Engine(
        w,
        h, 
        Engine::Light(w>>1, 300, -5), 
        camera
    ),
    toProduce { toProduce },
    files { getOutputFiles(toProduce, PPM_Engine::NUM_EXPECTED) }
{
    PPM_Engine::NUM_EXPECTED+=toProduce;
}

bool PPM_Engine::isRunning() const
{
    return (toProduce > 0);
}

void PPM_Engine::execute()
{

    --toProduce;

    files[toProduce] << "P6\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
        
            auto primaryRay = this->camera.project(x, y);

            auto color = this->trace(primaryRay);

            files[toProduce] << 
                (unsigned char)(std::min(1.0, color.x) * 255) <<
                (unsigned char)(std::min(1.0, color.y) * 255) <<
                (unsigned char)(std::min(1.0, color.z) * 255);

        }
    }
    
    files[toProduce].close();
}