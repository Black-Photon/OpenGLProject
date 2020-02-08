#ifndef OPENGLPROJECT_CAMERA_H
#define OPENGLPROJECT_CAMERA_H

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum Axis {
    X,
    Y,
    Z
};

enum Rotation {
    PITCH,
    YAW
};

// Distance beyond which objects will be shown
const float MIN_DISTANCE = 0.1f;
// Distance beyond which objects won't be shown
const float MAX_DISTANCE = 100.0f;

// Camera Speed
const float SPEED = 2.5f;

/**
 * Controls the camera
 */
class Camera {
public:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitch = 0;
    float yaw = 0;
    float fov = 45.0f;

    // Display Aspect Ratio
    float ASPECT_RATIO;

    // Whether the pitch is restricted between -90 and 90 degrees
    bool lockPitch = true;

    /**
     * Creates a camera of the given aspect ratio
     * @param aspectRatio Screen Display ratio
     */
    explicit Camera(const float &aspectRatio);
    /**
     * Moves the camera in the relative direction given
     * @param direction Direction to move
     * @param deltaT Time since last frame
     */
    void moveRelative(Direction direction, float deltaT);
    /**
     * Moves the camera in the relative direction given by the distance given
     * @param direction Direction to move
     * @param distance Distance to move
     */
    void moveByRelative(Direction direction, float distance);
    /**
     * Moves the camera in the absolute direction given
     * @param direction Direction to move
     * @param deltaT Time since last frame
     */
    void move(Axis direction, float deltaT);
    /**
     * Moves the camera in the absolute direction given by the distance given
     * @param direction Direction to move
     * @param distance Distance to move
     */
    void moveBy(Axis direction, float distance);
    /**
     * Moves the camera in the relative direction given on the plane given
     * @param direction Direction to move
     * @param plane Axis on which there will be no movement
     * @param deltaT Time since last frame
     */
    void moveOnPlane(Direction direction, Axis plane, float deltaT);
    /**
     * Moves the camera in the relative direction given on the plane given by the distance given
     * @param direction Direction to move
     * @param plane Axis on which there will be no movement
     * @param distance Distance to move
     */
    void moveByOnPlane(Direction direction, Axis plane, float distance);
    /**
     * Rotates the camera in the direction specified by the angle specified
     * @param rotation Direction to rotate
     * @param angle Angle to rotate in degrees
     */
    void rotate(Rotation rotation, float angle);
    /**
     * Rotates the camera in the direction specified by the angle specified
     * @param rotation Direction to rotate
     * @param angle Angle to rotate in radians
     */
    void rotateRad(Rotation rotation, float angle);
    /**
     * Zooms the camera out by the amount specified (FoV)
     * @param amount Amount to zoom out by
     */
    void zoom(float amount);
    /**
     * Gets the transformation to translate world coordinates to camera coordinates
     * @return Matrix describing the above transformation
     */
    glm::mat4 getTransformation() const;
    /**
     * Gets the transformation to camera coordinates into a perspective viewspace
     * @return Matrix describing the above transformation
     */
    glm::mat4 getPerspectiveTransformation() const;

    std::vector<glm::mat4> getCubemapTransforms() const;

private:
    /**
     * Finds the modulus of a value, restricting it to between -180 and 180 degrees
     * @param in Value to Modulus
     * @return Value after Modulus
     */
    static float modulus(float in);
};

#endif //OPENGLPROJECT_CAMERA_H
