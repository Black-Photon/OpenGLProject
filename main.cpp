#include <cmath>

#include <iostream>
#include "include/glad/glad.h"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <tgmath.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Prototypes

GLFWwindow * init();
void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow *window);
void buildImage(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);
void bindData(unsigned int VAO, unsigned int VBO, float vertices[], int length);
void draw(Shader shader, unsigned const int VAO, unsigned const int * EBO, unsigned const int texture[]);
void prerender();
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
void generateTexture(unsigned int * texture, const char * path, bool isPNG);
void makeModel(Shader shader);

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

    glEnable(GL_DEPTH_TEST);

    // Program
    Shader shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");

    unsigned int texture[2];

    stbi_set_flip_vertically_on_load(true);
    generateTexture(texture, "../assets/container.jpg", false);
    generateTexture(texture + 1, "../assets/awesomeface.png", true);

    shader.use(); // Must activate shader to use uniforms
    shader.setInt("ourTexture", 0);
    shader.setInt("otherTexture", 1);

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
        draw(shader, VAO[0], &EBO, texture);

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

float percent = 0.2;

/**
 * Polls and processes any user input
 * @param window Window to poll
 */
void processInput(GLFWwindow * window)
{
    // Pretty Straightforward
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        percent+=0.01;

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        percent-=0.01;

    if(percent < 0) percent = 0;
    if(percent > 1) percent = 1;
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
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3
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

    bindData(VAO[0], VBO[0], vertices, 36*5);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // Enables a generic vertex attribute at the given index
    glEnableVertexAttribArray(0);

//    // Colour
//    // Tells OpenGL how to interpret the vertex buffer data
//    // Index, Size, Type, Normalized, Stride, Pointer
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    // Enables a generic vertex attribute at the given index
//    glEnableVertexAttribArray(1);

    // Location
    // Tells OpenGL how to interpret the vertex buffer data
    // Index, Size, Type, Normalized, Stride, Pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // Enables a generic vertex attribute at the given index
    glEnableVertexAttribArray(1);
}

/**
 * Pre-renders the screen creating the background and clearing the colour buffer
 */
void prerender()
{
    // Makes the screen this colour
    glClearColor(1.0f, 0.8f, 0.5f, 1.0f);
    // Clears the buffer with the clear colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
void draw(Shader shader, unsigned const int VAO, unsigned const int * EBO, unsigned const int texture[])
{
    // Sets the shader program to use
    shader.use();
    shader.setFloat("percent", percent);
    makeModel(shader);

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Binds the VAO so glVertexAttribPointer and glEnableVertexAttribArray work on this VAO
    glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 rotate = glm::mat4(1.0f);
        if(i % 3 == 0) {
            rotate = glm::rotate(rotate, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        } else {
            rotate = glm::mat4(1.0f);
        }
        int rotateLoc = glGetUniformLocation(shader.ID, "rotate");
        glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, glm::value_ptr(rotate));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }








    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // Binds the buffer to the buffer type so glBufferData works on this
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    // Tells OpenGL how to render the polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Renders vertices in VBO using EBO
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Checks any recent errors
    glCheckError();
}

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                               error = "UNKNOWN_ERROR"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

void generateTexture(unsigned int * texture, const char * path, bool isPNG)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    GLenum useAlpha;
    if(isPNG) {
        useAlpha = GL_RGBA;
    } else {
        useAlpha = GL_RGB;
    }

    if (data)
    {
        // Target Dimension, Mipmap level, Texture Format, width, height, 0, Format, Data Type, Image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, useAlpha, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

void makeModel(Shader shader)
{
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

    shader.use();
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}