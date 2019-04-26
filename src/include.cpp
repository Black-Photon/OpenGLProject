#pragma once

/**
 * Includes all the required files for OpenGL to work, as well as some standard library files
 */

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <tgmath.h>
#include <cmath>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace core {

    /**
     * Checks for errors and prints them out, replacing the glCheckError function with this new one
     * @return Enum (String) representing the error that occurred
     */
    GLenum glCheckError_(const char *file, int line);
    #define glCheckError() glCheckError_(__FILE__, __LINE__)

    GLenum glCheckError_(const char *file, int line) {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR) {
            std::string error;
            switch (errorCode) {
                case GL_INVALID_ENUM:
                    error = "INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    error = "INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    error = "INVALID_OPERATION";
                    break;
                case GL_STACK_OVERFLOW:
                    error = "STACK_OVERFLOW";
                    break;
                case GL_STACK_UNDERFLOW:
                    error = "STACK_UNDERFLOW";
                    break;
                case GL_OUT_OF_MEMORY:
                    error = "OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error = "INVALID_FRAMEBUFFER_OPERATION";
                    break;
                default:
                    error = "UNKNOWN_ERROR";
                    break;
            }
            std::cout << error << " | " << file << " (" << line << ")" << std::endl;
        }
        return errorCode;
    }
}