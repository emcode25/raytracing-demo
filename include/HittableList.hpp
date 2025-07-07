#ifndef HITTABLELIST_HPP
#define HITTABLELIST_HPP
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

#include "Hittable.hpp"
#include "Interval.hpp"

#include <memory>
#include <vector>


class HittableList : public Hittable {
  public:
    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    void clear();
    void add(std::shared_ptr<Hittable> object);
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

  private:
	std::vector<std::shared_ptr<Hittable>> m_objects;
};


#endif
