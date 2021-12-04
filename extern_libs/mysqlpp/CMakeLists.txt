# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(mysqlpp)

file(GLOB MYSQLPP_OBJS "object/*.o" )

# SET(OBJS
#    /home/dsistemas/Desktop/CPP/test04/extern_libs/mysqlpp/static/mysqlpp_connection.o
# )

SET_SOURCE_FILES_PROPERTIES(
                             ${MYSQLPP_OBJS}
                             PROPERTIES
                             EXTERNAL_OBJECT true
                             GENERATED true
                           )


#Work!!!
set_property(GLOBAL PROPERTY MYSQLPP_OBJS "${MYSQLPP_OBJS}")

#file(GLOB SOURCES "src/*.cpp")
#add_library(lib_b src/b1.cpp)
#add_library(mysqlpp ${SOURCES})
#add_library(${PROJECT_NAME} ${MYSQLPP_OBJS})

ADD_LIBRARY(${PROJECT_NAME} INTERFACE)

# Work!!
#ADD_LIBRARY(${PROJECT_NAME} STATIC IMPORTED GLOBAL)

#SET_TARGET_PROPERTIES(mysqlpp PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libmysqlpp_excommon.a)
# Work!!

#Work too
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

#Work too
#SET_PROPERTY(TARGET ${PROJECT_NAME} APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include)

#include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

#message(SEND_MESSAGE " => ${PROJECT_SOURCE_DIR}/include")

#target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

#target_include_directories(BEFORE SYSTEM ${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include/mysqlpp)

# PUBLIC needed to make both lib_b.h and lib_b library available elsewhere in project
#include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
#target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
#target_compile_features(mysqlpp PUBLIC cxx_std_20)

#project(mysqlpp_ssqls2parse)

#ADD_LIBRARY(mysqlpp_ssqls2parse STATIC IMPORTED GLOBAL)

#SET_TARGET_PROPERTIES(mysqlpp_ssqls2parse PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libmysqlpp_ssqls2parse.a)
