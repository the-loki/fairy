cmake_minimum_required(VERSION 3.22)
project(fairy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

include_directories(src)

add_subdirectory(thirdparty)
add_subdirectory(src/runtime)
add_subdirectory(src/tools)