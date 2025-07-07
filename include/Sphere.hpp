#ifndef SPHERE_HPP
#define SPHERE_HPP
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

#include <memory>

#include "Material.hpp"
#include "Hittable.hpp"
#include "Interval.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable {
  public:
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

  private:
    Point3 m_center;
    double m_radius;
    std::shared_ptr<Material> m_mat;
};


#endif
