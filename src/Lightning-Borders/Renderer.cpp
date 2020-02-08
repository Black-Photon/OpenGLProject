#include "Renderer.h"

Renderer::Renderer(Scene &scene, Shader &oldShader):
    scene(scene),
    mainFramebuffer(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT, false, true),
    lightningFramebuffer(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT, false, true),
    shadowBuffer(1024, 1024, true, false),
    oldShader(oldShader),
    ppShader("basic2d.vert", "texture.frag"),
    lightningShader("basic3d.vert", "solidColour.frag"),
    ppLightningShader("basic2d.vert", "lightning.frag"),
    shadowShader("shadow.vert", "shadow.frag", "shadow.geom"),
    shadowCam(core::Data.SCR_WIDTH/core::Data.SCR_HEIGHT),
    lightningX(), lightningY() {
    shadowCam.fov = 90.0f;
}

void Renderer::drawScene(Shader &newShader, float size) {
    scene.replaceShader(newShader, oldShader);
    scene.drawScene(false, size);
    scene.replaceShader(oldShader, newShader);
}

void Renderer::drawTexture(Shader &postProcessing, unsigned int tex) {
    SquareMesh square;
    postProcessing.use();
    postProcessing.setInt("texture2D", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    square.draw(postProcessing);
}

void Renderer::renderOutline(float diff) {
    stencil::enable();

    stencil::startTrace(1);
    lightningShader.use();
    lightningShader.setVec4("colour", 0.1f, 0.1f, 0.1f, 0.0f);
    drawScene(lightningShader, 1.0f);

    stencil::startDrawInvert(1);
    lightningShader.use();
    lightningShader.setVec4("colour", 1.0f, 0.5f, 0.0f, 1.0f);
    drawScene(lightningShader, 1.0f + diff);
    drawScene(lightningShader, 1.0f - diff);

    stencil::disable();
}

void Renderer::renderSceneNormal() {
    generateShadows();

    mainFramebuffer.startWrite();
    core::prerender(0.07, 0.07, 0.07);
    oldShader.use();
    oldShader.setInt("shadow_in.depthMap", 2);
    oldShader.setFloat("shadow_in.far_plane", MAX_DISTANCE);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowBuffer.texture);
    scene.drawScene(true);
    mainFramebuffer.endWrite();
}

void Renderer::drawSceneNormal() {
    ppShader.use();
    ppShader.setFloat("zPos", 0.0f);
    drawTexture(ppShader, mainFramebuffer.texture);
}

void Renderer::renderSceneLightning() {
    lightningFramebuffer.startWrite();
    renderOutline(0.04f);
    lightningFramebuffer.endWrite();
}

void Renderer::drawSceneLightning() {
    lightningX.update(0.004);
    lightningY.update(0.004);
    ppLightningShader.use();
    ppLightningShader.setInt("lightningX", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_1D, lightningX.getTexture());
    ppLightningShader.setInt("lightningY", 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_1D, lightningY.getTexture());
    ppLightningShader.setFloat("zPos", 0.1f);
    drawTexture(ppLightningShader, lightningFramebuffer.texture);
}

void Renderer::draw() {
    renderSceneNormal();
    drawSceneNormal();
}

void Renderer::drawLightning() {
    renderSceneLightning();
    drawSceneLightning();
}

void Renderer::updateFramebuffer() {
    mainFramebuffer.updateSize(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT);
    lightningFramebuffer.updateSize(core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT);
}

void Renderer::generateShadows() {
    shadowBuffer.startWrite();
    shadowShader.use();
    shadowShader.setVec3("lightPos", scene.getLight("light").position);
    shadowShader.setFloat("far_plane", MAX_DISTANCE);
    Camera cam(1.0f);
    cam.cameraPos = scene.getLight("light").position;
    cam.fov = 90.0f;
    shadowShader.setCubemapCamera("shadowMatrices", cam);
    drawScene(shadowShader, 1.0f);
    shadowBuffer.endWrite();
}