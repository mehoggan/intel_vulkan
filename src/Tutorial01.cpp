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

#include <climits>
#include <cstdint>
#include <functional>
#include <vector>

#include "intel_vulkan/Logging.h"
#include "intel_vulkan/VulkanFunctions.h"

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
        : LoggedClass<Tutorial01>(*this)
        , m_vk_library_handle()
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
            Logging::error(LOG_TAG,
                           "Failed to destroy VkDebugUtilsMessengerExt!!!");
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
        Logging::error(LOG_TAG, "Could not load Vulkan library!");
        return false;
    }
    return true;
}

bool Tutorial01::loadExportedEntryPoints() {
#define LoadProcAddress dlsym

#define VK_EXPORTED_FUNCTION(fun)                                         \
    if (m_enable_vk_debug) {                                              \
        Logging::info(LOG_TAG, "Loading entry point", #fun, "...");       \
    }                                                                     \
    if (!(fun = (PFN_##fun)LoadProcAddress(m_vk_library_handle, #fun))) { \
        Logging::error(                                                   \
                LOG_TAG, "Could not load exported function:", #fun, "!"); \
        return false;                                                     \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::loadGlobalLevelEntryPoints() {
#define VK_GLOBAL_LEVEL_FUNCTION(fun)                                         \
    if (m_enable_vk_debug) {                                                  \
        Logging::info(LOG_TAG, "Loading global", #fun, "...");                \
    }                                                                         \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(nullptr, #fun))) {           \
        Logging::error(                                                       \
                LOG_TAG, "Could not load global level function:", #fun, "!"); \
        return false;                                                         \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::createInstance() {
    if (!checkValidationLayerSupport()) {
        Logging::error(LOG_TAG,
                       "Failed to create an instance that does not support",
                       "validation layers.");
        return false;
    }

    std::function<std::vector<const char*>()> get_required_extensions =
            []() -> std::vector<const char*> {
        return {VK_EXT_DEBUG_UTILS_EXTENSION_NAME};
    };

    std::uint32_t vk_version = VK_MAKE_VERSION(1, 3, 0);
    std::uint32_t engine_version = VK_MAKE_VERSION(1, 0, 0);

    VkApplicationInfo application_info{};
    application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pNext = nullptr;
    application_info.pApplicationName =
            "API without Secrets: Introduction to Vulkan";
    application_info.applicationVersion = vk_version;
    application_info.pEngineName = "Vulkan Tutorial by Intel";
    application_info.engineVersion = engine_version;
    application_info.apiVersion = vk_version;

    std::vector<const char*> vk_extensions =
            (m_enable_vk_debug ? get_required_extensions()
                               : std::vector<const char*>{});
    Logging::info(LOG_TAG,
                  "Creating an instance with the following extensions",
                  vk_extensions);

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
        Logging::error(LOG_TAG, "Could not create Vulkan instance!");
        return false;
    }

    if (!setupDebugMessenger()) {
        Logging::error(LOG_TAG, "Failed to setup debug messenger!!!");
    }

    return true;
}

bool Tutorial01::loadInstanceLevelEntryPoints() {
#define VK_INSTANCE_LEVEL_FUNCTION(fun)                                 \
    if (m_enable_vk_debug) {                                            \
        Logging::info(LOG_TAG, "Loading instance", #fun, "...");        \
    }                                                                   \
    if (!(fun = (PFN_##fun)vkGetInstanceProcAddr(                       \
                  m_vk_tutorial01_parameters.getVkInstance(), #fun))) { \
        Logging::error(LOG_TAG,                                         \
                       "Could not load instance level function:",       \
                       #fun,                                            \
                       "!");                                            \
        return false;                                                   \
    }

#include "intel_vulkan/ListOfFunctions.inl"

    return true;
}

bool Tutorial01::createDevice() {
    std::uint32_t num_devices = 0;
    if ((vkEnumeratePhysicalDevices(m_vk_tutorial01_parameters.getVkInstance(),
                                    &num_devices,
                                    nullptr) != VK_SUCCESS) ||
        (num_devices == 0)) {
        Logging::error(LOG_TAG,
                       "Error occurred during physical devices enumeration!");
        return false;
    }

    std::vector<VkPhysicalDevice> vk_physical_devices(num_devices);
    if (vkEnumeratePhysicalDevices(m_vk_tutorial01_parameters.getVkInstance(),
                                   &num_devices,
                                   vk_physical_devices.data()) != VK_SUCCESS) {
        Logging::error(LOG_TAG,
                       "Error occurred during physical devices enumeration!");
        return false;
    }

    VkPhysicalDevice vk_physical_device = VK_NULL_HANDLE;
    std::uint32_t selected_queue_family_index =
            std::numeric_limits<std::uint32_t>::max();
    for (std::uint32_t i = 0; i < num_devices; ++i) {
        if (checkPhysicalDeviceProperties(vk_physical_devices[i],
                                          selected_queue_family_index)) {
            vk_physical_device = vk_physical_devices[i];
            break;
        }
    }
    if (vk_physical_device == VK_NULL_HANDLE) {
        Logging::error(LOG_TAG,
                       "Could not select physical device based on the chosen "
                       "properties!");
        return false;
    }

    std::vector<float> queue_priorities = {1.0f};

    VkDeviceQueueCreateInfo vk_queue_create_info{};
    vk_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vk_queue_create_info.pNext = nullptr;
    vk_queue_create_info.flags = 0;
    vk_queue_create_info.queueFamilyIndex = selected_queue_family_index;
    vk_queue_create_info.queueCount =
            static_cast<std::uint32_t>(queue_priorities.size());
    vk_queue_create_info.pQueuePriorities = queue_priorities.data();

    VkDeviceCreateInfo vk_device_create_info{};
    vk_device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vk_device_create_info.pNext = nullptr;
    vk_device_create_info.flags = 0;
    vk_device_create_info.queueCreateInfoCount = 1;
    vk_device_create_info.pQueueCreateInfos = &vk_queue_create_info;
    vk_device_create_info.enabledLayerCount = 0;
    vk_device_create_info.ppEnabledLayerNames = nullptr;
    vk_device_create_info.enabledExtensionCount = 0;
    vk_device_create_info.ppEnabledExtensionNames = nullptr;
    vk_device_create_info.pEnabledFeatures = nullptr;

    if (vkCreateDevice(vk_physical_device,
                       &vk_device_create_info,
                       nullptr,
                       &m_vk_tutorial01_parameters.getVkDevice()) !=
        VK_SUCCESS) {
        Logging::error(LOG_TAG, "Could not create Vulkan device!");
        return false;
    }

    m_vk_tutorial01_parameters.setQueueFamilyIndex(
            selected_queue_family_index);
    return true;
}

bool Tutorial01::checkPhysicalDeviceProperties(
        VkPhysicalDevice physical_device, uint32_t& queue_family_index) {
    // TODO(mehoggan@gmail.com): Rename variable and refactor starting here.
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;

    vkGetPhysicalDeviceProperties(physical_device, &device_properties);
    vkGetPhysicalDeviceFeatures(physical_device, &device_features);

    std::int32_t major_version =
            VK_VERSION_MAJOR(device_properties.apiVersion);

    if ((major_version < 1) ||
        (device_properties.limits.maxImageDimension2D < 4096)) {
        Logging::error(LOG_TAG,
                       "Physical device",
                       physical_device,
                       "doesn't support required parameters!");
        return false;
    }

    uint32_t queue_families_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
            physical_device, &queue_families_count, nullptr);
    if (queue_families_count == 0) {
        Logging::error(LOG_TAG,
                       "Physical device",
                       physical_device,
                       "doesn't have any queue families!");
        return false;
    }

    std::vector<VkQueueFamilyProperties> queue_family_properties(
            queue_families_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,
                                             &queue_families_count,
                                             queue_family_properties.data());
    bool found = false;
    for (std::uint32_t i = 0; i < queue_families_count; ++i) {
        if ((queue_family_properties[i].queueCount > 0) &&
            (queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            queue_family_index = i;
            Logging::info(
                    LOG_TAG, "Selected device:", device_properties.deviceName);
            found = true;
            break;
        }
    }

    if (!found) {
        Logging::error(
                LOG_TAG,
                "Could not find queue family with required properties on",
                "physical device",
                physical_device,
                "!");
    }

    return found;
}

bool Tutorial01::loadDeviceLevelEntryPoints() {
#define VK_DEVICE_LEVEL_FUNCTION(fun)                                         \
    if (m_enable_vk_debug) {                                                  \
        Logging::info(LOG_TAG, "Loading device", #fun, "...");                \
    }                                                                         \
    if (!(fun = (PFN_##fun)vkGetDeviceProcAddr(                               \
                  m_vk_tutorial01_parameters.getVkDevice(), #fun))) {         \
        Logging::error(                                                       \
                LOG_TAG, "Could not load device level function:", #fun, "!"); \
        return false;                                                         \
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
    Logging::info(LOG_TAG, "The vk_instance has the following properties:");
    Logging::info(LOG_TAG, vk_layer_properties);

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
            Logging::error(LOG_TAG,
                           "The following layer \"",
                           layer_name,
                           "\""
                           "could not be loaded!!!");
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
    static LogTag debug_log_tag("DebugCallback");
    static std::atomic<bool> log_tag_created(false);
    if (!log_tag_created.load()) {
        Logging::addStdCerrLogger(debug_log_tag);
        log_tag_created.store(true);
    }

    Logging::error(debug_log_tag,
                   "validation layer:",
                   vk_debug_utils_messenger_callback_data_ext->pMessage);

    return VK_FALSE;
}

bool Tutorial01::setupDebugMessenger() {
    bool response = false;
    if (!m_enable_vk_debug.load()) {
        response = true;
    } else {
        Logging::info(LOG_TAG, "Setting up Vulkan debugger...");
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
