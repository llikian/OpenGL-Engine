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
    /**
     * @brief Sets the default value of all member variables and constants.
     */
    Application();

    /**
     * @brief Frees all allocated memory.
     */
     ~Application();

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

private:
    /**** Methods ****/

    /**
     * @brief Polls and handles events with glfw.
     */
    void handleEvents();

    /**** Variables & Constants ****/
    GLFWwindow* window;  ///< GLFW window.
    unsigned int width;  ///< The width of the window in pixels.
    unsigned int height; ///< The height of the window in pixels.
};