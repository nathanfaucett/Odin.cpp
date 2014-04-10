cmake_minimum_required(VERSION 2.6)
project(odin)

add_executable(odin main.cpp)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(odin ${SDL2_LIBRARIES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
target_link_libraries(odin ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_definitions(`sdl2-config --cflags --libs --static-libs` -lSDL2)
add_definitions(-lGL -lGLU -lGLEW)
add_definitions(-Wall -std=c++0x)