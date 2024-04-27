/***************************************************************************************************
 * @file  Camera.cpp
 * @brief Implementation of the Camera class
 **************************************************************************************************/

#include "Camera.hpp"

#include <limits>

Camera::Camera(const Point& position)
    : position(position),
      front(0.0f, 0.0f, -1.0f),
      up(0.0f, 1.0f, 0.0f),
      yaw(2.0f * M_PIf),
      pitch(0.0f) { }

Matrix4 Camera::getLookAt() {
    return lookAt(position, position + front, up);
}

void Camera::move(CameraControls direction, float deltaTime) {
    const float speed = 5.0f * deltaTime;

    switch(direction) {
        case CameraControls::forward:
            position += front * speed;
            break;
        case CameraControls::backward:
            position -= front * speed;
            break;
        case CameraControls::left:
            position -= normalize(glm::cross(front, up)) * speed;
            break;
        case CameraControls::right:
            position += normalize(glm::cross(front, up)) * speed;
            break;
        case CameraControls::upward:
            position += up * speed;
            break;
        case CameraControls::downward:
            position -= up * speed;
            break;
    }
}

void Camera::look(vec2 mouseOffset) {
    constexpr float sensitivity = 0.1f;
    constexpr float epsilon = 0.00001f;
    mouseOffset *= sensitivity;

    yaw += glm::radians(mouseOffset.x);
    if(yaw > 2.0f * M_PIf) {
        yaw -= 2.0f * M_PIf;
    } else if(yaw < -2.0f * M_PIf) {
        yaw += 2.0f * M_PIf;
    }

    pitch -= glm::radians(mouseOffset.y);
    if(pitch > M_PI_2f - epsilon) {
        pitch = M_PI_2f - epsilon;
    } else if(pitch < -M_PI_2f + epsilon) {
        pitch = -M_PI_2f + epsilon;
    }

    front.x = cosf(pitch) * cosf(yaw);
    front.y = sinf(pitch);
    front.z = cosf(pitch) * sinf(yaw);
}
