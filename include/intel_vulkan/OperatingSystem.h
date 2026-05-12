////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2026 intel_vulkan
// All rights reserved.
//
// Contact: mehoggan@gmail.com
//
// This software is licensed under the terms of the Your License.
// See the LICENSE file in the top-level directory.
/////////////////////////////////////////////////////////////////////////

#ifndef INTEL_VULKAN_OPERATING_SYSTEM_H
#define INTEL_VULKAN_OPERATING_SYSTEM_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <dlfcn.h>

#include <cstdlib>
#include <cstring>
#include <string>

// TODO (mehoggan@gmail.com): This file needs class and function documentation.
// It is not clear what the purpose of this file is and how it should be used.
// It seems to be a wrapper around X11 and Vulkan for cheating a window and
// rendering to it, but it is not clear how it should be used in the context of
// the rest of the codebase.

namespace intel_vulkan::os {

typedef void* LibraryHandle;

class ProjectBase {
public:
    ProjectBase();

    virtual ~ProjectBase();

    ProjectBase(const ProjectBase& other);

    ProjectBase& operator=(const ProjectBase& other);

    virtual bool readyToDraw() const;

    virtual bool onWindowSizeChanged() = 0;
    virtual bool draw() = 0;

protected:
    bool m_can_render;
};

class WindowParameters {
public:
    WindowParameters();

    Display* getDisplayPtr() const;
    Display*& getDisplayPtr();
    void setDisplayPtr(Display*& display_ptr);

    Window& getWindowHandle();

    void setWindowHandle(Window& handle);

private:
    Display* m_display_ptr;
    Window m_handle;
};

class Window {
public:
    Window();
    ~Window();

    WindowParameters getParameters() const;

    bool create(const std::string& title);
    bool renderingLoop(ProjectBase& project);

private:
    WindowParameters m_parameters;
};

}  // namespace intel_vulkan::os

#endif
