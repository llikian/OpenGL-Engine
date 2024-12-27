/***************************************************************************************************
 * @file  Camera.hpp
 * @brief Declaration of the Camera class
 **************************************************************************************************/

#pragma once

#include <maths/vec2.hpp>
#include <maths/vec3.hpp>
#include <maths/vec4.hpp>
#include <maths/mat4.hpp>

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
     * @brief Creates a camera at a specified position looking forward.
     * @param position The camera's position.
     */
    Camera(const vec3& position);

    /**
     * @brief Creates a camera at a specified position looking towards a specified point.
     * @param position The camera's position.
     * @param target The point the camera is looking towards.
     */
    Camera(const vec3& position, const vec3& target);

    /**
     * @brief Calculates the product of the projection matrix with the view (or look-at) matrix.
     * @param projection The projection matrix.
     * @return The product of the projection matrix with the view (or look-at) matrix corresponding
     * to the camera.
     */
    mat4 getVPmatrix(const mat4& projection) const;

    /**
     * @brief Getter for the view member.
     * @return The view (or look-at) matrix corresponding to the camera.
     */
    const mat4& getViewMatrix() const;

    /**
     * @brief Getter for the position member.
     * @return The position of the camera.
     */
    vec3 getPosition() const;

    /**
     * @brief Getter for the position member.
     * @return A const reference to the camera's position.
     */
    const vec3& getPositionReference() const;

    /**
     * @brief Getter for the front member.
     * @return The direction of the camera.
     */
    vec3 getDirection() const;

    /**
     * @brief Getter for the right member.
     * @return The right vector of the camera.
     */
    vec3 getRight() const;

    /**
     * @brief Getter for the up member.
     * @return The up vector of the camera.
     */
    vec3 getUp() const;

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

    float movementSpeed; ///< The speed at which the camera moves.

private:

    /**
     * @brief Updates the front, right and up vectors and uses these values to update the view matrix.
     */
    void updateViewMatrix();

    vec3 position; ///< The camera's position.

    float yaw;    ///< The camera's yaw ("left-right") angle.
    float pitch;  ///< The camera's pitch ("forward-back") angle.

    vec3 front; ///< The front vector, the direction the camera is looking in.
    vec3 right; ///< The right vector, cross product of the front vector and the world up.
    vec3 up;    ///< The up vector, cross product of the right vector and the front vector.

    const vec3 worldUp; ///< The world up vector, represents where the general "up" is.

    mat4 view; ///< The view matrix corresponding to the camera.
};