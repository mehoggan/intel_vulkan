////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2026 intel_vulkan
// All rights reserved.
//
// Contact: mehoggan@gmail.com
//
// This software is licensed under the terms of the Your License.
// See the LICENSE file in the top-level directory.
/////////////////////////////////////////////////////////////////////////

#ifndef INTEL_VULKAN_TOOLS_H
#define INTEL_VULKAN_TOOLS_H

#include <array>
#include <string>
#include <vector>

#include <vulkan/vulkan.h>

// TODO (mehoggan@gmail.com): This file needs to be doccumented.

namespace intel_vulkan::Tools {

template <class T, class F> class AutoDeleter {
public:
    AutoDeleter()
            : Object(VK_NULL_HANDLE)
            , Deleter(nullptr)
            , Device(VK_NULL_HANDLE) {}

    AutoDeleter(T object, F deleter, VkDevice device)
            : Object(object), Deleter(deleter), Device(device) {}

    AutoDeleter(AutoDeleter&& other) { *this = std::move(other); }

    ~AutoDeleter() {
        if ((Object != VK_NULL_HANDLE) && (Deleter != nullptr) &&
            (Device != VK_NULL_HANDLE)) {
            Deleter(Device, Object, nullptr);
        }
    }

    AutoDeleter& operator=(AutoDeleter&& other) {
        if (this != &other) {
            Object = other.Object;
            Deleter = other.Deleter;
            Device = other.Device;
            other.Object = VK_NULL_HANDLE;
        }
        return *this;
    }

    T get() { return Object; }

    bool operator!() const { return Object == VK_NULL_HANDLE; }

private:
    AutoDeleter(const AutoDeleter&);
    AutoDeleter& operator=(const AutoDeleter&);
    T Object;
    F Deleter;
    VkDevice Device;
};

std::vector<char> getBinaryFileContents(std::string const& filename);

std::vector<char> getImageData(std::string const& filename,
                               int requested_components,
                               int* width,
                               int* height,
                               int* components,
                               int* data_size);

std::array<float, 16> getPerspectiveProjectionMatrix(float const aspect_ratio,
                                                     float const field_of_view,
                                                     float const near_clip,
                                                     float const far_clip);

std::array<float, 16> getOrthographicProjectionMatrix(float const left_plane,
                                                      float const right_plane,
                                                      float const top_plane,
                                                      float const bottom_plane,
                                                      float const near_plane,
                                                      float const far_plane);

}  // namespace intel_vulkan::Tools

#endif
