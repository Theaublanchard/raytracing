#include "vector.h"

Vec3 Vec3::operator+(Vec3 v1) const
{
    Vec3 res = Vec3(x + v1.x, y + v1.y, z + v1.z);
    return res;
};
Vec3 Vec3::operator+(double p) const
{
    Vec3 res = Vec3(x + p, y + p, z + p);
    return res;
};
Vec3 Vec3::operator-(Vec3 v1) const
{
    Vec3 res = Vec3(x - v1.x, y - v1.y, z - v1.z);
    return res;
};
Vec3 Vec3::operator-(double p) const
{
    Vec3 res = Vec3(x - p, y - p, z - p);
    return res;
};
Vec3 Vec3::operator/(Vec3 v1) const
{
    Vec3 res = Vec3(x / v1.x, y / v1.y, z / v1.z);
    return res;
};
Vec3 Vec3::operator/(double p) const
{
    Vec3 res = Vec3(x / p, y / p, z / p);
    return res;
};
Vec3 operator/(double p, Vec3 const &v)
{
    Vec3 res = Vec3(p / v.x, p / v.y, p / v.z);
    return res;
}
Vec3 Vec3::operator*(Vec3 v1) const
{
    Vec3 res = Vec3(x * v1.x, y * v1.y, z * v1.z);
    return res;
};
Vec3 Vec3::operator*(double p) const
{
    Vec3 res = Vec3(x * p, y * p, z * p);
    return res;
};
Vec3 operator*(double p, Vec3 const &v)
{
    Vec3 res = Vec3(v.x * p, v.y * p, v.z * p);
    return res;
}

// void printv(Vec3 const &p)
std::ostream &operator<<(std::ostream &os, const Vec3 p)
{
    os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
    return os;
}

double Vec3::len() const
{
    return sqrt(Vec3::lensqr());
};

double Vec3::lensqr() const
{
    return x * x + y * y + z * z;
};

Vec3 Vec3::normalize() const
{
    double l = this->len();
    return *this / l;
}

double Vec3::dot(Vec3 const &p) const
{
    return x * p.x + y * p.y + z * p.z;
}

Vec3 cross_product(Vec3 u, Vec3 v)
{
    double x, y, z;
    x = u.y * v.z - u.z * v.y;
    y = u.z * v.x - u.x * v.z;
    z = u.x * v.y - u.y * v.x;
    return Vec3(x, y, z);
}
int printf(const Vec3 p)
{
    std::cout << p << "\n";
    return 0;
}

int main_vector()
{
    std::cout << "init my vec\n";
    Vec3 myVec = Vec3(5, 7, 0);
    int myint = 3;
    std::cout << myint;
    std::cout << "init my vec done\n";
    std::cout << "print my vec " << myVec;
    std::cout << " of lensqr " << myVec.lensqr() << std::endl;
    printf(myVec);
    return 0;
}