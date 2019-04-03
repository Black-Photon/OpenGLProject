#include <cmath>

#include <iostream>
#include "include/glad/glad.h"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <tgmath.h>
#include <cmath>

// Prototypes

GLFWwindow * init();
void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow *window);
void buildImage(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);
void bindData(unsigned int VAO, unsigned int VBO, float vertices[], int length);
void draw(Shader shader, unsigned const int VAO, unsigned const int * EBO);
void prerender();

// Global Variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/**
 * Main Program
 * @return 0 for successful exit
 */
int main()
{
    GLFWwindow * window = init();
    if(window == nullptr)
    {
        return -1;
    }

    // Program
    Shader shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");

    // Vertex attribute object and Virtual Buffer Object
    unsigned int EBO;
    unsigned int VBO[1] = {};
    unsigned int VAO[1] = {};
    buildImage(VAO, VBO, &EBO);

    // Creates the actual main viewport, and makes it adjust for window size changes
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Pre-Render
        prerender();

        // Draw
        draw(shader, VAO[0], &EBO);

        // Swap buffers and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deletes VAO and VBO data from memory
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);

    glfwTerminate();
    return 0;
}

/**
 * Initialized the program, creating a basic window
 * @return The resulting window, or nullptr if error
 */
GLFWwindow * init()
{
    // Sets all the window settings
    glfwInit(); // Required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates a window object and checks it actually works
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    // Tells it what window to apply OpenGL operations to
    glfwMakeContextCurrent(window);
    // Tells OpenGL to use this function when resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Sets up GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}

/**
 * Polls and processes any user input
 * @param window Window to poll
 */
void processInput(GLFWwindow * window)
{
    // Pretty Straightforward
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
 * Builds the image putting results into values
 * @param VAO Location to save the Vertex Array Object index
 * @param VBO Location to save the Vertex Buffer Object index
 * @param EBO Location to save the Element Buffer Object index
 */
void buildImage(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO)
{
    // Triangle example
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2
    };

    // Generates the Element Buffer Object
    glGenBuffers(1, EBO);
    // Binds the buffer to the buffer type so glBufferData works on this
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    // Allocates memory for and stores the indices data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Generates a Vertex Array Object
    glGenVertexArrays(1, VAO);
    // Generates the Vertex Buffer Objects
    glGenBuffers(1, VBO);

    bindData(VAO[0], VBO[0], vertices, 18);

    // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // Unbinds the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

/**
 * Binds VAO and VBO data to the vertices passed
 * @param VAO VAO to bind
 * @param VBO VBO to use
 * @param vertices Vertices to bind to VBO
 * @param length Length of array
 */
void bindData(unsigned int VAO, unsigned int VBO, float vertices[], int length)
{
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // Binds the VAO so glVertexAttribPointer and glEnableVertexAttribArray work on this VAO
    glBindVertexArray(VAO);

    // Binds the buffer to the buffer type so glBufferData works on this
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Allocates memory for and stores the vertices data
    glBufferData(GL_ARRAY_BUFFER, length*sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    // Tells OpenGL how to interpret the vertex buffer data
    // Index, Size, Type, Normalized, Stride, Pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // Enables a generic vertex attribute at the given index
    glEnableVertexAttribArray(0);

    // Colour
    // Tells OpenGL how to interpret the vertex buffer data
    // Index, Size, Type, Normalized, Stride, Pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // Enables a generic vertex attribute at the given index
    glEnableVertexAttribArray(1);
}

float red = 1;
float green = 0;
float blue = 0;
int varyRed = 0;
int varyGreen = 1;
int varyBlue = 0;

/**
 * Pre-renders the screen creating the background and clearing the colour buffer
 */
void prerender()
{
    //float time = glfwGetTime();
    red = red + 0.01 * varyRed;
    green = green + 0.01 * varyGreen;
    blue = blue + 0.01 * varyBlue;

    if(varyGreen == 1 && green >= 1) {
        green = 1;
        varyRed = -1;
        varyGreen = 0;
        varyBlue = 0;
    } else if(varyRed == -1 && red <= 0) {
        red = 0;
        varyRed = 0;
        varyGreen = 0;
        varyBlue = 1;
    } else if(varyBlue == 1 && blue >= 1) {
        blue = 1;
        varyRed = 0;
        varyGreen = -1;
        varyBlue = 0;
    } else if(varyGreen == -1 && green <= 0) {
        green = 0;
        varyRed = 1;
        varyGreen = 0;
        varyBlue = 0;
    } else if(varyRed == 1 && red >= 1) {
        red = 1;
        varyRed = 0;
        varyGreen = 0;
        varyBlue = -1;
    } else if(varyBlue == -1 && blue <= 0) {
        blue = 0;
        varyRed = 0;
        varyGreen = 1;
        varyBlue = 0;
    }

    // Makes the screen this colour
    glClearColor(red, green, blue, 1.0f);
    // Clears the buffer with the clear colour
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * DO NOT CALL
 * Called every time the viewport is updated
 * @param window Window for viewport to affect
 * @param width New viewport width
 * @param height New viewport height
 */
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * Applies the shader program to the VAO and draws it to the buffer
 * @param shaderProgram Shader program index to draw with
 * @param VAO Array Object index to draw
 */
void draw(Shader shader, unsigned const int VAO, unsigned const int * EBO)
{
    // Sets the shader program to use
    shader.use();
    // Binds the VAO so glVertexAttribPointer and glEnableVertexAttribArray work on this VAO
    glBindVertexArray(VAO);
    // Binds the buffer to the buffer type so glBufferData works on this
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // Tells OpenGL how to render the polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Renders vertices in VBO using EBO
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}