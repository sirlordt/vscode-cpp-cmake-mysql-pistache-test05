# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(mysql_client)

add_library(mysql_client STATIC IMPORTED GLOBAL)
#add_library(lib_b src/b1.cpp)
#add_library(mysql STATIC)

#file(GLOB STATIC "static/*.a")

SET_TARGET_PROPERTIES(mysql_client PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libmysqlclient.a)
#SET_TARGET_PROPERTIES(mysql PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libmysqlservices.a)

#find_library(mysql_client ClassLibrary ${PROJECT_SOURCE_DIR}/static/libmysqlclient.a)
#find_library(mysql_services ClassLibrary ${PROJECT_SOURCE_DIR}/static/libmysqlclient.a)

# PUBLIC needed to make both lib_b.h and lib_b library available elsewhere in project

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

#Work !!!
#include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

project(mysql_services)

add_library(mysql_services STATIC IMPORTED GLOBAL)
SET_TARGET_PROPERTIES(mysql_services PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libmysqlservices.a)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
#target_compile_features(mysql PUBLIC cxx_std_20)