/***************************************************************************************************
 * @file  ApplicationBase.hpp
 * @brief Declaration of the ApplicationBase class
 **************************************************************************************************/

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Window.hpp"
#include "maths/vec2.hpp"

/**
 * @class ApplicationBase
 * @brief The core of the engine.
 */
class ApplicationBase {
public:
    /* ---- Constructor & Destructor ---- */

    /**
     * @brief Sets the default value of all member variables and constants.
     */
    ApplicationBase();

    /* ---- Public Methods ---- */

    /**
     * @brief Contains the main loop.
     */
    virtual void run() = 0;

    /* ---- Callbacks ---- */

    virtual void handleWindowSizeCallback(int width, int height);

    virtual void handleFrameBufferSizeCallback(int width, int height);

    virtual void handleKeyCallback(int key, int scancode, int action, int mods);

    virtual void handleMouseButtonCallback(int button, int action, int mods);

    virtual void handleCursorPositionCallback(double xPos, double yPos);

    virtual void handleScrollCallback(double xOffset, double yOffset);

protected:
    /* ---- Protected Methods ---- */

    /**
     * @brief Polls and handles events.
     */
    void handleEvents();

    /**
     * @brief Handles what happens when a specific key is pressed.
     */
    virtual void handleKeyEvent(int key) = 0;

    /* ---- Variables & Constants ---- */
    Window window;  ///< The GLFW window.

    std::unordered_map<int, bool> keys; ///< Map of the current state of keys.
    std::unordered_set<int> controls; ///< List of all keys which have an action associated to them.

    vec2 mousePos; ///< The position of the mouse on the screen.

    float time;  ///< The current time in seconds;
    float delta; ///< The time difference between this frame and the previous in seconds.
};