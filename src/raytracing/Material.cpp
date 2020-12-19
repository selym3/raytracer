#include "../../raytracing/Material.hpp"

Material::Material(Color ambient, Color diffuse, Color specular, double shininess) :
    ambient { ambient },
    diffuse { diffuse },
    specular { specular },
    shininess { shininess }
{
}

Material::Material(Color estimate) :
    Material(estimate * 0.1, estimate * 0.65)
{
}