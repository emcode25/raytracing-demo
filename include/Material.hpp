#ifndef MATERIAL_HPP
#define MATERIAL_HPP
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
#include "Ray.hpp"
#include "Color.hpp" 

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const {
        return false;
    }
};


class Lambertian : public Material {
  public:
    Lambertian(const Color& albedo) : m_albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);
        attenuation = m_albedo;
        return true;
    }

  private:
    Color m_albedo;
};


class Metal : public Material {
  public:
    Metal(const Color& albedo, double fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        Vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (m_fuzz * random_unit_vector());
        scattered = Ray(rec.p, reflected);
        attenuation = m_albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

  private:
    Color m_albedo;
    double m_fuzz;
};


class Dielectric : public Material {
  public:
    Dielectric(double refraction_index) : m_refraction_index(refraction_index) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/ m_refraction_index) : m_refraction_index;

        Vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        Vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > RT::random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = Ray(rec.p, direction);
        return true;
    }

  private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double m_refraction_index;

    static double reflectance(double cosine, double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine),5);
    }
};


#endif
