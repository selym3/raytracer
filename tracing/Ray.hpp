#ifndef __RAY_HPP__
#define __RAY_HPP__

#include <optional>

#include "Vec3.hpp"
#include "Shape.hpp"

template <typename T>
struct Ray
{
public:
    // Data & Constructors

    Vec3<T> origin, direction;

    Ray(const Vec3<T>& origin, const Vec3<T>& direction) :
        origin { origin }, direction { direction }
    {
    }

public:
    // Ray Operations

    Vec3<T> operator()(const T& t) const
    {
        return origin + direction * t;
    }

    // Ray reflected() const
    // {
    // }

public:
    // Ray Collision

    struct Collision
    {
        Vec3<T> where, normal;
    };

};

#endif