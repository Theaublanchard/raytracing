#ifndef VEC
#include "vector.h"
#endif

#ifndef OBJECTS
#include "objects.h"
#endif

#include <vector>
class Camera
{
public:
    Vec3 pos_center, focal_point;
    int height, width;
    float pixel_size = 0.1;
    Vec3 top_left_corner, right_dir, down_dir;

    Camera(){};
    ~Camera() = default;
    Camera(Vec3 pos, Vec3 focal, int width, int height);
    // {pos_center(pos), focal_point(focal), pixel_size(0.1)};
    Camera(Vec3 pos, Vec3 focal, float px_size, int width, int height);
    // {pos_center(pos), focal_point(focal), pixel_size(px_size)};

    Ray shoot_ray(int i, int j) const;
    std::vector<Ray *> shoot_rays(int i, int j) const;
    void compute_corners();
};

std::ostream &operator<<(std::ostream &os, const Camera o);
int printf(Camera const o);