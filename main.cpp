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

    void drawScene(Shader* shader, Shader lightShader, Model* model, LightModel light, glm::vec3 lightPos, int cardboard) {
        core::prerender(0.01, 0.01, 0.01);

        model->bind();
        core::makeModel(*shader);
        glBindTexture(GL_TEXTURE_2D, cardboard);
        model->draw(glm::vec3(0.0, 0.0, 0.0), *shader);

        core::makeModel(lightShader);
        light.draw(lightPos, lightShader);
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

    Shader lightShader("light.vert", "light.frag", core::Path.shaders);

    Shader *shader = core::Data.shader3d;
    Shader *shader2d = core::Data.shader2d;
    Model *model = core::Data.models.at(0);
    Model *model2d = core::Data.models.at(1);

    glm::vec3 lightColour(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(2.0f, 1.5f, 1.0f);

    shader->setVec3("objectColour", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightColour", lightColour.x, lightColour.y, lightColour.z);
    shader->setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
    shader->setFloat("ambientStrength", 0.3f);
    shader->setFloat("diffuseStrength", 1.0f);
    shader->setFloat("specularStrength", 0.0f);

    lightShader.use();
    lightShader.setVec3("colour", lightColour.x, lightColour.y, lightColour.z);


    // framebuffer configuration
    // -------------------------
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w = core::Data.SCR_WIDTH;
    int h = core::Data.SCR_HEIGHT;
    for(int i = 0; i < 10; i++, w/=2, h/=2)
        glTexImage2D(GL_TEXTURE_2D, i, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR::FRAMEBUFFER::GENERATION_FAILURE" << std::endl;
    else
        std::cout << "INFO::FRAMEBUFFER::GENERATION_SUCCESS" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //unsigned int *tex;
    //core::generateTexture(tex, "container.jpg", false);

    float exposure = 0.0f;
    shader->use();
    shader->setFloat("exposure", exposure);

    while (!core::shouldClose()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - core::Data.lastFrame;
        core::Data.lastFrame = currentFrame;

        core::processInput(deltaTime);

        // render
        // ------
        // bind to framebuffer and draw scene as we normally would to color texture
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
        glViewport(0, 0, core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT); // Have to tell framebuffer to use this each time

        core::drawScene(shader, lightShader, model, light, lightPos, cardboard);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.


        model2d->bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        model2d->draw(glm::vec2(0.0f, 0.0f), glm::vec2(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT), glm::vec2(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT), *shader2d);

        unsigned char pixel[4];
        glReadPixels(0, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        int average = (pixel[0] + pixel[1] + pixel[2]) / 3;
        float exposureDiff = average * 11.0 / 126.0 - 1;
        exposure = exposure * 0.95 + exposureDiff * 0.05;
        if(exposure < -1) exposure = -1;
        if(exposure > 10) exposure = 10;
        std::cout << "Exposure:  " << exposure << std::endl;
        shader->use();
        shader->setFloat("exposure", exposure);


        core::drawScene(shader, lightShader, model, light, lightPos, cardboard);

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
    glDeleteFramebuffers(1, &framebuffer);

    core::close();
}

