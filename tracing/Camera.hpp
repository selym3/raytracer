#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <cstdlib>
#include <cmath>
#include <utility>

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera
{
public:
    std::size_t width, height;
    double fov;

public:
    Camera(std::size_t width, std::size_t height, double fov = 90.0) :
        width{width}, height{height}, fov{fov}
    {
    }

    template <typename Pixel>
    Ray get_ray(const Pixel& pixel) const
    {
        // normalize the pixel into normalized space
        // ranges between [0,1] in each axis (ignoring + 0.5)
        double normalized_x = (pixel.x + 0.5) / width;
        double normalized_y = (pixel.y + 0.5) / height;

        // Puts pixels in the range 
        // [-1,1] for x and [1, -1] for y
        double screen_x = normalized_x * 2 - 1;
        double screen_y = 1 - normalized_y * 2;

        // Account for non-square screen sizes and 
        // the camera fov
        auto h = std::tan((fov/2) * 3.14159 / 180.0);
        auto aspect_ratio = width / (double)height;
        
        screen_x *= aspect_ratio * h;
        screen_y *= h;

        // Create final ray that looks out to +1 z
        return Ray(
            Vec3d(0),
            Vec3d(screen_x, screen_y, +1)
        );
    }
};

#endif