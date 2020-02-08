#ifndef SPACIALFREEZE_RENDERER_H
#define SPACIALFREEZE_RENDERER_H


class Renderer {
private:
    Framebuffer mainFramebuffer;
    Framebuffer lightningFramebuffer;
    Framebuffer shadowBuffer;
    Shader oldShader;
    Shader ppShader;
    Shader lightningShader;
    Shader ppLightningShader;
    Shader shadowShader;
    Lightning lightningX;
    Lightning lightningY;
    void drawScene(Shader &newShader, float size);
    void drawTexture(Shader &postProcessing, unsigned int tex);
    void renderOutline(float diff);

    void generateShadows();

public:
    Scene scene;
    Camera shadowCam;
    Renderer(Scene &scene, Shader &oldShader);
    /**
     * Draws the scene normally
     */
    void draw();
    /**
     * Draws the scene using lightning borders
     */
    void drawLightning();
    /**
     * Updates the framebuffer size in case of window resizing
     */
    void updateFramebuffer();


    void renderSceneNormal();
    void drawSceneNormal();
    void renderSceneLightning();
    void drawSceneLightning();
};


#endif //SPACIALFREEZE_RENDERER_H
