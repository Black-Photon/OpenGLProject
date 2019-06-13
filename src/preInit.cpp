#include "data.cpp"

/**
 * Methods used in Pre-Initialisation
 */

namespace core {

    /**
     * DO NOT CALL
     * Called every time the viewport is updated
     * @param window Window for viewport to affect
     * @param width New viewport width
     * @param height New viewport height
     */
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    /**
     * DO NOT CALL
     * Called every time the mouse moves
     * @param window Window for mouse to move in
     * @param xpos X-Coordinate of mouse
     * @param ypos Y-Coordinate of mouse
     */
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    /**
     * DO NOT CALL
     * Called every time the mouse scrolls
     * @param window Window for mouse to scroll in
     * @param xpos X-Offset of mouse
     * @param ypos Y-Offset of mouse
     */
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        // Simply makes the viewport in the whole screen - bottom left to top right
        glViewport(0, 0, width, height);
    }

    void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        // Sets default values if first time
        if (Mouse.first) {
            Mouse.lastX = xpos;
            Mouse.lastY = ypos;
            Mouse.first = false;
        }

        // Offset is distance moved
        float xoffset = xpos - Mouse.lastX;
        float yoffset = Mouse.lastY - ypos; // reversed since y-coordinates range from bottom to top
        Mouse.lastX = xpos;
        Mouse.lastY = ypos;

        // Movement sensitivity
        float sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        // Adjusts the yaw and pitch according to the mouse movement
        Data.camera->rotate(YAW, xoffset);
        Data.camera->rotate(PITCH, yoffset);
    }

    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        //Data.camera->zoom(-yoffset);
    }

    void click_callback(GLFWwindow *window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
           Mouse.rightClick = true;
        }
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            Mouse.leftClick = true;
        }
    }
}