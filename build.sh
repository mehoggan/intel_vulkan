#!/bin/bash

function build {
  echo "Compiling 'IntroductionToVulkan' examples..."

  mkdir build
  cd build

  if [ "$1" == "xcb" ]; then
    USE_PLATFORM=VK_USE_PLATFORM_XCB_KHR
  else
    USE_PLATFORM=VK_USE_PLATFORM_XLIB_KHR
  fi

  if [ "$2" == "release" ]; then
    BUILD_TYPE=release
  else
    BUILD_TYPE=debug
  fi

cmake ../ -DUSE_PLATFORM=$USE_PLATFORM -DCMAKE_BUILD_TYPE=$BUILD_TYPE && make -j 8 2> >(tee build.log 1>&2)

cd ..
}

if [ "$1" != "xcb" ] && [ "$1" != "x11" ]; then
  echo "Valid Usage: ./build.sh <platform> <build type>"
  echo "             <platform>   - xcb | x11"
  echo "             <build type> - release | debug (optional, default is debug)"
else
  build $1 $2
fi

