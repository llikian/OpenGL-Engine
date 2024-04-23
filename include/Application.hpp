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

private:
    /**** Methods ****/

    /**
     * @brief Initializes GLFW and the GLFW window.
     */
    void initGLFW();

    void handleEvents();

    /**** Variables & Constants ****/
    GLFWwindow* window;    ///< GLFW window.
    const uint32_t width;  ///< The width of the window in pixels.
    const uint32_t height; ///< The height of the window in pixels.
};