cmake_minimum_required(VERSION 2.8)

include(CMakeDependentOption)
option(EMSCRIPTEN "EMSCRIPTEN" FALSE)

if (EMSCRIPTEN)
 set(CMAKE_C_FLAGS " ")
 set(CMAKE_CXX_FLAGS " ")

 set(CMAKE_C_COMPILER   /home/nathan/emscripten/emcc)
 set(CMAKE_CXX_COMPILER /home/nathan/emscripten/em++)
endif(EMSCRIPTEN)

include(FindSDL2)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARY})

include(FindSDL2_image)
include_directories(${SDLIMAGE_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDLIMAGE_LIBRARY})

include(FindOpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES})

include(FindGLEW)
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GLEW_LIBRARY})

if (NOT EMSCRIPTEN)
 set(CMAKE_C_COMPILER   gcc)
 set(CMAKE_CXX_COMPILER g++)

 set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")
 add_definitions(-lSDL2 -lSDL2_image -lGL -lGLU -lGLEW)
endif(NOT EMSCRIPTEN)

add_definitions(-Wall -Wwrite-strings -g -std=c++1y)