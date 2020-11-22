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

// protected:
public:

    // this is used in RayIntersection.cpp for calculateNormal function
    // friend class RayIntersection;

    /*
    I have to make sure that this works, but instead of calculate normal, 
    there can be an abstract getCenter() method and then the normal would be
    (phit - getCenter()).normalized()
    */


    // assume vector is intersection point
    // this function will return a normailzed normal
    virtual Vec3 calculateNormal(const Vec3& in) const = 0;
    Vec3 calculateNormal(const Ray& ray, double t) const;

    
};

#endif