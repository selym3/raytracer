#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "./RayIntersection.hpp"
#include "./Ray.hpp"

#include "./Material.hpp"

struct RayIntersection;

class Shape
{

    Material m_material;

public:
    Shape(const Material& material);
    virtual ~Shape();

    virtual RayIntersection intersect(const Ray& ray) const = 0;

    const Material& material() const;    
};

#endif