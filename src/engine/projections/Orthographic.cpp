#include "../../../engine/projections/Orthographic.hpp"

Orthographic::Orthographic(int w, int h) : width{w}, height{h} {}

Ray Orthographic::operator()(int x, int y) const
{
    return Ray(
        Vec3(x - (width >> 1), y - (height >> 1), 0),
        Vec3(0, 0, -1)//.normalized()
    );
}