cmake_minimum_required(VERSION 3.25) 
project(hw3)
set(CMAKE_CXX_STANDARD 17)

# library file locn
include_directories(include/)

# detect fmt libraty
find_package(fmt)

add_library(html_writer src/html_writer.cpp)
add_executable(main src/main.cpp)

target_link_libraries(main html_writer fmt::fmt stdc++fs)