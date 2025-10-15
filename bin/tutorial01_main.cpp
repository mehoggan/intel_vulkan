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

#include "intel_vulkan/Tutorial01.h"

int main(int argc, char** argv) {
    intel_vulkan::os::Window window;
    intel_vulkan::Tutorial01 tutorial01(true);

    // Window creation
    if (!window.create("01 - The Beginning")) {
        return -1;
    }

    // Vulkan preparations and initialization
    if (!tutorial01.prepareVulkan()) {
        return -1;
    }

    // Rendering loop
    if (!window.renderingLoop(tutorial01)) {
        return -1;
    }

    return 0;
}
