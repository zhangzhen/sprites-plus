cmake_minimum_required(VERSION 2.8)

project(sprites2)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O2")

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(BUILD_POSTFIX "_d")
else(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(BUILD_POSTFIX "")
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

add_subdirectory(src)
add_subdirectory(test)
