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

#include "intel_vulkan/Tutorial03.h"

#include <iostream>

#include <vulkan/vulkan_core.h>

#include "intel_vulkan/VulkanFunctions.h"

namespace intel_vulkan {

VulkanTutorial03Parameters::VulkanTutorial03Parameters()
        : m_vk_render_pass(VK_NULL_HANDLE)
        , m_vk_framebuffers({})
        , m_vk_pipeline(VK_NULL_HANDLE)
        , m_image_available_vk_semaphore(VK_NULL_HANDLE)
        , m_rendering_finished_vk_semaphore(VK_NULL_HANDLE)
        , m_vk_command_pool(VK_NULL_HANDLE)
        , m_vk_command_buffers({})
        , m_vk_debug_utils_messenger(VK_NULL_HANDLE) {}

const VkRenderPass& VulkanTutorial03Parameters::getVkRenderPass() const {
    return m_vk_render_pass;
}
VkRenderPass& VulkanTutorial03Parameters::getVkRenderPass() {
    return m_vk_render_pass;
}
void VulkanTutorial03Parameters::setVkRenderPass(
        const VkRenderPass& vk_render_pass) {
    m_vk_render_pass = vk_render_pass;
}

const std::vector<VkFramebuffer>&
VulkanTutorial03Parameters::getVkFramebuffers() const {
    return m_vk_framebuffers;
}
std::vector<VkFramebuffer>& VulkanTutorial03Parameters::getVkFramebuffers() {
    return m_vk_framebuffers;
}
void VulkanTutorial03Parameters::setVkFramebuffers(
        const std::vector<VkFramebuffer>& vk_framebuffers) {
    m_vk_framebuffers = vk_framebuffers;
}

const VkPipeline& VulkanTutorial03Parameters::getVkPipeline() const {
    return m_vk_pipeline;
}
VkPipeline& VulkanTutorial03Parameters::getVkPipeline() {
    return m_vk_pipeline;
}
void VulkanTutorial03Parameters::setVkPipeline(const VkPipeline& vk_pipeline) {
    m_vk_pipeline = vk_pipeline;
}

const VkSemaphore& VulkanTutorial03Parameters::getImageAvailableVkSemaphore()
        const {
    return m_image_available_vk_semaphore;
}
VkSemaphore& VulkanTutorial03Parameters::getImageAvailableVkSemaphore() {
    return m_image_available_vk_semaphore;
}
void VulkanTutorial03Parameters::setImageAvailableVkSemaphore(
        const VkSemaphore& vk_semaphore) {
    m_image_available_vk_semaphore = vk_semaphore;
}

const VkSemaphore&
VulkanTutorial03Parameters::getRenderingFinishedVkSemaphore() const {
    return m_rendering_finished_vk_semaphore;
}
VkSemaphore& VulkanTutorial03Parameters::getRenderingFinishedVkSemaphore() {
    return m_rendering_finished_vk_semaphore;
}
void VulkanTutorial03Parameters::setRenderingFinishedVkSemaphore(
        const VkSemaphore& vk_semaphore) {
    m_rendering_finished_vk_semaphore = vk_semaphore;
}

const VkCommandPool& VulkanTutorial03Parameters::getVkCommandPool() const {
    return m_vk_command_pool;
}
VkCommandPool& VulkanTutorial03Parameters::getVkCommandPool() {
    return m_vk_command_pool;
}
void VulkanTutorial03Parameters::setVkCommandPool(
        const VkCommandPool& vk_command_pool) {
    m_vk_command_pool = vk_command_pool;
}

const std::vector<VkCommandBuffer>&
VulkanTutorial03Parameters::getVkCommandBuffers() const {
    return m_vk_command_buffers;
}
std::vector<VkCommandBuffer>&
VulkanTutorial03Parameters::getVkCommandBuffers() {
    return m_vk_command_buffers;
}
void VulkanTutorial03Parameters::setVkCommandBuffers(
        const std::vector<VkCommandBuffer>& vk_command_buffers) {
    m_vk_command_buffers = vk_command_buffers;
}

const VkDebugUtilsMessengerEXT&
VulkanTutorial03Parameters::getVkDebugUtilsMessenger() const {
    return m_vk_debug_utils_messenger;
}
VkDebugUtilsMessengerEXT&
VulkanTutorial03Parameters::getVkDebugUtilsMessenger() {
    return m_vk_debug_utils_messenger;
}
void VulkanTutorial03Parameters::setVkDebugUtilsMessenger(
        const VkDebugUtilsMessengerEXT& vk_debug_utils_messenger) {
    m_vk_debug_utils_messenger = vk_debug_utils_messenger;
}

Tutorial03::Tutorial03() {}

Tutorial03::~Tutorial03() {
    childClear();

    if (getVkDevice() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(getVkDevice());

        if (m_vulkan_tutorial03_parameters.getImageAvailableVkSemaphore() !=
            VK_NULL_HANDLE) {
            vkDestroySemaphore(getVkDevice(),
                               m_vulkan_tutorial03_parameters
                                       .getImageAvailableVkSemaphore(),
                               nullptr);
        }

        if (m_vulkan_tutorial03_parameters.getRenderingFinishedVkSemaphore() !=
            VK_NULL_HANDLE) {
            vkDestroySemaphore(getVkDevice(),
                               m_vulkan_tutorial03_parameters
                                       .getRenderingFinishedVkSemaphore(),
                               nullptr);
        }
    }
}

bool Tutorial03::createRenderPass() {
    VkAttachmentDescription attachment_descriptions[] = {
            {0,
             getSwapchainParameters().getVkFormat(),
             VK_SAMPLE_COUNT_1_BIT,
             VK_ATTACHMENT_LOAD_OP_CLEAR,
             VK_ATTACHMENT_STORE_OP_STORE,
             VK_ATTACHMENT_LOAD_OP_DONT_CARE,
             VK_ATTACHMENT_STORE_OP_DONT_CARE,
             VK_IMAGE_LAYOUT_UNDEFINED,
             VK_IMAGE_LAYOUT_PRESENT_SRC_KHR}};

    VkAttachmentReference color_attachment_references[] = {
            {0,  // uint32_t                       attachment
             VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}};

    VkSubpassDescription subpass_descriptions[] = {
            {0,
             VK_PIPELINE_BIND_POINT_GRAPHICS,
             0,
             nullptr,
             1,
             color_attachment_references,
             nullptr,
             nullptr,
             0,
             nullptr}};

    VkRenderPassCreateInfo render_pass_create_info = {
            VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            nullptr,
            0,
            1,
            attachment_descriptions,
            1,
            subpass_descriptions,
            0,
            nullptr};

    if (vkCreateRenderPass(
                getVkDevice(),
                &render_pass_create_info,
                nullptr,
                &m_vulkan_tutorial03_parameters.getVkRenderPass()) !=
        VK_SUCCESS) {
        Logging::error(LOG_TAG, "Could not create render pass!");
        return false;
    }

    return true;
}

bool Tutorial03::createFramebuffers() {
    const std::vector<ImageParameters>& swap_chain_images =
            getSwapchainParameters().getImageParameters();
    m_vulkan_tutorial03_parameters.getVkFramebuffers().resize(
            swap_chain_images.size());

    for (size_t i = 0; i < swap_chain_images.size(); ++i) {
        VkFramebufferCreateInfo framebuffer_create_info = {
                VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                nullptr,
                0,
                m_vulkan_tutorial03_parameters.getVkRenderPass(),
                1,
                &swap_chain_images[i].getVkImageView(),
                300,
                300,
                1};

        if (vkCreateFramebuffer(
                    getVkDevice(),
                    &framebuffer_create_info,
                    nullptr,
                    &m_vulkan_tutorial03_parameters.getVkFramebuffers()[i]) !=
            VK_SUCCESS) {
            Logging::error(LOG_TAG, "Could not create a framebuffer!");
            return false;
        }
    }
    return true;
}

bool Tutorial03::createPipeline() {
    Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>
            vertex_shader_module =
                    createShaderModule("Data/Tutorials/03/shader.vert.spv");
    Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>
            fragment_shader_module =
                    createShaderModule("Data/Tutorials/03/shader.frag.spv");

    if (!vertex_shader_module || !fragment_shader_module) {
        return false;
    }

    std::vector<VkPipelineShaderStageCreateInfo> shader_stage_create_infos = {
            // Vertex shader
            {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
             nullptr,
             0,
             VK_SHADER_STAGE_VERTEX_BIT,
             vertex_shader_module.Get(),
             "main",
             nullptr},
            // Fragment shader
            {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
             nullptr,
             0,
             VK_SHADER_STAGE_FRAGMENT_BIT,
             fragment_shader_module.Get(),
             "main",
             nullptr}};

    VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            nullptr,
            0,
            0,
            nullptr,
            0,
            nullptr};

