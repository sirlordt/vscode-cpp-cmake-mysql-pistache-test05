# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(pistache)

add_library(pistache STATIC IMPORTED GLOBAL)
#add_library(lib_b src/b1.cpp)
#add_library(mysql STATIC)

#file(GLOB STATIC "static/*.a")

SET_TARGET_PROPERTIES(pistache PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libpistache.a)
#SET_TARGET_PROPERTIES(mysql PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libmysqlservices.a)

#find_library(mysql_client ClassLibrary ${PROJECT_SOURCE_DIR}/static/libmysqlclient.a)
#find_library(mysql_services ClassLibrary ${PROJECT_SOURCE_DIR}/static/libmysqlclient.a)

# PUBLIC needed to make both lib_b.h and lib_b library available elsewhere in project

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

#Work !!!
#include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
