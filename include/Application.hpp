/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Camera.hpp"
#include "Shader.hpp"
#include "maths/Matrix4.hpp"

/**
 * @class Application
 * @brief The core of the engine.
 */
class Application {
public:
    /**** Constructor & Destructor ****/

    /**
     * @brief Sets the default value of all member variables and constants.
     */
    Application();

    /**
     * @brief Frees all allocated memory.
     */
     ~Application();

     /**** Public Methods ****/

    /**
     * @brief Contains the main loop.
     */
    void run();

    /**
     * @brief Sets the width and height of the GLFW window.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    void setWindowSize(int width, int height);

    /**
     * @brief Handles the event where the cursor is moved.
     * @param xPos The new x position of the cursor.
     * @param yPos The new y position of the cursor.
     */
    void handleCursorPositionEvent(float xPos, float yPos);

private:
    /**** Private Methods ****/

    /**
     * @brief Polls and handles events with glfw.
     */
    void handleEvents();

    /**
     * @brief Handles keyboard events.
     */
    void handleKeyboardEvents();

    /**
     * @brief Passes a new value of the model matrix to the shader.
     * @param model The new value of the model matrix. It is a product of translation, scale
     * and rotation matrices used to apply transformations on the scene's objects.
     */
    void setModel(const Matrix4& model);

    /**** Variables & Constants ****/
    GLFWwindow* window;  ///< GLFW window.
    unsigned int width;  ///< The width of the window in pixels.
    unsigned int height; ///< The height of the window in pixels.

    vec2 mousePos; ///< The position of the mouse on the screen.

    float time;  ///< The current time in seconds;
    float delta; ///< The time difference between this frame and the previous in seconds.

    bool wireframe; ///< Whether the display mode is in wireframe.

    Shader* shader; ///< The default shader program.

    Matrix4 view;       ///< Allows to simulate the camera's position and orientation.
    Matrix4 projection; ///< Allows to simulate the perspective distortion that occurs when viewing
                        ///< a 3D scene from a specific viewpoint.

    Camera camera; ///< A first camera to move around the scene.
};