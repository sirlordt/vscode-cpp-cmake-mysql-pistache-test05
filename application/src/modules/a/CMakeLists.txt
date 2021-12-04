# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(module_a)

file(GLOB SOURCES "*.cpp")

add_library(module_a ${SOURCES})

# PUBLIC needed to make both lib_a.h and lib_a library available elsewhere in project
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(module_a PUBLIC cxx_std_20)