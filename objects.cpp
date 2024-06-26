#include "objects.h"
#include <iostream>

// =======================================================================
// RAY

Ray::Ray(Vec3 const &pos_, Vec3 const &dir_)
{
    pos = pos_;
    dir = dir_.normalize();
    color = Vec3(0);
    invdir = computeInvDir();
};

Ray::Ray(Vec3 const &pos_, Vec3 const &dir_, Vec3 const &color_)
{
    pos = pos_;
    dir = dir_.normalize();
    color = color_;
    invdir = computeInvDir();
};

Ray::Ray(Vec3 const &pos_, Vec3 const &dir_, Vec3 const &color_, int depth_)
{
    pos = pos_;
    dir = dir_.normalize();
    color = color_;
    invdir = computeInvDir();
    depth = depth_;
}

Vec3 Ray::computeInvDir()
{
    // std::cerr << "Calling : computeinvdir.Modify this function to accomodate 0.\n";
    return 1. / dir;
};

std::ostream &operator<<(std::ostream &os, const Ray o)
{
    os << "Ray at " << o.pos << " of direction " << o.dir << " and of color " << o.color << std::endl;
    return os;
}
int printf(Ray r)
{
    std::cout << r << std::endl;
    return 0;
}

void Ray::setDir(Vec3 const &p)
{
    this->dir = p.normalize();
    this->invdir = computeInvDir();
}

// =======================================================================
// OBJECT

Object::~Object(){};

std::ostream &operator<<(std::ostream &os, const Object &obj)
{
    obj.print(os);
    return os;
}

// =======================================================================
// SPHERE

Sphere::Sphere(Vec3 pos_, Vec3 color_, double s_)
    : Object(pos_, s_)
{
    color = color_;
};

std::ostream &operator<<(std::ostream &os, const Sphere o)
{
    std::cout << "Sphere at " << o.pos << ", of scale " << o.s << " and of color " << o.color;
    return os;
}
void Sphere::print(std::ostream &os) const
{
    os << *this;
}

double Sphere::signedDst(Vec3 const &p) const
{
    return (p - pos).lensqr() - s * s;
}

bool findroots(double a, double b, double c, double &t1, double &t2)
{
    double discr = b * b - 4 * a * c;
    if (discr < 0)
    {
        return false;
    }
    if (discr == 0)
    {
        t1 = t2 = -b / (2 * a);
        return true;
    }
    double discr_sqrt = sqrt(discr);
    double inv_denum = 1 / (2 * a);
    t1 = (-b - discr_sqrt) * inv_denum;
    t2 = (-b + discr_sqrt) * inv_denum;
    return true;
}

bool Sphere::intersect(Ray r) const
{
    Vec3 deltaVec = r.pos - pos;
    double b = -2 * deltaVec.dot(r.dir);
    double c = deltaVec.lensqr() - s * s;

    double t1, t2;
    return findroots(1, b, c, t1, t2);
}

bool Sphere::intersect(Ray r, double &t_hit) const
{
    Vec3 deltaVec = r.pos - pos;
    double b = 2 * deltaVec.dot(r.dir);
    double c = deltaVec.lensqr() - s * s;

    double t1, t2;
    if (!findroots(1, b, c, t1, t2))
    {
        return false;
    }

    if (t1 < 0 && t2 < 0)
    {
        // the sphere is behind
        return false;
    }
    if (t1 < 0 && t2 >= 0)
    {
        // we are inside
        t_hit = t2;
    }
    else
    {
        // Intersection ahead at the smallest t value.
        t_hit = t1;
    }

    return true;
}

bool Sphere::intersect(Ray r, Vec3 &hitPoint) const
{
    double t_hit;
    if (!intersect(r, t_hit))
    {
        return false;
    }
    hitPoint = r.pos + t_hit * r.dir;
    return true;
}

Vec3 Sphere::computeNormalDir(Vec3 const &hitPoint) const
{
    return (hitPoint - pos).normalize();
}
Vec3 Sphere::getColorAt(Vec3 const &pos) const
{
    return color;
}
int printf(Sphere o)
{
    std::cout << o << std::endl;
    return 0;
}

// =======================================================================
// CHECKBOARD

bool CheckBoard::intersect(Ray r) const
{
    if (r.dir.z >= 0)
    {
        return false;
    }
    return true;
}
bool CheckBoard::intersect(Ray r, double &t_hit) const
{
    if (r.dir.z >= 0)
    {
        return false;
    }
    t_hit = -r.pos.z / r.dir.z;
    return true;
}

bool CheckBoard::intersect(Ray r, Vec3 &hitPoint) const
{
    if (r.dir.z >= 0)
    {
        return false;
    }

    double t_hit = -r.pos.z / r.dir.z;
    hitPoint = r.pos + t_hit * r.dir;
    hitPoint.z = 0;
    return true;
}

