#if !defined(VULKAN_FUNCTIONS_HEADER)
#define VULKAN_FUNCTIONS_HEADER

#include <vulkan/vulkan.h>

#include <X11/Xlib.h>
#include <vulkan/vulkan_xlib.h>

namespace intel_vulkan {

#define VK_EXPORTED_FUNCTION(fun) extern PFN_##fun fun;
#define VK_GLOBAL_LEVEL_FUNCTION(fun) extern PFN_##fun fun;
#define VK_INSTANCE_LEVEL_FUNCTION(fun) extern PFN_##fun fun;
#define VK_DEVICE_LEVEL_FUNCTION(fun) extern PFN_##fun fun;

#include "ListOfFunctions.inl"

}  // namespace intel_vulkan

#endif
