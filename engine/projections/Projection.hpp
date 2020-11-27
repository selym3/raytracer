#ifndef __PROJECTION_HPP__
#define __PROJECTION_HPP__

#include "../../raytracing/Ray.hpp"

struct Projection {
    virtual ~Projection()=default;

    // The ray direction should be normalized 
    virtual Ray project(int x, int y) const = 0;
};

#endif