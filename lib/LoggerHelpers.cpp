////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Directed Acyclic Graph Scheduler
// All rights reserved.
//
// Contact: mehoggan@gmail.com
//
// This software is licensed under the terms of the Your License.
// See the LICENSE file in the top-level directory.
/////////////////////////////////////////////////////////////////////////

#include "intel_vulkan/LoggerHelpers.h"

#include <algorithm>

std::stringstream& operator<<(std::stringstream& out,
                              const std::vector<const char*>& vect) {
    out << "[";
    std::for_each(vect.begin(), vect.end(), [&out](const char* value) {
        out << value << ", ";
    });
    out << "]";
    return out;
}

std::stringstream& operator<<(std::stringstream& out,
                              const VkLayerProperties& vk_layer_properties) {
    out << vk_layer_properties.layerName;
    return out;
}

std::stringstream& operator<<(std::stringstream& out,
                              const std::vector<VkLayerProperties>& vect) {
    for (std::vector<VkLayerProperties>::const_iterator vector_const_it =
                 vect.cbegin();
         vector_const_it != vect.cend();
         ++vector_const_it) {
        out << (*vector_const_it);
        if (vector_const_it != vect.cend() - 1) {
            out << "\n\t";
        }
    }
    return out;
}
