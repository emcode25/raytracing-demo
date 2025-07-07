#include "Sphere.hpp"

Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat)
	: m_center(center), m_radius(std::fmax(0, radius)), m_mat(mat) {}

bool Sphere::hit(const Ray& r, Interval ray_t, HitRecord& rec) const {
	Vec3 oc = m_center - r.origin();
	auto a = r.direction().length_squared();
	auto h = dot(r.direction(), oc);
	auto c = oc.length_squared() - m_radius * m_radius;

	auto discriminant = h * h - a * c;
	if(discriminant < 0)
		return false;

	auto sqrtd = std::sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (h - sqrtd) / a;
	if(!ray_t.surrounds(root)) {
		root = (h + sqrtd) / a;
		if(!ray_t.surrounds(root))
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outward_normal = (rec.p - m_center) / m_radius;
	set_face_normal(rec, r, outward_normal);
	rec.mat = m_mat;

	return true;
}