#pragma once

/**
 * Holds static data structures holding necessary information for the program
 */

#include "include.cpp"
#include "../classes/Shader.h"
#include "../classes/Camera.h"
#include "../classes/Model.h"

namespace core {

    /**
     * Holds Screen and Program data
     */
    struct Data {
        unsigned int SCR_WIDTH = 800;
        unsigned int SCR_HEIGHT = 600;
        float lastFrame = 0.0f;
        GLFWwindow *window = nullptr;
        Shader *shader3d = nullptr;
        Shader *shader2d = nullptr;
        Camera *camera = nullptr;
        std::vector<Model*> models;
    } Data;

    /**
     * Holds variables relating to mouse movement
     */
    struct Mouse {
        float lastX, lastY;
        bool first = true;
        bool rightClick = false;
        bool leftClick = false;
    } Mouse;

    /**
     * Holds path pre-pends for different locations
     */
    struct Path {
        std::string root = "../";
        std::string assets = root + "assets/";
        std::string shaders = root + "shaders/";
    } Path;

    /**
     * Indicated an error occurred while initialising
     */
    struct initialisationException : public std::exception {
        std::string s;

        explicit initialisationException(const std::string string) {
            s = string;
        }

        const char *what() const noexcept(true) override {
            return s.c_str();
        }
    };
}