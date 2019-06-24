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

    void drawScene(Shader shader, Shader coolShader, Model* model, glm::vec3 lightColour, glm::vec3 offset) {
//        coolShader.use();
//        model->draw(glm::vec3(0.0f, 0.0f, 0.0f)+offset, coolShader);

        shader.use();
        shader.setVec3("lightColour", lightColour.x, lightColour.y, lightColour.z);

        for(int f = -4; f < 8; f += 8) {
            model->draw(glm::vec3(f, -1.0f, 0.0f)+offset, shader);
            model->draw(glm::vec3(f, 1.0f, 0.0f)+offset, shader);
            model->draw(glm::vec3(f, -1.0f, -1.0f)+offset, shader);
            model->draw(glm::vec3(f, 1.0f, -1.0f)+offset, shader);
            model->draw(glm::vec3(f, -1.0f, 1.0f)+offset, shader);
            model->draw(glm::vec3(f, 1.0f, 1.0f)+offset, shader);
            model->draw(glm::vec3(f, 0.0f, -1.0f)+offset, shader);
            model->draw(glm::vec3(f, 0.0f, 1.0f)+offset, shader);
            shader.setVec3("lightColour", 0.3, 1, 0.1);
        }

//        shader.setVec3("lightColour", 1.0, 0.3, 0.3);
//        model->draw(offset, shader);

        shader.setVec3("lightColour", lightColour.x, lightColour.y, lightColour.z);
    }

    void portalAtLoc(glm::vec3 position, Model* model, Shader coolShader) {
        coolShader.use();

        coolShader.setInt("alpha", 0);
        model->draw(position, coolShader);
        coolShader.setInt("alpha", 1);
    }
}

namespace stencil {
    void startTrace(int channel) {
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_ALWAYS, channel, 0xFF); // Always draw
    }

    void startDraw(int channel) {
        glDepthMask(GL_TRUE);
        glStencilFunc(GL_EQUAL, channel, 0xFF); // Only draw on stencil
    }

    void enable() {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xFF);
    }

    void disable() {
        glDisable(GL_STENCIL_TEST);
    }
}

glm::vec3 multiply(glm::vec3 vector, int i) {
    if(i <= 0) return glm::vec3(0);
    else return vector + multiply(vector, i-1);
}

int main() {
    core::preInit(1920, 1080, "Stuff");
    core::init(true);

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

        core::prerender(1, 1, 1);

        shader->use();
        model->bind();
        core::makeModel(*shader);
//        model->draw(glm::vec3(0.0, 0.0, 0.0), *shader);

        // Creates the model matrix by translating by coordinates
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4 {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

//        model = glm::translate(model, glm::vec3(0.0, 1.0, 0.0));
        int modelLoc = glGetUniformLocation(shader->ID, "model");

        // Sets the relative shader3d uniform
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, glm::value_ptr(model));

        // Draws the model
        glDrawArrays(GL_TRIANGLES, 0, 36);

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

