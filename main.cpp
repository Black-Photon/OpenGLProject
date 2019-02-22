#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

// Prototypes

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void renderFrame(GLFWwindow *window);
GLFWwindow* init();

/**
 * Main Program
 * @return 0 for successful exit
 */
int main()
{
    GLFWwindow* window = init();
    if(window == nullptr){
        return -1;
    }

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Render
        renderFrame(window);

        // Swap buffers and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/**
 * Initialized the program, creating a basic window
 * @return The resulting window, or nullptr if error
 */
GLFWwindow* init(){
    // Sets all the window settings
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates a window object and checks it actually works
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Set's up GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // Creates the actual main viewport, and makes it adjust for window size changes
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

/**
 * Polls and processes any user input
 * @param window Window to poll
 */
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
 * Renders the screen frame
 * @param window Window to render to
 */
void renderFrame(GLFWwindow *window)
{
    // Colour example
//    glClearColor(0.239f, 0.188f, 0.318f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

    // Triangle example
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
    };

    // For Virtual Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

/**
 * DO NOT CALL
 * Called every time the viewport is updated
 * @param window Window for viewport to affect
 * @param width New viewport width
 * @param height New viewport height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}