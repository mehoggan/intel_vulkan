////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2026 intel_vulkan
// All rights reserved.
//
// Contact: mehoggan@gmail.com
//
// This software is licensed under the terms of the Your License.
// See the LICENSE file in the top-level directory.
/////////////////////////////////////////////////////////////////////////

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
