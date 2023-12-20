#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>






Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch), 
      MovementSpeed(2.5f), autoRotate(false), rotationAngle(0.0f) {
    updateCameraVectors();
}



void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}


void Camera::Move(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == UP)
        Position += Up * velocity;
    if (direction == DOWN)
        Position -= Up * velocity;
}

void Camera::Rotate(float angleDelta) {
    if (autoRotate) {
        rotationAngle += angleDelta;
        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
        Yaw = rotationAngle;
        updateCameraVectors();
    }
}

void Camera::ToggleAutoRotate() {
    autoRotate = !autoRotate;
    if (autoRotate) rotationAngle = Yaw;
}

void Camera::IncreaseSpeed() {
    MovementSpeed += 0.1f;
}
