#ifndef INTEL_VULKAN_CURVESAMPLE3D_HPP
#define INTEL_VULKAN_CURVESAMPLE3D_HPP

#include <limits>

#include "intel_vulkan/MathTypes.hpp"

namespace intel_vulkan::Math {

// A single sample along a CubicCurve: the position, tangent, and curve
// parameter (t) it was evaluated at.
template <typename T> struct CurveSample3D {
    CurveSample3D()
            : position(T(0), T(0), T(0))
            , tangent(T(0), T(0), T(0))
            , parameter(T(0)) {}

    CurveSample3D(Vec3<T> const& position_in,
                  Vec3<T> const& tangent_in,
                  T parameter_in)
            : position(position_in)
            , tangent(tangent_in)
            , parameter(parameter_in) {}

    void normalizeTangent() {
        if (glm::length(tangent) > std::numeric_limits<T>::epsilon()) {
            tangent = glm::normalize(tangent);
        }
    }

    Vec3<T> position;
    Vec3<T> tangent;
    T parameter;

    friend bool operator<(CurveSample3D const& lhs, CurveSample3D const& rhs) {
        return lhs.parameter < rhs.parameter;
    }
};

}  // namespace intel_vulkan::Math

#endif
