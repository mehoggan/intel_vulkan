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
#include <functional>
#include <iostream>
#include <vector>

#include "intel_vulkan/VulkanFunctions.h"

std::ostream& operator<<(std::ostream& out,
                         const std::vector<const char*>& vect) {
    out << "[";
    std::for_each(vect.begin(), vect.end(), [&out](const char* value) {
        out << value << ", ";
    });
    out << "]";
    return out;
}

std::ostream& operator<<(std::ostream& out,
                         const VkLayerProperties& vk_layer_properties) {
    out << vk_layer_properties.layerName;
    return out;
}

std::ostream& operator<<(std::ostream& out,
                         const std::vector<VkLayerProperties>& vect) {
    for (std::vector<VkLayerProperties>::const_iterator vector_const_it =
                 vect.cbegin();
         vector_const_it != vect.cend();
         ++vector_const_it) {
        std::cout << (*vector_const_it);
        if (vector_const_it != vect.cend() - 1) {
            std::cout << "\n\t";
        }
    }
    return out;
}

namespace intel_vulkan {

VulkanTutorial01Parameters::VulkanTutorial01Parameters()
        : m_vk_instance(VK_NULL_HANDLE)
        , m_vk_device(VK_NULL_HANDLE)
        , m_queue_family_index(0)
        , m_vk_queue(VK_NULL_HANDLE)
        , m_vk_debug_utils_messenger(VK_NULL_HANDLE) {}

const VkInstance& VulkanTutorial01Parameters::getVkInstance() const {
    return m_vk_instance;
}

VkInstance& VulkanTutorial01Parameters::getVkInstance() {
    return m_vk_instance;
}

void VulkanTutorial01Parameters::setVkInstance(const VkInstance& vk_instance) {
    m_vk_instance = vk_instance;
}

const VkDevice& VulkanTutorial01Parameters::getVkDevice() const {
    return m_vk_device;
}

VkDevice& VulkanTutorial01Parameters::getVkDevice() { return m_vk_device; }

void VulkanTutorial01Parameters::setVkDevice(const VkDevice& vk_device) {
    m_vk_device = vk_device;
}

std::uint32_t VulkanTutorial01Parameters::getQueueFamilyIndex() const {
    return m_queue_family_index;
}

void VulkanTutorial01Parameters::setQueueFamilyIndex(
        const std::uint32_t queue_family_index) {
    m_queue_family_index = queue_family_index;
}

const VkQueue& VulkanTutorial01Parameters::getVkQueue() const {
    return m_vk_queue;
}

VkQueue& VulkanTutorial01Parameters::getVkQueue() { return m_vk_queue; }

void VulkanTutorial01Parameters::setVkQueue(const VkQueue& vk_queue) {
    m_vk_queue = vk_queue;
}

const VkDebugUtilsMessengerEXT&
VulkanTutorial01Parameters::getVkDebugUtilsMessenger() const {
    return m_vk_debug_utils_messenger;
}

VkDebugUtilsMessengerEXT&
VulkanTutorial01Parameters::getVkDebugUtilsMessenger() {
    return m_vk_debug_utils_messenger;
}

void VulkanTutorial01Parameters::setVkDebugUtilsMessenger(
        const VkDebugUtilsMessengerEXT& vk_debug_utils_messenger) {
    m_vk_debug_utils_messenger = vk_debug_utils_messenger;
}

Tutorial01::Tutorial01(bool enable_debug)
        : m_vk_library_handle()
        , m_vk_tutorial01_parameters()
        , m_enable_vk_debug(enable_debug) {}

Tutorial01::~Tutorial01() {
    if (m_vk_tutorial01_parameters.getVkDevice() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(m_vk_tutorial01_parameters.getVkDevice());
        vkDestroyDevice(m_vk_tutorial01_parameters.getVkDevice(), nullptr);
    }

    if (m_vk_tutorial01_parameters.getVkDebugUtilsMessenger() !=
        VK_NULL_HANDLE) {
        if (!destroyDebugMessenger()) {
            std::cerr << "Failed to destroy VkDebugUtilsMessengerExt!!!"
                      << std::endl;
        }
    }

    if (m_vk_tutorial01_parameters.getVkInstance() != VK_NULL_HANDLE) {
        vkDestroyInstance(m_vk_tutorial01_parameters.getVkInstance(), nullptr);
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
        std::cerr << "Could not load Vulkan library!" << std::endl;
        return false;
    }
    return true;
}

bool Tutorial01::loadExportedEntryPoints() {
#define LoadProcAddress dlsym

#define VK_EXPORTED_FUNCTION(fun)                                          \
    if (m_enable_vk_debug) {                                               \
        std::cout << "Loading entry point " << #fun << "..." << std::endl; \
    }                                                                      \
    if (!(fun = (PFN_##fun)LoadProcAddress(m_vk_library_handle, #fun))) {  \
        std::cerr << "Could not load exported function: " << #fun << "!"   \
                  << std::endl;                                            \
        return false;                                                      \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::loadGlobalLevelEntryPoints() {
#define VK_GLOBAL_LEVEL_FUNCTION(fun)                                        \
    if (m_enable_vk_debug) {                                                 \
        std::cout << "Loading global " << #fun << "..." << std::endl;        \
    }                                                                        \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(nullptr, #fun))) {          \
        std::cerr << "Could not load global level function: " << #fun << "!" \
                  << std::endl;                                              \
        return false;                                                        \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::createInstance() {
    if (!checkValidationLayerSupport()) {
        std::cerr << "Failed to create an instance that does not support "
                  << "validation layers." << std::endl;
        return false;
    }

    std::function<std::vector<const char*>()> get_required_extensions =
            []() -> std::vector<const char*> {
        return {VK_EXT_DEBUG_UTILS_EXTENSION_NAME};
    };

    VkApplicationInfo application_info{};
    application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pNext = nullptr;
    application_info.pApplicationName =
            "API without Secrets: Introduction to Vulkan";
    application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.pEngineName = "Vulkan Tutorial by Intel";
    application_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    std::vector<const char*> vk_extensions =
            (m_enable_vk_debug ? get_required_extensions()
                               : std::vector<const char*>{});
    std::cout << "Creating an instance with the following extensions "
              << vk_extensions << std::endl;

    VkInstanceCreateInfo instance_create_info{};
    instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pNext = nullptr;
    instance_create_info.flags = 0;
    instance_create_info.pApplicationInfo = &application_info;
    instance_create_info.enabledLayerCount = 0;
    instance_create_info.ppEnabledLayerNames = nullptr;
    if (m_enable_vk_debug.load()) {
        instance_create_info.enabledExtensionCount =
                static_cast<std::uint32_t>(vk_extensions.size());
        instance_create_info.ppEnabledExtensionNames = vk_extensions.data();
    } else {
        instance_create_info.enabledExtensionCount = 0;
        instance_create_info.ppEnabledExtensionNames = vk_extensions.data();
    }

    if (vkCreateInstance(&instance_create_info,
                         nullptr,
                         &m_vk_tutorial01_parameters.getVkInstance()) !=
        VK_SUCCESS) {
        std::cerr << "Could not create Vulkan instance!" << std::endl;
        return false;
    }

    if (!setupDebugMessenger()) {
        std::cerr << "Failed to setup debug messenger!!!" << std::endl;
    }

    return true;
}

bool Tutorial01::loadInstanceLevelEntryPoints() {
#define VK_INSTANCE_LEVEL_FUNCTION(fun)                                 \
    if (m_enable_vk_debug) {                                            \
        std::cout << "Loading instance " << #fun << "..." << std::endl; \
    }                                                                   \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(                       \
                  m_vk_tutorial01_parameters.getVkInstance(), #fun))) { \
        std::cerr << "Could not load instance level function: " << #fun \
                  << "!" << std::endl;                                  \
        return false;                                                   \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::createDevice() {
    uint32_t num_devices = 0;
    if ((vkEnumeratePhysicalDevices(m_vk_tutorial01_parameters.getVkInstance(),
                                    &num_devices,
                                    nullptr) != VK_SUCCESS) ||
        (num_devices == 0)) {
        std::cerr << "Error occurred during physical devices enumeration!"
                  << std::endl;
        return false;
    }

    std::vector<VkPhysicalDevice> physical_devices(num_devices);
    if (vkEnumeratePhysicalDevices(m_vk_tutorial01_parameters.getVkInstance(),
                                   &num_devices,
                                   physical_devices.data()) != VK_SUCCESS) {
        std::cerr << "Error occurred during physical devices enumeration!"
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
        std::cerr << "Could not select physical device based on the chosen "
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
            nullptr,  // const char * const *ppEnabledLayerNames
            0,  // uint32_t                           enabledExtensionCount
            nullptr,  // const char * const *ppEnabledExtensionNames
            nullptr   // const VkPhysicalDeviceFeatures    *pEnabledFeatures
    };

    if (vkCreateDevice(selected_physical_device,
                       &device_create_info,
                       nullptr,
                       &m_vk_tutorial01_parameters.getVkDevice()) !=
        VK_SUCCESS) {
        std::cerr << "Could not create Vulkan device!" << std::endl;
        return false;
    }

    m_vk_tutorial01_parameters.setQueueFamilyIndex(
            selected_queue_family_index);
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
        std::cerr << "Physical device " << physical_device
                  << " doesn't support required parameters!" << std::endl;
        return false;
    }

    uint32_t queue_families_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
            physical_device, &queue_families_count, nullptr);
    if (queue_families_count == 0) {
        std::cerr << "Physical device " << physical_device
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
            std::cerr << "Selected device: " << device_properties.deviceName
                      << std::endl;
            return true;
        }
    }

    std::cerr << "Could not find queue family with required properties on "
                 "physical device "
              << physical_device << "!" << std::endl;
    return false;
}

bool Tutorial01::loadDeviceLevelEntryPoints() {
#define VK_DEVICE_LEVEL_FUNCTION(fun)                                        \
    if (m_enable_vk_debug) {                                                 \
        std::cout << "Loading device " << #fun << "..." << std::endl;        \
    }                                                                        \
    if (!(fun = (PFN_##fun)vkGetDeviceProcAddr(                              \
                  m_vk_tutorial01_parameters.getVkDevice(), #fun))) {        \
        std::cerr << "Could not load device level function: " << #fun << "!" \
                  << std::endl;                                              \
        return false;                                                        \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::getDeviceQueue() {
    vkGetDeviceQueue(m_vk_tutorial01_parameters.getVkDevice(),
                     m_vk_tutorial01_parameters.getQueueFamilyIndex(),
                     0,
                     &m_vk_tutorial01_parameters.getVkQueue());
    return true;
}

bool Tutorial01::checkValidationLayerSupport() const {
    static const std::vector<const char*> validation_layers = {
            "VK_LAYER_KHRONOS_validation"};

    std::uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> vk_layer_properties(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count,
                                       vk_layer_properties.data());
    std::cout << "The vk_instance has the following properties: " << std::endl;
    std::cout << "\t" << vk_layer_properties << std::endl;

    bool response = true;
    for (const char* layer_name : validation_layers) {
        std::vector<VkLayerProperties>::iterator layer_it = std::find_if(
                vk_layer_properties.begin(),
                vk_layer_properties.end(),
                [&layer_name](const VkLayerProperties& vk_layer_property) {
                    return strcmp(layer_name, vk_layer_property.layerName) ==
                           0;
                });
        if (layer_it == vk_layer_properties.end()) {
            std::cerr << "The following layer \"" << layer_name << "\""
                      << " could not be loaded!!!" << std::endl;
            response = false;
            break;
        }
    }

    return response;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
              VkDebugUtilsMessageTypeFlagsEXT message_type,
              const VkDebugUtilsMessengerCallbackDataEXT*
                      vk_debug_utils_messenger_callback_data_ext,
              void* p_user_data) {
    std::cerr << "validation layer: "
              << vk_debug_utils_messenger_callback_data_ext->pMessage
              << std::endl;

    return VK_FALSE;
}

bool Tutorial01::setupDebugMessenger() {
    bool response = false;
    if (!m_enable_vk_debug.load()) {
        response = true;
    } else {
        std::cout << "Setting up Vulkan debugger..." << std::endl;
        VkDebugUtilsMessengerCreateInfoEXT
                vk_debug_utils_messenger_create_info_ext{};
        vk_debug_utils_messenger_create_info_ext.sType =
                VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        vk_debug_utils_messenger_create_info_ext.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        vk_debug_utils_messenger_create_info_ext.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        vk_debug_utils_messenger_create_info_ext.pfnUserCallback =
                debugCallback;

        PFN_vkCreateDebugUtilsMessengerEXT func =
                (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
                        m_vk_tutorial01_parameters.getVkInstance(),
                        "vkCreateDebugUtilsMessengerEXT");

        VkResult vk_result = VK_SUCCESS;
        if (func != nullptr) {
            vk_result = func(
                    m_vk_tutorial01_parameters.getVkInstance(),
                    &vk_debug_utils_messenger_create_info_ext,
                    nullptr,
                    &m_vk_tutorial01_parameters.getVkDebugUtilsMessenger());
        } else {
            vk_result = VK_ERROR_EXTENSION_NOT_PRESENT;
        }

        response = vk_result == VK_SUCCESS;
    }

    return response;
}

bool Tutorial01::destroyDebugMessenger() {
    bool response = false;
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            m_vk_tutorial01_parameters.getVkInstance(),
            "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(m_vk_tutorial01_parameters.getVkInstance(),
             m_vk_tutorial01_parameters.getVkDebugUtilsMessenger(),
             nullptr);
        response = true;
    }

    return response;
}
}  // namespace intel_vulkan
