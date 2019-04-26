#pragma once
#include "src/include.cpp"

#include "classes/Shader.h"
#include "src/data.cpp"
#include "src/preInit.cpp"
#include "src/init.cpp"
#include "src/frame.cpp"
#include "classes/CubeModel.h"
#include "classes/SquareModel.h"

namespace core {

    // Prototypes
    /**
     * Initializes the program, creating a basic window
     * @throws initialisationException If it fails to successfully initialise the program
     */
    void preInit(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, std::string title);

    /**
     * Performs all operations that are required for drawing
     */
    void init(bool capture);

    /**
     * Checks if the window has received a close signal
     * @return True if the window should close
     */
    bool shouldClose();

    /**
     * Closes the program by deleting any references
     */
    void close();

    void preInit(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, std::string title) {
        Data.SCR_WIDTH = SCR_WIDTH;
        Data.SCR_HEIGHT = SCR_HEIGHT;

        // Sets all the window settings
        glfwInit(); // Required
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Creates a window object and checks it actually works
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw initialisationException("Failed to create GLFW window");
        }
        // Tells it what window to apply OpenGL operations to
        glfwMakeContextCurrent(window);
        // Tells OpenGL to use this function when resizing
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetMouseButtonCallback(window, click_callback);

        // Sets up GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw initialisationException("Failed to initialize GLAD");
        }

        Data.window = window;
    }

    void init(bool capture) {
        glEnable(GL_DEPTH_TEST);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        // Program
        auto *shader3d = new Shader("vertexShader.vert", "fragmentShader.frag", Path.shaders);
        Data.shader3d = shader3d;

        auto *shader2d = new Shader("2dImage.vert", "2dImage.frag", Path.shaders);
        Data.shader2d = shader2d;

        stbi_set_flip_vertically_on_load(true);

        shader3d->use(); // Must activate shader3d to use uniforms

        // Creates the actual main viewport, and makes it adjust for window size changes
        glViewport(0, 0, Data.SCR_WIDTH, Data.SCR_HEIGHT);

        Data.lastFrame = glfwGetTime();

        auto *camera = new Camera(1920.0f/1080.0f);
        Data.camera = camera;
        Data.camera->rotate(YAW, -90.0f);

        Model *model = new CubeModel();
        Data.models.push_back(model);
        model = new SquareModel();
        Data.models.push_back(model);

        if(capture) {
            glfwSetInputMode(Data.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    bool shouldClose() {
        return glfwWindowShouldClose(Data.window);
    }

    void close() {
        delete (Data.shader3d);
        delete (Data.camera);

        glfwTerminate();
    }
}

int main() {
    core::preInit(1920, 1080, "Lighting");
    core::init(true);

    unsigned int cardboard;
    core::generateTexture(&cardboard, std::string("container.jpg"), false);

    while (!core::shouldClose()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - core::Data.lastFrame;
        core::Data.lastFrame = currentFrame;

        core::processInput(deltaTime);
        core::prerender(1.0f, 0.4f, 0.6f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cardboard);

        Model *model = core::Data.models.at(0);
        model->bind();

        Shader *shader = core::Data.shader3d;
        core::makeModel(*shader);

        model->draw(glm::vec3(0.0f, 0.0f, 0.0f), *shader);

        core::glCheckError();
        glfwPollEvents();
        glfwSwapBuffers(core::Data.window);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);




        if(glfwGetKey(core::Data.window, GLFW_KEY_W) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(FORWARD, Y, deltaTime);
        }
    }
    core::close();
}