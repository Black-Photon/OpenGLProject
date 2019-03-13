#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

// Prototypes

GLFWwindow * init();
void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow *window);
void buildImage(unsigned int *VAO, unsigned int *VBO);
bool getGLSL();
void makeShaders(unsigned int * shaderProgram);
void draw(unsigned const int * shaderProgram, unsigned const int * VAO);
void prerender();
std::string * getFileContents(std::string filename);

// Global Variables
const char *vertexShaderSource;
const char *fragmentShaderSource;
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

    if(!getGLSL())
    {
        return -1;
    }

    // Program
    unsigned int shaderProgram;
    makeShaders(&shaderProgram);

    // Vertex attribute object and Virtual Buffer Object
    unsigned int VAO, VBO;
    buildImage(&VAO, &VBO);

    // Set's the shader to use
    glUseProgram(shaderProgram);

    // Creates the actual main viewport, and makes it adjust for window size changes
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Render
        prerender();

        // Draw
        draw(&shaderProgram, &VAO);

        // Swap buffers and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
    glfwInit();
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
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set's up GLAD
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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
 * Builds the image putting results into values
 * @param VAO Location to save the Vertex Array Object index
 * @param VBO Location to save the Vertex Buffer Object index
 */
void buildImage(unsigned int *VAO, unsigned int *VBO)
{
    // Triangle example
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

/**
 * Pre-renders the screen creating the background and clearing the colour buffer
 */
void prerender()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
 * Gets the GLSL file source and puts it into associated strings
 */
bool getGLSL()
{
    vertexShaderSource = getFileContents("../shaders/vertexShader.vert")->c_str();

    if(vertexShaderSource == nullptr){
        std::cout << std::string("Could not find vertex shader file") << std::endl;
        return false;
    }

    fragmentShaderSource = getFileContents("../shaders/fragmentShader.vert")->c_str();

    if(vertexShaderSource == nullptr){
        std::cout << std::string("Could not find fragment shader file") << std::endl;
        return false;
    }

    return true;
}

/**
 * Builds and compiles the shaders
 * @param shaderProgram Location to store the shader program index
 */
void makeShaders(unsigned int * shaderProgram)
{
    // VERTEX SHADERS
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
    }
    else
    {
        std::cout << "INFO::SHADER::VERTEX::COMPILATION_SUCCESS" << std::endl;
    }

    // FRAGMENT SHADERS
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
    }
    else
    {
        std::cout << "INFO::SHADER::FRAGMENT::COMPILATION_SUCCESS" << std::endl;
    }

    // SHADER LINKING
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(*shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << std::endl;
    }
    else
    {
        std::cout << "INFO::SHADER::PROGRAM::LINKING_SUCCESS" << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

/**
 * Applies the shader program to the VAO and draws it to the buffer
 * @param shaderProgram Shader program index to draw with
 * @param VAO Array Object index to draw
 */
void draw(unsigned const int * shaderProgram, unsigned const int * VAO)
{
    glUseProgram(*shaderProgram);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/**
 * Gets the contents of the file with the given name
 * @param filename Name of file to get contents of
 * @return Contents of file
 */
std::string * getFileContents(std::string filename)
{
    // Create a stream for the string file data
    std::ifstream ifs(filename);

    // Iterates through the stream, putting it into a string
    //
    // Uses constructor:
    // template <class InputIterator>
    //  string  (InputIterator first, InputIterator last);
    std::string * content = new std::string((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    ifs.close();


    return content;
}