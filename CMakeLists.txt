cmake_minimum_required(VERSION 3.5)

project(opengl_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(headers
    defines.h
    vertex_buffer.h
)

set(sources
    main.cpp
    vertex_buffer.cpp
)

add_executable(opengl_demo ${sources})

if(UNIX)
    target_link_libraries(opengl_demo glfw GLEW GL)
endif(UNIX)

if(WIN32)
    add_definitions(-DGLEW_STATIC)
    target_link_libraries(opengl_demo glfw3 GLEW opengl32)
endif(WIN32)
