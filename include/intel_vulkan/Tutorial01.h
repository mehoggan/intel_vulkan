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

#ifndef INTEL_VULKAN_TUTORIAL01_H
#define INTEL_VULKAN_TUTORIAL01_H

#include <atomic>
#include <cstdint>

#include <vulkan/vulkan.h>

#include "intel_vulkan/LoggedClass.hpp"
#include "intel_vulkan/OperatingSystem.h"

namespace intel_vulkan {

// ************************************************************ //
// VulkanTutorial01Parameters                                   //
//                                                              //
// Vulkan specific parameters                                   //
// ************************************************************ //
class VulkanTutorial01Parameters {
public:
    VulkanTutorial01Parameters();

    const VkInstance& getVkInstance() const;
    VkInstance& getVkInstance();
    void setVkInstance(const VkInstance& vk_instance);

    const VkDevice& getVkDevice() const;
    VkDevice& getVkDevice();
    void setVkDevice(const VkDevice& vk_device);

    std::uint32_t getQueueFamilyIndex() const;
    void setQueueFamilyIndex(const std::uint32_t queue_family_index);

    const VkQueue& getVkQueue() const;
    VkQueue& getVkQueue();
    void setVkQueue(const VkQueue& vk_queue);

    const VkDebugUtilsMessengerEXT& getVkDebugUtilsMessenger() const;
    VkDebugUtilsMessengerEXT& getVkDebugUtilsMessenger();
    void setVkDebugUtilsMessenger(
            const VkDebugUtilsMessengerEXT& vk_debug_messenger);

private:
    VkInstance m_vk_instance;
    VkDevice m_vk_device;
    std::uint32_t m_queue_family_index;
    VkQueue m_vk_queue;
    VkDebugUtilsMessengerEXT m_vk_debug_utils_messenger;
};

// ************************************************************ //
// Tutorial01                                                   //
//                                                              //
// Class for presenting Vulkan usage topics                     //
// ************************************************************ //
class Tutorial01 : public os::ProjectBase, public LoggedClass<Tutorial01> {
public:
    explicit Tutorial01(bool enable_vk_debug = false);
    ~Tutorial01() override;

    bool onWindowSizeChanged() override;
    bool draw() override;

    bool prepareVulkan();

private:
    bool loadVulkanLibrary();
    bool loadExportedEntryPoints();
    bool loadGlobalLevelEntryPoints();
    bool createInstance();
    bool loadInstanceLevelEntryPoints();
    bool createDevice();
    bool checkPhysicalDeviceProperties(VkPhysicalDevice physical_device,
                                       uint32_t& queue_family_index);
    bool loadDeviceLevelEntryPoints();
    bool getDeviceQueue();

    bool checkValidationLayerSupport() const;
    bool setupDebugMessenger();
    bool destroyDebugMessenger();

    friend std::ostream& operator<<(
            std::ostream& out, const std::vector<VkLayerProperties>& vect);

    os::LibraryHandle m_vk_library_handle;
    VulkanTutorial01Parameters m_vk_tutorial01_parameters;
    std::atomic<bool> m_enable_vk_debug;
};

}  // namespace intel_vulkan

#endif
