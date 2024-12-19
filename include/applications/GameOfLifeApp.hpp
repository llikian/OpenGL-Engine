/***************************************************************************************************
 * @file  GameOfLifeApp.hpp
 * @brief Declaration of the GameOfLifeApp class
 **************************************************************************************************/

#pragma once

#include "engine/ApplicationBase.hpp"

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

    void handleWindowSizeCallback(int width, int height);

    void handleCursorPositionCallback(double xPos, double yPos);

private:
    /* ---- Private Methods ---- */

    void handleKeyEvent(int key);

};