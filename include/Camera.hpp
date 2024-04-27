/***************************************************************************************************
 * @file  Camera.hpp
 * @brief Declaration of the Camera class
 **************************************************************************************************/

#pragma once

#include "maths/Matrix4.hpp"
#include "maths/transformations.hpp"
#include "maths/vec2.hpp"
#include "maths/vec3.hpp"

/**
 * @enum CameraControls
 * @brief
 */
enum class CameraControls {
    forward,
    backward,
    left,
    right,
    upward,
    downward
};

/**
 * @class Camera
 * @brief
 */
class Camera {
public:
    Camera(const Point& position);

    Point position;
    Vector front;
    Vector up;

    float yaw;
    float pitch;

    Matrix4 getLookAt();

    void move(CameraControls direction, float deltaTime);

    void look(vec2 mouseOffset);
};