    VkPipelineInputAssemblyStateCreateInfo input_assembly_state_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            nullptr,
            0,
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            VK_FALSE};

    VkViewport viewport = {0.0f, 0.0f, 300.0f, 300.0f, 0.0f, 1.0f};

    VkRect2D scissor = {{0, 0}, {300, 300}};

    VkPipelineViewportStateCreateInfo viewport_state_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            nullptr,
            0,
            1,
            &viewport,
            1,
            &scissor};

    VkPipelineRasterizationStateCreateInfo rasterization_state_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            nullptr,
            0,
            VK_FALSE,
            VK_FALSE,
            VK_POLYGON_MODE_FILL,
            VK_CULL_MODE_BACK_BIT,
            VK_FRONT_FACE_COUNTER_CLOCKWISE,
            VK_FALSE,
            0.0f,
            0.0f,
            0.0f,
            1.0f};

    VkPipelineMultisampleStateCreateInfo multisample_state_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            nullptr,
            0,
            VK_SAMPLE_COUNT_1_BIT,
            VK_FALSE,
            1.0f,
            nullptr,
            VK_FALSE,
            VK_FALSE};

    VkPipelineColorBlendAttachmentState color_blend_attachment_state = {
            VK_FALSE,
            VK_BLEND_FACTOR_ONE,
            VK_BLEND_FACTOR_ZERO,
            VK_BLEND_OP_ADD,
            VK_BLEND_FACTOR_ONE,
            VK_BLEND_FACTOR_ZERO,
            VK_BLEND_OP_ADD,
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                    VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT};

    VkPipelineColorBlendStateCreateInfo color_blend_state_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            nullptr,
            0,
            VK_FALSE,
            VK_LOGIC_OP_COPY,
            1,
            &color_blend_attachment_state,
            {0.0f, 0.0f, 0.0f, 0.0f}};

    Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>
            pipeline_layout = createPipelineLayout();
    if (!pipeline_layout) {
        return false;
    }

    VkGraphicsPipelineCreateInfo pipeline_create_info = {
            VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            nullptr,
            0,
            static_cast<uint32_t>(shader_stage_create_infos.size()),
            shader_stage_create_infos.data(),
            &vertex_input_state_create_info,
            &input_assembly_state_create_info,
            nullptr,
            &viewport_state_create_info,
            &rasterization_state_create_info,
            &multisample_state_create_info,
            nullptr,
            &color_blend_state_create_info,
            nullptr,
            pipeline_layout.Get(),
            m_vulkan_tutorial03_parameters.getVkRenderPass(),
            0,
            VK_NULL_HANDLE,
            -1};

    if (vkCreateGraphicsPipelines(
                getVkDevice(),
                VK_NULL_HANDLE,
                1,
                &pipeline_create_info,
                nullptr,
                &m_vulkan_tutorial03_parameters.getVkPipeline()) !=
        VK_SUCCESS) {
        Logging::error(LOG_TAG, "Could not create graphics pipeline!");
        return false;
    }
    return true;
}

