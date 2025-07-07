#include "HittableList.hpp"

HittableList::HittableList() {}
HittableList::HittableList(std::shared_ptr<Hittable> object) { add(object); }

void HittableList::clear() { m_objects.clear(); }

void HittableList::add(std::shared_ptr<Hittable> object) {
	m_objects.push_back(object);
}

bool HittableList::hit(const Ray& r, Interval ray_t, HitRecord& rec) const {
	HitRecord temp_rec;
	bool hit_anything = false;
	auto closest_so_far = ray_t.getMax();

	for(const auto& object : m_objects) {
		if(object->hit(r, Interval(ray_t.getMin(), closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}