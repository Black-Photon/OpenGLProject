#include "headers/Transformation.h"

glm::mat4 Transformation::getMatrix()  {
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::scale(matrix, size * glm::vec3(0.1));
    return matrix;
}