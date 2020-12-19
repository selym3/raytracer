#include "../../raytracing/Light.hpp"

Light::Light(Vec3 position, Color ambient, Color diffuse, Color specular) :
    position { position },
    material { ambient, diffuse, specular, 0 }
{
}

Light::Light(Vec3 position) :
    Light(
        position,
        Color(1,1,1),
        Color(1,1,1),
        Color(1,1,1)
    )
{
}