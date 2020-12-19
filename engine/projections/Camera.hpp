#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "./Projection.hpp"

struct Camera
{
    Camera(Projection projector);
    Camera(Projection projector, Vec3 translation);
    Camera(Projection projector, double y, double p, double r);
    Camera(Projection projector, Vec3 translation, double y, double p, double r);
    ~Camera()=default;

    Ray project(int x, int y) const;

public:

    /*
    Transation & Rotation
    */

    Vec3 translation;
    double yaw, pitch, roll; 
    
private:

    /*
    Projection storage
    */

    Projection projection;

};

#endif