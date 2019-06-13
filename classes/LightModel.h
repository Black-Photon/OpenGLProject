#ifndef OPENGLPROJECT_LIGHTMODEL_H
#define OPENGLPROJECT_LIGHTMODEL_H


#include "Model.h"
static constexpr float L_SIZE = 0.10f;

static constexpr float l_vertices[] = {
        // Position          // Texture
        -L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 0.0f,
        L_SIZE, -L_SIZE, -L_SIZE, 1.0f, 0.0f,
        L_SIZE,  L_SIZE, -L_SIZE, 1.0f, 1.0f,
        L_SIZE,  L_SIZE, -L_SIZE, 1.0f, 1.0f,
        -L_SIZE,  L_SIZE, -L_SIZE, 0.0f, 1.0f,
        -L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 0.0f,

        -L_SIZE, -L_SIZE,  L_SIZE, 0.0f, 0.0f,
        L_SIZE, -L_SIZE,  L_SIZE, 1.0f, 0.0f,
        L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 1.0f,
        L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 1.0f,
        -L_SIZE,  L_SIZE,  L_SIZE, 0.0f, 1.0f,
        -L_SIZE, -L_SIZE,  L_SIZE, 0.0f, 0.0f,

        -L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 0.0f,
        -L_SIZE,  L_SIZE, -L_SIZE, 1.0f, 1.0f,
        -L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 1.0f,
        -L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 1.0f,
        -L_SIZE, -L_SIZE,  L_SIZE, 0.0f, 0.0f,
        -L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 0.0f,

        L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 0.0f,
        L_SIZE,  L_SIZE, -L_SIZE, 1.0f, 1.0f,
        L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 1.0f,
        L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 1.0f,
        L_SIZE, -L_SIZE,  L_SIZE, 0.0f, 0.0f,
        L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 0.0f,

        -L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 1.0f,
        L_SIZE, -L_SIZE, -L_SIZE, 1.0f, 1.0f,
        L_SIZE, -L_SIZE,  L_SIZE, 1.0f, 0.0f,
        L_SIZE, -L_SIZE,  L_SIZE, 1.0f, 0.0f,
        -L_SIZE, -L_SIZE,  L_SIZE, 0.0f, 0.0f,
        -L_SIZE, -L_SIZE, -L_SIZE, 0.0f, 1.0f,

        -L_SIZE,  L_SIZE, -L_SIZE, 0.0f, 1.0f,
        L_SIZE,  L_SIZE, -L_SIZE, 1.0f, 1.0f,
        L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 0.0f,
        L_SIZE,  L_SIZE,  L_SIZE, 1.0f, 0.0f,
        -L_SIZE,  L_SIZE,  L_SIZE, 0.0f, 0.0f,
        -L_SIZE,  L_SIZE, -L_SIZE, 0.0f, 1.0f
};

class LightModel: public Model {
public:

    LightModel();

    void draw(glm::vec3 position, Shader shader);
    /**
     * DO NOT USE - This is specifically for 2D Models
     */
    void draw(glm::vec2 position, glm::vec2 screen, glm::vec2 size, Shader shader) {};

};


#endif //OPENGLPROJECT_LIGHTMODEL_H
