#ifndef VEC
#include "vector.h"
#endif

#ifndef COLORS
#include "colors.h"
#endif

#ifndef OBJECTS
#include "objects.h"
#endif

#ifndef CAMERA
#include "camera.h"
#endif

#include "progress_bar.h"

#include <vector>
#include <ctime>
#include <fstream> // For std::ofstream

struct Options
{
    int MAX_DEPTH;
    int WIDTH;
    int HEIGHT;
    int n_ray_shadow;
    double PIXEL_SIZE;
    bool random_alliasing;
    int n_ray_per_pixel;
};

bool checkCollisions(Ray const &r,
                     std::vector<Object *> const &all_objects,
                     double &t_hit,
                     Object *&hit_object);
double rand01();

std::vector<Ray> sampleLightPoints(Ray const &rayToLight,
                                   Sphere const &light,
                                   int n_pts);

Vec3 traceShadowRay(Ray const &rayToLight,
                    Ray const &normal_ray,
                    Vec3 const &color_surface,
                    std::vector<Object *> const &all_objects,
                    Sphere const &light,
                    Options const &option);

Vec3 castShadowRay(Ray const &normal_ray,
                   Vec3 const &color_surface,
                   std::vector<Object *> const &all_objects,
                   Sphere const &light);

Vec3 trace(Ray const &r,
           std::vector<Object *> const &all_objects,
           Sphere const &light,
           Options const &option);

Vec3 compute_pixel_color(Ray const &primaryRay,
                         std::vector<Object *> const &all_objects,
                         Sphere const &light,
                         Options const &option);

double clamp(double low, double high, double val);
void print_image(const std::vector<std::vector<Vec3>> &image, int WIDTH, int HEIGHT);
void write_image(const std::vector<std::vector<Vec3>> &image,
                 int WIDTH, int HEIGHT);
int main();