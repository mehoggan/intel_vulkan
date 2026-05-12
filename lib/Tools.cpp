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

#include "intel_vulkan/Tools.h"

#include <unistd.h>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "intel_vulkan/stb_image.h"

namespace intel_vulkan::Tools {

namespace {
std::filesystem::path executableDir() {
    char exec_buf[4096];
    ssize_t nread =
            ::readlink("/proc/self/exe", exec_buf, sizeof(exec_buf) - 1);
    if (nread == -1) {
        return {};
    }
    exec_buf[nread] = '\0';
    std::filesystem::path exec_dir =
            std::filesystem::path(exec_buf).parent_path();
    if (exec_dir.filename() == ".libs") {
        exec_dir = exec_dir.parent_path();
    }
    return exec_dir;
}
}  // namespace

std::vector<char> getBinaryFileContents(std::string const& filename) {
    std::filesystem::path path(filename);
    if (!std::filesystem::exists(path)) {
        path = executableDir() / filename;
    }
    std::ifstream file(path, std::ios::binary);
    if (file.fail()) {
        std::cout << "Could not open \"" << filename << "\" file!"
                  << std::endl;
        return std::vector<char>();
    }

    std::streampos begin, end;
    begin = file.tellg();
    file.seekg(0, std::ios::end);
    end = file.tellg();

    std::vector<char> result(static_cast<size_t>(end - begin));
    file.seekg(0, std::ios::beg);
    file.read(&result[0], end - begin);
    file.close();

    return result;
}

// ************************************************************ //
// GetImageData                                                 //
//                                                              //
// Function loading image (texture) data from a specified file  //
// ************************************************************ //
std::vector<char> getImageData(std::string const& filename,
                               int requested_components,
                               int* width,
                               int* height,
                               int* components,
                               int* data_size) {
    std::vector<char> file_data = Tools::getBinaryFileContents(filename);
    if (file_data.size() == 0) {
        return std::vector<char>();
    }

    int tmp_width = 0, tmp_height = 0, tmp_components = 0;
    unsigned char* image_data = stbi_load_from_memory(
            reinterpret_cast<unsigned char*>(&file_data[0]),
            static_cast<int>(file_data.size()),
            &tmp_width,
            &tmp_height,
            &tmp_components,
            requested_components);
    if ((image_data == nullptr) || (tmp_width <= 0) || (tmp_height <= 0) ||
        (tmp_components <= 0)) {
        std::cout << "Could not read image data!" << std::endl;
        return std::vector<char>();
    }

    int size = (tmp_width) * (tmp_height) *
               (requested_components <= 0 ? tmp_components
                                          : requested_components);
    if (data_size) {
        *data_size = size;
    }
    if (width) {
        *width = tmp_width;
    }
    if (height) {
        *height = tmp_height;
    }
    if (components) {
        *components = tmp_components;
    }

    std::vector<char> output(size);
    memcpy(&output[0], image_data, size);

    stbi_image_free(image_data);
    return output;
}

// ************************************************************ //
// GetPerspectiveProjectionMatrix                               //
//                                                              //
// Function calculating perspective projection matrix           //
// ************************************************************ //
std::array<float, 16> getPerspectiveProjectionMatrix(float const aspect_ratio,
                                                     float const field_of_view,
                                                     float const near_clip,
                                                     float const far_clip) {
    float fov_value = 1.0f / std::tan(field_of_view * 0.5f *
                                      0.01745329251994329576923690768489f);

    return {fov_value / aspect_ratio,
            0.0f,
            0.0f,
            0.0f,

            0.0f,
            -fov_value,
            0.0f,
            0.0f,

            0.0f,
            0.0f,
            far_clip / (near_clip - far_clip),
            -1.0f,

            0.0f,
            0.0f,
            (near_clip * far_clip) / (near_clip - far_clip),
            0.0f};
}

std::array<float, 16> getOrthographicProjectionMatrix(float const left_plane,
                                                      float const right_plane,
                                                      float const top_plane,
                                                      float const bottom_plane,
                                                      float const near_plane,
                                                      float const far_plane) {
    return {2.0f / (right_plane - left_plane),
            0.0f,
            0.0f,
            0.0f,

            0.0f,
            2.0f / (bottom_plane - top_plane),
            0.0f,
            0.0f,

            0.0f,
            0.0f,
            1.0f / (near_plane - far_plane),
            0.0f,

            -(right_plane + left_plane) / (right_plane - left_plane),
            -(bottom_plane + top_plane) / (bottom_plane - top_plane),
            near_plane / (near_plane - far_plane),
            1.0f};
}

}  // namespace intel_vulkan::Tools
