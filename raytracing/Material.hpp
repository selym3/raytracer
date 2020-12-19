#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "../math/Vec3.hpp"

using Color = Vec3;

struct Material 
{
    Color ambient;
    Color diffuse;
    Color specular;
    double shininess;

    Material(Color ambient, Color diffuse, Color specular = Color(1,1,1), double shininess = 100);
    Material(Color estimate);
};

#endif