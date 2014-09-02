cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(MeshLoader)

set(CMAKE_MODULE_PATH
  "${MeshLoader_SOURCE_DIR}/CMake"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# FIND SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
#link_directories(${SDL_LIBRARY_DIRS})
#add_definitions(${SDL_DEFINITIONS})
if(NOT SDL2_FOUND)
    message(ERROR " SDL2 not found!")
endif(NOT SDL2_FOUND)

# FIND OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


add_executable(MeshLoader main.cc util.cc model.cpp)
target_link_libraries(MeshLoader ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} )
