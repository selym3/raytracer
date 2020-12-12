/**
 * Needs implementation
 * 
 * Check README.md for implementation
 */

#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <memory>

#include "./Projection.hpp"
#include "./Perspective.hpp"

struct Camera : public Projection
{
    using ProjectorType = std::unique_ptr<Projection>;

    Camera(ProjectorType realProjection);
    ~Camera()=default;

    Ray project(int x, int y) const override;

private:

    /*
    Transation & Rotation
    */

    Vec3 translation;
    // need information for 3d rotation

private:

    /*
    Projection storage
    */

    ProjectorType interalProjection;



};

#endif