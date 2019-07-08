cmake_minimum_required(VERSION 3.0)

set(RPI true CACHE BOOL "Compile for Rapbery Pi 3 B")
set(ORG false CACHE BOOL "Compile for Orange Pi Zero")

if(RPI OR ORG)
  set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
  set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
else()
  set(CMAKE_C_COMPILER "/usr/bin/cc")
  set(CMAKE_CXX_COMPILER "/usr/bin/c++")
endif()

project(electric-sheep)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wextra -Wall -lpthread -ljpeg -lm -lv4l2 -lv4lconvert -fPIC -ftree-vectorize -flto -fvisibility=hidden -ffast-math -Ofast")
if(RPI)
  message("Arch: ARMv8 32")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgomp -fopenmp -march=armv8-a+crc -mfpu=neon-vfpv4 -mtune=cortex-a53 -mfloat-abi=hard")
  add_definitions("-DRPI=1")
else()
  if(ORG)
    message("Arch: ARMv7 32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgomp -fopenmp -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard")
    add_definitions("-DRPI=0")
  else()
    message("Arch: AMD 64")
    add_definitions("-DRPI=0")
  endif()
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
set(DARKNET_PATH src/vision/darknet)
set(DARKNET_LIB_NAME darklib)
add_subdirectory(${DARKNET_PATH})

execute_process(
  COMMAND bash -c "echo \"$(git rev-parse --abbrev-ref HEAD)->$(git log -1 --format=%h\\ %an\\ %aE)\""
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions("-DGIT_HASH=\"${GIT_HASH}\"")

add_executable(robot src/main.cc)
add_dependencies(robot ${DARKNET_LIB_NAME})
target_link_libraries(robot ${DARKNET_LIB_NAME})
set_target_properties(robot PROPERTIES LINK_FLAGS "-Wl,-rpath,./")

if(RPI OR ORG)
  message("Skipping tests..")
else()
  add_executable(tests src/test.cc)
  add_dependencies(tests ${DARKNET_LIB_NAME})
  target_link_libraries(tests ${DARKNET_LIB_NAME})
  set_target_properties(tests PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
  add_custom_target(tests_run
    COMMAND tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running tests..."
  )
  add_dependencies(robot tests_run)
endif()