bool Tutorial03::createSemaphores() {
    VkSemaphoreCreateInfo semaphore_create_info = {
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, nullptr, 0};

    if ((vkCreateSemaphore(getVkDevice(),
                           &semaphore_create_info,
                           nullptr,
                           &m_vulkan_tutorial03_parameters
                                    .getImageAvailableVkSemaphore()) !=
         VK_SUCCESS) ||
        (vkCreateSemaphore(getVkDevice(),
                           &semaphore_create_info,
                           nullptr,
                           &m_vulkan_tutorial03_parameters
                                    .getRenderingFinishedVkSemaphore()) !=
         VK_SUCCESS)) {
        Logging::error(LOG_TAG, "Could not create semaphores!");
        return false;
    }

    return true;
}

bool Tutorial03::createCommandBuffers() {
    if (!createCommandPool(
                getGraphicsQueueParameters().getFamilyIndex(),
                &m_vulkan_tutorial03_parameters.getVkCommandPool())) {
        Logging::error(LOG_TAG, "Could not create command pool!");
        return false;
    }

    uint32_t image_count = static_cast<uint32_t>(
            getSwapchainParameters().getImageParameters().size());
    m_vulkan_tutorial03_parameters.setVkCommandBuffers(
            std::vector<VkCommandBuffer>(image_count, VK_NULL_HANDLE));

    if (!allocateCommandBuffers(
                m_vulkan_tutorial03_parameters.getVkCommandPool(),
                image_count,
                m_vulkan_tutorial03_parameters.getVkCommandBuffers().data())) {
        Logging::error(LOG_TAG, "Could not allocate command buffers!");
        return false;
    }
    return true;
}

