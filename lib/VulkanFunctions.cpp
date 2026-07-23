#include <vulkan/vulkan.h>

namespace intel_vulkan {

#define VK_EXPORTED_FUNCTION(fun) PFN_##fun fun;
#define VK_GLOBAL_LEVEL_FUNCTION(fun) PFN_##fun fun;
#define VK_INSTANCE_LEVEL_FUNCTION(fun) PFN_##fun fun;
#define VK_DEVICE_LEVEL_FUNCTION(fun) PFN_##fun fun;

#include "intel_vulkan/ListOfFunctions.inl"

}  // namespace intel_vulkan
