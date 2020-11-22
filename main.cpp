#include "./math/Vec3.hpp"
#include "./raytracing/Ray.hpp"
#include "./raytracing/Sphere.hpp"
#include <cmath>
#include <iostream>
#include <fstream> 
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const Vec3& rhs) 
{
    return os << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " ]";
}

// #include <SFML/Graphics.hpp>

// void CenterWindow(sf::RenderWindow& window)
// {
//     auto desktop = sf::VideoMode::getDesktopMode();

//     sf::Vector2u desktop_size{
//         desktop.width, 
//         desktop.height
//     };

//     window.setPosition(
//         (sf::Vector2i) 
//         ((desktop_size -  window.getSize()) / 2u)
//     );

// }

#include <vector>
#include <array>

Color trace(
    const std::vector<Sphere>& spheres, 
    const Ray& ray, 
    const Vec3& light
)
{
    RayIntersection finalCollision;
    const Sphere * sphereHit = nullptr;

    for (const auto& sphere : spheres) {

        auto collision = sphere.intersect(ray);

        // std::cout << "Checking collision\n";

        if (collision.intersected) {
            // std::cout << "Intersected!\n";

            // if nothing has been hit yet, or something 
            // has been hit and it's closer than what's already found
            if (!sphereHit || (sphereHit && collision.t0 < finalCollision.t0)) {
                // std::cout << "RUNNING BITCH" << "\n";
                finalCollision = collision;
                sphereHit = &sphere;
            }
        }

    }

    // return background color
    if (!sphereHit) { 
        // std::cout << "leavingearly\n"; 
        return Color(2); 
    }
    
    Ray shadowRay(finalCollision.hit, light - finalCollision.hit);
    double shadeValue = 1;

    for (const auto& sphere : spheres) {
        if (&sphere != sphereHit) {
            if (sphere.intersect(shadowRay).intersected) {
                shadeValue = 0;
                break; // don't compute any cool shading yet
            }
        }
    }

    return sphereHit->color();// * shadeValue;
}

struct Projection {
    virtual ~Projection()=default;
    virtual Ray projectRay(int x, int y) const = 0;
};

struct Orthographic : public Projection {
    int width, height;

    Orthographic(int width, int height) :
        width { width },
        height { height }
    {
    }

    Ray projectRay(int x, int y) const 
    {
        return Ray(
            Vec3(x - (width>>1), y - (height>>1), 0), 
            Vec3(0,0,-1).normalized()
        );
    }
};

struct Perspective : public Projection {

    double fov;
    double iWidth, iHeight;
    double ratio;
    double angle;

    Perspective(double fov, int width, int height) : 
        fov { fov }, 
        iWidth { 1.0 / (double)width }, 
        iHeight { 1.0 / (double)height }, 
        ratio { width / (double) height },
        angle { std::tan(3.14159 * 0.5 * fov / 180.0) }
    {
        std::cout << fov << " " 
            << iWidth << " " 
            << iHeight << " " 
            << iWidth << " " 
            << ratio << " " 
            << angle << "\n";
    }

    Ray projectRay(int x, int y) const 
    {
        return Ray(
            Vec3(0),
            Vec3(
                (2 * ((x + 0.5) * iWidth) - 1) * angle * ratio,
                (1 - 2 * ((y + 0.5) * iHeight)) * angle,
                -1
            ).normalized()
        );
    }
    
};

// Ray ortrographic(int x, int y) {
//     return Ray(Vec3(x,y,0), Vec3(0, 0, -1).normalized());
// }

// double fov, double aspectRatio
// Ray projection()

int main(void)
{
    // sf::RenderWindow window(
    //     sf::VideoMode(600, 600),
    //     "Raytracer",
    //     sf::Style::None
    // );
    // CenterWindow(window);

    constexpr int WIDTH  = 600;
    constexpr int HEIGHT = 600;

    std::vector<Sphere> spheres({
        // WITH MERCATOR:
        Sphere(Vec3( 0, 0, -500), 4, Color(1, 0, 0)),
        Sphere(Vec3( 4, 0, -5), 4, Color(0, 1, 0)),
        Sphere(Vec3( 0, 4, -50), 4, Color(0, 0, 1))
    });

    const Projection& eye = Orthographic(WIDTH, HEIGHT);
    // const Projection& eye = Perspective(45.0, WIDTH, HEIGHT);
    // static std::array<Color, WIDTH * HEIGHT> pixels;
    std::vector<Color> pixels;
    pixels.resize(WIDTH * HEIGHT);
    int ptr = 0;
    const Vec3 light( WIDTH>>1, 300, -30);

    for (int i = 0; i < WIDTH; ++i) {

        for (int j = 0; j < HEIGHT; ++j, ++ptr) {
            
            // projection
            auto primary = eye.projectRay(i, j);
        
            // get the pixel
            pixels[ptr] = trace(spheres, primary, light);

        }

    }


    std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary );
    ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n"; 
    for (const auto& pixel : pixels) {
        // std::cout << pixel << "\n";
        ofs << 
        (unsigned char)(std::min(1.0, pixel.x) * 255) <<
        (unsigned char)(std::min(1.0, pixel.y) * 255) <<
        (unsigned char)(std::min(1.0, pixel.z) * 255);
    }
    ofs.close();

    std::cout <<  "I am done " << "\n";

    return 0;
}