#ifndef RTWEEKEND_HPP
#define RTWEEKEND_HPP
//==============================================================================================
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

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


namespace RT {
	// Constants

	constexpr double INF = std::numeric_limits<double>::infinity();
	constexpr double PI = 3.1415926535897932385;


	// Utility Functions

	inline double degrees_to_radians(double degrees) {
		return degrees * PI / 180.0;
	}

	inline double random_double() {
		// Returns a random real in [0,1).
		return std::rand() / (RAND_MAX + 1.0);
	}

	inline double random_double(double min, double max) {
		// Returns a random real in [min,max).
		return min + (max - min) * random_double();
	}
}


#endif
