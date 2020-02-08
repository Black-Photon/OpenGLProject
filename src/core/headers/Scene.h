#ifndef SPACIALFREEZE_SCENE_H
#define SPACIALFREEZE_SCENE_H

#include "Instance.h"

class Scene {
private:
    std::vector<Shader> shaders;
    std::map<int, std::vector<Instance*>> instances;
    std::map<std::string, Light> lights;

public:
    void addInstance(Instance &instance);
    bool removeInstance(Instance &instance);

    void replaceShader(Shader &newShader, Shader &oldShader);

    void drawScene(bool drawRoom, float size);
    void drawScene(bool drawRoom);

    void addLight(std::string name, Light &light);
    bool removeLight(std::string name);
    Light& getLight(std::string name);
    Instance& getInstance(std::string name);

    void update(float deltaT);

    /**
     * Indicated an error occurred in searching for a scene object
     */
    struct sceneSearchException : public std::exception {
        std::string s;

        explicit sceneSearchException(const std::string &string) {
            s = string;
        }

        const char *what() const noexcept(true) override {
            return s.c_str();
        }
    };
};


#endif //SPACIALFREEZE_SCENE_H
