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

#ifndef INTEL_VULKAN_TUTORIAL03_H
#define INTEL_VULKAN_TUTORIAL03_H

#include <vector>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "intel_vulkan/Tools.h"
#include "intel_vulkan/VulkanCommon.h"

namespace intel_vulkan {

// ************************************************************ //
// VulkanTutorial03Parameters                                   //
//                                                              //
// Vulkan specific parameters                                   //
// ************************************************************ //
struct VulkanTutorial03Parameters {
public:
    VulkanTutorial03Parameters();

    const VkRenderPass& getVkRenderPass() const;
    VkRenderPass& getVkRenderPass();
    void setVkRenderPass(const VkRenderPass& vk_render_pass);

    const std::vector<VkFramebuffer>& getVkFramebuffers() const;
    std::vector<VkFramebuffer>& getVkFramebuffers();
    void setVkFramebuffers(const std::vector<VkFramebuffer>& vk_framebuffers);

    const VkPipeline& getVkPipeline() const;
    VkPipeline& getVkPipeline();
    void setVkPipeline(const VkPipeline& vk_pipeline);

    const VkSemaphore& getImageAvailableVkSemaphore() const;
    VkSemaphore& getImageAvailableVkSemaphore();
    void setImageAvailableVkSemaphore(const VkSemaphore& vk_semaphore);

    const VkSemaphore& getRenderingFinishedVkSemaphore() const;
    VkSemaphore& getRenderingFinishedVkSemaphore();
    void setRenderingFinishedVkSemaphore(const VkSemaphore& vk_semaphore);

    const VkCommandPool& getVkCommandPool() const;
    VkCommandPool& getVkCommandPool();
    void setVkCommandPool(const VkCommandPool& vk_command_pool);

    const std::vector<VkCommandBuffer>& getVkCommandBuffers() const;
    std::vector<VkCommandBuffer>& getVkCommandBuffers();
    void setVkCommandBuffers(
            const std::vector<VkCommandBuffer>& vk_command_buffers);

private:
    VkRenderPass m_vk_render_pass;
    std::vector<VkFramebuffer> m_vk_framebuffers;
    VkPipeline m_vk_pipeline;
    VkSemaphore m_image_available_vk_semaphore;
    VkSemaphore m_rendering_finished_vk_semaphore;
    VkCommandPool m_vk_command_pool;
    std::vector<VkCommandBuffer> m_vk_command_buffers;
};

// ************************************************************ //
// Tutorial03                                                   //
//                                                              //
// Class for presenting Vulkan usage topics                     //
// ************************************************************ //
class Tutorial03 : public VulkanCommon {
public:
    Tutorial03();
    ~Tutorial03() override;

    bool createRenderPass();
    bool createFramebuffers();
    bool createPipeline();
    bool createSemaphores();
    bool createCommandBuffers();
    bool recordCommandBuffers();

    bool draw() override;

private:
    VulkanTutorial03Parameters m_vk_tutorial03_parameters;

    Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>
    createShaderModule(const char* filename);
    Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>
    createPipelineLayout();
    bool createCommandPool(uint32_t queue_family_index, VkCommandPool* pool);
    bool allocateCommandBuffers(VkCommandPool pool,
                                uint32_t count,
                                VkCommandBuffer* command_buffers);

    void childClear() override;
    bool childOnWindowSizeChanged() override;
};

}  // namespace intel_vulkan

#endif  // TUTORIAL_03_HEADER
