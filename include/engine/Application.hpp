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
#include "Window.hpp"
#include "maths/mat4.hpp"

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
     * @param key The affected key. This is a platform-independent key code using GLFW_KEY_*.
     * @param action The action performed. Can be one of three values:\n
     * - GLFW_PRESS: The key was pressed.\n
     * - GLFW_RELEASE: The key was released.\n
     * - GLFW_REPEAT: The key was held down and is being repeatedly sent.
     * @param mods Bit field representing the modifier keys that were held down when the event occured.
     * It is a bitwise OR combination of the following flags:\n
     * - GLFW_MOD_SHIFT\n
     * - GLFW_MOD_CONTROL\n
     * - GLFW_MOD_ALT\n
     * - GLFW_MOD_SUPER\n
     */
    void handleKeyCallback(int key, int action, int mods);

    /**
     * @brief Handles the event where the cursor is moved.
     * @param xPos The new x position of the cursor.
     * @param yPos The new y position of the cursor.
     */
    void handleCursorPositionEvent(float xPos, float yPos);

    /**** Callbacks ****/

    /**
     * @brief Callback for when the specified window is resized.
     * @param window The GLFW window.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    static void windowSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * @brief Callback for when the framebuffer of the specified window is resized.
     * @param window The GLFW window.
     * @param width The new width of the frame buffer.
     * @param height The new height of the frame buffer.
     */
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * @brief Callback for when a key is pressed, released or held down.
     * @param window The GLFW window.
     * @param key The affected key. This is a platform-independent key code using GLFW_KEY_*.
     * @param scancode The system-specific scancode for the key.
     * @param action The action performed. Can be one of three values:\n
     * - GLFW_PRESS: The key was pressed.\n
     * - GLFW_RELEASE: The key was released.\n
     * - GLFW_REPEAT: The key was held down and is being repeatedly sent.
     * @param mods Bit field representing the modifier keys that were held down when the event occured.
     * It is a bitwise OR combination of the following flags:\n
     * - GLFW_MOD_SHIFT\n
     * - GLFW_MOD_CONTROL\n
     * - GLFW_MOD_ALT\n
     * - GLFW_MOD_SUPER\n
     */
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief Callback for when the mouse is moved in the window.
     * @param window The GLFW window.
     * @param xPos The new horizontal position of the mouse.
     * @param yPos The new vertical position of the mouse.
     */
    static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

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
    void calculateMVP(const mat4& model);

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
    Window window;  ///< The GLFW window.

    std::unordered_map<int, bool> keys; ///< Map of the current state of keys.

    vec2 mousePos; ///< The position of the mouse on the screen.

    float time;  ///< The current time in seconds;
    float delta; ///< The time difference between this frame and the previous in seconds.

    bool wireframe;         ///< Whether to display in wireframe mode.
    bool cullface;          ///< Whether face culling is activated.
    bool cursorVisible;     ///< Whether the cursor is currently visible.
    bool areAxesDrawn;      ///< Whether the axes are drawn.
    bool isGridDrawn;       ///< Whether the grid is drawn.
    bool isGroundDrawn;     ///< Whether the ground is drawn.
    bool hasGlobalLighting; ///< Whether the scene has global lighting.

    Shader* shader; ///< The default shader program.

    mat4 projection; ///< The projection matrix.

    Camera camera; ///< A first person camera to move around the scene.

    DirectionalLight directionalLight;   ///< Light used for global illumination.
    FlashLight flashlight;               ///< A flashlight.
    std::vector<PointLight> pointLights; ///< Point lights used to light up smaller areas.
};