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
