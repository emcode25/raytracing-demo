#ifndef CAMERA_HPP
#define CAMERA_HPP
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
#include "Color.hpp"
#include "Hittable.hpp"

class Camera {
  public:
	Camera(double aspect_ratio, int image_width, int pixel_samples, 
		   int ray_depth, double fov, Point3 lookfrom, Point3 lookat, 
		   Vec3 world_up, double defocus_angle, double focus_dist);

    void render(const Hittable& world);

  private:
	double m_aspect_ratio{1.0};      // Ratio of image width over height
	int m_image_width{100};       // Rendered image width in pixel count
	int m_samples_per_pixel{10};  // Count of random samples for each pixel
	int m_max_depth{10};          // Maximum number of ray bounces into scene

	double m_vfov{90};                   // Vertical view angle (field of view)
	Point3 m_lookfrom{Point3(0, 0, 0)};  // Point camera is looking from
	Point3 m_lookat{Point3(0, 0, -1)};   // Point camera is looking at
	Vec3   m_vup{Vec3(0, 1, 0)};         // Camera-relative "up" direction

	double m_defocus_angle = 0;  // Variation angle of rays through each pixel
	double m_focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    int    m_image_height;         // Rendered image height
    double m_pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    Point3 m_center;               // Camera center
    Point3 m_pixel00_loc;          // Location of pixel 0, 0
    Vec3   m_pixel_delta_u;        // Offset to pixel to the right
    Vec3   m_pixel_delta_v;        // Offset to pixel below
    Vec3   m_u, m_v, m_w;          // Camera frame basis vectors
    Vec3   m_defocus_disk_u;       // Defocus disk horizontal radius
    Vec3   m_defocus_disk_v;       // Defocus disk vertical radius

    void initialize();
    Ray get_ray(int i, int j) const;
    Vec3 sample_square() const;
    Vec3 sample_disk(double radius) const;
    Point3 defocus_disk_sample() const;
    Color ray_color(const Ray& r, int depth, const Hittable& world) const;
};


#endif
