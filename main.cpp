#pragma once
#include "src/include.cpp"

#include "classes/Shader.h"
#include "src/data.cpp"
#include "src/preInit.cpp"
#include "src/init.cpp"
#include "src/frame.cpp"
#include "classes/CubeModel.h"
#include "classes/SquareModel.h"
#include "classes/LightModel.h"

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
        glEnable(GL_STENCIL_TEST);

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

    glStencilMask(0x00); // Read

//    unsigned int cardboard;
//    core::generateTexture(&cardboard, std::string("container.jpg"), false);

    LightModel light;

    Shader lightShader("light.vert", "light.frag", core::Path.shaders);

    Shader *shader = core::Data.shader3d;
    Model *model = core::Data.models.at(0);

    glm::vec3 lightColour(1.0f, 0.5f, 0.8f);

    shader->setVec3("objectColour", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightColour", lightColour.x, lightColour.y, lightColour.z);
    shader->setFloat("ambientStrength", 0.3f);
    shader->setFloat("specularStrength", 0.5f);

    lightShader.use();

    Shader coolShader("vertexShader.vert", "shaderSingleColour.frag", core::Path.shaders);

    while (!core::shouldClose()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - core::Data.lastFrame;
        core::Data.lastFrame = currentFrame;

        core::processInput(deltaTime);

        float colour = sin(currentFrame/10);
        if(colour < 0.5f && colour > -0.5f) {
            core::prerender(1.0f * colour, 0.4f * colour, 0.4f * colour);
        } else if(colour >= 0.5f){
            core::prerender(0.4f * colour, 0.4f * colour, 1.0f * colour);
        } else {
            core::prerender(colour, colour, colour);
        }

//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cardboard);

        shader->use();
        glm::vec3 camera = core::Data.camera->cameraPos;

        shader->setVec3("viewPos", camera.x, camera.y, camera.z);


        core::glCheckError();
        model->bind();
        core::makeModel(*shader);

        glm::vec3 lightPos(2.0f * sin(currentFrame), 1.5f * cos(currentFrame), 1.0f);
        shader->setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//        // Draw Normal Cube
//        glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always Draw
//        glStencilMask(0x00); // Read Only
//        model->draw(glm::vec3(0.0f, 0.0f, 0.0f), *shader);
//
//        // Draw Cube 2
//        glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always draw
//        glStencilMask(0xFF); // Write
//        model->draw(glm::vec3(0.0f, 0.0f, -1.5f), *shader);
//
//        // Draw outline for 2
//        glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Only draw on non-stencil
//        glStencilMask(0x00); // Read
////        glDisable(GL_DEPTH_TEST);
//        coolShader.use();
//        core::makeModel(coolShader);
//        model->drawS(glm::vec3(0.0f, 0.0f, -1.5f), coolShader, 1.2);

        shader->setVec3("lightColour", lightColour.x, lightColour.y, lightColour.z);

        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always draw
        glStencilMask(0xFF); // Write
        coolShader.use();
        core::makeModel(coolShader);
        model->draw(glm::vec3(0.0f, 0.0f, 0.0f), coolShader);
        glStencilMask(0x00); // Read

        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

//        glDisable(GL_DEPTH_TEST);
        glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw on stencil
        glStencilMask(0x00); // Read
        shader->use();
        model->draw(glm::vec3(0.0f, 0.0f, -2.0f), *shader);
        model->draw(glm::vec3(0.0f, 2.0f, -2.0f), *shader);
        model->draw(glm::vec3(0.0f, 4.0f, -2.0f), *shader);
//        glEnable(GL_DEPTH_TEST);

        glStencilMask(0xFF); // Write
//        glStencilMask(0xFF);
//        glEnable(GL_DEPTH_TEST);


        shader->setVec3("lightColour", 0.2, 1, 0.5);

        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_ALWAYS, 2, 0xFF); // Always draw
        glStencilMask(0xFF); // Write
        coolShader.use();
        core::makeModel(coolShader);
        model->draw(glm::vec3(-1.0f, 0.0f, 0.0f), coolShader);
        glStencilMask(0x00); // Read

        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

//        glDisable(GL_DEPTH_TEST);
        glStencilFunc(GL_EQUAL, 2, 0xFF); // Only draw on stencil
        glStencilMask(0x00); // Read
        shader->use();
        model->draw(glm::vec3(-1.0f, 0.0f, -2.0f), *shader);
        model->draw(glm::vec3(-1.0f, 2.0f, -2.0f), *shader);
        model->draw(glm::vec3(-1.0f, 4.0f, -2.0f), *shader);
//        glEnable(GL_DEPTH_TEST);

        glStencilMask(0xFF); // Write







        // Creates the model matrix by translating by coordinates
        glm::mat4 model = glm::mat4(1.0f);
        int modelLoc = glGetUniformLocation(lightShader.ID, "model");

        // Sets the relative shader3d uniform
        lightShader.use();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        core::makeModel(lightShader);
        lightShader.use();
        lightShader.setVec3("colour", lightColour.x, lightColour.y, lightColour.z);
        light.bind();
        light.draw(lightPos, lightShader);

        lightShader.setVec3("colour", 1.0f, 0.0f, 1.0f);
        light.draw(glm::vec3(0, 100, 0), lightShader);

        core::glCheckError();
        glfwPollEvents();
        glfwSwapBuffers(core::Data.window);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);




        if(glfwGetKey(core::Data.window, GLFW_KEY_W) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(FORWARD, Y, deltaTime);
        }
        if(glfwGetKey(core::Data.window, GLFW_KEY_A) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(LEFT, Y, deltaTime);
        }
        if(glfwGetKey(core::Data.window, GLFW_KEY_S) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(BACKWARD, Y, deltaTime);
        }
        if(glfwGetKey(core::Data.window, GLFW_KEY_D) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(RIGHT, Y, deltaTime);
        }
        if(glfwGetKey(core::Data.window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(FORWARD, Z, deltaTime);
        }
        if(glfwGetKey(core::Data.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            core::Data.camera->moveOnPlane(BACKWARD, Z, deltaTime);
        }
    }
    core::close();
}