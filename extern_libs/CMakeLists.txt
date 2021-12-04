# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(external_libs)

add_subdirectory(lib_a)     # look in lib_a subdirectory for CMakeLists.txt to process
add_subdirectory(lib_b)     # look in lib_a subdirectory for CMakeLists.txt to process
add_subdirectory(mysql)     # look in lib_a subdirectory for CMakeLists.txt to process
add_subdirectory(mysqlpp)   # look in lib_a subdirectory for CMakeLists.txt to process
add_subdirectory(pistache)   # look in lib_a subdirectory for CMakeLists.txt to process
