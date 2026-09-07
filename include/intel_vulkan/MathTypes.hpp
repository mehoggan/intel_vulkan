#ifndef INTEL_VULKAN_MATHTYPES_HPP
#define INTEL_VULKAN_MATHTYPES_HPP

#include <glm/glm.hpp>

namespace intel_vulkan::Math {

// Generic-precision aliases shared by the intel_vulkan::Math headers, so
// each of them isn't spelling out glm::vec<N, T, glm::defaultp> on its own.
template <typename T> using Vec2 = glm::vec<2, T, glm::defaultp>;
template <typename T> using Vec3 = glm::vec<3, T, glm::defaultp>;
template <typename T> using Vec4 = glm::vec<4, T, glm::defaultp>;
template <typename T> using Mat4 = glm::mat<4, 4, T, glm::defaultp>;

}  // namespace intel_vulkan::Math

#endif
