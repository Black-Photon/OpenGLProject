// Data Includes
#include "include.cpp"

namespace core {
    void frame(Scene &scene, void draw(Scene &, float)) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - Data.lastFrame;
        Data.lastFrame = currentFrame;
        processInput(deltaTime);
        prerender(0.1, 0.1, 0.1);

        draw(scene, deltaTime);

        glCheckError();
        glfwPollEvents();
        glfwSwapBuffers(Data.window);
    }

    void run() {
        logger::message("Starting Program");
        preInit(1920, 1080, "OpenGL Project");
        logger::message("Pre-Initialisation Complete");
        init(false);
        logger::message("Initialisation Complete");

        CubeModel cube;
        Shader solidShader("solid", "basic3d.vert", "solidColour.frag");
        Shader modelShader("model", "basic3d.vert", "model.frag");
        Shader depthShader("depth", "depthShader.vert", "depthShader.frag");
        Shader tex2dShader("tex2d", "basic2d.vert", "texture.frag");

        Instance cubeInstance(cube, solidShader, "cube");
        PhysicsComponent phy;
        cubeInstance.addComponent("physics", &phy);
        Scene scene;
        scene.addInstance(cubeInstance);

        glCheckError();

        logger::message("Starting draw Phase");
        while (!shouldClose()) {
//            frame(scene, stencil_example);
            frame(scene, lighting_example);
        }
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