bool Tutorial03::recordCommandBuffers() {
    VkCommandBufferBeginInfo graphics_command_buffer_begin_info = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            nullptr,
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
            nullptr};

    VkImageSubresourceRange image_subresource_range = {
            VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

    VkClearValue clear_value{{1.0f, 0.8f, 0.4f, 0.0f}};

    const std::vector<ImageParameters>& swap_chain_images =
            getSwapchainParameters().getImageParameters();

    for (size_t i = 0;
         i < m_vulkan_tutorial03_parameters.getVkCommandBuffers().size();
         ++i) {
        vkBeginCommandBuffer(
                m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i],
                &graphics_command_buffer_begin_info);

        if (getPresentQueueParameters().getVkQueue() !=
            getGraphicsQueueParameters().getVkQueue()) {
            VkImageMemoryBarrier barrier_from_present_to_draw = {
                    VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                    nullptr,
                    VK_ACCESS_MEMORY_READ_BIT,
                    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                    VK_IMAGE_LAYOUT_UNDEFINED,
                    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                    getPresentQueueParameters().getFamilyIndex(),
                    getGraphicsQueueParameters().getFamilyIndex(),
                    swap_chain_images[i].getVkImage(),
                    image_subresource_range};
            vkCmdPipelineBarrier(
                    m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i],
                    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                    0,
                    0,
                    nullptr,
                    0,
                    nullptr,
                    1,
                    &barrier_from_present_to_draw);
        }

        VkRenderPassBeginInfo render_pass_begin_info = {
                VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                nullptr,
                m_vulkan_tutorial03_parameters.getVkRenderPass(),
                m_vulkan_tutorial03_parameters.getVkFramebuffers()[i],
                {{0, 0}, {300, 300}},
                1,
                &clear_value};

        vkCmdBeginRenderPass(
                m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i],
                &render_pass_begin_info,
                VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(
                m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i],
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                m_vulkan_tutorial03_parameters.getVkPipeline());

        vkCmdDraw(m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i],
                  3,
                  1,
                  0,
                  0);

        vkCmdEndRenderPass(
                m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i]);

        if (getGraphicsQueueParameters().getVkQueue() !=
            getPresentQueueParameters().getVkQueue()) {
            VkImageMemoryBarrier barrier_from_draw_to_present = {
                    VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                    nullptr,
                    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                    VK_ACCESS_MEMORY_READ_BIT,
                    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                    getGraphicsQueueParameters().getFamilyIndex(),
                    getPresentQueueParameters().getFamilyIndex(),
                    swap_chain_images[i].getVkImage(),
                    image_subresource_range};
            vkCmdPipelineBarrier(
                    m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i],
                    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                    VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                    0,
                    0,
                    nullptr,
                    0,
                    nullptr,
                    1,
                    &barrier_from_draw_to_present);
        }
        if (vkEndCommandBuffer(
                    m_vulkan_tutorial03_parameters.getVkCommandBuffers()[i]) !=
            VK_SUCCESS) {
            Logging::error(LOG_TAG, "Could not record command buffer!");
            return false;
        }
    }
    return true;
}

