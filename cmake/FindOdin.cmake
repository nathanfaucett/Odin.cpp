cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")

include(CMakeDependentOption)
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})

include(FindSDL2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES})

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GLEW_LIBRARIES})

add_definitions(-Wall -g -std=c++0x -o3 -lSDL2_image -lGL -lGLU -lGLEW)