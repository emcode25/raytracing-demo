#include "Camera.hpp"

#include <iostream>

#include "Hittable.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "rtweekend.hpp"

Camera::Camera(double aspect_ratio, int image_width, int pixel_samples,
		int ray_depth, double fov, Point3 lookfrom, Point3 lookat,
		Vec3 world_up, double defocus_angle, double focus_dist) :
	m_aspect_ratio{aspect_ratio}, m_image_width{image_width},
	m_samples_per_pixel{pixel_samples}, m_max_depth{ray_depth},
	m_vfov{fov}, m_lookfrom{lookfrom}, m_lookat{lookat}, m_vup{world_up},
	m_defocus_angle{defocus_angle}, m_focus_dist{focus_dist} {};

void Camera::render(const Hittable& world) {
	initialize();

	std::cout << "P3\n" << m_image_width << ' ' << m_image_height << "\n255\n";

	for(int j = 0; j < m_image_height; j++) {
		std::clog << "\rScanlines remaining: " << (m_image_height - j) << ' ' << std::flush;
		for(int i = 0; i < m_image_width; i++) {
			Color pixel_color(0, 0, 0);
			for(int sample = 0; sample < m_samples_per_pixel; sample++) {
				Ray r = get_ray(i, j);
				pixel_color += ray_color(r, m_max_depth, world);
			}
			write_color(std::cout, m_pixel_samples_scale * pixel_color);
		}
	}

	std::clog << "\rDone.                 \n";
}

void Camera::initialize() {
	m_image_height = int(m_image_width / m_aspect_ratio);
	m_image_height = (m_image_height < 1) ? 1 : m_image_height;

	m_pixel_samples_scale = 1.0 / m_samples_per_pixel;

	m_center = m_lookfrom;

	// Determine viewport dimensions.
	auto theta = RT::degrees_to_radians(m_vfov);
	auto h = std::tan(theta / 2);
	auto viewport_height = 2 * h * m_focus_dist;
	auto viewport_width = viewport_height * (double(m_image_width) / m_image_height);

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	m_w = unit_vector(m_lookfrom - m_lookat);
	m_u = unit_vector(cross(m_vup, m_w));
	m_v = cross(m_w, m_u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	Vec3 viewport_u = viewport_width * m_u;    // Vector across viewport horizontal edge
	Vec3 viewport_v = viewport_height * -m_v;  // Vector down viewport vertical edge

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	m_pixel_delta_u = viewport_u / m_image_width;
	m_pixel_delta_v = viewport_v / m_image_height;

	// Calculate the location of the upper left pixel.
	auto viewport_upper_left = m_center - (m_focus_dist * m_w) - viewport_u / 2 - viewport_v / 2;
	m_pixel00_loc = viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);

	// Calculate the camera defocus disk basis vectors.
	auto defocus_radius = m_focus_dist * std::tan(RT::degrees_to_radians(m_defocus_angle / 2));
	m_defocus_disk_u = m_u * defocus_radius;
	m_defocus_disk_v = m_v * defocus_radius;
}

Ray Camera::get_ray(int i, int j) const {
	// Construct a camera ray originating from the defocus disk and directed at a randomly
	// sampled point around the pixel location i, j.

	auto offset = sample_square();
	auto pixel_sample = m_pixel00_loc
		+ ((i + offset.x()) * m_pixel_delta_u)
		+ ((j + offset.y()) * m_pixel_delta_v);

	auto ray_origin = (m_defocus_angle <= 0) ? m_center : defocus_disk_sample();
	auto ray_direction = pixel_sample - ray_origin;

	return Ray(ray_origin, ray_direction);
}

Vec3 Camera::sample_square() const {
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	return Vec3(RT::random_double() - 0.5, RT::random_double() - 0.5, 0);
}

Vec3 Camera::sample_disk(double radius) const {
	// Returns a random point in the unit (radius 0.5) disk centered at the origin.
	return radius * random_in_unit_disk();
}

Point3 Camera::defocus_disk_sample() const {
	// Returns a random point in the camera defocus disk.
	auto p = random_in_unit_disk();
	return m_center + (p[0] * m_defocus_disk_u) + (p[1] * m_defocus_disk_v);
}

Color Camera::ray_color(const Ray& r, int depth, const Hittable& world) const {
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if(depth <= 0)
		return Color(0, 0, 0);

	HitRecord rec;

	if(world.hit(r, Interval(0.001, RT::INF), rec)) {
		Ray scattered;
		Color attenuation;
		if(rec.mat->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, depth - 1, world);
		return Color(0, 0, 0);
	}

	Vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}