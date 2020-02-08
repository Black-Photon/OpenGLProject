// Data Includes
#include "include.cpp"

namespace core {
    void frame(Scene &scene) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - Data.lastFrame;
        Data.lastFrame = currentFrame;
        processInput(deltaTime);
        prerender(0.1, 0.1, 0.1);

        glm::vec3 pos(0, 0, 0);
        scene.drawScene(false);

        glCheckError();
        glfwPollEvents();
        glfwSwapBuffers(Data.window);
    }

    void run() {
        logger::message("Starting Program");
        preInit(1920, 1080, "OpenGL Project");
        logger::message("Pre-Initialisation Complete");
        init(true);
        logger::message("Initialisation Complete");
        glCheckError();

        CubeModel cube;
        Shader shader("basic3d.vert", "solidColour.frag");
        shader.setVec3("colour", 0.5, 0.5, 0.5);

        Instance cubeInstance(cube, shader, "cube");
        Scene scene;
        scene.addInstance(cubeInstance);

        logger::message("Starting draw Phase");
        while (!shouldClose()) frame(scene);
    }
}

int main() {
    try {
        core::run();
    } catch (core::initialisationException &e) {
        logger::fatal(e.what(), "Initialisation");
    } catch (shaderException &e) {
        logger::fatal(e.what(), "Shaders");
    } catch (framebufferException &e) {
        logger::fatal(e.what(), "Framebuffer");
    } catch (modelLoadingException &e) {
        logger::fatal(e.what(), "Model Loading");
    }

    core::close();
}

