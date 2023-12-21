#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>



enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch); 
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
    void Move(Camera_Movement direction, float deltaTime);
    glm::mat4 GetViewMatrix();
    void Rotate(float angleDelta);
    void ToggleAutoRotate();
    void IncreaseSpeed();
    glm::vec3 GetPosition() const;


private:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    bool autoRotate;
    float rotationAngle;
    void updateCameraVectors();
};



#endif

