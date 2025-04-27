cmake_minimum_required(VERSION 3.15)

project(SecurityLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SecurityLib STATIC  ${CMAKE_SOURCE_DIR}/src/Security.cpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Set)
include(Install)
include(Dependecies)

# For google test
add_subdirectory(test)