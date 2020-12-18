#ifndef __PROJECTION_HPP__
#define __PROJECTION_HPP__

#include "../../raytracing/Ray.hpp"

#include <functional>

using Projection = std::function<Ray(int, int)>;

#endif