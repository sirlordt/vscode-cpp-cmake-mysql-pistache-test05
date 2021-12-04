# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

#SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/lib")

project(
    Test03
    VERSION 0.1
    DESCRIPTION "Small CMake Test03 built with VSCode")

add_subdirectory(extern_libs)  # look in hello subdirectory for CMakeLists.txt to process
add_subdirectory(application)  # look in apps subdirectory for CMakeLists.txt to process