#include "Tutorial04.h"

int main(int argc, char** argv) {
    ApiWithoutSecrets::OS::Window window;
    ApiWithoutSecrets::Tutorial04 tutorial04;

    // Window creation
    if (!window.Create("04 - Vertex Attributes")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial04.PrepareVulkan(window.GetParameters())) {
        return -1;
    }

    // Tutorial 04
    if (!tutorial04.CreateRenderPass()) {
        return -1;
    }
    if (!tutorial04.CreatePipeline()) {
        return -1;
    }
    if (!tutorial04.CreateVertexBuffer()) {
        return -1;
    }
    if (!tutorial04.CreateRenderingResources()) {
        return -1;
    }

    // Rendering loop
    if (!window.RenderingLoop(tutorial04)) {
        return -1;
    }

    return 0;
}
