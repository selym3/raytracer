#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "./RayIntersection.hpp"
#include "./Ray.hpp"

using Color = Vec3;

class RayIntersection;

class Shape
{

    Color m_color;

public:
    Shape(const Color& color);
    virtual ~Shape();

    virtual RayIntersection intersect(const Ray& ray) const = 0;

    const Vec3& color() const;    
};

#endif