#ifndef SPACIALFREEZE_LIGHT_H
#define SPACIALFREEZE_LIGHT_H


class Light {
public:
    glm::vec3 position = glm::vec3();
    glm::vec3 colour = glm::vec3(1.0f);
    float intensity = 1;
};


#endif //SPACIALFREEZE_LIGHT_H
