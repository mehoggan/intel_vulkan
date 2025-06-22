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

#include "intel_vulkan/VulkanCommon.h"

#include <cstdint>
#include <iostream>

#include "intel_vulkan/VulkanFunctions.h"

namespace ApiWithoutSecrets {

/*
 * QueueParameters
 */
QueueParameters::QueueParameters()
        : m_vk_queue(VK_NULL_HANDLE), m_family_index(0) {}

const VkQueue& QueueParameters::getVkQueue() const { return m_vk_queue; }

VkQueue& QueueParameters::getVkQueue() { return m_vk_queue; }

void QueueParameters::setVkQueue(const VkQueue& vk_queue) {
    m_vk_queue = vk_queue;
}

std::uint32_t QueueParameters::getFamilyIndex() const {
    return m_family_index;
}

void QueueParameters::setFamilyIndex(const std::uint32_t family_index) {
    m_family_index = family_index;
}

/*
 * ImageParameters
 */
ImageParameters::ImageParameters()
        : m_vk_image(VK_NULL_HANDLE)
        , m_vk_image_view(VK_NULL_HANDLE)
        , m_vk_sampler(VK_NULL_HANDLE)
        , m_vk_device_memory(VK_NULL_HANDLE) {}

const VkImage& ImageParameters::getVkImage() const { return m_vk_image; }

void ImageParameters::setVkImage(const VkImage& other) { m_vk_image = other; }

const VkImageView& ImageParameters::getVkImageView() const {
    return m_vk_image_view;
}

VkImageView& ImageParameters::getVkImageView() { return m_vk_image_view; }

void ImageParameters::setVkImageView(const VkImageView& other) {
    m_vk_image_view = other;
}

const VkSampler& ImageParameters::getVkSampler() const { return m_vk_sampler; }

void ImageParameters::setVkSampler(const VkSampler& other) {
    m_vk_sampler = other;
}

const VkDeviceMemory& ImageParameters::getVkDeviceMemory() const {
    return m_vk_device_memory;
}

void ImageParameters::setVkDeviceMemory(const VkDeviceMemory& other) {
    m_vk_device_memory = other;
}

/*
 * BufferParameters
 */
BufferParameters::BufferParameters()
        : m_vk_buffer(VK_NULL_HANDLE)
        , m_vk_device_memory(VK_NULL_HANDLE)
        , m_size(0) {}

const VkBuffer& BufferParameters::getVkBuffer() const { return m_vk_buffer; }

void BufferParameters::setVkBuffer(const VkBuffer& other) {
    m_vk_buffer = other;
}

const VkDeviceMemory& BufferParameters::getVkDeviceMemory() const {
    return m_vk_device_memory;
}

void BufferParameters::setVkDeviceMemory(const VkDeviceMemory& other) {
    m_vk_device_memory = other;
}

std::uint32_t BufferParameters::getSize() const { return m_size; }

void BufferParameters::setSize(const std::uint32_t size) { m_size = size; }

/*
 * DescriptorParameters
 */
DescriptorSetParameters::DescriptorSetParameters()
        : m_vk_descriptor_pool(VK_NULL_HANDLE)
        , m_vk_descriptor_set_layout(VK_NULL_HANDLE)
        , m_vk_descriptor_set(VK_NULL_HANDLE) {}

const VkDescriptorPool& DescriptorSetParameters::getVkDescriptorPool() const {
    return m_vk_descriptor_pool;
}

void DescriptorSetParameters::setVkDescriptorPool(
        const VkDescriptorPool& other) {
    m_vk_descriptor_pool = other;
}

const VkDescriptorSetLayout&
DescriptorSetParameters::getVkDescriptorSetLayout() const {
    return m_vk_descriptor_set_layout;
}

void DescriptorSetParameters::setVkDescriptorSetLayout(
        const VkDescriptorSetLayout& other) {
    m_vk_descriptor_set_layout = other;
}

const VkDescriptorSet& DescriptorSetParameters::getVkDescriptorSet() const {
    return m_vk_descriptor_set;
}

void DescriptorSetParameters::setVkDescriptorSet(
        const VkDescriptorSet& other) {
    m_vk_descriptor_set = other;
}

/*
 * SwapChainParameters
 */
SwapChainParameters::SwapChainParameters()
        : m_vk_swapchain_khr(VK_NULL_HANDLE)
        , m_vk_format(VK_FORMAT_UNDEFINED)
        , m_image_parameters{}
        , m_vk_extent_2d() {}

const VkSwapchainKHR& SwapChainParameters::getVkSwapchainKhr() const {
    return m_vk_swapchain_khr;
}

VkSwapchainKHR& SwapChainParameters::getVkSwapchainKhr() {
    return m_vk_swapchain_khr;
}

void SwapChainParameters::setVkSwapchainKhr(const VkSwapchainKHR& other) {
    m_vk_swapchain_khr = other;
}

const VkFormat& SwapChainParameters::getVkFormat() const {
    return m_vk_format;
}

void SwapChainParameters::setVkFormat(VkFormat& other) { m_vk_format = other; }

const std::vector<ImageParameters>& SwapChainParameters::getImageParameters()
        const {
    return m_image_parameters;
}

std::vector<ImageParameters>& SwapChainParameters::getImageParameters() {
    return m_image_parameters;
}

void SwapChainParameters::setImageParameters(
        const std::vector<ImageParameters>& other) {
    m_image_parameters = other;
}

const VkExtent2D& SwapChainParameters::getVkExtent2d() const {
    return m_vk_extent_2d;
}

void SwapChainParameters::setVkExtent2d(VkExtent2D& other) {
    m_vk_extent_2d = other;
}

/*
 * Vulkan Common Parameters
 */
VulkanCommonParameters::VulkanCommonParameters()
        : m_vk_instance(VK_NULL_HANDLE)
        , m_vk_physical_device(VK_NULL_HANDLE)
        , m_vk_device(VK_NULL_HANDLE)
        , m_graphics_queue_parameters()
        , m_present_queue_parameters()
        , m_vk_surface_khr(VK_NULL_HANDLE)
        , m_swapchain_parameters() {}

const VkInstance& VulkanCommonParameters::getVkInstance() const {
    return m_vk_instance;
}

VkInstance& VulkanCommonParameters::getVkInstance() { return m_vk_instance; }

void VulkanCommonParameters::setVkInstance(const VkInstance& other) {
    m_vk_instance = other;
}

const VkPhysicalDevice& VulkanCommonParameters::getVkPhysicalDevice() const {
    return m_vk_physical_device;
}

VkPhysicalDevice& VulkanCommonParameters::getVkPhysicalDevice() {
    return m_vk_physical_device;
}

void VulkanCommonParameters::setVkPhysicalDevice(
        const VkPhysicalDevice& other) {
    m_vk_physical_device = other;
}

const VkDevice& VulkanCommonParameters::getVkDevice() const {
    return m_vk_device;
}

VkDevice& VulkanCommonParameters::getVkDevice() { return m_vk_device; }

void VulkanCommonParameters::setVkDevice(const VkDevice& other) {
    m_vk_device = other;
}

const QueueParameters& VulkanCommonParameters::getGraphicsQueueParameters()
        const {
    return m_graphics_queue_parameters;
}

QueueParameters& VulkanCommonParameters::getGraphicsQueueParameters() {
    return m_graphics_queue_parameters;
}

void VulkanCommonParameters::setGraphicsQueueParameters(
        const QueueParameters& other) {
    m_graphics_queue_parameters = other;
}

const QueueParameters& VulkanCommonParameters::getPresentQueueParameters()
        const {
    return m_present_queue_parameters;
}

QueueParameters& VulkanCommonParameters::getPresentQueueParameters() {
    return m_present_queue_parameters;
}

void VulkanCommonParameters::setPresentQueueParameters(
        const QueueParameters& other) {
    m_present_queue_parameters = other;
}

const VkSurfaceKHR& VulkanCommonParameters::getVkSurfaceKhr() const {
    return m_vk_surface_khr;
}

VkSurfaceKHR& VulkanCommonParameters::getVkSurfaceKhr() {
    return m_vk_surface_khr;
}

void VulkanCommonParameters::setVkSurfaceKhr(const VkSurfaceKHR& other) {
    m_vk_surface_khr = other;
}

const SwapChainParameters& VulkanCommonParameters::getSwapchainParameters()
        const {
    return m_swapchain_parameters;
}

SwapChainParameters& VulkanCommonParameters::getSwapchainParameters() {
    return m_swapchain_parameters;
}

void VulkanCommonParameters::setSwapchainParameters(
        const SwapChainParameters& other) {
    m_swapchain_parameters = other;
}

VulkanCommon::VulkanCommon() : VulkanLibrary(), Window(), Vulkan() {}

bool VulkanCommon::PrepareVulkan(OS::WindowParameters parameters) {
    Window = parameters;

    if (!LoadVulkanLibrary()) {
        return false;
    }
    if (!LoadExportedEntryPoints()) {
        return false;
    }
    if (!LoadGlobalLevelEntryPoints()) {
        return false;
    }
    if (!CreateInstance()) {
        return false;
    }
    if (!LoadInstanceLevelEntryPoints()) {
        return false;
    }
    if (!CreatePresentationSurface()) {
        return false;
    }
    if (!CreateDevice()) {
        return false;
    }
    if (!LoadDeviceLevelEntryPoints()) {
        return false;
    }
    if (!GetDeviceQueue()) {
        return false;
    }
    if (!CreateSwapChain()) {
        return false;
    }
    return true;
}

bool VulkanCommon::onWindowSizeChanged() {
    if (Vulkan.getVkDevice() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(Vulkan.getVkDevice());
    }

    ChildClear();

    if (CreateSwapChain()) {
        if (m_can_render) {
            return ChildOnWindowSizeChanged();
        }
        return true;
    }

    return false;
}

VkPhysicalDevice VulkanCommon::GetPhysicalDevice() const {
    return Vulkan.getVkPhysicalDevice();
}

VkDevice VulkanCommon::GetDevice() const { return Vulkan.getVkDevice(); }

const QueueParameters& VulkanCommon::GetGraphicsQueue() const {
    return Vulkan.getGraphicsQueueParameters();
}

const QueueParameters& VulkanCommon::GetPresentQueue() const {
    return Vulkan.getPresentQueueParameters();
}

const SwapChainParameters& VulkanCommon::GetSwapChain() const {
    return Vulkan.getSwapchainParameters();
}

bool VulkanCommon::LoadVulkanLibrary() {
    VulkanLibrary = dlopen("libvulkan.so.1", RTLD_NOW);

    if (VulkanLibrary == nullptr) {
        std::cout << "Could not load Vulkan library!" << std::endl;
        return false;
    }
    return true;
}

bool VulkanCommon::LoadExportedEntryPoints() {
#if defined(VK_USE_PLATFORM_WIN32_KHR)
#define LoadProcAddress GetProcAddress
#elif defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
#define LoadProcAddress dlsym
#endif

#define VK_EXPORTED_FUNCTION(fun)                                        \
    if (!(fun = (PFN_##fun)LoadProcAddress(VulkanLibrary, #fun))) {      \
        std::cout << "Could not load exported function: " << #fun << "!" \
                  << std::endl;                                          \
        return false;                                                    \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool VulkanCommon::LoadGlobalLevelEntryPoints() {
#define VK_GLOBAL_LEVEL_FUNCTION(fun)                                        \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(nullptr, #fun))) {          \
        std::cout << "Could not load global level function: " << #fun << "!" \
                  << std::endl;                                              \
        return false;                                                        \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool VulkanCommon::CreateInstance() {
    uint32_t extensions_count = 0;
    if ((vkEnumerateInstanceExtensionProperties(
                 nullptr, &extensions_count, nullptr) != VK_SUCCESS) ||
        (extensions_count == 0)) {
        std::cout << "Error occurred during instance extensions enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<VkExtensionProperties> available_extensions(extensions_count);
    if (vkEnumerateInstanceExtensionProperties(
                nullptr, &extensions_count, available_extensions.data()) !=
        VK_SUCCESS) {
        std::cout << "Error occurred during instance extensions enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<const char*> extensions = {VK_KHR_SURFACE_EXTENSION_NAME,
                                           VK_KHR_XLIB_SURFACE_EXTENSION_NAME};

    for (size_t i = 0; i < extensions.size(); ++i) {
        if (!CheckExtensionAvailability(extensions[i], available_extensions)) {
            std::cout << "Could not find instance extension named \""
                      << extensions[i] << "\"!" << std::endl;
            return false;
        }
    }

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
            nullptr,            // const void                *pNext
            0,                  // VkInstanceCreateFlags      flags
            &application_info,  // const VkApplicationInfo   *pApplicationInfo
            0,                  // uint32_t                   enabledLayerCount
            nullptr,  // const char * const        *ppEnabledLayerNames
            static_cast<uint32_t>(
                    extensions.size()),  // uint32_t enabledExtensionCount
            extensions.data()  // const char * const *ppEnabledExtensionNames
    };

    if (vkCreateInstance(&instance_create_info,
                         nullptr,
                         &Vulkan.getVkInstance()) != VK_SUCCESS) {
        std::cout << "Could not create Vulkan instance!" << std::endl;
        return false;
    }
    return true;
}

bool VulkanCommon::LoadInstanceLevelEntryPoints() {
#define VK_INSTANCE_LEVEL_FUNCTION(fun)                                  \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(Vulkan.getVkInstance(), \
                                                 #fun))) {               \
        std::cout << "Could not load instance level function: " << #fun  \
                  << "!" << std::endl;                                   \
        return false;                                                    \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool VulkanCommon::CreatePresentationSurface() {
    VkXlibSurfaceCreateInfoKHR surface_create_info = {
            VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,  // VkStructureType
                                                             // sType
            nullptr,                  // const void                    *pNext
            0,                        // VkXlibSurfaceCreateFlagsKHR    flags
            Window.getDisplayPtr(),   // Display                       *dpy
            Window.getWindowHandle()  // Window                         window
    };
    if (vkCreateXlibSurfaceKHR(Vulkan.getVkInstance(),
                               &surface_create_info,
                               nullptr,
                               &Vulkan.getVkSurfaceKhr()) == VK_SUCCESS) {
        return true;
    }

    std::cout << "Could not create presentation surface!" << std::endl;
    return false;
}

bool VulkanCommon::CreateDevice() {
    uint32_t num_devices = 0;
    if ((vkEnumeratePhysicalDevices(Vulkan.getVkInstance(),
                                    &num_devices,
                                    nullptr) != VK_SUCCESS) ||
        (num_devices == 0)) {
        std::cout << "Error occurred during physical devices enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<VkPhysicalDevice> physical_devices(num_devices);
    if (vkEnumeratePhysicalDevices(Vulkan.getVkInstance(),
                                   &num_devices,
                                   physical_devices.data()) != VK_SUCCESS) {
        std::cout << "Error occurred during physical devices enumeration!"
                  << std::endl;
        return false;
    }

    uint32_t selected_graphics_queue_family_index = UINT32_MAX;
    uint32_t selected_present_queue_family_index = UINT32_MAX;

    for (uint32_t i = 0; i < num_devices; ++i) {
        if (CheckPhysicalDeviceProperties(
                    physical_devices[i],
                    selected_graphics_queue_family_index,
                    selected_present_queue_family_index)) {
            Vulkan.setVkPhysicalDevice(physical_devices[i]);
            break;
        }
    }
    if (Vulkan.getVkPhysicalDevice() == VK_NULL_HANDLE) {
        std::cout << "Could not select physical device based on the chosen "
                     "properties!"
                  << std::endl;
        return false;
    }

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::vector<float> queue_priorities = {1.0f};

    queue_create_infos.push_back({
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,  // VkStructureType
                                                         // sType
            nullptr,  // const void                  *pNext
            0,        // VkDeviceQueueCreateFlags     flags
            selected_graphics_queue_family_index,  // uint32_t queueFamilyIndex
            static_cast<uint32_t>(
                    queue_priorities.size()),  // uint32_t queueCount
            queue_priorities.data()            // const float *pQueuePriorities
    });

    if (selected_graphics_queue_family_index !=
        selected_present_queue_family_index) {
        queue_create_infos.push_back({
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,  // VkStructureType
                                                             // sType
                nullptr,  // const void                  *pNext
                0,        // VkDeviceQueueCreateFlags     flags
                selected_present_queue_family_index,  // uint32_t
                                                      // queueFamilyIndex
                static_cast<uint32_t>(
                        queue_priorities.size()),  // uint32_t queueCount
                queue_priorities.data()  // const float *pQueuePriorities
        });
    }

    std::vector<const char*> extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    VkDeviceCreateInfo device_create_info = {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,  // VkStructureType sType
            nullptr,  // const void                        *pNext
            0,        // VkDeviceCreateFlags                flags
            static_cast<uint32_t>(
                    queue_create_infos
                            .size()),   // uint32_t queueCreateInfoCount
            queue_create_infos.data(),  // const VkDeviceQueueCreateInfo
                                        // *pQueueCreateInfos
            0,        // uint32_t                           enabledLayerCount
            nullptr,  // const char * const                *ppEnabledLayerNames
            static_cast<uint32_t>(
                    extensions.size()),  // uint32_t enabledExtensionCount
            extensions.data(),  // const char * const *ppEnabledExtensionNames
            nullptr  // const VkPhysicalDeviceFeatures    *pEnabledFeatures
    };

    if (vkCreateDevice(Vulkan.getVkPhysicalDevice(),
                       &device_create_info,
                       nullptr,
                       &Vulkan.getVkDevice()) != VK_SUCCESS) {
        std::cout << "Could not create Vulkan device!" << std::endl;
        return false;
    }

    Vulkan.getGraphicsQueueParameters().setFamilyIndex(
            selected_graphics_queue_family_index);
    Vulkan.getPresentQueueParameters().setFamilyIndex(
            selected_present_queue_family_index);
    return true;
}

bool VulkanCommon::CheckPhysicalDeviceProperties(
        VkPhysicalDevice physical_device,
        uint32_t& selected_graphics_queue_family_index,
        uint32_t& selected_present_queue_family_index) {
    uint32_t extensions_count = 0;
    if ((vkEnumerateDeviceExtensionProperties(
                 physical_device, nullptr, &extensions_count, nullptr) !=
         VK_SUCCESS) ||
        (extensions_count == 0)) {
        std::cout << "Error occurred during physical device "
                  << physical_device << " extensions enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<VkExtensionProperties> available_extensions(extensions_count);
    if (vkEnumerateDeviceExtensionProperties(physical_device,
                                             nullptr,
                                             &extensions_count,
                                             available_extensions.data()) !=
        VK_SUCCESS) {
        std::cout << "Error occurred during physical device "
                  << physical_device << " extensions enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<const char*> device_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    for (size_t i = 0; i < device_extensions.size(); ++i) {
        if (!CheckExtensionAvailability(device_extensions[i],
                                        available_extensions)) {
            std::cout << "Physical device " << physical_device
                      << " doesn't support extension named \""
                      << device_extensions[i] << "\"!" << std::endl;
            return false;
        }
    }

    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;

    vkGetPhysicalDeviceProperties(physical_device, &device_properties);
    vkGetPhysicalDeviceFeatures(physical_device, &device_features);

    uint32_t major_version = VK_VERSION_MAJOR(device_properties.apiVersion);

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
    std::vector<VkBool32> queue_present_support(queue_families_count);

    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,
                                             &queue_families_count,
                                             queue_family_properties.data());

    uint32_t graphics_queue_family_index = UINT32_MAX;
    uint32_t present_queue_family_index = UINT32_MAX;

    for (uint32_t i = 0; i < queue_families_count; ++i) {
        vkGetPhysicalDeviceSurfaceSupportKHR(physical_device,
                                             i,
                                             Vulkan.getVkSurfaceKhr(),
                                             &queue_present_support[i]);

        if ((queue_family_properties[i].queueCount > 0) &&
            (queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            // Select first queue that supports graphics
            if (graphics_queue_family_index == UINT32_MAX) {
                graphics_queue_family_index = i;
            }

            // If there is queue that supports both graphics and present -
            // prefer it
            if (queue_present_support[i]) {
                selected_graphics_queue_family_index = i;
                selected_present_queue_family_index = i;
                return true;
            }
        }
    }

    // We don't have queue that supports both graphics and present so we have
    // to use separate queues
    for (uint32_t i = 0; i < queue_families_count; ++i) {
        if (queue_present_support[i]) {
            present_queue_family_index = i;
            break;
        }
    }

    // If this device doesn't support queues with graphics and present
    // capabilities don't use it
    if ((graphics_queue_family_index == UINT32_MAX) ||
        (present_queue_family_index == UINT32_MAX)) {
        std::cout
                << "Could not find queue families with required properties on "
                   "physical device "
                << physical_device << "!" << std::endl;
        return false;
    }

    selected_graphics_queue_family_index = graphics_queue_family_index;
    selected_present_queue_family_index = present_queue_family_index;
    return true;
}

bool VulkanCommon::LoadDeviceLevelEntryPoints() {
#define VK_DEVICE_LEVEL_FUNCTION(fun)                                        \
    if (!(fun = (PFN_##fun)vkGetDeviceProcAddr(Vulkan.getVkDevice(),         \
                                               #fun))) {                     \
        std::cout << "Could not load device level function: " << #fun << "!" \
                  << std::endl;                                              \
        return false;                                                        \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool VulkanCommon::GetDeviceQueue() {
    vkGetDeviceQueue(Vulkan.getVkDevice(),
                     Vulkan.getGraphicsQueueParameters().getFamilyIndex(),
                     0,
                     &Vulkan.getGraphicsQueueParameters().getVkQueue());
    vkGetDeviceQueue(Vulkan.getVkDevice(),
                     Vulkan.getPresentQueueParameters().getFamilyIndex(),
                     0,
                     &Vulkan.getPresentQueueParameters().getVkQueue());
    return true;
}

bool VulkanCommon::CreateSwapChain() {
    m_can_render = false;

    if (Vulkan.getVkDevice() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(Vulkan.getVkDevice());
    }

    for (size_t i = 0;
         i < Vulkan.getSwapchainParameters().getImageParameters().size();
         ++i) {
        if (Vulkan.getSwapchainParameters()
                    .getImageParameters()[i]
                    .getVkImageView() != VK_NULL_HANDLE) {
            vkDestroyImageView(GetDevice(),
                               Vulkan.getSwapchainParameters()
                                       .getImageParameters()[i]
                                       .getVkImageView(),
                               nullptr);
            Vulkan.getSwapchainParameters()
                    .getImageParameters()[i]
                    .setVkImageView(VK_NULL_HANDLE);
        }
    }
    Vulkan.getSwapchainParameters().getImageParameters().clear();

    VkSurfaceCapabilitiesKHR surface_capabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Vulkan.getVkPhysicalDevice(),
                                                  Vulkan.getVkSurfaceKhr(),
                                                  &surface_capabilities) !=
        VK_SUCCESS) {
        std::cout << "Could not check presentation surface capabilities!"
                  << std::endl;
        return false;
    }

    uint32_t formats_count;
    if ((vkGetPhysicalDeviceSurfaceFormatsKHR(Vulkan.getVkPhysicalDevice(),
                                              Vulkan.getVkSurfaceKhr(),
                                              &formats_count,
                                              nullptr) != VK_SUCCESS) ||
        (formats_count == 0)) {
        std::cout << "Error occurred during presentation surface formats "
                     "enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<VkSurfaceFormatKHR> surface_formats(formats_count);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(Vulkan.getVkPhysicalDevice(),
                                             Vulkan.getVkSurfaceKhr(),
                                             &formats_count,
                                             surface_formats.data()) !=
        VK_SUCCESS) {
        std::cout << "Error occurred during presentation surface formats "
                     "enumeration!"
                  << std::endl;
        return false;
    }

    uint32_t present_modes_count;
    if ((vkGetPhysicalDeviceSurfacePresentModesKHR(
                 Vulkan.getVkPhysicalDevice(),
                 Vulkan.getVkSurfaceKhr(),
                 &present_modes_count,
                 nullptr) != VK_SUCCESS) ||
        (present_modes_count == 0)) {
        std::cout
                << "Error occurred during presentation surface present modes "
                   "enumeration!"
                << std::endl;
        return false;
    }

    std::vector<VkPresentModeKHR> present_modes(present_modes_count);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(Vulkan.getVkPhysicalDevice(),
                                                  Vulkan.getVkSurfaceKhr(),
                                                  &present_modes_count,
                                                  present_modes.data()) !=
        VK_SUCCESS) {
        std::cout
                << "Error occurred during presentation surface present modes "
                   "enumeration!"
                << std::endl;
        return false;
    }

    uint32_t desired_number_of_images =
            GetSwapChainNumImages(surface_capabilities);
    VkSurfaceFormatKHR desired_format = GetSwapChainFormat(surface_formats);
    VkExtent2D desired_extent = GetSwapChainExtent(surface_capabilities);
    VkImageUsageFlags desired_usage =
            GetSwapChainUsageFlags(surface_capabilities);
    VkSurfaceTransformFlagBitsKHR desired_transform =
            GetSwapChainTransform(surface_capabilities);
    VkPresentModeKHR desired_present_mode =
            GetSwapChainPresentMode(present_modes);
    const VkSwapchainKHR& old_swap_chain =
            Vulkan.getSwapchainParameters().getVkSwapchainKhr();

    if (static_cast<int>(desired_usage) == -1) {
        return false;
    }
    if (static_cast<int>(desired_present_mode) == -1) {
        return false;
    }
    if ((desired_extent.width == 0) || (desired_extent.height == 0)) {
        // Current surface size is (0, 0) so we can't create a swap chain and
        // render anything (CanRender == false) But we don't wont to kill the
        // application as this situation may occur i.e. when window gets
        // minimized
        return true;
    }

    VkSwapchainCreateInfoKHR swap_chain_create_info = {
            VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,  // VkStructureType
                                                          // sType
            nullptr,                    // const void                    *pNext
            0,                          // VkSwapchainCreateFlagsKHR      flags
            Vulkan.getVkSurfaceKhr(),   // VkSurfaceKHR surface
            desired_number_of_images,   // uint32_t minImageCount
            desired_format.format,      // VkFormat imageFormat
            desired_format.colorSpace,  // VkColorSpaceKHR imageColorSpace
            desired_extent,  // VkExtent2D                     imageExtent
            1,               // uint32_t                       imageArrayLayers
            desired_usage,   // VkImageUsageFlags              imageUsage
            VK_SHARING_MODE_EXCLUSIVE,  // VkSharingMode imageSharingMode
            0,        // uint32_t                       queueFamilyIndexCount
            nullptr,  // const uint32_t                *pQueueFamilyIndices
            desired_transform,  // VkSurfaceTransformFlagBitsKHR  preTransform
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,  // VkCompositeAlphaFlagBitsKHR
                                                // compositeAlpha
            desired_present_mode,               // VkPresentModeKHR presentMode
            VK_TRUE,        // VkBool32                       clipped
            old_swap_chain  // VkSwapchainKHR                 oldSwapchain
    };

    if (vkCreateSwapchainKHR(
                Vulkan.getVkDevice(),
                &swap_chain_create_info,
                nullptr,
                &Vulkan.getSwapchainParameters().getVkSwapchainKhr()) !=
        VK_SUCCESS) {
        std::cout << "Could not create swap chain!" << std::endl;
        return false;
    }
    if (old_swap_chain != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(Vulkan.getVkDevice(), old_swap_chain, nullptr);
    }

    Vulkan.getSwapchainParameters().setVkFormat(desired_format.format);

    uint32_t image_count = 0;
    if ((vkGetSwapchainImagesKHR(
                 Vulkan.getVkDevice(),
                 Vulkan.getSwapchainParameters().getVkSwapchainKhr(),
                 &image_count,
                 nullptr) != VK_SUCCESS) ||
        (image_count == 0)) {
        std::cout << "Could not get swap chain images!" << std::endl;
        return false;
    }

    Vulkan.getSwapchainParameters().getImageParameters().resize(image_count);

    std::vector<VkImage> images(image_count);
    if (vkGetSwapchainImagesKHR(
                Vulkan.getVkDevice(),
                Vulkan.getSwapchainParameters().getVkSwapchainKhr(),
                &image_count,
                images.data()) != VK_SUCCESS) {
        std::cout << "Could not get swap chain images!" << std::endl;
        return false;
    }

    for (size_t i = 0;
         i < Vulkan.getSwapchainParameters().getImageParameters().size();
         ++i) {
        Vulkan.getSwapchainParameters().getImageParameters()[i].setVkImage(
                images[i]);
    }
    Vulkan.getSwapchainParameters().setVkExtent2d(desired_extent);

    return CreateSwapChainImageViews();
}

bool VulkanCommon::CreateSwapChainImageViews() {
    for (size_t i = 0;
         i < Vulkan.getSwapchainParameters().getImageParameters().size();
         ++i) {
        VkImageViewCreateInfo image_view_create_info = {
                VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,  // VkStructureType
                                                           // sType
                nullptr,  // const void                    *pNext
                0,        // VkImageViewCreateFlags         flags
                Vulkan.getSwapchainParameters()
                        .getImageParameters()[i]
                        .getVkImage(),         // VkImage image
                VK_IMAGE_VIEW_TYPE_2D,         // VkImageViewType viewType
                GetSwapChain().getVkFormat(),  // VkFormat format
                {
                        // VkComponentMapping             components
                        VK_COMPONENT_SWIZZLE_IDENTITY,  // VkComponentSwizzle r
                        VK_COMPONENT_SWIZZLE_IDENTITY,  // VkComponentSwizzle g
                        VK_COMPONENT_SWIZZLE_IDENTITY,  // VkComponentSwizzle b
                        VK_COMPONENT_SWIZZLE_IDENTITY   // VkComponentSwizzle a
                },
                {
                        // VkImageSubresourceRange        subresourceRange
                        VK_IMAGE_ASPECT_COLOR_BIT,  // VkImageAspectFlags
                                                    // aspectMask
                        0,  // uint32_t                       baseMipLevel
                        1,  // uint32_t                       levelCount
                        0,  // uint32_t                       baseArrayLayer
                        1   // uint32_t                       layerCount
                }};

        if (vkCreateImageView(GetDevice(),
                              &image_view_create_info,
                              nullptr,
                              &Vulkan.getSwapchainParameters()
                                       .getImageParameters()[i]
                                       .getVkImageView()) != VK_SUCCESS) {
            std::cout << "Could not create image view for framebuffer!"
                      << std::endl;
            return false;
        }
    }

    m_can_render = true;

    return true;
}

bool VulkanCommon::CheckExtensionAvailability(
        const char* extension_name,
        const std::vector<VkExtensionProperties>& available_extensions) {
    for (size_t i = 0; i < available_extensions.size(); ++i) {
        if (strcmp(available_extensions[i].extensionName, extension_name) ==
            0) {
            return true;
        }
    }
    return false;
}

uint32_t VulkanCommon::GetSwapChainNumImages(
        VkSurfaceCapabilitiesKHR& surface_capabilities) {
    // Set of images defined in a swap chain may not always be available for
    // application to render to: One may be displayed and one may wait in a
    // queue to be presented If application wants to use more images at the
    // same time it must ask for more images
    uint32_t image_count = surface_capabilities.minImageCount + 2;
    if ((surface_capabilities.maxImageCount > 0) &&
        (image_count > surface_capabilities.maxImageCount)) {
        image_count = surface_capabilities.maxImageCount;
    }
    return image_count;
}

VkSurfaceFormatKHR VulkanCommon::GetSwapChainFormat(
        std::vector<VkSurfaceFormatKHR>& surface_formats) {
    // If the list contains only one entry with undefined format
    // it means that there are no preferred surface formats and any can be
    // chosen
    if ((surface_formats.size() == 1) &&
        (surface_formats[0].format == VK_FORMAT_UNDEFINED)) {
        return {VK_FORMAT_R8G8B8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR};
    }

    // Check if list contains most widely used R8 G8 B8 A8 format
    // with nonlinear color space
    for (VkSurfaceFormatKHR& surface_format : surface_formats) {
        if (surface_format.format == VK_FORMAT_R8G8B8A8_UNORM) {
            return surface_format;
        }
    }

    // Return the first format from the list
    return surface_formats[0];
}

VkExtent2D VulkanCommon::GetSwapChainExtent(
        VkSurfaceCapabilitiesKHR& surface_capabilities) {
    // Special value of surface extent is width == height == -1
    // If this is so we define the size by ourselves but it must fit within
    // defined confines
    if (static_cast<std::int32_t>(surface_capabilities.currentExtent.width) ==
        -1) {
        VkExtent2D swap_chain_extent = {640, 480};
        if (swap_chain_extent.width <
            surface_capabilities.minImageExtent.width) {
            swap_chain_extent.width =
                    surface_capabilities.minImageExtent.width;
        }
        if (swap_chain_extent.height <
            surface_capabilities.minImageExtent.height) {
            swap_chain_extent.height =
                    surface_capabilities.minImageExtent.height;
        }
        if (swap_chain_extent.width >
            surface_capabilities.maxImageExtent.width) {
            swap_chain_extent.width =
                    surface_capabilities.maxImageExtent.width;
        }
        if (swap_chain_extent.height >
            surface_capabilities.maxImageExtent.height) {
            swap_chain_extent.height =
                    surface_capabilities.maxImageExtent.height;
        }
        return swap_chain_extent;
    }

    // Most of the cases we define size of the swap_chain images equal to
    // current window's size
    return surface_capabilities.currentExtent;
}

VkImageUsageFlags VulkanCommon::GetSwapChainUsageFlags(
        VkSurfaceCapabilitiesKHR& surface_capabilities) {
    // Color attachment flag must always be supported
    // We can define other usage flags but we always need to check if they are
    // supported
    if (surface_capabilities.supportedUsageFlags &
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) {
        return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    }
    std::cout << "VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT image usage is not "
                 "supported by the swap chain!"
              << std::endl
              << "Supported swap chain's image usages include:" << std::endl
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_TRANSFER_SRC_BIT
                          ? "    VK_IMAGE_USAGE_TRANSFER_SRC\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_TRANSFER_DST_BIT
                          ? "    VK_IMAGE_USAGE_TRANSFER_DST\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_SAMPLED_BIT
                          ? "    VK_IMAGE_USAGE_SAMPLED\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_STORAGE_BIT
                          ? "    VK_IMAGE_USAGE_STORAGE\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
                          ? "    VK_IMAGE_USAGE_COLOR_ATTACHMENT\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
                          ? "    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT
                          ? "    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT\n"
                          : "")
              << (surface_capabilities.supportedUsageFlags &
                                  VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
                          ? "    VK_IMAGE_USAGE_INPUT_ATTACHMENT"
                          : "")
              << std::endl;
    return static_cast<VkImageUsageFlags>(-1);
}

VkSurfaceTransformFlagBitsKHR VulkanCommon::GetSwapChainTransform(
        VkSurfaceCapabilitiesKHR& surface_capabilities) {
    // Sometimes images must be transformed before they are presented (i.e. due
    // to device's orientation being other than default orientation) If the
    // specified transform is other than current transform, presentation engine
    // will transform image during presentation operation; this operation may
    // hit performance on some platforms Here we don't want any transformations
    // to occur so if the identity transform is supported use it otherwise just
    // use the same transform as current transform
    if (surface_capabilities.supportedTransforms &
        VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
        return VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    } else {
        return surface_capabilities.currentTransform;
    }
}

VkPresentModeKHR VulkanCommon::GetSwapChainPresentMode(
        std::vector<VkPresentModeKHR>& present_modes) {
    // MAILBOX is the lowest latency V-Sync enabled mode (something like
    // triple-buffering) so use it if available
    for (VkPresentModeKHR& present_mode : present_modes) {
        if (present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return present_mode;
        }
    }
    // IMMEDIATE mode allows us to display frames in a V-Sync independent
    // manner so it can introduce screen tearing But this mode is the best for
    // benchmarking purposes if we want to check the real number of FPS
    for (VkPresentModeKHR& present_mode : present_modes) {
        if (present_mode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            return present_mode;
        }
    }
    // FIFO present mode is always available
    for (VkPresentModeKHR& present_mode : present_modes) {
        if (present_mode == VK_PRESENT_MODE_FIFO_KHR) {
            return present_mode;
        }
    }
    std::cout << "FIFO present mode is not supported by the swap chain!"
              << std::endl;
    return static_cast<VkPresentModeKHR>(-1);
}

VulkanCommon::~VulkanCommon() {
    if (Vulkan.getVkDevice() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(Vulkan.getVkDevice());

        for (size_t i = 0;
             i < Vulkan.getSwapchainParameters().getImageParameters().size();
             ++i) {
            if (Vulkan.getSwapchainParameters()
                        .getImageParameters()[i]
                        .getVkImageView() != VK_NULL_HANDLE) {
                vkDestroyImageView(GetDevice(),
                                   Vulkan.getSwapchainParameters()
                                           .getImageParameters()[i]
                                           .getVkImageView(),
                                   nullptr);
            }
        }

        if (Vulkan.getSwapchainParameters().getVkSwapchainKhr() !=
            VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(
                    Vulkan.getVkDevice(),
                    Vulkan.getSwapchainParameters().getVkSwapchainKhr(),
                    nullptr);
        }
        vkDestroyDevice(Vulkan.getVkDevice(), nullptr);
    }

    if (Vulkan.getVkSurfaceKhr() != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(
                Vulkan.getVkInstance(), Vulkan.getVkSurfaceKhr(), nullptr);
    }

    if (Vulkan.getVkInstance() != VK_NULL_HANDLE) {
        vkDestroyInstance(Vulkan.getVkInstance(), nullptr);
    }

    if (VulkanLibrary) {
        dlclose(VulkanLibrary);
    }
}

}  // namespace ApiWithoutSecrets
