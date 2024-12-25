/***************************************************************************************************
 * @file  GameOfLifeApp.hpp
 * @brief Declaration of the GameOfLifeApp class
 **************************************************************************************************/

#pragma once

#include "applications/game_of_life/Cell.hpp"
#include "applications/game_of_life/Ruleset.hpp"
#include "engine/ApplicationBase.hpp"
#include "engine/Camera.hpp"
#include "engine/Shader.hpp"
#include "maths/mat4.hpp"
#include "mesh/meshes.hpp"

#define CELL_SIZE 72

/**
 * @class GameOfLifeApp
 * @brief
 */
class GameOfLifeApp : public ApplicationBase {
public:
    /* ---- Constructor & Destructor ---- */

    /**
     * @brief Sets the default value of all member variables and constants.
     */
    GameOfLifeApp();

    /**
     * @brief Frees all allocated memory.
     */
    ~GameOfLifeApp();

    /* ---- Public Methods ---- */

    /**
     * @brief Contains the main loop.
     */
    void run();

    /* ---- Callbacks ----*/

    /**
     * @brief Handles what happens when the window is resized. Updates the width and height in Window, and
     * updates the projection matrix.
     * @param width The new width.
     * @param height The new height.
     */
    void handleWindowSizeCallback(int width, int height);

    /**
     * @brief Handles what happens when the cursor is moved. Handles the camera's movement and updates the
     * mouse position.
     * @param xPos The horizontal position of the mouse.
     * @param yPos The vertical position of the mouse.
     */
    void handleCursorPositionCallback(double xPos, double yPos);

private:
    /* ---- Private Methods ---- */

    /**
     * @brief Handles what happends when a specific key is pressed.
     * @param key The key.
     */
    void handleKeyEvent(int key);

    /**
     * @brief Initializes all the uniforms to their correct default values.
     */
    void initUniforms();

    /**
     * @brief Updates all the uniforms.
     */
    void updateUniforms();

    void nextGeneration();

    /* ---- Variables & Constants ---- */
    bool wireframe;     ///< Whether to display in wireframe mode.
    bool cullface;      ///< Whether face culling is activated.
    bool cursorVisible; ///< Whether the cursor is currently visible.

    Shader* shader; ///< The default shader program.

    mat4 projection; ///< The projection matrix.

    Camera camera; ///< A first person camera to move around the scene.

    Ruleset ruleset;
    Cell cells[CELL_SIZE][CELL_SIZE][CELL_SIZE];

    float cubeSize;
    Mesh cube;
};