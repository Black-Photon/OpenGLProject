#ifndef OPENGLPROJECT_SQUAREMODEL_H
#define OPENGLPROJECT_SQUAREMODEL_H


#include "Model.h"

static constexpr float SQ_SIZE = 1.0f;

static constexpr float sq_vertices[] = {
        // Position          // Texture
        -SQ_SIZE, -SQ_SIZE, 0, 0.0f, 0.0f,
        SQ_SIZE, -SQ_SIZE, 0, 1.0f, 0.0f,
        -SQ_SIZE,  SQ_SIZE, 0, 1.0f, 0.0f,

        SQ_SIZE, -SQ_SIZE, 0, 1.0f, 0.0f,
        -SQ_SIZE,  SQ_SIZE, 0, 1.0f, 0.0f,
        SQ_SIZE,  SQ_SIZE, 0, 1.0f, 1.0f,
};

class SquareModel: public Model {
public:

    SquareModel();

    /**
     * DO NOT USE - This is specifically for 3D Models
     */
    void draw(glm::vec3 position, Shader shader){};
    void draw(glm::vec2 position, glm::vec2 screen, glm::vec2 size, Shader shader);
};


#endif //OPENGLPROJECT_SQUAREMODEL_H
