#include "../../../engine/projections/Camera.hpp"

Camera::Camera(Projection projection) :
    projection { projection }
{
}

Ray Camera::project(int x, int y) const
{
    return this->projection(x, y);
}