#ifndef SPACIALFREEZE_PHYSICSCOMPONENT_H
#define SPACIALFREEZE_PHYSICSCOMPONENT_H

#include <string>

class PhysicsComponent : public Component {
public:
    PhysicsComponent() = default;
    void update(float deltaT) override;

protected:
    float velocity = -0.01f;
};


#endif //SPACIALFREEZE_PHYSICSCOMPONENT_H