bool Tutorial03::draw() {
    VkSwapchainKHR swap_chain = getSwapchainParameters().getVkSwapchainKhr();
    uint32_t image_index;

    VkResult result = vkAcquireNextImageKHR(
            getVkDevice(),
            swap_chain,
            UINT64_MAX,
            m_vulkan_tutorial03_parameters.getImageAvailableVkSemaphore(),
            VK_NULL_HANDLE,
            &image_index);
    switch (result) {
        case VK_SUCCESS:
        case VK_SUBOPTIMAL_KHR:
            break;
        case VK_ERROR_OUT_OF_DATE_KHR:
            return onWindowSizeChanged();
        default:
            Logging::error(
                    LOG_TAG,
                    "Problem occurred during swap chain image acquisition!");
            return false;
    }

    VkPipelineStageFlags wait_dst_stage_mask =
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submit_info = {
            VK_STRUCTURE_TYPE_SUBMIT_INFO,
            nullptr,
            1,
            &m_vulkan_tutorial03_parameters.getImageAvailableVkSemaphore(),
            &wait_dst_stage_mask,
            1,
            &m_vulkan_tutorial03_parameters.getVkCommandBuffers()[image_index],
            1,
            &m_vulkan_tutorial03_parameters.getRenderingFinishedVkSemaphore()};

    if (vkQueueSubmit(getGraphicsQueueParameters().getVkQueue(),
                      1,
                      &submit_info,
                      VK_NULL_HANDLE) != VK_SUCCESS) {
        return false;
    }

    VkPresentInfoKHR present_info = {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            nullptr,
            1,
            &m_vulkan_tutorial03_parameters.getRenderingFinishedVkSemaphore(),
            1,
            &swap_chain,
            &image_index,
            nullptr};
    result = vkQueuePresentKHR(getPresentQueueParameters().getVkQueue(),
                               &present_info);

    switch (result) {
        case VK_SUCCESS:
            break;
        case VK_ERROR_OUT_OF_DATE_KHR:
        case VK_SUBOPTIMAL_KHR:
            return onWindowSizeChanged();
        default:
            Logging::error(LOG_TAG,
                           "Problem occurred during image presentation!");
            return false;
    }

    return true;
}

Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>
Tutorial03::createShaderModule(const char* filename) {
    const std::vector<char> code = Tools::GetBinaryFileContents(filename);
    if (code.size() == 0) {
        return Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>();
    }

    VkShaderModuleCreateInfo shader_module_create_info = {
            VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            nullptr,
            0,
            code.size(),
            reinterpret_cast<const uint32_t*>(code.data())};

    VkShaderModule shader_module;
    if (vkCreateShaderModule(getVkDevice(),
                             &shader_module_create_info,
                             nullptr,
                             &shader_module) != VK_SUCCESS) {
        Logging::error(LOG_TAG,
                       "Could not create shader module from a \"",
                       filename,
                       "\" file!");
        return Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>();
    }

    return Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>(
            shader_module, vkDestroyShaderModule, getVkDevice());
}

Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>
Tutorial03::createPipelineLayout() {
    VkPipelineLayoutCreateInfo layout_create_info = {
            VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            nullptr,
            0,
            0,
            nullptr,
            0,
            nullptr};

    VkPipelineLayout pipeline_layout;
    if (vkCreatePipelineLayout(getVkDevice(),
                               &layout_create_info,
                               nullptr,
                               &pipeline_layout) != VK_SUCCESS) {
        Logging::error(LOG_TAG, "Could not create pipeline layout!");
        return Tools::AutoDeleter<VkPipelineLayout,
                                  PFN_vkDestroyPipelineLayout>();
    }

    return Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>(
            pipeline_layout, vkDestroyPipelineLayout, getVkDevice());
}

