#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SquareModel.h"

SquareModel::SquareModel() : Model((float*) sq_vertices, 30)
{
    // Position
    // Tells OpenGL how to interpret the vertex buffer data
    // Index, Size, Type, Normalized, Stride, Pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    // Enables a generic vertex attribute at the given index
    glEnableVertexAttribArray(0);

    // Location
    // Tells OpenGL how to interpret the vertex buffer data
    // Index, Size, Type, Normalized, Stride, Pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    // Enables a generic vertex attribute at the given index
    glEnableVertexAttribArray(1);

    // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // Unbinds the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void SquareModel::draw(glm::vec2 position, glm::vec2 screen, glm::vec2 size, Shader shader) {
    shader.use();

    // Creates the model matrix by translating by coordinates
    int positionLoc = glGetUniformLocation(shader.ID, "position");
    glUniform2fv(positionLoc, 1, glm::value_ptr(position));
    int screenLoc = glGetUniformLocation(shader.ID, "screen");
    glUniform2fv(screenLoc, 1, glm::value_ptr(screen));
    int sizeLoc = glGetUniformLocation(shader.ID, "size");
    glUniform2fv(sizeLoc, 1, glm::value_ptr(size));

    glDrawArrays(GL_TRIANGLES, 0, 6);
}