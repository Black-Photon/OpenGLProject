/**
 * Methods used in Initialisation
 */
namespace core {
    void init(bool capture) {
        // Enables basic features
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
//        glEnable(GL_CULL_FACE);
        glEnable(GL_SCISSOR_TEST);

        // Flips Textures to correct orientation
        stbi_set_flip_vertically_on_load(true);

        // Creates the actual main viewport, and makes it adjust for window size changes
        glViewport(0, 0, Data.SCR_WIDTH, Data.SCR_HEIGHT);

        // Initialises time
        Data.lastFrame = glfwGetTime();

        // Creates Camera viewed from
        auto *camera = new Camera(1920.0f/1080.0f);
        Data.camera = std::unique_ptr<Camera>(camera);
        Data.camera->rotate(YAW, -90.0f);
        Data.camera->moveBy(Z, -2.0f);

        Data.black = texture::generateTexture(Path.texture + "Black.png", false);

        if(capture) {
            glfwSetInputMode(Data.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}