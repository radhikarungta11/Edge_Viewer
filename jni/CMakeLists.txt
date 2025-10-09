cmake_minimum_required(VERSION 3.18)
project(image_processor)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")

# Pass -DOpenCV_DIR=/absolute/path/to/OpenCV-android-sdk/sdk/native/jni
if (NOT DEFINED OpenCV_DIR)
  message(WARNING "OpenCV_DIR not set; pass -DOpenCV_DIR=<...>/sdk/native/jni from Gradle")
endif()
find_package(OpenCV REQUIRED)

add_library(image_processor SHARED image_processor.cpp)
target_include_directories(image_processor PRIVATE ${OpenCV_INCLUDE_DIRS})

find_library(log-lib log)
find_library(android-lib android)
find_library(glesv2-lib GLESv2)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(image_processor
  ${OpenCV_LIBS}
  ${log-lib}
  ${jnigraphics-lib}
  ${android-lib}
  ${glesv2-lib}
)

