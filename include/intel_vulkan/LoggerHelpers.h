#ifndef INTEL_VULKAN_LOGGERHELPERS_H
#define INTEL_VULKAN_LOGGERHELPERS_H

#include <sstream>
#include <vector>

#include <vulkan/vulkan.h>

std::stringstream& operator<<(std::stringstream& out,
                              const std::vector<const char*>& vect);

std::stringstream& operator<<(std::stringstream& out,
                              const VkLayerProperties& vk_layer_properties);

std::stringstream& operator<<(std::stringstream& out,
                              const std::vector<VkLayerProperties>& vect);

#endif
