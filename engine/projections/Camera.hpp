#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "./Projection.hpp"

struct Camera
{
    Camera(Projection projector);
    ~Camera()=default;

    Ray project(int x, int y) const;
    // Ray operator()(int x, int y) const;

public:

    /*
    Transation & Rotation
    */

    Vec3 translation;
    double pitch, yaw, roll;

private:

    /*
    Projection storage
    */

    Projection projection;

};

#endif