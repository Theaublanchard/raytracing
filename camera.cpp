#include "camera.h"

Camera::Camera(Vec3 pos, Vec3 focal, int width_, int height_)
{
    pos_center = pos;
    focal_point = focal;
    pixel_size = 0.1;
    width = width_;
    height = height_;

    this->compute_corners();
}

void Camera::compute_corners()
{
    /* reculer de la moitié de l'image, ie
    width * pixel_size / 2
    puis descendre pareil ie
    height * pixel /2
    le tout par rapport au plan défine par
    le vecteur normal donnée par center - focal
    */

    float real_width = width * pixel_size;
    float real_height = height * pixel_size;

    Vec3 normal_vec = pos_center - focal_point;
    normal_vec = normal_vec.normalize();

    Vec3 z_axis = Vec3(0, 0, 1);

    Vec3 first_basis_vec = cross_product(normal_vec, z_axis);
    Vec3 second_basis_vec = cross_product(normal_vec, first_basis_vec);
    first_basis_vec = first_basis_vec.normalize();
    second_basis_vec = second_basis_vec.normalize();

    Vec3 width_vector = first_basis_vec * real_width / 2;
    Vec3 height_vector = second_basis_vec * real_height / 2;

    top_left_corner = pos_center - width_vector - height_vector;
    right_dir = first_basis_vec;
    down_dir = second_basis_vec;
};

Camera::Camera(Vec3 pos, Vec3 focal, float px_size, int width_, int height_)
{
    pos_center = pos;
    focal_point = focal;
    pixel_size = px_size;
    width = width_;
    height = height_;
    this->compute_corners();
}

Ray Camera::shoot_ray(int i, int j) const
{

    Vec3 r_pos = top_left_corner + j * pixel_size * right_dir + i * pixel_size * down_dir;
    Vec3 r_dir = r_pos - focal_point;
    return Ray(r_pos, r_dir, Vec3(1));
}

std::vector<Ray *> Camera::shoot_rays(int i, int j) const
{
    std::vector<Ray *> res;
    Vec3 r_pos, r_dir;
    r_pos = top_left_corner + (j + 0.5) * pixel_size * right_dir + i * pixel_size * down_dir;
    r_dir = r_pos - focal_point;
    res.push_back(new Ray(r_pos, r_dir, Vec3(1)));

    r_pos = top_left_corner + j * pixel_size * right_dir + i * pixel_size * down_dir;
    r_dir = r_pos - focal_point;
    res.push_back(new Ray(r_pos, r_dir, Vec3(1)));

    r_pos = top_left_corner + (j + 0.5) * pixel_size * right_dir + (i + 0.5) * pixel_size * down_dir;
    r_dir = r_pos - focal_point;
    res.push_back(new Ray(r_pos, r_dir, Vec3(1)));

    r_pos = top_left_corner + j * pixel_size * right_dir + (i + 0.5) * pixel_size * down_dir;
    r_dir = r_pos - focal_point;
    res.push_back(new Ray(r_pos, r_dir, Vec3(1)));

    return res;
}

double rand_uni()
{
    return ((double)rand() / (RAND_MAX));
}

std::vector<Ray *> Camera::shoot_random_rays(int i, int j, int n_rays) const
{
    std::vector<Ray *> res;
    Vec3 r_pos, r_dir;
    for (int k = 0; k < n_rays; k++)
    {
        double offset_x = rand_uni();
        double offset_y = rand_uni();
        r_pos = top_left_corner + (j + offset_x) * pixel_size * right_dir + (i + offset_y) * pixel_size * down_dir;
        r_dir = r_pos - focal_point;
        res.push_back(new Ray(r_pos, r_dir, Vec3(1)));
    }
    return res;
}

std::ostream &operator<<(std::ostream &os, const Camera o)
{
    os << "Camera at position " << o.pos_center << " with focal at " << o.focal_point << " with a pixel size of " << o.pixel_size << ", width of "
       << o.width << " and a height of " << o.height;
    return os;
}

int printf(const Camera o)
{
    std::cout << o;
    return 0;
}