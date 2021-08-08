#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <vector>

#include "Vec3.hpp"

struct Light
{
    Vec3d position;
    Vec3d color;

    // Light(const Vec3d& position, cost)
};

using LightSet = std::vector<Light>;

#endif