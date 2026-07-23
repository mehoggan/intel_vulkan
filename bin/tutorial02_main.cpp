#include "intel_vulkan/Tutorial02.h"

int main(int argc, char** argv) {
    intel_vulkan::os::Window window;
    intel_vulkan::Tutorial02 tutorial02;

    // Window creation
    if (!window.create("02 - Swap chain")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial02.prepareVulkan(window.getParameters())) {
        return -1;
    }
    if (!tutorial02.createSwapChain()) {
        return -1;
    }
    if (!tutorial02.createCommandBuffers()) {
        return -1;
    }

    // Rendering loop
    if (!window.renderingLoop(tutorial02)) {
        return -1;
    }

    return 0;
}
