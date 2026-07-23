#include "Tutorial06.h"

int main(int argc, char** argv) {
    ApiWithoutSecrets::OS::Window window;
    ApiWithoutSecrets::Tutorial06 tutorial06;

    // Window creation
    if (!window.Create("06 - Descriptor Sets")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial06.PrepareVulkan(window.GetParameters())) {
        return -1;
    }

    // Tutorial 06
    if (!tutorial06.CreateRenderingResources()) {
        return -1;
    }
    if (!tutorial06.CreateStagingBuffer()) {
        return -1;
    }
    if (!tutorial06.CreateTexture()) {
        return -1;
    }
    if (!tutorial06.CreateDescriptorSetLayout()) {
        return -1;
    }
    if (!tutorial06.CreateDescriptorPool()) {
        return -1;
    }
    if (!tutorial06.AllocateDescriptorSet()) {
        return -1;
    }
    if (!tutorial06.UpdateDescriptorSet()) {
        return -1;
    }
    if (!tutorial06.CreateRenderPass()) {
        return -1;
    }
    if (!tutorial06.CreatePipelineLayout()) {
        return -1;
    }
    if (!tutorial06.CreatePipeline()) {
        return -1;
    }
    if (!tutorial06.CreateVertexBuffer()) {
        return -1;
    }

    // Rendering loop
    if (!window.RenderingLoop(tutorial06)) {
        return -1;
    }

    return 0;
}
