#ifndef VEC
#include "vector.h"
#endif

#ifndef OBJECTS
#include "objects.h"
#endif

#ifndef CAMERA
#include "camera.h"
#endif

#include <vector>
#include <fstream> // For std::ofstream

bool checkCollisions(Ray r,
                     std::vector<Object *> all_objects,
                     double &t_hit,
                     Object *&hit_object);
// double castShadowRay(Ray const &normal_ray,
Vec3 castShadowRay(Ray const &normal_ray,
                   Vec3 const &color_surface,
                   std::vector<Object *> all_objects,
                   Sphere const &light);
Vec3 trace(Ray r,
           std::vector<Object *> all_objects,
           Sphere light);
Vec3 compute_pixel_color(Ray primaryRay,
                         std::vector<Object *> all_objects,
                         Sphere light);
void print_image(const std::vector<std::vector<Vec3>> &image, int WIDTH, int HEIGHT);
double clamp(double low, double high, double val);
void write_image(const std::vector<std::vector<Vec3>> &image,
                 int WIDTH, int HEIGHT);
int main();