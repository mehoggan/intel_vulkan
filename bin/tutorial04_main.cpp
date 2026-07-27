#include "intel_vulkan/Tutorial04.h"
#include "intel_vulkan/TutorialBase.h"

int main(int argc, char** argv) {
    intel_vulkan::os::Window window;
    std::shared_ptr<intel_vulkan::TutorialBase> tutorial =
            std::make_shared<intel_vulkan::Tutorial04>();

    // Window creation
    if (!window.create("04 - Vertex Attributes")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial->prepareVulkan(window.getParameters())) {
        return -1;
    }

    std::shared_ptr<intel_vulkan::Tutorial04> tutorial04 =
            std::dynamic_pointer_cast<intel_vulkan::Tutorial04>(tutorial);

    // Tutorial 04
    if (!tutorial04->createRenderPass()) {
        return -1;
    }
    if (!tutorial04->createPipeline()) {
        return -1;
    }
    if (!tutorial04->createVertexBuffer()) {
        return -1;
    }
    if (!tutorial04->createRenderingResources()) {
        return -1;
    }

    // Rendering loop
    if (!window.renderingLoop(*tutorial)) {
        return -1;
    }

    return 0;
}
