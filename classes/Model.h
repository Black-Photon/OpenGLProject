#ifndef OPENGLPROJECT_MODEL_H
#define OPENGLPROJECT_MODEL_H

#include <glm/glm.hpp>
#include "Shader.h"

/**
 * Represents a specific shape type
 *
 * Holds reused information to make copies of the same shape with different positions
 */
class Model {
public:
    /**
     * Builds a model with the given Vertices
     * @param vertices Vertices of the points
     * @param length Length of the vertex array
     */
    Model(float vertices[], int length);
    /**
     * Deletes saved resources
     */
    ~Model();

    /**
     * Draws the model to the screen at the given position
     * @param position Position to draw to the screen
     * @param shader Shader to draw using
     * @param vertices Number of vertices to draw
     */
    void draw(glm::vec3 position, Shader shader, int vertices);

    /**
     * Draws the model to the screen at the given position
     * @param position Position to draw to the screen
     * @param shader Shader to draw using
     */
    virtual void draw(glm::vec3 position, Shader shader) = 0;

    /**
     * Draws the model to the screen at the given position
     * @param position Position to draw to the screen
     * @param screen Screen size
     * @param size Size of shape
     * @param shader Shader to draw using
     */
    virtual void draw(glm::vec2 position, glm::vec2 screen, glm::vec2 size, Shader shader) = 0;

    /**
     * Binds the VAO
     */
    void bind();

protected:
    unsigned int VAO;
    unsigned int VBO;
};


#endif //OPENGLPROJECT_MODEL_H
