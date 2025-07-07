#include "Hittable.hpp"

void set_face_normal(HitRecord& rec, const Ray& r, const Vec3& outward_normal) {
	// Sets the hit record normal vector.
	// NOTE: the parameter `outward_normal` is assumed to have unit length.

	rec.front_face = dot(r.direction(), outward_normal) < 0;
	rec.normal = rec.front_face ? outward_normal : -outward_normal;
}