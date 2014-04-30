cmake_minimum_required(VERSION 2.8)

project(Odin)
add_executable(Odin main.cpp)

include(CMakeDependentOption)
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(Odin ${SDL2_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(Odin ${OPENGL_LIBRARIES})

add_definitions(-Wall -g -std=c++0x -lGL -lGLU -lGLEW)