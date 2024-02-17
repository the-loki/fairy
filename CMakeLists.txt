cmake_minimum_required(VERSION 3.22)
project(Fairy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Thirdparty/CMake/Modules")

add_subdirectory(ThirdParty)
add_subdirectory(Source/Runtime)
add_subdirectory(Source/Tools)