Vec3 CheckBoard::computeNormalDir(Vec3 const &hitPoint) const
{
    return Vec3(0, 0, 1);
}

inline int positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

Vec3 CheckBoard::getColorAt(Vec3 const &pos) const
{
    int tile_x = int(pos.x);
    int tile_y = int(pos.y);

    tile_x = positive_modulo(tile_x, 2);
    tile_y = positive_modulo(tile_y, 2);

    Vec3 return_color = (tile_x == tile_y) ? DARK : WHITE;

    return return_color;
}

std::ostream &operator<<(std::ostream &os, const CheckBoard o)
{
    os << "Checkboard";
    return os;
}
void CheckBoard::print(std::ostream &os) const
{
    os << *this;
}
int printf(CheckBoard o)
{
    std::cout << o << std::endl;
    return 0;
}

// =======================================================================
// CUBE
Cube::Cube(Vec3 pos_, Vec3 color_, double s_)
{
    pos = pos_;
    color = color_;
    s = s_;
}

bool Cube::intersect(Ray r, double &t_hit) const
{
    std::cout << "intersect not done";

    return false;
}
bool Cube::intersect(Ray r) const
{
    double t_hit;
    return intersect(r, t_hit);
}
bool Cube::intersect(Ray r, Vec3 &hitPoint) const
{

    double t_hit = INFINITY;
    bool hit = intersect(r, t_hit);
    if (hit)
    {
        hitPoint = r.pos + t_hit * r.dir;
    }
    return hit;
}

int Cube::getClosestFace(Vec3 const &point) const
{
    std::cout << "getClosestFace not done";
    return 0;
}
Vec3 Cube::computeNormalDir(Vec3 const &hitPoint) const
{

    Vec3 normal_dir;
    switch (getClosestFace(hitPoint))
    {
    case 0: // top
        normal_dir = Vec3(0, 0, 1);
        break;

    case 1: // bottom
        normal_dir = Vec3(0, 0, -1);
        break;

    case 2: // left
        normal_dir = Vec3(-1, 0, 0);
        break;

    case 3: // right
        normal_dir = Vec3(1, 0, 0);
        break;

    case 4: // front
        normal_dir = Vec3(0, -1, 0);
        break;

    case 5: // back
        normal_dir = Vec3(0, 1, 0);
        break;

    default:
        break;
    }
    return normal_dir;
}
Vec3 Cube::getColorAt(Vec3 const &pos) const
{
    return color;
}

void Cube::print(std::ostream &os) const
{
    os << *this;
}
std::ostream &operator<<(std::ostream &os, const Cube o)
{
    std::cout << "Cube at " << o.pos << ", of scale " << o.s << " and of color " << o.color;
    return os;
}
int printf(Cube o)
{
    std::cout << o << std::endl;
    return 0;
}
// =======================================================================
// MISC
Ray computeReflectedRay(Ray const &normalRay, Ray const &incommingRay)
{
    double dot = normalRay.dir.dot(incommingRay.dir);
    Vec3 dirReflec = incommingRay.dir - 2 * dot * normalRay.dir;
    Ray res = Ray(normalRay.pos, dirReflec, normalRay.color, incommingRay.depth + 1);
    return res;
}

Ray computeReflectedRay(Ray const &normalRay, Ray const &incommingRay, double const opacity)
{
    double dot = normalRay.dir.dot(incommingRay.dir);
    Vec3 dirReflec = incommingRay.dir - 2 * dot * normalRay.dir;
    Vec3 new_color = (1 - opacity) * incommingRay.color + opacity * normalRay.color; // old_color + surface_color
    Ray res = Ray(normalRay.pos, dirReflec, new_color, incommingRay.depth + 1);
    return res;
}

int main_objects()
// int main()
{
    const Vec3 dir = Vec3(1, 0, 0);
    Ray myRay = Ray(Vec3(0), Vec3(1, 0, 0));

    const Vec3 pos = Vec3(2, 0, 0);
    Sphere mySphere = Sphere(pos, Vec3(0), 1.);

    printf(myRay);
    printf(mySphere);

    Vec3 hitPoint;
    Ray normalRay;

    // mySphere.print();
    // myRay.print();
    double t_hit;
    bool hit = mySphere.intersect(myRay, t_hit);
    if (hit)
    {
        std::cout << "Hit ! At : ";
        printf(hitPoint);
    }
    else
    {
        std::cout << "No hit.";
    }

    // double incr = 0.2;
    // for (int t = 0; t < 25; t++)
    // {
    //     double dst = mySphere.signedDst(Vec3(0) + t * incr * dir);
    //     std::cout << " t = " << t * incr
    //               << " for dst(t) = " << dst << "\n";
    // }
    return 0;
};