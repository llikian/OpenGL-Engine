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

#include "Shader.hpp"

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
     * @brief Handles the event in which a key is pressed, released or held down.
     * @param key The affected key. This is a platform-independent key code using GLFW_KEY_*.
     * @param action The action performed. Can be one of three things:\n
     * - GLFW_PRESS: The key was pressed.\n
     * - GLFW_RELEASE: The key was released.\n
     * - GLFW_REPEAT: The key was held down and is being repeatedly sent.
     * @param mods Bit field representing the modifier keys that were held down when the event occured.
     * It is a bitwise combination of the following flags:\n
     * - GLFW_MOD_SHIFT\n
     * - GLFW_MOD_CONTROL\n
     * - GLFW_MOD_ALT\n
     * - GLFW_MOD_SUPER\n
     */
    void handleKeyEvent(int key, int action, int mods);

private:
    /**** Private Methods ****/

    /**
     * @brief Polls and handles events with glfw.
     */
    void handleEvents();

    /**** Variables & Constants ****/
    GLFWwindow* window;  ///< GLFW window.
    unsigned int width;  ///< The width of the window in pixels.
    unsigned int height; ///< The height of the window in pixels.

    bool wireframe; ///< Whether the display mode is in wireframe.

    double seconds; ///< Time ellapsed since glfw was initialized.
};