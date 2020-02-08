#ifndef SPACIALFREEZE_INSTANCE_H
#define SPACIALFREEZE_INSTANCE_H

#include "Transformation.h"
#include "Component.h"

class Instance {
public:
    long ID;
    std::string name;
    Shader shader;
    Transformation transformation;
    bool inside = false;

private:
    static long lastID;
    Model *model;
    std::map<std::string, Component*> components;

public:
    Instance(Model &model, Shader &shader, std::string name);
    void draw();
    void draw(Shader &shader);
    void draw(Shader &shader, Transformation altTrans);

    void update(float deltaT);
    void addComponent(std::string name, Component* component);
    Component* getComponent(std::string name);

    /**
     * Indicated an error occurred in searching for a component
     */
    struct componentSearchException : public std::exception {
        std::string s;

        explicit componentSearchException(const std::string &string) {
            s = string;
        }

        const char *what() const noexcept(true) override {
            return s.c_str();
        }
    };
};


#endif //SPACIALFREEZE_INSTANCE_H
