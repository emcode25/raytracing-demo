#ifndef RAY_HPP
#define RAY_HPP
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

#include "Vec3.hpp"

class Ray {
  public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction);

    const Point3& origin() const;
    const Vec3& direction() const;

    Point3 at(double t) const;

  private:
    Point3 m_orig;
    Vec3 m_dir;
};


#endif
