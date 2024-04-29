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
 * @brief Enumeration of the possible controls available for the camera.
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
 * @brief Represents a first person camera for navigating a 3D scene.
 */
class Camera {
public:
    /**
     * @brief
     * @param position
     */
    Camera(const Point& position);

    /**
     * @brief Calculates the look-at matrix corresponding to the camera's position, yaw and pitch.
     * @return The look-at or view matrix.
     */
    Matrix4 getLookAt();

    /**
     * @brief Getter for the position member.
     * @return The position of the camera.
     */
    Point getPosition() const;

    /**
     * @brief Moves the camera's position in the specified direction.
     * @param direction The direction of the movement.
     * @param deltaTime How much time has passed since the last frame in seconds.
     */
    void move(CameraControls direction, float deltaTime);

    /**
     * @brief Rotates the camera accordingly depending of the mouse's offset.
     * @param mouseOffset How much the mouse moved since the last frame in both directions.
     */
    void look(vec2 mouseOffset);

private:
    Point position; ///< The camera's position.

    Vector front; ///< The direction the camera is looking in.
    float yaw;    ///< The camera's yaw ("left-right") angle.
    float pitch;  ///< The camera's pitch ("forward-back") angle.
};