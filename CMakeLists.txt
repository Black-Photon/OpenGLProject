cmake_minimum_required(VERSION 3.12)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# GLaDOS

include_directories(include)

add_executable(OpenGLProject
        ./main.cpp
        src/glad.c
        include/glad/glad.h
        include/stb_image.h
        classes/Shader.cpp classes/Camera.cpp classes/CubeModel.cpp classes/SquareModel.cpp classes/Model.cpp classes/LightModel.cpp)

# GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#add_subdirectory("/home/joseph/CLionProjects/OpenGLProject/include/glfw-3.2.1/")
add_subdirectory("/run/media/u1800015/USB-ALPHA/C++/OpenGLProject/include/glfw-3.2.1/")
#add_subdirectory("/home/joseph/Documents/Programming/Graphics/OpenGLProject/include/glfw-3.2.1/")
target_link_libraries(OpenGLProject glfw)


# OpenGL Stuff - Probably not necessary

#find_package(OpenGL REQUIRED)
#if(OPENGL_FOUND)
#    include_directories(${OPENGL_INCLUDE_DIR})
#    target_link_libraries(OpenGLProject ${OPENGL_gl_LIBRARY})
#endif()
#
