cmake_minimum_required(VERSION 3.12)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# Project Files
add_executable(
        OpenGLProject

        src/main.cpp

        # Library Includes
        src/glad.c
        include/glad/glad.h
        include/stb_image.h)

# GLFW / GLAD
add_subdirectory("include/glfw-3.2.1/")
include_directories(include)
include_directories(include/glfw-3.2.1/deps)
include_directories(include/glad)

# Assimp
if(WIN32)
        include_directories(include/win32)
        include_directories(include/win32/assimp)
endif()
if(UNIX)
        add_subdirectory(include/assimp)
        include_directories(include/assimp/include include/assimp/build/include)
endif()
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)

# Link all
if(WIN32)
        add_library( assimp STATIC IMPORTED src/core/PhysicsComponent.cpp src/core/headers/PhysicsComponent.h src/lightning-borders/lightning-borders.hpp src/stencil/stencil.cpp src/stencil/stencil.h)
        set_target_properties( assimp PROPERTIES IMPORTED_LOCATION "C:/Program Files/Assimp/lib/x64/assimp-vc140-mt.lib" )
endif()
target_link_libraries(OpenGLProject glfw assimp)