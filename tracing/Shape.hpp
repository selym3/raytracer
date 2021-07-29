#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <functional>
#include "Ray.hpp"

struct Shape
{
public:
    // Type Definitions 

    using Number = double;
    using Result = std::optional<Ray<Number>::Collision>;

    using Collider = std::function<Result(const Ray<Number>&)>;

public:
    // Data & Constructors

    Collider collider;

    Shape(const Collider& collider) : 
        collider { collider }
    {
    }

public:
    // Ray Collision

    // Result collision(const )


};

#endif