cmake_minimum_required (VERSION 2.6)
project (crimson)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

set(CMAKE_C_FLAGS "-std=gnu99")

add_subdirectory (src)
