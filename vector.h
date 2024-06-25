#ifndef CMATH
#define CMATH
#include <cmath>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef OSTREAM
#define OSTREAM
#include <ostream>
#endif

#ifndef VEC
#define VEC

class Vec3
{
public:
    double x, y, z;
    Vec3(){};
    Vec3(double x, double y, double z) : x(x), y(y), z(z){};
    Vec3(double val) : x(val), y(val), z(val){};

    ~Vec3() = default;
    // {
    //     std::cout << "\nDestroying vector at pos : [" << x
    //               << ", " << y << ", " << z << "]" << std::endl;
    // }
    Vec3 operator+(Vec3 p) const;
    Vec3 operator+(double p) const;
    Vec3 operator-(Vec3 p) const;
    Vec3 operator-(double p) const;
    Vec3 operator/(Vec3 p) const;
    Vec3 operator/(double p) const;
    Vec3 operator*(Vec3 p) const;
    Vec3 operator*(double p) const;

    double len() const;
    double lensqr() const;
    double dot(Vec3 const &p) const;
    Vec3 normalize() const;
};

Vec3 operator/(double p, Vec3 const &v);
Vec3 operator*(double p, Vec3 const &v);

std::ostream &operator<<(std::ostream &os, const Vec3 v);
int printf(const Vec3 p);

Vec3 cross_product(Vec3 a, Vec3 b);
#endif