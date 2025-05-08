/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include "engine/ApplicationBase.hpp"

#include "engine/Camera.hpp"
#include "engine/Scene.hpp"
#include "engine/Shader.hpp"
#include "engine/Texture.hpp"
#include "maths/mat4.hpp"

/**
 * @class Application
 * @brief An Application used to test functionalities.
 */
class Application : public ApplicationBase {
public:
    /* ---- Constructor & Destructor ---- */

    /**
     * @brief Sets the default value of all member variables and constants.
     */
    Application();

    /**
     * @brief Frees all allocated memory.
     */
    ~Application() override;

    /* ---- Public Methods ---- */

    /**
     * @brief Contains the main loop.
     */
    void run() override;

    /* ---- Callbacks ----*/

    /**
     * @brief Handles what happens when the window is resized. Updates the width and height in Window, and
     * updates the projection matrix.
     * @param width The new width.
     * @param height The new height.
     */
    void handleWindowSizeCallback(int width, int height) override;

    /**
     * @brief Handles what happens when the cursor is moved. Handles the camera's movement and updates the
     * mouse position.
     * @param xPos The horizontal position of the mouse.
     * @param yPos The vertical position of the mouse.
     */
    void handleCursorPositionCallback(double xPos, double yPos) override;

private:
    /* ---- Private Methods ---- */

    /**
     * @brief Handles what happends when a specific key is pressed.
     * @param key The key.
     */
    void handleKeyEvent(int key) override;

    /* ---- Variables & Constants ---- */
    bool wireframe;     ///< Whether to display in wireframe mode.
    bool cullface;      ///< Whether face culling is activated.
    bool cursorVisible; ///< Whether the cursor is currently visible.
    bool areAxesDrawn;  ///< Whether the axes are drawn.

    mat4 projection; ///< The projection matrix.

    Camera camera; ///< A first person camera to move around the scene.
};
