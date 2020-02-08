#ifndef SPACIALFREEZE_TRANSFORMATION_H
#define SPACIALFREEZE_TRANSFORMATION_H


class Transformation {
public:
    glm::vec3 position;
    glm::vec3 size = glm::vec3(1.0f);

    glm::mat4 getMatrix();
};


#endif //SPACIALFREEZE_TRANSFORMATION_H
