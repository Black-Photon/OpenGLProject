#pragma once

/**
 * Holds static data structures holding necessary information for the program
 */

namespace core {

    /**
     * Holds Screen and Program data
     */
    struct Data {
        unsigned int SCR_WIDTH = 800;
        unsigned int SCR_HEIGHT = 600;
        float lastFrame = 0.0f;
        GLFWwindow *window = nullptr;
        std::unique_ptr<Camera> camera = nullptr;

        float distanceOpen = 1.0f;
        bool closed = false;
        bool ctrlPressed = false;
        Texture black;
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
        const std::string root = "../";
        const std::string source = root + "src/";
        const std::string assets = root + "assets/";
        const std::string shaders = source + "shaders/";
        const std::string texture = assets + "textures/";
        const std::string models = assets + "models/";
    } Path;

    /**
     * Indicated an error occurred while initialising
     */
    struct initialisationException : public std::exception {
        std::string s;

        explicit initialisationException(const std::string &string) {
            s = string;
        }

        const char *what() const noexcept(true) override {
            return s.c_str();
        }
    };
}