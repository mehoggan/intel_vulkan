#include "intel_vulkan/Tutorial03.h"
#include "intel_vulkan/TutorialBase.h"

int main(int /*argc*/, char** /*argv*/) {
    intel_vulkan::os::Window window;
    std::shared_ptr<intel_vulkan::TutorialBase> tutorial =
            std::make_shared<intel_vulkan::Tutorial03>();

    // Window creation
    if (!window.create("03 - First Triangle")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial->prepareVulkan(window.getParameters())) {
        return -1;
    }

    std::shared_ptr<intel_vulkan::Tutorial03> tutorial03 =
            std::dynamic_pointer_cast<intel_vulkan::Tutorial03>(tutorial);

    // Tutorial 03
    if (!tutorial03->createRenderPass()) {
        return -1;
    }
    if (!tutorial03->createFramebuffers()) {
        return -1;
    }
    if (!tutorial03->createPipeline()) {
        return -1;
    }
    if (!tutorial03->createSemaphores()) {
        return -1;
    }
    if (!tutorial03->createCommandBuffers()) {
        return -1;
    }
    if (!tutorial03->recordCommandBuffers()) {
        return -1;
    }

    // Rendering loop
    if (!window.renderingLoop(*tutorial)) {
        return -1;
    }

    return 0;
}
