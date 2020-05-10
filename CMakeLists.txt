cmake_minimum_required(VERSION 2.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(SymbolicComputation)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Enable C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-enum-compare -Wno-deprecated-declarations")

# Find the libraries

find_package(EIGEN REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS})

set(SYMBCOMP_LIB  "SymbolicComputation")

add_subdirectory(src/)
