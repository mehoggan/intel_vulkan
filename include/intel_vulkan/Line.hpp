#ifndef INTEL_VULKAN_LINE_HPP
#define INTEL_VULKAN_LINE_HPP

#include "intel_vulkan/MathTypes.hpp"

namespace intel_vulkan::Math {

// A line segment between two 3D points.
template <typename T> class Line {
public:
    Line(Vec3<T> const& point0, Vec3<T> const& point1)
            : m_point0(point0), m_point1(point1) {}

    Vec3<T> const& p0() const { return m_point0; }
    Vec3<T> const& p1() const { return m_point1; }

private:
    Vec3<T> m_point0;
    Vec3<T> m_point1;
};

}  // namespace intel_vulkan::Math

#endif
