#include <vulkan/vulkan.h>

namespace vulkan_graphix {

#define VK_EXPORTED_FUNCTION(fun) PFN_##fun fun;
#define VK_GLOBAL_LEVEL_FUNCTION(fun) PFN_##fun fun;
#define VK_INSTANCE_LEVEL_FUNCTION(fun) PFN_##fun fun;
#define VK_DEVICE_LEVEL_FUNCTION(fun) PFN_##fun fun;

#include "vulkan_graphix/ListOfFunctions.inl"

}  // namespace vulkan_graphix
