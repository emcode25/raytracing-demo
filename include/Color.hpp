#ifndef COLOR_HPP
#define COLOR_HPP
//==============================================================================================
// Originally written in 2020 by Peter Shirley <ptrshrl@gmail.com>
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

#include "Interval.hpp"
#include "Vec3.hpp"

using Color = Vec3;

inline double linear_to_gamma(double linear_component);

void write_color(std::ostream& out, const Color& pixel_color);

#endif
