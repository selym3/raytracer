#include "../../../engine/projections/Perspective.hpp"
#include <cmath>

Perspective::Perspective(double fov, int width, int height) : 
    inverseWidth { 1.0 / (double) width },
    inverseHeight { 1.0 / (double) height },
    aspectRatio { width / (double) height },
    angle { std::tan( (fov * 0.5) * (M_PI / 180.0) ) }
{
}

Ray Perspective::project(int x, int y) const
{
    return Ray(
        Vec3(0),
        Vec3(
            (2 * (x + 0.5) * inverseWidth - 1) * angle * aspectRatio,
            (1 - 2 * (y + 0.5) * inverseHeight) * angle,
            -1
        ).normalized()
    );
}
