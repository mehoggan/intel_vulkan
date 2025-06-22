////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

#if !defined(VULKAN_COMMON_HEADER)
#define VULKAN_COMMON_HEADER

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>
#include "OperatingSystem.h"

namespace ApiWithoutSecrets {

// ************************************************************ //
// QueueParameters                                              //
//                                                              //
// Vulkan Queue's parameters container class                    //
// ************************************************************ //
class QueueParameters {
public:
    QueueParameters();

    const VkQueue& getVkQueue() const;
    VkQueue& getVkQueue();
    void setVkQueue(const VkQueue& vk_queue);

    std::uint32_t getFamilyIndex() const;
    void setFamilyIndex(const std::uint32_t family_index);

private:
    VkQueue m_vk_queue;
    std::uint32_t m_family_index;
};

// ************************************************************ //
// ImageParameters                                              //
//                                                              //
// Vulkan Image's parameters container class                    //
// ************************************************************ //
class ImageParameters {
public:
    ImageParameters();

    const VkImage& getVkImage() const;
    void setVkImage(const VkImage& other);

    const VkImageView& getVkImageView() const;
    VkImageView& getVkImageView();
    void setVkImageView(const VkImageView& other);

    const VkSampler& getVkSampler() const;
    void setVkSampler(const VkSampler& other);

    const VkDeviceMemory& getVkDeviceMemory() const;
    void setVkDeviceMemory(const VkDeviceMemory& other);

private:
    VkImage m_vk_image;
    VkImageView m_vk_image_view;
    VkSampler m_vk_sampler;
    VkDeviceMemory m_vk_device_memory;
};

// ************************************************************ //
// BufferParameters                                             //
//                                                              //
// Vulkan Buffer's parameters container class                   //
// ************************************************************ //
class BufferParameters {
public:
    BufferParameters();

    const VkBuffer& getVkBuffer() const;
    void setVkBuffer(const VkBuffer& other);

    const VkDeviceMemory& getVkDeviceMemory() const;
    void setVkDeviceMemory(const VkDeviceMemory& other);

    std::uint32_t getSize() const;
    void setSize(const std::uint32_t size);

private:
    VkBuffer m_vk_buffer;
    VkDeviceMemory m_vk_device_memory;
    std::uint32_t m_size;
};

// ************************************************************ //
// DescriptorParameters                                         //
//                                                              //
// Container class for descriptor related resources             //
// ************************************************************ //
class DescriptorSetParameters {
public:
    DescriptorSetParameters();

    const VkDescriptorPool& getVkDescriptorPool() const;
    void setVkDescriptorPool(const VkDescriptorPool& other);

    const VkDescriptorSetLayout& getVkDescriptorSetLayout() const;
    void setVkDescriptorSetLayout(const VkDescriptorSetLayout& other);

    const VkDescriptorSet& getVkDescriptorSet() const;
    void setVkDescriptorSet(const VkDescriptorSet& other);

private:
    VkDescriptorPool m_vk_descriptor_pool;
    VkDescriptorSetLayout m_vk_descriptor_set_layout;
    VkDescriptorSet m_vk_descriptor_set;
};

// ************************************************************ //
// SwapChainParameters                                          //
//                                                              //
// Vulkan SwapChain's parameters container class                //
// ************************************************************ //
class SwapChainParameters {
public:
    SwapChainParameters();

    const VkSwapchainKHR& getVkSwapchainKhr() const;
    VkSwapchainKHR& getVkSwapchainKhr();
    void setVkSwapchainKhr(const VkSwapchainKHR& other);

    const VkFormat& getVkFormat() const;
    void setVkFormat(VkFormat& other);

    const std::vector<ImageParameters>& getImageParameters() const;
    std::vector<ImageParameters>& getImageParameters();
    void setImageParameters(const std::vector<ImageParameters>& other);

    const VkExtent2D& getVkExtent2d() const;
    void setVkExtent2d(VkExtent2D& other);

private:
    VkSwapchainKHR m_vk_swapchain_khr;
    VkFormat m_vk_format;
    std::vector<ImageParameters> m_image_parameters;
    VkExtent2D m_vk_extent_2d;
};

// ************************************************************ //
// VulkanCommonParameters                                       //
//                                                              //
// General Vulkan parameters' container class                   //
// ************************************************************ //
class VulkanCommonParameters {
public:
    VulkanCommonParameters();

