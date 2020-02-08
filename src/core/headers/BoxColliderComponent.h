#ifndef SPACIALFREEZE_BOXCOLLIDERCOMPONENT_H
#define SPACIALFREEZE_BOXCOLLIDERCOMPONENT_H


class BoxColliderComponent : public PhysicsComponent{
public:
    BoxColliderComponent() = default;
    void update(float deltaT) override;
    void setSize(float xwidth, float height, float zwidth);
    void setIsInverted(bool inverted) {
        isInverted = inverted;
    }
    void setCollisionList(std::vector<BoxColliderComponent> &colliders) {
        this->colliders = colliders;
    }

private:
    float xwidth;
    float height;
    float zwidth;
    bool isInverted;
    std::vector<BoxColliderComponent> colliders;
};


#endif //SPACIALFREEZE_BOXCOLLIDERCOMPONENT_H
