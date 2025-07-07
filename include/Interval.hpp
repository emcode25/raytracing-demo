#ifndef INTERVAL_HPP
#define INTERVAL_HPP
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

#include "rtweekend.hpp"

class Interval {
public:
    Interval(); // Default interval is empty
    Interval(double min, double max);

	double getMin() const;
	void setMin(double x);
	double getMax() const;
	void setMax(double x);

    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const;

	static const Interval empty;
	static const Interval universe;

private:
	double m_min, m_max;
};


#endif
