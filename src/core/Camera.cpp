Camera::Camera(const float &aspectRatio)
{
    ASPECT_RATIO = aspectRatio;
}

void Camera::moveRelative(Direction direction, float deltaT)
{
    float cameraSpeed = SPEED * deltaT;
    moveByRelative(direction, cameraSpeed);
}

void Camera::moveByRelative(Direction direction, float distance)
{
    if (direction == FORWARD)
        cameraPos += distance * cameraFront;
    if (direction == BACKWARD)
        cameraPos -= distance * cameraFront;
    if (direction == LEFT)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * distance;
    if (direction == RIGHT)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * distance;
}

void Camera::move(Axis direction, float deltaT)
{
    float cameraSpeed = SPEED * deltaT;
    moveBy(direction, cameraSpeed);
}

void Camera::moveBy(Axis direction, float distance)
{
    if (direction == X)
        cameraPos.x += distance;
    if (direction == Y)
        cameraPos.y += distance;
    if (direction == Z)
        cameraPos.z += distance;
}

void Camera::moveOnPlane(Direction direction, Axis plane, float deltaT)
{
    float cameraSpeed = SPEED * deltaT;
    moveByOnPlane(direction, plane, cameraSpeed);
}

void Camera::moveByOnPlane(Direction direction, Axis plane, float distance)
{
    glm::vec3 movement;

    if (direction == FORWARD)
        movement = distance * cameraFront;
    if (direction == BACKWARD)
        movement = -distance * cameraFront;
    if (direction == LEFT)
        movement = -glm::normalize(glm::cross(cameraFront, cameraUp)) * distance;
    if (direction == RIGHT)
        movement = glm::normalize(glm::cross(cameraFront, cameraUp)) * distance;

    if (plane == X)
        movement.x = 0;
    if (plane == Y)
        movement.y = 0;
    if (plane == Z)
        movement.z = 0;

    cameraPos += movement;
}

void Camera::rotate(Rotation rotation, float angle)
{
    switch (rotation) {
        case PITCH:
            pitch += angle;

            if(lockPitch) {
                // Stops you looking below or above
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;
            }

            pitch = modulus(pitch);
            break;
        case YAW:
            yaw += angle;

            yaw = modulus(yaw);
            break;
        default:
            throw std::invalid_argument("rotation");
    }

    // Applies as a vector to the camera forward direction
    glm::vec3 direction;
    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(direction);
}

void Camera::rotateRad(Rotation rotation, float angle)
{
    rotate(rotation, glm::degrees(angle));
}

glm::mat4 Camera::getTransformation() const
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::getPerspectiveTransformation() const
{
    return glm::perspective(glm::radians(fov), ASPECT_RATIO, MIN_DISTANCE, MAX_DISTANCE);
}

std::vector<glm::mat4> Camera::getCubemapTransforms() const
{
    glm::mat4 cubeProj = getPerspectiveTransformation();

    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(cubeProj *
                               glm::lookAt(cameraPos, cameraPos + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    shadowTransforms.push_back(cubeProj *
                               glm::lookAt(cameraPos, cameraPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    shadowTransforms.push_back(cubeProj *
                               glm::lookAt(cameraPos, cameraPos + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    shadowTransforms.push_back(cubeProj *
                               glm::lookAt(cameraPos, cameraPos + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)));
    shadowTransforms.push_back(cubeProj *
                               glm::lookAt(cameraPos, cameraPos + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)));
    shadowTransforms.push_back(cubeProj *
                               glm::lookAt(cameraPos, cameraPos + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0)));

    return shadowTransforms;
}

float Camera::modulus(float in)
{
    while (in < -180.0f) {
        in += 360;
    }
    while (in > 180.0f) {
        in -= 360;
    }

    return in;
}