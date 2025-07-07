#include "Interval.hpp"

const Interval Interval::empty = Interval(+RT::INF, -RT::INF);
const Interval Interval::universe = Interval(-RT::INF, +RT::INF);

Interval::Interval() : m_min(+RT::INF), m_max(-RT::INF) {} // Default interval is empty

Interval::Interval(double min, double max) : m_min(min), m_max(max) {}

double Interval::getMin() const { return m_min; };
void Interval::setMin(double x) { m_min = x; };
double Interval::getMax() const { return m_max; };
void Interval::setMax(double x) { m_max = x; };

double Interval::size() const {
	return m_max - m_min;
}

bool Interval::contains(double x) const {
	return m_min <= x && x <= m_max;
}

bool Interval::surrounds(double x) const {
	return m_min < x && x < m_max;
}

double Interval::clamp(double x) const {
	if(x < m_min) return m_min;
	if(x > m_max) return m_max;
	return x;
}
