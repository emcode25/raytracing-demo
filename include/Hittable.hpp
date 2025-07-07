#ifndef HITTABLE_HPP
#define HITTABLE_HPP
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

#include "Interval.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

class Material;

struct HitRecord {
	Point3 p;
	Vec3 normal;
	std::shared_ptr<Material> mat;
	double t;
	bool front_face;
};

typedef struct HitRecord HitRecord;

void set_face_normal(HitRecord& hit, const Ray& r, const Vec3& outward_normal);


class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};


#endif
