cmake_minimum_required(VERSION 3.22.1)
project(edge_native)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(edge_native SHARED
    native-lib.cpp
    image_processor.cpp
)

find_library(log-lib log)
find_library(android-lib android)
find_library(jnigraphics-lib jnigraphics)

# If building with local OpenCV Android SDK, set env var:
#   OpenCV_DIR = <OpenCV-android-sdk>/sdk/native/jni
if(DEFINED ENV{OpenCV_DIR})
    set(OpenCV_DIR $ENV{OpenCV_DIR})
endif()

find_package(OpenCV REQUIRED core imgproc)

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Set OpenCV_DIR to your OpenCV-android-sdk/sdk/native/jni")
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(edge_native ${OpenCV_LIBS} ${log-lib} ${android-lib} ${jnigraphics-lib})
