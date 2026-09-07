#ifndef INTEL_VULKAN_SPHERE_HPP
#define INTEL_VULKAN_SPHERE_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <glm/gtc/epsilon.hpp>
#include <tuple>
#include <vector>

#include "intel_vulkan/Geometry.hpp"
#include "intel_vulkan/MathTypes.hpp"
#include "intel_vulkan/TessellationOps.hpp"
#include "intel_vulkan/TessellationTypes.hpp"
#include "intel_vulkan/Triangle.hpp"

namespace intel_vulkan::Math {

template <typename T, typename I> class SphereGenerator {
public:
    virtual ~SphereGenerator() = default;

    virtual void generate(TessellatedTriangleData<T, I>& output) const = 0;
};

// Generates a sphere by subdividing an octahedron.
template <typename T, typename I>
class OctahedronGenerator : public SphereGenerator<T, I> {
public:
    OctahedronGenerator(T radius, std::size_t subdivision_count)
            : m_radius(radius), m_subdivision_count(subdivision_count) {}

    void generate(TessellatedTriangleData<T, I>& output) const override {
        Vec3<T> const points[6] = {
                Vec3<T>(T(+0.0), -m_radius, T(+0.0)),
                Vec3<T>(T(+0.0), T(+0.0), +m_radius),
                Vec3<T>(+m_radius, T(+0.0), T(+0.0)),
                Vec3<T>(T(+0.0), T(+0.0), -m_radius),
                Vec3<T>(-m_radius, T(+0.0), T(+0.0)),
                Vec3<T>(T(+0.0), +m_radius, T(+0.0)),
        };
        std::vector<Triangle<T>> const octahedron_tris = {
                Triangle<T>(points[0], points[1], points[2]),
                Triangle<T>(points[5], points[1], points[2]),
                Triangle<T>(points[0], points[3], points[2]),
                Triangle<T>(points[5], points[2], points[3]),
                Triangle<T>(points[0], points[3], points[4]),
                Triangle<T>(points[5], points[3], points[4]),
                Triangle<T>(points[0], points[4], points[1]),
                Triangle<T>(points[5], points[4], points[1]),
        };
        I current_index = 0;
        tessellateTrianglesByMidpointSubdivision<T, I>(
                octahedron_tris, m_subdivision_count, current_index, output);
    }

    T radius() const { return m_radius; }

private:
    T m_radius;
    std::size_t m_subdivision_count;
};

namespace detail {

// Epsilon chosen for the precision of std::sin/std::cos, matching the
// spherical -> cartesian conversion these points come from.
template <typename T, typename I>
std::tuple<bool, I> vectorContainsPoint(std::vector<Vec3<T>> const& points,
                                        Vec3<T> const& point) {
    auto point_it = std::find_if(
            points.begin(), points.end(), [&point](Vec3<T> const& candidate) {
                return glm::all(
                        glm::epsilonEqual(point, candidate, T(0.000001)));
            });

    if (point_it == points.end()) {
        return std::make_tuple(false, static_cast<I>(-1));
    }
    return std::make_tuple(true, static_cast<I>(point_it - points.begin()));
}

}  // namespace detail

// Generates a sphere by walking a latitude/longitude grid of spherical
// coordinates.
template <typename T, typename I>
class SphericalCoordinateGenerator : public SphereGenerator<T, I> {
public:
    SphericalCoordinateGenerator(T radius,
                                 T theta_angle_delta,
                                 T phi_angle_delta,
                                 AngleMode mode)
            : m_theta_angle_delta(theta_angle_delta)
            , m_phi_angle_delta(phi_angle_delta)
            , m_radius(radius) {
        if (mode == AngleMode::Radians) {
            m_theta_angle_delta = glm::degrees(m_theta_angle_delta);
            m_phi_angle_delta = glm::degrees(m_phi_angle_delta);
        }
    }

    void generate(TessellatedTriangleData<T, I>& output) const override {
        I current_index = 0;
        T phi_angle(-90.0);
        while (phi_angle <= T(+90.0)) {
            T theta_angle(+0.0);
            while (theta_angle <= T(+360.0)) {
                SphericalCoordinates<T, AngleMode::Degrees> coords(
                        theta_angle, phi_angle, m_radius);
                Vec3<T> point = sphericalToCartesian(coords);

                auto [found, existing_index] =
                        detail::vectorContainsPoint<T, I>(output.points(),
                                                          point);
                static_cast<void>(existing_index);
                if (!found) {
                    output.points().push_back(point);
                    output.indices().push_back(current_index);
                    ++current_index;
                }

                theta_angle += m_theta_angle_delta;
            }
            phi_angle += m_phi_angle_delta;
        }
    }

    T radius() const { return m_radius; }

private:
    T m_theta_angle_delta;
    T m_phi_angle_delta;
    T m_radius;
};

// Wraps a SphereGenerator so the tessellation strategy can be swapped
// without changing call sites.
template <typename T,
          typename I,
          template <typename, typename> class GenT = OctahedronGenerator>
class Sphere {
public:
    explicit Sphere(GenT<T, I> const& generator) : m_generator(generator) {}

    void generate(TessellatedTriangleData<T, I>& output) const {
        m_generator.generate(output);
    }

    T radius() const { return m_generator.radius(); }

private:
    GenT<T, I> m_generator;
};

}  // namespace intel_vulkan::Math

#endif