    const VkInstance& getVkInstance() const;
    VkInstance& getVkInstance();
    void setVkInstance(const VkInstance& other);

    const VkPhysicalDevice& getVkPhysicalDevice() const;
    VkPhysicalDevice& getVkPhysicalDevice();
    void setVkPhysicalDevice(const VkPhysicalDevice& other);

    const VkDevice& getVkDevice() const;
    VkDevice& getVkDevice();
    void setVkDevice(const VkDevice& other);

    const QueueParameters& getGraphicsQueueParameters() const;
    QueueParameters& getGraphicsQueueParameters();
    void setGraphicsQueueParameters(const QueueParameters& other);

    const QueueParameters& getPresentQueueParameters() const;
    QueueParameters& getPresentQueueParameters();
    void setPresentQueueParameters(const QueueParameters& other);

    const VkSurfaceKHR& getVkSurfaceKhr() const;
    VkSurfaceKHR& getVkSurfaceKhr();
    void setVkSurfaceKhr(const VkSurfaceKHR& other);

    const SwapChainParameters& getSwapchainParameters() const;
    SwapChainParameters& getSwapchainParameters();
    void setSwapchainParameters(const SwapChainParameters& other);

private:
    VkInstance m_vk_instance;
    VkPhysicalDevice m_vk_physical_device;
    VkDevice m_vk_device;
    QueueParameters m_graphics_queue_parameters;
    QueueParameters m_present_queue_parameters;
    VkSurfaceKHR m_vk_surface_khr;
    SwapChainParameters m_swapchain_parameters;
};

// ************************************************************ //
// VulkanCommon                                                 //
//                                                              //
// Base class for Vulkan more advanced tutorial classes         //
// ************************************************************ //
class VulkanCommon : public OS::ProjectBase {
public:
    VulkanCommon();
    ~VulkanCommon() override;

    bool PrepareVulkan(OS::WindowParameters parameters);
    bool onWindowSizeChanged() final override;

    VkPhysicalDevice GetPhysicalDevice() const;
    VkDevice GetDevice() const;

    const QueueParameters& GetGraphicsQueue() const;
    const QueueParameters& GetPresentQueue() const;

    const SwapChainParameters& GetSwapChain() const;

private:
    OS::LibraryHandle VulkanLibrary;
    OS::WindowParameters Window;
    VulkanCommonParameters Vulkan;

    bool LoadVulkanLibrary();
    bool LoadExportedEntryPoints();
    bool LoadGlobalLevelEntryPoints();
    bool CreateInstance();
    bool LoadInstanceLevelEntryPoints();
    bool CreatePresentationSurface();
    bool CreateDevice();
    bool CheckPhysicalDeviceProperties(VkPhysicalDevice physical_device,
                                       uint32_t& graphics_queue_family_index,
                                       uint32_t& present_queue_family_index);
    bool LoadDeviceLevelEntryPoints();
    bool GetDeviceQueue();
    bool CreateSwapChain();
    bool CreateSwapChainImageViews();
    virtual bool ChildOnWindowSizeChanged() = 0;
    virtual void ChildClear() = 0;

    bool CheckExtensionAvailability(
            const char* extension_name,
            const std::vector<VkExtensionProperties>& available_extensions);
    uint32_t GetSwapChainNumImages(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkSurfaceFormatKHR GetSwapChainFormat(
            std::vector<VkSurfaceFormatKHR>& surface_formats);
    VkExtent2D GetSwapChainExtent(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkImageUsageFlags GetSwapChainUsageFlags(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkSurfaceTransformFlagBitsKHR GetSwapChainTransform(
            VkSurfaceCapabilitiesKHR& surface_capabilities);
    VkPresentModeKHR GetSwapChainPresentMode(
            std::vector<VkPresentModeKHR>& present_modes);
};

}  // namespace ApiWithoutSecrets

#endif  // VULKAN_COMMON_HEADER
