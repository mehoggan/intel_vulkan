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

#if !defined(OPERATING_SYSTEM_HEADER)
#define OPERATING_SYSTEM_HEADER

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <dlfcn.h>

#include <cstdlib>
#include <cstring>
#include <string>

namespace ApiWithoutSecrets::OS {

// ************************************************************ //
// LibraryHandle                                                //
//                                                              //
// Dynamic Library OS dependent type                            //
// ************************************************************ //
//
typedef void* LibraryHandle;

// ************************************************************ //
// ProjectBase                                                  //
//                                                              //
// Base class for handling window size changes and drawing      //
// ************************************************************ //
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

// ************************************************************ //
// WindowParameters                                             //
//                                                              //
// OS dependent window parameters                               //
// ************************************************************ //
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

// ************************************************************ //
// Window                                                       //
//                                                              //
// OS dependent window creation and destruction class           //
// ************************************************************ //
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

}  // namespace ApiWithoutSecrets::OS

#endif  // OPERATING_SYSTEM_HEADER
