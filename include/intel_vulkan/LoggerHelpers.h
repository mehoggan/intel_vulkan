///////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License.  You may obtain a copy
// of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
///////////////////////////////////////////////////////////////////////////////

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

