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

#ifndef INTEL_VULKAN_TUTORIAL02_H
#define INTEL_VULKAN_TUTORIAL02_H

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>

#include "intel_vulkan/LoggedClass.hpp"
#include "intel_vulkan/OperatingSystem.h"

namespace intel_vulkan {

// ************************************************************ //
// VulkanTutorial02Parameters                                   //
//                                                              //
// Vulkan specific parameters                                   //
// ************************************************************ //
class VulkanTutorial02Parameters {
public:
    VulkanTutorial02Parameters();

    const VkInstance& getVkInstance() const;
    VkInstance& getVkInstance();
    void setVkInstance(const VkInstance& vk_instance);

    const VkPhysicalDevice& getVkPhysicalDevice() const;
    void setVkPhysicalDevice(const VkPhysicalDevice& vk_physical_device);

    const VkDevice& getVkDevice() const;
    VkDevice& getVkDevice();
    void setVkDevice(const VkDevice& vk_device);

    const VkQueue& getGraphicsVkQueue() const;
    VkQueue& getGraphicsVkQueue();
    void setGraphicsVkQueue(const VkQueue& graphics_vk_queue);

    const VkQueue& getPresentVkQueue() const;
    VkQueue& getPresentVkQueue();
    void setPresentVkQueue(const VkQueue& present_vk_queue);

    std::uint32_t getGraphicsQueueFamilyIndex() const;
    void setGraphicsQueueFamilyIndex(
            const std::uint32_t graphics_queue_family_index);

    std::uint32_t getPresentQueueFamilyIndex() const;
    void setPresentQueueFamilyIndex(
            const std::uint32_t graphics_queue_family_index);

    const VkSurfaceKHR& getPresentVkSurfaceKHR() const;
    VkSurfaceKHR& getPresentVkSurfaceKHR();
    void setPresentVkSurfaceKHR(
            const VkSurfaceKHR& presentation_vk_surface_khr);

    const VkSwapchainKHR& getVkSwapchainKHR() const;
    VkSwapchainKHR& getVkSwapchainKHR();
    void setVkSwapchainKHR(const VkSwapchainKHR& vk_swapchain_khr);

    const std::vector<VkCommandBuffer>& getPresentQueueVkCommandBuffers()
            const;
    std::vector<VkCommandBuffer>& getPresentQueueVkCommandBuffers();
    void setPresentQueueVkCommandBuffers(
            const std::vector<VkCommandBuffer>&
                    present_queue_vk_command_buffers);

    const VkCommandPool& getPresentQueueVkCommandPool() const;
    VkCommandPool& getPresentQueueVkCommandPool();
    void setPresentQueueVkCommandPool(
            const VkCommandPool& present_queue_vk_command_pool);

    const VkSemaphore& getImageAvailableVkSemaphore() const;
    VkSemaphore& getImageAvailableVkSemaphore();
    void setImageAvailableVkSemaphore(
            const VkSemaphore& image_available_vk_semaphore);

    const VkSemaphore& getRenderingFinishedVkSemaphore() const;
    VkSemaphore& getRenderingFinishedVkSemaphore();
    void setRenderingFinishedVkSemaphore(
            const VkSemaphore& rendering_finished_vk_semaphore);

    const VkDebugUtilsMessengerEXT& getVkDebugUtilsMessenger() const;
    VkDebugUtilsMessengerEXT& getVkDebugUtilsMessenger();
    void setVkDebugUtilsMessenger(
            const VkDebugUtilsMessengerEXT& vk_debug_messenger);

private:
    VkInstance m_vk_instance;
    VkPhysicalDevice m_vk_physical_device;
    VkDevice m_vk_device;
    VkQueue m_graphics_vk_queue;
    VkQueue m_present_vk_queue;
    std::uint32_t m_graphics_queue_family_index;
    std::uint32_t m_present_queue_family_index;
    VkSurfaceKHR m_presentation_vk_surface_khr;
    VkSwapchainKHR m_vk_swapchain_khr;
    std::vector<VkCommandBuffer> m_present_queue_vk_command_buffers;
    VkCommandPool m_present_queue_vk_command_pool;
    VkSemaphore m_image_available_vk_semaphore;
    VkSemaphore m_rendering_finished_vk_semaphore;
    VkDebugUtilsMessengerEXT m_vk_debug_utils_messenger;
};

// ************************************************************ //
// Tutorial02                                                   //
//                                                              //
// Class for presenting Vulkan usage topics                     //
// ************************************************************ //
class Tutorial02 : public os::ProjectBase, public LoggedClass<Tutorial02> {
public:
    Tutorial02();
    ~Tutorial02() override;

    bool prepareVulkan(os::WindowParameters parameters);
    bool createSwapChain();
    bool onWindowSizeChanged() override;
    bool createCommandBuffers();
    bool draw() override;

private:
    bool loadVulkanLibrary();
    bool loadExportedEntryPoints();
    bool loadGlobalLevelEntryPoints();
    bool createInstance();
    bool loadInstanceLevelEntryPoints();
    bool createPresentationSurface();
    bool createDevice();
    bool checkPhysicalDeviceProperties(
            VkPhysicalDevice physical_device,
            std::uint32_t& graphics_queue_family_index,
            std::uint32_t& present_queue_family_index);
    bool loadDeviceLevelEntryPoints();
    bool getDeviceQueue();
    bool createSemaphores();
    bool recordCommandBuffers();
    void clear();

    bool checkValidationLayerSupport() const;
    bool setupDebugMessenger();
    bool destroyDebugMessenger();

    bool checkExtensionAvailability(
            const char* extension_name,
            const std::vector<VkExtensionProperties>& available_extensions);
    std::uint32_t getSwapChainNumImages(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkSurfaceFormatKHR getSwapChainFormat(
            std::vector<VkSurfaceFormatKHR>& surface_formats);
    VkExtent2D getSwapChainExtent(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkImageUsageFlags getSwapChainUsageFlags(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkSurfaceTransformFlagBitsKHR getSwapChainTransform(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkPresentModeKHR getSwapChainPresentMode(
            std::vector<VkPresentModeKHR>& present_modes);

    friend std::ostream& operator<<(
            std::ostream& out, const std::vector<VkLayerProperties>& vect);

    os::LibraryHandle m_vulkan_library;
    os::WindowParameters m_window_parameters;
    VulkanTutorial02Parameters m_vk_tutorial02_parameters;
    std::atomic<bool> m_enable_vk_debug;
};

}  // namespace intel_vulkan

#endif
