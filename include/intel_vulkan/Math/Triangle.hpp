#ifndef INTEL_VULKAN_TRIANGLE_HPP
#define INTEL_VULKAN_TRIANGLE_HPP

#include "intel_vulkan/Math/MathTypes.hpp"

namespace intel_vulkan::Math {

// A triangle defined by three 3D points.
template <typename T> class Triangle {
public:
    Triangle(Vec3<T> const& point0,
             Vec3<T> const& point1,
             Vec3<T> const& point2)
            : m_point0(point0), m_point1(point1), m_point2(point2) {}

    Vec3<T> const& p0() const { return m_point0; }
    Vec3<T> const& p1() const { return m_point1; }
    Vec3<T> const& p2() const { return m_point2; }

private:
    Vec3<T> m_point0;
    Vec3<T> m_point1;
    Vec3<T> m_point2;
};

}  // namespace intel_vulkan::Math

#endif
