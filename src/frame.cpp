#include "data.cpp"
#include "../classes/Shader.h"
#include "../classes/Camera.h"

/**
 * Methods used from frame to frame
 */

namespace core {

    /**
    * Polls and processes any user input
    * @param deltaT Time since last frame
    */
    void processInput(float deltaT);
    /**
     * Pre-renders the screen creating the background and clearing the colour buffer
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void prerender(float r, float g, float b);
    /**
     * Builds the model and transforms to the view space
     * @param shader Shader to transform
     */
    void makeModel(Shader shader);

    void processInput(float deltaT) {
        // Pretty Straightforward
        if (glfwGetKey(Data.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(Data.window, true);
    }

    void prerender(float r, float g, float b) {
        // Makes the screen this colour
        glClearColor(r, g, b, 1.0f);
        // Clears the buffer with the clear colour
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
    }

    void makeModel(Shader shader) {
        glm::mat4 view = Data.camera->getTransformation();
        glm::mat4 projection = Data.camera->getPerspectiveTransformation();

        shader.use();
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
}