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

#if !defined(OPERATING_SYSTEM_HEADER)
#define OPERATING_SYSTEM_HEADER

#if defined(VK_USE_PLATFORM_WIN32_KHR)
#include <Windows.h>

#elif defined(VK_USE_PLATFORM_XCB_KHR)
#include <dlfcn.h>
#include <xcb/xcb.h>

#include <cstdlib>

#elif defined(VK_USE_PLATFORM_XLIB_KHR)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <dlfcn.h>

#include <cstdlib>

#endif

#include <cstring>

namespace ApiWithoutSecrets::OS {

// ************************************************************ //
// LibraryHandle                                                //
//                                                              //
// Dynamic Library OS dependent type                            //
// ************************************************************ //
//
#if defined(VK_USE_PLATFORM_WIN32_KHR)
typedef HMODULE LibraryHandle;

#elif defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
typedef void* LibraryHandle;

#endif

// ************************************************************ //
// ProjectBase                                                  //
//                                                              //
// Base class for handling window size changes and drawing      //
// ************************************************************ //
class ProjectBase {
public:
    virtual bool onWindowSizeChanged() = 0;
    virtual bool draw() = 0;

    virtual bool readyToDraw() const { return m_can_render; }

    ProjectBase() : m_can_render(false) {}

    virtual ~ProjectBase() {}

protected:
    bool m_can_render;
};

// ************************************************************ //
// WindowParameters                                             //
//                                                              //
// OS dependent window parameters                               //
// ************************************************************ //
struct WindowParameters {
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    HINSTANCE Instance;
    HWND Handle;

    WindowParameters() : Instance(), Handle() {}

#elif defined(VK_USE_PLATFORM_XCB_KHR)
    xcb_connection_t* Connection;
    xcb_window_t Handle;

    WindowParameters() : Connection(), Handle() {}

#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    Display* DisplayPtr;
    Window Handle;

    WindowParameters() : DisplayPtr(), Handle() {}

#endif
};

// ************************************************************ //
// Window                                                       //
//                                                              //
// OS dependent window creation and destruction class           //
// ************************************************************ //
class Window {
public:
    Window();
    ~Window();

    bool Create(const char* title);
    bool RenderingLoop(ProjectBase& project) const;
    WindowParameters GetParameters() const;

private:
    WindowParameters Parameters;
};

}  // namespace ApiWithoutSecrets::OS

#endif  // OPERATING_SYSTEM_HEADER
