cmake_minimum_required(VERSION 3.25)
project(hw3)
set(CMAKE_CXX_STANDARD 17)

# set path for runtime and output library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# library file .hpp
include_directories(include/)

# detect fmt libraty
find_package(fmt)

# detect OpenCV
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(image_browser src/image_browser.cpp)
add_library(html_writer src/html_writer.cpp)
add_library(mat_serialize src/serialize.cpp)
add_library(convert_dataset src/convert_dataset.cpp)
add_library(kmean src/kmeans.cpp)
add_executable(main src/main.cpp)

target_link_libraries(convert_dataset mat_serialize)
target_link_libraries(main kmeans image_browser html_writer fmt::fmt stdc++fs ${OpenCV_LIBS} convert_dataset mat_serialize)
