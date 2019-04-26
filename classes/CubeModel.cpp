#include "CubeModel.h"

CubeModel::CubeModel() : Model((float*) vertices, 180)
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

void CubeModel::draw(glm::vec3 position, Shader shader)
{
    Model::draw(position, shader, 36);
}