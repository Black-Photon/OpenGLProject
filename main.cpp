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

    void drawScene(Shader* shader, Shader* lightShader, Shader* solidShader, Model* model, glm::vec3 lightPos, bool renderlight) {
        core::prerender(0.1, 0.1, 0.1);

        model->bind();
        lightShader->use();
//        core::makeModel(*lightShader);
        if(renderlight) model->draw(lightPos, *lightShader);

        shader->use();
//        core::makeModel(*shader);

        // Creates the model matrix by translating by coordinates
        glm::mat4 modelMat = glm::mat4 {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        int modelLoc = glGetUniformLocation(shader->ID, "model");

        // Sets the relative shader3d uniform
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, glm::value_ptr(modelMat));

        // Draws the model
        glDrawArrays(GL_TRIANGLES, 0, 36);

        solidShader->use();
//        core::makeModel(*solidShader);

        modelMat = glm::mat4 {
                1, 0, 0, 0,
                0, 0, -1, 0,
                0, 1, 0, 0,
                0, 0, 0, 1
        } * glm::mat4 {
                32, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 32, 0,
                0, 0, 0, 1
        } * glm::mat4 {
                1, 0, 0, 0,
                0, 1, 0, -1.5,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        modelLoc = glGetUniformLocation(solidShader->ID, "model");

        // Sets the relative shader3d uniform
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, glm::value_ptr(modelMat));

        // Draws the model
        glDrawArrays(GL_TRIANGLES, 0, 6);
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

    unsigned int cardboard;
    core::generateTexture(&cardboard, std::string("container.jpg"), false);

    LightModel light;
    SquareModel square;

    Shader lightShader("light.vert", "light.frag", core::Path.shaders);
    Shader simpleDepthShader("simpleDepthShader.vert", "simpleDepthShader.frag", core::Path.shaders);
    Shader depthShader("depthShader.vert", "depthShader.frag", core::Path.shaders);

    Shader *shader = core::Data.shader3d;
    Shader *shader2d = core::Data.shader2d;
    Model *model = core::Data.models.at(0);

    glm::vec3 lightColour(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(1.0f, 1.5f, 2.0f);

    shader->use();
    shader->setVec3("objectColour", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightColour", lightColour);
    shader->setVec3("lightPos", lightPos);
    shader->setFloat("ambientStrength", 0.3f);
    shader->setFloat("diffuseStrength", 1.0f);
    shader->setFloat("specularStrength", 0.5f);

    lightShader.use();
    lightShader.setVec3("colour", lightColour);

    Shader solidShader("vertexShader.vert", "shaderSingleColour.frag", core::Path.shaders);
    solidShader.use();
    solidShader.setInt("alpha", 1);
    solidShader.setVec3("lightPos", lightPos);

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);



    // shader configuration
    // --------------------
    shader->use();
    shader->setInt("diffuseTexture", 0);
    shader->setInt("shadowMap", 1);
    solidShader.use();
    solidShader.setInt("diffuseTexture", 0);
    solidShader.setInt("shadowMap", 1);
    depthShader.use();
    depthShader.setInt("depthMap", 0);


    while (!core::shouldClose()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - core::Data.lastFrame;
        core::Data.lastFrame = currentFrame;

        core::processInput(deltaTime);

        shader->use();
        shader->setVec3("viewPos", core::Data.camera->cameraPos);

//        core::drawScene(shader, &lightShader, &solidShader, model, lightPos);


        float near_plane = 0.1f, far_plane = 10.0f;
//        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightProjection = glm::perspective(glm::radians(90.0f), ((float) SHADOW_WIDTH)/ ((float) SHADOW_HEIGHT), near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(      lightPos,
                                                glm::vec3(0.0f),
                                                glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        simpleDepthShader.use();
        int matLoc = glGetUniformLocation(simpleDepthShader.ID, "lightSpaceMatrix");

        // Sets the relative shader3d uniform
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        // 1. first render to depth map
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, cardboard);
        core::drawScene(&simpleDepthShader, &simpleDepthShader, &simpleDepthShader, model, lightPos, false);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // 2. then render scene as normal with shadow mapping (using depth map)
        glViewport(0, 0, core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cardboard);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        shader->use();
        matLoc = glGetUniformLocation(shader->ID, "lightSpaceMatrix");
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        solidShader.use();
        matLoc = glGetUniformLocation(solidShader.ID, "lightSpaceMatrix");
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        core::makeModel(*shader);
        core::makeModel(lightShader);
        core::makeModel(solidShader);
        core::drawScene(shader, &lightShader, &solidShader, model, lightPos, true);

        // render Depth map to quad for visual debugging
        // ---------------------------------------------
//        depthShader.use();
//        depthShader.setFloat("near_plane", near_plane);
//        depthShader.setFloat("far_plane", far_plane);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, depthMap);
//        square.bind();
//        square.draw(glm::vec2(0.0f), glm::vec2(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT), glm::vec2(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT), depthShader);


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

