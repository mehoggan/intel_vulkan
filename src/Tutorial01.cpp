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

#include "intel_vulkan/Tutorial01.h"

#include <cstdint>
#include <iostream>
#include <vector>

#include "intel_vulkan/VulkanFunctions.h"

namespace ApiWithoutSecrets {

Tutorial01::Tutorial01()
        : m_vk_library_handle(), m_vk_tutorial01_parameters() {}

Tutorial01::~Tutorial01() {
    if (m_vk_tutorial01_parameters.Device != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(m_vk_tutorial01_parameters.Device);
        vkDestroyDevice(m_vk_tutorial01_parameters.Device, nullptr);
    }

    if (m_vk_tutorial01_parameters.Instance != VK_NULL_HANDLE) {
        vkDestroyInstance(m_vk_tutorial01_parameters.Instance, nullptr);
    }

    if (m_vk_library_handle) {
        dlclose(m_vk_library_handle);
    }
}

bool Tutorial01::onWindowSizeChanged() { return true; }

bool Tutorial01::draw() { return true; }

bool Tutorial01::prepareVulkan() {
    if (!loadVulkanLibrary()) {
        return false;
    }
    if (!loadExportedEntryPoints()) {
        return false;
    }
    if (!loadGlobalLevelEntryPoints()) {
        return false;
    }
    if (!createInstance()) {
        return false;
    }
    if (!loadInstanceLevelEntryPoints()) {
        return false;
    }
    if (!createDevice()) {
        return false;
    }
    if (!loadDeviceLevelEntryPoints()) {
        return false;
    }
    if (!getDeviceQueue()) {
        return false;
    }
    return true;
}

bool Tutorial01::loadVulkanLibrary() {
    m_vk_library_handle = dlopen("libvulkan.so.1", RTLD_NOW);

    if (m_vk_library_handle == nullptr) {
        std::cout << "Could not load Vulkan library!" << std::endl;
        return false;
    }
    return true;
}

bool Tutorial01::loadExportedEntryPoints() {
#define LoadProcAddress dlsym

#define VK_EXPORTED_FUNCTION(fun)                                         \
    if (!(fun = (PFN_##fun)LoadProcAddress(m_vk_library_handle, #fun))) { \
        std::cout << "Could not load exported function: " << #fun << "!"  \
                  << std::endl;                                           \
        return false;                                                     \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::loadGlobalLevelEntryPoints() {
#define VK_GLOBAL_LEVEL_FUNCTION(fun)                                        \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(nullptr, #fun))) {          \
        std::cout << "Could not load global level function: " << #fun << "!" \
                  << std::endl;                                              \
        return false;                                                        \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::createInstance() {
    VkApplicationInfo application_info = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO,  // VkStructureType sType
            nullptr,  // const void                *pNext
            "API without Secrets: Introduction to Vulkan",  // const char
                                                            // *pApplicationName
            VK_MAKE_VERSION(1, 0, 0),    // uint32_t applicationVersion
            "Vulkan Tutorial by Intel",  // const char *pEngineName
            VK_MAKE_VERSION(1, 0, 0),    // uint32_t engineVersion
            VK_MAKE_VERSION(1, 0, 0)  // uint32_t                   apiVersion
    };

    VkInstanceCreateInfo instance_create_info = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,  // VkStructureType sType
            nullptr,            // const void*                pNext
            0,                  // VkInstanceCreateFlags      flags
            &application_info,  // const VkApplicationInfo   *pApplicationInfo
            0,                  // uint32_t                   enabledLayerCount
            nullptr,  // const char * const        *ppEnabledLayerNames
            0,        // uint32_t                   enabledExtensionCount
            nullptr   // const char * const        *ppEnabledExtensionNames
    };

    if (vkCreateInstance(&instance_create_info,
                         nullptr,
                         &m_vk_tutorial01_parameters.Instance) != VK_SUCCESS) {
        std::cout << "Could not create Vulkan instance!" << std::endl;
        return false;
    }
    return true;
}

bool Tutorial01::loadInstanceLevelEntryPoints() {
#define VK_INSTANCE_LEVEL_FUNCTION(fun)                                 \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(                       \
                  m_vk_tutorial01_parameters.Instance, #fun))) {        \
        std::cout << "Could not load instance level function: " << #fun \
                  << "!" << std::endl;                                  \
        return false;                                                   \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::createDevice() {
    uint32_t num_devices = 0;
    if ((vkEnumeratePhysicalDevices(m_vk_tutorial01_parameters.Instance,
                                    &num_devices,
                                    nullptr) != VK_SUCCESS) ||
        (num_devices == 0)) {
        std::cout << "Error occurred during physical devices enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<VkPhysicalDevice> physical_devices(num_devices);
    if (vkEnumeratePhysicalDevices(m_vk_tutorial01_parameters.Instance,
                                   &num_devices,
                                   physical_devices.data()) != VK_SUCCESS) {
        std::cout << "Error occurred during physical devices enumeration!"
                  << std::endl;
        return false;
    }

    VkPhysicalDevice selected_physical_device = VK_NULL_HANDLE;
    uint32_t selected_queue_family_index = UINT32_MAX;
    for (uint32_t i = 0; i < num_devices; ++i) {
        if (checkPhysicalDeviceProperties(physical_devices[i],
                                          selected_queue_family_index)) {
            selected_physical_device = physical_devices[i];
            break;
        }
    }
    if (selected_physical_device == VK_NULL_HANDLE) {
        std::cout << "Could not select physical device based on the chosen "
                     "properties!"
                  << std::endl;
        return false;
    }

    std::vector<float> queue_priorities = {1.0f};

    VkDeviceQueueCreateInfo queue_create_info = {
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,  // VkStructureType
                                                         // sType
            nullptr,                                     // const void* pNext
            0,                            // VkDeviceQueueCreateFlags flags
            selected_queue_family_index,  // uint32_t queueFamilyIndex
            static_cast<uint32_t>(
                    queue_priorities.size()),  // uint32_t queueCount
            queue_priorities.data()            // const float *pQueuePriorities
    };

    VkDeviceCreateInfo device_create_info = {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,  // VkStructureType sType
            nullptr,  // const void                        *pNext
            0,        // VkDeviceCreateFlags                flags
            1,  // uint32_t                           queueCreateInfoCount
            &queue_create_info,  // const VkDeviceQueueCreateInfo
                                 // *pQueueCreateInfos
            0,        // uint32_t                           enabledLayerCount
            nullptr,  // const char * const                *ppEnabledLayerNames
            0,  // uint32_t                           enabledExtensionCount
            nullptr,  // const char * const *ppEnabledExtensionNames
            nullptr   // const VkPhysicalDeviceFeatures    *pEnabledFeatures
    };

    if (vkCreateDevice(selected_physical_device,
                       &device_create_info,
                       nullptr,
                       &m_vk_tutorial01_parameters.Device) != VK_SUCCESS) {
        std::cout << "Could not create Vulkan device!" << std::endl;
        return false;
    }

    m_vk_tutorial01_parameters.QueueFamilyIndex = selected_queue_family_index;
    return true;
}

bool Tutorial01::checkPhysicalDeviceProperties(
        VkPhysicalDevice physical_device, uint32_t& queue_family_index) {
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;

    vkGetPhysicalDeviceProperties(physical_device, &device_properties);
    vkGetPhysicalDeviceFeatures(physical_device, &device_features);

    std::int32_t major_version =
            VK_VERSION_MAJOR(device_properties.apiVersion);

    if ((major_version < 1) ||
        (device_properties.limits.maxImageDimension2D < 4096)) {
        std::cout << "Physical device " << physical_device
                  << " doesn't support required parameters!" << std::endl;
        return false;
    }

    uint32_t queue_families_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
            physical_device, &queue_families_count, nullptr);
    if (queue_families_count == 0) {
        std::cout << "Physical device " << physical_device
                  << " doesn't have any queue families!" << std::endl;
        return false;
    }

    std::vector<VkQueueFamilyProperties> queue_family_properties(
            queue_families_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,
                                             &queue_families_count,
                                             queue_family_properties.data());
    for (uint32_t i = 0; i < queue_families_count; ++i) {
        if ((queue_family_properties[i].queueCount > 0) &&
            (queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            queue_family_index = i;
            std::cout << "Selected device: " << device_properties.deviceName
                      << std::endl;
            return true;
        }
    }

    std::cout << "Could not find queue family with required properties on "
                 "physical device "
              << physical_device << "!" << std::endl;
    return false;
}

bool Tutorial01::loadDeviceLevelEntryPoints() {
#define VK_DEVICE_LEVEL_FUNCTION(fun)                                        \
    if (!(fun = (PFN_##fun)vkGetDeviceProcAddr(                              \
                  m_vk_tutorial01_parameters.Device, #fun))) {               \
        std::cout << "Could not load device level function: " << #fun << "!" \
                  << std::endl;                                              \
        return false;                                                        \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::getDeviceQueue() {
    vkGetDeviceQueue(m_vk_tutorial01_parameters.Device,
                     m_vk_tutorial01_parameters.QueueFamilyIndex,
                     0,
                     &m_vk_tutorial01_parameters.Queue);
    return true;
}

}  // namespace ApiWithoutSecrets
