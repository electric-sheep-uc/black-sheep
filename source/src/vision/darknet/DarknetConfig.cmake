# Config file for the Darknet package
# It defines the following variables
#  Darknet_INCLUDE_DIRS - include directories for Darknet
#  Darknet_LIBRARIES    - libraries to link against

# Compute paths
get_filename_component(Darknet_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(Darknet_INCLUDE_DIRS "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet")
list(APPEND CMAKE_MODULE_PATH "${Darknet_CMAKE_DIR}")

include(CMakeFindDependencyMacro)

if(TRUE)
  find_dependency(OpenCV REQUIRED)
  add_definitions(-DOPENCV)
endif()

find_dependency(Stb REQUIRED)

if(FALSE)
  find_dependency(CUDNN)
  add_definitions(-DGPU)
  if(CUDNN_FOUND)
    add_definitions(-DCUDNN)
    if(0 VERSION_GREATER_EQUAL 70)
      add_definitions(-DCUDNN_HALF)
      message(STATUS "Enabled CUDNN_HALF")
    endif()
  endif()
endif()

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_dependency(Threads)

if(MSVC)
  find_dependency(PThreads_windows)
endif()

if("${CMAKE_VERSION}" VERSION_GREATER "3.9.0")
  find_dependency(OpenMP)
endif()

# Our library dependencies (contains definitions for IMPORTED targets)
include("${Darknet_CMAKE_DIR}/DarknetTargets.cmake")

# These are IMPORTED targets created by DarknetTargets.cmake
set(Darknet_LIBRARIES darklib)
