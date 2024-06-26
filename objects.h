#ifndef OBJECTS
#define OBJECTS

#ifndef COLORS
#include "colors.h"
#endif

#ifndef VEC
#include "vector.h"
#endif

class Ray
{
public:
    Vec3 pos, dir, color, invdir;
    int depth = 0;

    Ray(){};
    ~Ray() = default;
    Ray(Vec3 const &pos, Vec3 const &dir);
    Ray(Vec3 const &pos, Vec3 const &dir, Vec3 const &color);
    Ray(Vec3 const &pos, Vec3 const &dir, Vec3 const &color, int depth);
    void setDir(Vec3 const &p);
    Vec3 computeInvDir();
    // void print();
};
std::ostream &operator<<(std::ostream &os, const Ray o);
int printf(Ray r);
Ray computeReflectedRay(Ray const &normalRay, Ray const &incommingRay);

class Object
{
public:
    Vec3 pos;
    bool isGlass = false;
    double opacity = 1;
    double roughness = 1;
    double s; // scale
    // Mat4 rotMat ; // rotation matrix world to local;

    Object(){};
    virtual ~Object();
    Object(Vec3 const pos_, double const s_) : pos(pos_), s(s_){};

    virtual bool intersect(Ray r) const = 0;
    virtual bool intersect(Ray r, Vec3 &hitPoint) const = 0;
    virtual bool intersect(Ray r, double &t_hit) const = 0;
    virtual Vec3 computeNormalDir(Vec3 const &hitPoint) const = 0; //{ return Vec3(1); };
    virtual Vec3 getColorAt(Vec3 const &pos) const = 0;
    virtual void print(std::ostream &os) const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Object &obj);
};

// std::ostream &operator<<(std::ostream &os, Object o);

class Sphere : public Object
{

public:
    Vec3 color;
    Sphere(Vec3 pos, Vec3 color, double s);
    bool intersect(Ray r) const override;
    bool intersect(Ray r, Vec3 &hitPoint) const override;
    bool intersect(Ray r, double &t_hit) const override;
    Vec3 computeNormalDir(Vec3 const &hitPoint) const override;
    double signedDst(Vec3 const &p) const;
    Vec3 getColorAt(Vec3 const &pos) const override;
    void print(std::ostream &os) const override;
};
std::ostream &operator<<(std::ostream &os, const Sphere o);
int printf(Sphere o);

class CheckBoard : public Object
{
public:
    CheckBoard(){};
    CheckBoard(Vec3 pos, double s) : Object(pos, s){};
    bool intersect(Ray r) const override;
    bool intersect(Ray r, double &t_hit) const override;
    bool intersect(Ray r, Vec3 &hitPoint) const override;
    Vec3 computeNormalDir(Vec3 const &hitPoint) const override;
    Vec3 getColorAt(Vec3 const &pos) const override;
    void print(std::ostream &os) const override;
};
std::ostream &operator<<(std::ostream &os, const CheckBoard o);
int printf(CheckBoard o);

class Cube : public Object
{
public:
    Vec3 color;
    Cube(){};
    Cube(Vec3 pos, double s) : Object(pos, s){};
    Cube(Vec3 pos_, Vec3 color_, double s_);
    bool intersect(Ray r) const override;
    bool intersect(Ray r, double &t_hit) const override;
    bool intersect(Ray r, Vec3 &hitPoint) const override;
    int getClosestFace(Vec3 const &point) const;
    Vec3 computeNormalDir(Vec3 const &hitPoint) const override;
    Vec3 getColorAt(Vec3 const &pos) const override;
    void print(std::ostream &os) const override;
};
std::ostream &operator<<(std::ostream &os, const Cube o);
int printf(Cube o);

Ray computeReflectedRay(Ray const &normalRay, Ray const &incommingRay, double opacity);

bool findroots(double a, double b, double c, double &t1, double &t2);

#endif