/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "Camera.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
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
     * @brief Handles what happens when a key is pressed.
     * @param key
     * @param action
     * @param mods
     */
    void handleKeyCallback(int key, int action, int mods);

    /**
     * @brief Handles the event where the cursor is moved.
     * @param xPos The new x position of the cursor.
     * @param yPos The new y position of the cursor.
     */
    void handleCursorPositionEvent(float xPos, float yPos);

private:
    /**** Private Methods ****/

    /**
     * @brief Initializes all the uniforms to their correct default values.
     */
    void initUniforms();

    /**
     * @brief Updates all the uniforms.
     */
    void updateUniforms();

    /**
     * @brief Polls and handles events with glfw.
     */
    void handleEvents();

    /**
     * @brief Handles keyboard events.
     */
    void handleKeyboardEvents();

    /**
     * @brief Calculates the MVP (Matrix-View-Projection) Matrix and sends it to the shader.
     * @param model The new value of the model matrix. It is a product of translation, scale
     * and rotation matrices used to apply transformations on the scene's objects.
     */
    void calculateMVP(const Matrix4& model);

    /**
     * @brief Binds a texture to a specific texture unit.
     * @param texture The texture to bind.
     * @param texUnit The texture unit to bind to.
     */
    void bindTexture(const Texture& texture, unsigned int texUnit);

    /**
     * @brief Binds a texture class to a specific texture unit.
     * @param textureID The texture's id.
     * @param texUnit The texture unit to bind to.
     */
    void bindTexture(unsigned int textureID, unsigned int texUnit);

    /**
     * @brief Binds a texture to the active texture unit.
     * @param texture The texture to bind.
     */
    void bindTexture(const Texture& texture);

    /**
     * @brief Binds a texture to the active texture unit.
     * @param textureID The texture's id.
     */
    void bindTexture(unsigned int textureID);

    /**** Variables & Constants ****/
    GLFWwindow* window;  ///< GLFW window.
    unsigned int width;  ///< The width of the window in pixels.
    unsigned int height; ///< The height of the window in pixels.

    std::unordered_map<int, bool> keys; ///< Map of the current state of keys.

    vec2 mousePos; ///< The position of the mouse on the screen.

    float time;  ///< The current time in seconds;
    float delta; ///< The time difference between this frame and the previous in seconds.

    bool wireframe;     ///< Whether to display in wireframe mode.
    bool cullface;      ///< Whether face culling is activated.
    bool cursorVisible; ///< Whether the cursor is currently visible.
    bool areAxesDrawn;  ///< Whether the axes are drawn.
    bool isGridDrawn;   ///< Whether the grid is drawn.
    bool isGroundDrawn; ///< Whether the ground is drawn.

    Shader* shader; ///< The default shader program.

    Matrix4 projection; ///< The projection matrix.

    Camera camera; ///< A first person camera to move around the scene.

    DirectionalLight directionalLight;   ///< Light used for global illumination.
    FlashLight flashlight;               ///< A flashlight.
    std::vector<PointLight> pointLights; ///< Point lights used to light up smaller areas.
};