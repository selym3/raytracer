#ifndef __RAY_HPP__
#define __RAY_HPP__

#include <optional>

#include "Vec3.hpp"
#include "Shape.hpp"

#include <ostream>

struct Ray
{
public:
    // Data & Constructors
    Vec3d origin, direction;

    Ray(const Vec3d& origin, const Vec3d& direction) :
        origin { origin }, direction { !direction }
    {
    }

public:

    friend std::ostream& operator<<(std::ostream& os, const Ray& r)
    {
        return os << "[ " << r.origin << ", " << r.direction << " ]";
    }

public:
    // Ray Operations

    Vec3d sample(double t) const
    {
        return origin + direction * t;
    }

    Ray fix(const Vec3d& fix_direction, double eps) const
    {
        return Ray(
            origin + fix_direction * eps,
            direction
        );
    }

    Ray reflect(const Vec3d& surface, const Vec3d& normal, double eps = 1.0) const
    {
        // TODO: add formula later
        return Ray(
            surface,
            direction - 2 * (normal % direction) * normal
        ).fix(normal, eps);
    }

};

#endif