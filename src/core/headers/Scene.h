#ifndef SPACIALFREEZE_SCENE_H
#define SPACIALFREEZE_SCENE_H

#include "Instance.h"
#include "Assignment.h"

class Scene {
private:
    Assignment assignment;
    std::map<Instance, std::string> instances;
    std::map<std::string, Light> lights;

public:
    void drawScene(float size);
    void drawScene();

    void update(float deltaT);

    void addInstance(Instance &instance, std::string group);
    Instance& getInstance(std::string name);
    void removeInstance(Instance &instance);

    void setGroup(Instance &instance, std::string group);
    int getGroup(Instance &instance);

    void addLight(std::string name, Light &light);
    Light& getLight(std::string name);
    void removeLight(std::string name);

    void setAssignment(Assignment &a);
    Assignment& getAssignment();

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
