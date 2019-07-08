# Install script for directory: /media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib" TYPE SHARED_LIBRARY FILES "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/libdarklib.so")
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/lib/libdarklib.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/activation_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/activations.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/avgpool_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/batchnorm_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/blas.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/box.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/classifier.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/col2im.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/connected_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/convolutional_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/cost_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/crnn_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/crop_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/dark_cuda.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/darkunistd.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/data.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/deconvolutional_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/demo.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/detection_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/dropout_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/gemm.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/gru_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/http_stream.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/im2col.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/image.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/image_opencv.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/list.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/local_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/lstm_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/matrix.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/maxpool_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/network.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/normalization_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/option_list.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/parser.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/region_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/reorg_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/reorg_old_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/rnn_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/route_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/shortcut_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/softmax_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/tree.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/upsample_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/utils.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/version.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/yolo_layer.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/darknet.h;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/yolo_v2_class.hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include" TYPE FILE FILES
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/activation_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/activations.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/avgpool_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/batchnorm_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/blas.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/box.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/classifier.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/col2im.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/connected_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/convolutional_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/cost_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/crnn_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/crop_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/dark_cuda.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/darkunistd.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/data.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/deconvolutional_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/demo.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/detection_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/dropout_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/gemm.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/gru_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/http_stream.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/im2col.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/image.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/image_opencv.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/list.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/local_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/lstm_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/matrix.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/maxpool_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/network.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/normalization_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/option_list.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/parser.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/region_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/reorg_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/reorg_old_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/rnn_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/route_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/shortcut_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/softmax_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/tree.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/upsample_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/utils.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/version.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/src/yolo_layer.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/darknet.h"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/include/yolo_v2_class.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet" TYPE EXECUTABLE FILES "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib")
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib"
         OLD_RPATH "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet" TYPE EXECUTABLE FILES "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet")
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/darknet")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet" TYPE EXECUTABLE FILES "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track")
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track"
         OLD_RPATH "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/uselib_track")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets.cmake"
         "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/CMakeFiles/Export/_media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet" TYPE FILE FILES "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/CMakeFiles/Export/_media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets-noconfig.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet" TYPE FILE FILES "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/CMakeFiles/Export/_media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetConfig.cmake;/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet/DarknetConfigVersion.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/share/darknet" TYPE FILE FILES
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/CMakeFiles/DarknetConfig.cmake"
    "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/DarknetConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/media/dan/DATA/Documents/Projects/nz-dev/rc-19-platform/source/src/vision/darknet/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
