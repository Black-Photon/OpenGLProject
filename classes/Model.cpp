#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"

Model::Model(float vertices[], int length)
{
    // Generates a Vertex Array Object
    glGenVertexArrays(1, &VAO);
    // Generates the Vertex Buffer Objects
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // Binds the VAO so glVertexAttribPointer and glEnableVertexAttribArray work on this VAO
    glBindVertexArray(VAO);

    // Binds the buffer to the buffer type so glBufferData works on this
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Allocates memory for and stores the vertices data
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(*vertices), vertices, GL_STATIC_DRAW);
}

Model::~Model()
{
    // Deletes VAO and VBO data from memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Model::draw(glm::vec3 position, Shader shader, int vertices)
{
    // Creates the model matrix by translating by coordinates
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    int modelLoc = glGetUniformLocation(shader.ID, "model");

    // Sets the relative shader3d uniform
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Draws the model
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

void Model::bind()
{
    glBindVertexArray(VAO);
}