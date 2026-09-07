#include "intel_vulkan/Tutorial05.h"
#include "intel_vulkan/TutorialBase.h"

int main(int /*argc*/, char** /*argv*/) {
    intel_vulkan::os::Window window;
    std::shared_ptr<intel_vulkan::TutorialBase> tutorial =
            std::make_shared<intel_vulkan::Tutorial05>();

    // Window creation
    if (!window.create("05 - Staging Resources")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial->prepareVulkan(window.getParameters())) {
        return -1;
    }

    std::shared_ptr<intel_vulkan::Tutorial05> tutorial05 =
            std::dynamic_pointer_cast<intel_vulkan::Tutorial05>(tutorial);

    // Tutorial 05
    if (!tutorial05->createRenderingResources()) {
        return -1;
    }
    if (!tutorial05->createRenderPass()) {
        return -1;
    }
    if (!tutorial05->createPipeline()) {
        return -1;
    }
    if (!tutorial05->createVertexBuffer()) {
        return -1;
    }
    if (!tutorial05->createStagingBuffer()) {
        return -1;
    }
    if (!tutorial05->copyVertexData()) {
        return -1;
    }

    // Rendering loop
    if (!window.renderingLoop(*tutorial)) {
        return -1;
    }

    return 0;
}