bool Tutorial03::createCommandPool(uint32_t queue_family_index,
                                   VkCommandPool* pool) {
    VkCommandPoolCreateInfo cmd_pool_create_info = {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            nullptr,
            0,
            queue_family_index};

    if (vkCreateCommandPool(
                getVkDevice(), &cmd_pool_create_info, nullptr, pool) !=
        VK_SUCCESS) {
        return false;
    }
    return true;
}

bool Tutorial03::allocateCommandBuffers(VkCommandPool pool,
                                        uint32_t count,
                                        VkCommandBuffer* command_buffers) {
    VkCommandBufferAllocateInfo command_buffer_allocate_info = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            nullptr,
            pool,
            VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            count};

    if (vkAllocateCommandBuffers(getVkDevice(),
                                 &command_buffer_allocate_info,
                                 command_buffers) != VK_SUCCESS) {
        return false;
    }
    return true;
}

void Tutorial03::childClear() {
    if (getVkDevice() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(getVkDevice());

        if ((m_vulkan_tutorial03_parameters.getVkCommandBuffers().size() >
             0) &&
            (m_vulkan_tutorial03_parameters.getVkCommandBuffers()[0] !=
             VK_NULL_HANDLE)) {
            vkFreeCommandBuffers(
                    getVkDevice(),
                    m_vulkan_tutorial03_parameters.getVkCommandPool(),
                    static_cast<uint32_t>(m_vulkan_tutorial03_parameters
                                                  .getVkCommandBuffers()
                                                  .size()),
                    m_vulkan_tutorial03_parameters.getVkCommandBuffers()
                            .data());
            m_vulkan_tutorial03_parameters.getVkCommandBuffers().clear();
        }

        if (m_vulkan_tutorial03_parameters.getVkCommandPool() !=
            VK_NULL_HANDLE) {
            vkDestroyCommandPool(
                    getVkDevice(),
                    m_vulkan_tutorial03_parameters.getVkCommandPool(),
                    nullptr);
            m_vulkan_tutorial03_parameters.getVkCommandPool() = VK_NULL_HANDLE;
        }

        if (m_vulkan_tutorial03_parameters.getVkPipeline() != VK_NULL_HANDLE) {
            vkDestroyPipeline(getVkDevice(),
                              m_vulkan_tutorial03_parameters.getVkPipeline(),
                              nullptr);
            m_vulkan_tutorial03_parameters.getVkPipeline() = VK_NULL_HANDLE;
        }

        if (m_vulkan_tutorial03_parameters.getVkRenderPass() !=
            VK_NULL_HANDLE) {
            vkDestroyRenderPass(
                    getVkDevice(),
                    m_vulkan_tutorial03_parameters.getVkRenderPass(),
                    nullptr);
            m_vulkan_tutorial03_parameters.getVkRenderPass() = VK_NULL_HANDLE;
        }

        for (size_t i = 0;
             i < m_vulkan_tutorial03_parameters.getVkFramebuffers().size();
             ++i) {
            if (m_vulkan_tutorial03_parameters.getVkFramebuffers()[i] !=
                VK_NULL_HANDLE) {
                vkDestroyFramebuffer(
                        getVkDevice(),
                        m_vulkan_tutorial03_parameters.getVkFramebuffers()[i],
                        nullptr);
                m_vulkan_tutorial03_parameters.getVkFramebuffers()[i] =
                        VK_NULL_HANDLE;
            }
        }
        m_vulkan_tutorial03_parameters.getVkFramebuffers().clear();
    }
}

bool Tutorial03::childOnWindowSizeChanged() {
    if (!createRenderPass()) {
        return false;
    }
    if (!createFramebuffers()) {
        return false;
    }
    if (!createPipeline()) {
        return false;
    }
    if (!createCommandBuffers()) {
        return false;
    }
    if (!recordCommandBuffers()) {
        return false;
    }

    return true;
}

}  // namespace intel_vulkan
