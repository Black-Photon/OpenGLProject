#ifndef SPACIALFREEZE_COMPONENT_H
#define SPACIALFREEZE_COMPONENT_H

class Component {
protected:
    Component() {
        id = global_id++;
    };
    static int global_id;
public:
    Transformation *transformation = nullptr;
    virtual void update(float) = 0;
    void setTransformation(Transformation *transformation) {
        this->transformation = transformation;
    };
    int id;
};

int Component::global_id = 0;


#endif //SPACIALFREEZE_COMPONENT_H
