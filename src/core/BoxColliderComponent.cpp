void BoxColliderComponent::update(float deltaT) {
    PhysicsComponent::update(deltaT);

    for(auto &collider : colliders) {
        if(collider.id != id) {
            // DoStuff
        }
    }
}

void BoxColliderComponent::setSize(float xwidth, float height, float zwidth) {
    this->xwidth = xwidth;
    this->height = height;
    this->zwidth = zwidth;
}
