/**
 * Methods used in Pre-Initialisation
 */

namespace core {

    /**
     * Initializes the program, creating a basic window
     * @throws initialisationException If it fails to successfully initialise the program
     */
    void preInit(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, std::string &title);
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
    /**
     * DO NOT CALL
     * Called every time the mouse is clicked
     * @param window Window for mouse to scroll in
     * @param button Button Pressed - e.g. GLFW_MOUSE_BUTTON_RIGHT
     * @param action Action - e.g. GLFW_PRESS
     * @param mods Modifier bits (E.g. Shift Pressed)
     */
    void click_callback(GLFWwindow *window, int button, int action, int mods);
}