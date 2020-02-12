void PhysicsComponent::update(float deltaT) {
    if (transformation != nullptr) {
        transformation->position += glm::vec3(0.0f, deltaT * velocity, 0.0f);
    } else {
        logger::error("Physics Component " + std::to_string(id) + " has no transformation");
    }
}
