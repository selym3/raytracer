# raytracer

Raytracing implementation in C++

## TODO

* Improve `Projection` (and/or `Camera`) abstraction. 
  * `Camera` would be a child of `Projection` and would take in another `Projection`
  * `Camera` would be the projection type of `Engine`. All engines would then handle how to change camera angle and the camera will rotate the rays of the projection.
* Light sources
* Refraction
* Reflection
* Abstraction for Rendering
  * `isDone()` and `execute()` class
  * `Projection` and `Shape` containers
  * Should allow for ppm outputs (runs once) and SFML windows (runs forever)
* Routine to reduce rays and interpolate
