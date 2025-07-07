#ifndef VEC3_HPP
#define VEC3_HPP
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

//==============================================================================================
// Modified as of 2025 by Camila Molinares <emcode@vt.edu>
//==============================================================================================

class Vec3 {
  public:
    Vec3();
    Vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& v);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

    double length() const;
    double length_squared() const;
    bool near_zero() const;
    
	static Vec3 random();
    static Vec3 random(double min, double max);

private:
	double m_e[3];
};

// Point3 is just an alias for Vec3, but useful for geometric clarity in the code.
using Point3 = Vec3;


// Vector Utility Functions

extern inline Vec3 operator+(const Vec3& u, const Vec3& v);
extern inline Vec3 operator-(const Vec3& u, const Vec3& v);
extern inline Vec3 operator*(const Vec3& u, const Vec3& v);
extern inline Vec3 operator*(double t, const Vec3& v);
extern inline Vec3 operator*(const Vec3& v, double t);
extern inline Vec3 operator/(const Vec3& v, double t);

extern inline double dot(const Vec3& u, const Vec3& v);
extern inline Vec3 cross(const Vec3& u, const Vec3& v);
extern inline Vec3 unit_vector(const Vec3& v);
extern inline Vec3 random_in_unit_disk();
extern inline Vec3 random_unit_vector();
extern inline Vec3 random_on_hemisphere(const Vec3& normal);
extern inline Vec3 reflect(const Vec3& v, const Vec3& n);
extern inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat);

#endif
