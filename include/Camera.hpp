/***************************************************************************************************
 * @file  Camera.hpp
 * @brief Declaration of the Camera class
 **************************************************************************************************/

#pragma once

#include "maths/mat4.hpp"
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
     * @brief Calculates the product of the projection matrix with the view (or look-at) matrix.
     * @param projection The projection matrix.
     * @return The product of the projection matrix with the view (or look-at) matrix corresponding
     * to the camera.
     */
    mat4 getVPmatrix(const mat4& projection);

    /**
     * @brief Getter for the position member.
     * @return The position of the camera.
     */
    Point getPosition() const;

    /**
     * @brief Getter for the front member.
     * @return The direction of the camera.
     */
    Point getDirection() const;

    /**
     * @brief Getter for the right member.
     * @return The right vector of the camera.
     */
    Point getRight() const;

    /**
     * @brief Getter for the up member.
     * @return The up vector of the camera.
     */
    Point getUp() const;

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

    float yaw;    ///< The camera's yaw ("left-right") angle.
    float pitch;  ///< The camera's pitch ("forward-back") angle.

    Vector front; ///< The front vector, the direction the camera is looking in.
    Vector right; ///< The right vector, cross product of the front vector and the world up.
    Vector up;    ///< The up vector, cross product of the right vector and the front vector.

    const Vector worldUp;

    mat4 view; ///< The view matrix corresponding to the camera.
};