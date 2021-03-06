#ifndef OPENGLPROJECT_CUBEMODEL_H
#define OPENGLPROJECT_CUBEMODEL_H


#include "Model.h"

static constexpr float SIZE = 0.5f;

static constexpr float vertices[] = {
        -SIZE, -SIZE, -SIZE,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        SIZE, -SIZE, -SIZE,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        SIZE,  SIZE, -SIZE,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        SIZE,  SIZE, -SIZE,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -SIZE,  SIZE, -SIZE,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -SIZE, -SIZE, -SIZE,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -SIZE, -SIZE,  SIZE,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
        SIZE, -SIZE,  SIZE,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
        SIZE,  SIZE,  SIZE,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        SIZE,  SIZE,  SIZE,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        -SIZE,  SIZE,  SIZE,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        -SIZE, -SIZE,  SIZE,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

        -SIZE,  SIZE,  SIZE, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        -SIZE,  SIZE, -SIZE, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -SIZE, -SIZE, -SIZE, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -SIZE, -SIZE, -SIZE, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -SIZE, -SIZE,  SIZE, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -SIZE,  SIZE,  SIZE, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

        SIZE,  SIZE,  SIZE,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        SIZE,  SIZE, -SIZE,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        SIZE, -SIZE, -SIZE,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        SIZE, -SIZE, -SIZE,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        SIZE, -SIZE,  SIZE,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        SIZE,  SIZE,  SIZE,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

        -SIZE, -SIZE, -SIZE,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        SIZE, -SIZE, -SIZE,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        SIZE, -SIZE,  SIZE,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        SIZE, -SIZE,  SIZE,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        -SIZE, -SIZE,  SIZE,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        -SIZE, -SIZE, -SIZE,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

        -SIZE,  SIZE, -SIZE,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        SIZE,  SIZE, -SIZE,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        SIZE,  SIZE,  SIZE,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        SIZE,  SIZE,  SIZE,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        -SIZE,  SIZE,  SIZE,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        -SIZE, SIZE, -SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
};

class CubeModel: public Model {
public:

    CubeModel();

    void draw(glm::vec3 position, Shader shader);
    /**
     * DO NOT USE - This is specifically for 2D Models
     */
    void draw(glm::vec2 position, glm::vec2 screen, glm::vec2 size, Shader shader) {};

    void drawS(glm::vec3 position, Shader shader, float size);
};


#endif //OPENGLPROJECT_CUBEMODEL_H
