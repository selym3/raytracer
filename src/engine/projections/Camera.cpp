#include "../../../engine/projections/Camera.hpp"

Camera::Camera(Projection projector, Vec3 translation, double y, double p, double r) :
    projection { projector },
    translation { translation },
    yaw { y }, pitch { p }, roll { r }
{
}

Camera::Camera(Projection projection) :
    Camera { projection, Vec3(0,0,0), 0, 0, 0 }
{
}

Camera::Camera(Projection projection, Vec3 translation) :
    Camera(projection, translation, 0.0, 0.0, 0.0)
{
}

Camera::Camera(Projection projection, double y, double p, double r) :
    Camera(projection, Vec3(0,0,0), y, p, r) 
{
}

Ray Camera::project(int x, int y) const
{
    Ray out = this->projection(x, y);

    // first rotate
    out.setDestination(out.destination().rotate(
        yaw,
        pitch,
        roll,
        out.origin()
    ));
    
    // then translate
    out.setOrigin(out.origin() + translation);
    out.setDestination(out.destination());

    return out;
}