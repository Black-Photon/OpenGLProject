void stencil_example(Scene &scene, Assignment &assignment, float deltaT) {
//    Shader shader = scene.getShader("solid");
//    shader.use();
//    stencil::enable();
//    stencil::startTrace(1);
//    shader.setVec4("colour", 0.5f, 0.5f, 0.5f, 1.0f);
//    scene.drawScene(0.1f);
//    stencil::startDrawInvert(1);
//    shader.setVec4("colour", 1.0f, 0.5f, 0.5f, 1.0f);
//    scene.drawScene(1.1f);
//    stencil::disable();
}

void lighting_example(Scene &scene, Assignment &assignment, float deltaT) {
    scene.drawScene();
}