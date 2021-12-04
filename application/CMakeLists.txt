add_subdirectory(src/modules/a) # look in module_a subdirectory for CMakeLists.txt to process
add_subdirectory(src/modules/b) # look in module_a subdirectory for CMakeLists.txt to process

# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(main)

message( STATUS "Compiler path: ${CMKE_CXX_CMPILER}" )

file(GLOB SOURCES "src/*.cpp")

#Come from folder extern_libs/mysqlpp/CMakeLists.txt
get_property(MYSQLPP_OBJS GLOBAL PROPERTY MYSQLPP_OBJS )

add_executable(main ${SOURCES} ${MYSQLPP_OBJS})
#add_executable(main src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes)

# We need a1.h a2.h b1.h b2.h and the lib_a and lib_b library
target_link_libraries(main PRIVATE module_a)
target_link_libraries(main PRIVATE module_b)

# We need a1.h a2.h b1.h b2.h and the lib_a and lib_b library
target_link_libraries(main PRIVATE lib_a)
target_link_libraries(main PRIVATE lib_b)

#********* libmysqlclient C Driver *********

target_link_libraries(main PRIVATE mysql_client)
target_link_libraries(main PRIVATE mysql_services)

  #========> Dependencies from libmysqlclient.a <==========

  target_link_libraries(main PRIVATE ssl)
  target_link_libraries(main PRIVATE crypto)
  target_link_libraries(main PRIVATE pthread)
  target_link_libraries(main PRIVATE dl)
  target_link_libraries(main PRIVATE m)
  target_link_libraries(main PRIVATE z)

  #========> Dependencies from libmysqlclient.a <==========

#********* libmysqlclient C Driver *********

#********* libmysql++ C++ wrapper *********

target_link_libraries(main PRIVATE mysqlpp)

#********* libmysql++ C++ wrapper *********

#********* libpistache *********

target_link_libraries(main PRIVATE pistache)

#********* libpistache *********

# VERY Important made your executable full static linked like golang
target_link_options(main PRIVATE --static -static-libgcc -static-libstdc++)

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(main PUBLIC cxx_std_20)






#********************* Usesfull examples *************************

#****** vcpkg integration ******
#include(/home/dsistemas/Desktop/CPP/vcpkg/scripts/buildsystems/vcpkg.cmake)

#****** SQLite ******
#find_package(unofficial-sqlite3 CONFIG REQUIRED)
#find_package(libmysql CONFIG REQUIRED)
#****** SQLite ******

#****** vcpkg integration ******

# file(GLOB OBJS "/home/dsistemas/Desktop/CPP/test04/extern_libs/mysqlpp/static/*.o")

# # SET(OBJS
# #    /home/dsistemas/Desktop/CPP/test04/extern_libs/mysqlpp/static/mysqlpp_connection.o
# # )

# SET_SOURCE_FILES_PROPERTIES(
#   ${OBJS}
#   PROPERTIES
#   EXTERNAL_OBJECT true
#   GENERATED true
# )

#target_link_libraries(main ${PROJECT_SOURCE_DIR}/extern_libs/mysqlpp/static/mysqlpp_connection.o)
#target_link_libraries(main PRIVATE -L/home/dsistemas/Desktop/CPP/test04/extern_libs/mysqlpp/static/libmysqlpp_ssqls2parse.a)
#target_link_libraries(main PRIVATE mysqlpp_ssqls2parse)
#target_link_libraries(main PRIVATE mysqlpp_excommon)

#--static -static-libgcc -static-libstdc++

#****** vcpkg integration ******

#****** SQLite ******
#target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)
#target_link_libraries(main PRIVATE ${MYSQL_LIBRARIES})
#****** SQLite ******

#****** vcpkg integration ******

# function(find_static_library LIB_NAME OUT)

#   if (WIN32 OR MSVC)
#      set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
#   elseif (UNIX)
#       set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#   endif()      

#   find_library(
#       FOUND_${LIB_NAME}_STATIC
#       ${LIB_NAME}
#   )

#     if (FOUND_${LIB_NAME}_STATIC)
#         get_filename_component(ABS_FILE ${FOUND_${LIB_NAME}_STATIC} ABSOLUTE)
#     else()
#         message(SEND_ERROR "Unable to find library ${LIB_NAME}")
#     endif()

#     set(${OUT} ${ABS_FILE} PARENT_SCOPE)

# endfunction()

# find_static_library(ssl SSL)
# find_static_library(crypto CRYPTO)
# find_static_library(pthread PTHREAD)
# find_static_library(c C)
# find_static_library(c_nonshared C_NONSHARED)
# find_static_library(dl DL)
# find_static_library(m M)
# find_static_library(z Z)
