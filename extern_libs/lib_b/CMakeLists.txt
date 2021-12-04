# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(lib_b)

#add_library(lib_b src/b1.cpp)
file(GLOB SOURCES "src/*.cpp")

add_library(lib_b ${SOURCES})

# PUBLIC needed to make both lib_b.h and lib_b library available elsewhere in project
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(lib_b PUBLIC cxx_std_20)