/**
 * Methods used from frame to frame
 */

namespace core {
    void processInput(float deltaT) {
        if (glfwGetKey(Data.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(Data.window, true);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_W) == GLFW_PRESS) {
            Data.camera->moveOnPlane(FORWARD, Y, deltaT);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_A) == GLFW_PRESS) {
            Data.camera->moveOnPlane(LEFT, Y, deltaT);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_S) == GLFW_PRESS) {
            Data.camera->moveOnPlane(BACKWARD, Y, deltaT);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_D) == GLFW_PRESS) {
            Data.camera->moveOnPlane(RIGHT, Y, deltaT);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            Data.camera->moveBy(Y, deltaT);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            Data.camera->moveBy(Y, -deltaT);
        }
        if(glfwGetKey(Data.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && !Data.ctrlPressed) {
            Data.closed = !Data.closed;
            Data.ctrlPressed = true;
        } else if(glfwGetKey(Data.window, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS) Data.ctrlPressed = false;
    }

    void prerender(float r, float g, float b) {
        // Makes the screen this colour
        glClearColor(r, g, b, 1.0f);
        // Clears the buffer with the clear colour
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
    }

    void makeModel(const Shader &shader, const Camera &camera) {
        glm::mat4 view = camera.getTransformation();
        glm::mat4 projection = camera.getPerspectiveTransformation();

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
    }
}