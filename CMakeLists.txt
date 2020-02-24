cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(downloader CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
enable_testing()

add_subdirectory(3rdParty)
add_subdirectory(src)
