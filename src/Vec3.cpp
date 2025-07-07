#include "Vec3.hpp"

#include <cmath>

#include "rtweekend.hpp"

Vec3::Vec3() : m_e{0,0,0} {}
Vec3::Vec3(double e0, double e1, double e2) : m_e{e0, e1, e2} {}

double Vec3::x() const { return m_e[0]; }
double Vec3::y() const { return m_e[1]; }
double Vec3::z() const { return m_e[2]; }

Vec3 Vec3::operator-() const { return Vec3(-m_e[0], -m_e[1], -m_e[2]); }
double Vec3::operator[](int i) const { return m_e[i]; }
double& Vec3::operator[](int i) { return m_e[i]; }

Vec3& Vec3::operator+=(const Vec3& v) {
	m_e[0] += v.x();
	m_e[1] += v.y();
	m_e[2] += v.z();
	return *this;
}

Vec3& Vec3::operator*=(double t) {
	m_e[0] *= t;
	m_e[1] *= t;
	m_e[2] *= t;
	return *this;
}

Vec3& Vec3::operator/=(double t) {
	return *this *= 1 / t;
}

double Vec3::length() const {
	return std::sqrt(length_squared());
}

double Vec3::length_squared() const {
	return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
}

bool Vec3::near_zero() const {
	// Return true if the vector is close to zero in all dimensions.
	auto s = 1e-8;
	return (std::fabs(m_e[0]) < s) && (std::fabs(m_e[1]) < s) && (std::fabs(m_e[2]) < s);
}

Vec3 Vec3::random() {
	return Vec3(RT::random_double(), RT::random_double(), RT::random_double());
}

Vec3 Vec3::random(double min, double max) {
	return Vec3(RT::random_double(min, max), RT::random_double(min, max), RT::random_double(min, max));
}

// Vector Utility Functions

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.x(), t * v.y(), t * v.z());
}

inline Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}

inline Vec3 operator/(const Vec3& v, double t) {
	return (1 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
	return u.x() * v.x()
		+ u.y() * v.y()
		+ u.z() * v.z();
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.y() * v.z() - u.z() * v.y(),
				u.z() * v.x() - u.x() * v.z(),
				u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unit_vector(const Vec3& v) {
	return v / v.length();
}

inline Vec3 random_in_unit_disk() {
	while(true) {
		auto p = Vec3(RT::random_double(-1, 1), RT::random_double(-1, 1), 0);
		if(p.length_squared() < 1)
			return p;
	}
}

inline Vec3 random_unit_vector() {
	while(true) {
		auto p = Vec3::random(-1, 1);
		auto lensq = p.length_squared();
		if(1e-160 < lensq && lensq <= 1.0)
			return p / sqrt(lensq);
	}
}

inline Vec3 random_on_hemisphere(const Vec3& normal) {
	Vec3 on_unit_sphere = random_unit_vector();
	if(dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
	auto cos_theta = std::fmin(dot(-uv, n), 1.0);
	Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}