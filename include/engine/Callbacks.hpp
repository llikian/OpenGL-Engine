/***************************************************************************************************
 * @file  Callbacks.hpp
 * @brief Declaration of the Callbacks class
 **************************************************************************************************/

#pragma once

#include <GLFW/glfw3.h>

/**
 * @class Callbacks
 * @brief
 */
struct Callbacks {
    Callbacks();

    void applyCallbacks(GLFWwindow* window);

    GLFWwindowsizefun windowSizeCallback;
    GLFWframebuffersizefun frameBufferSizeCallback;
    GLFWkeyfun keyCallback;
    GLFWmousebuttonfun mouseButtonCallback;
    GLFWcursorposfun cursorPositionCallback;
    GLFWscrollfun scrollCallback;
};