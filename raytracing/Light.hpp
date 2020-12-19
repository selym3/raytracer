#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include "../math/Vec3.hpp"
#include "./Material.hpp"

struct Light 
{
    Vec3 position;
    
    // use material but ignore shininess
    Material material;

    Light(Vec3 position, Color ambient, Color diffuse, Color specular);
    Light(Vec3 position);
    
};

#endif