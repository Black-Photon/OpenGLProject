void PhysicsComponent::update(float deltaT) {
    transformation->position += glm::vec3(0.0f, deltaT * velocity, 0.0f);
}
