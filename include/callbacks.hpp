/***************************************************************************************************
 * @file  callbacks.hpp
 * @brief Declaration of the callback functions for OpenGL
 **************************************************************************************************/

#pragma once

#include "Application.hpp"

extern Application app;

/**
 * @brief Callback for when the specified window is resized.
 * @param window The GLFW window.
 * @param width The new width of the window.
 * @param height The new height of the window.
 */
void windowSizeCallback(GLFWwindow* window, int width, int height);

/**
 * @brief Callback for when the framebuffer of the specified window is resized.
 * @param window The GLFW window.
 * @param width The new width of the frame buffer.
 * @param height The new height of the frame buffer.
 */
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

/**
 * @brief Callback for when a button of the mouse is pressed or released.
 * @param window The GLFW window.
 * @param button The mouse button that was pressed or released. Can be one of three values:\n
 * - GLFW_MOUSE_BUTTON_LEFT
 * - GLFW_MOUSE_BUTTON_MIDDLE
 * - GLFW_MOUSE_BUTTON_RIGHT
 * @param action Tha action performed.  Can be one of two values:\n
 * - GLFW_PRESS: The button was pressed.\n
 * - GLFW_RELEASE: The button was released.
 * @param mods Bit field representing the modifier keys that were held down when the event occured.
 * It is a bitwise OR combination of the following flags:\n
 * - GLFW_MOD_SHIFT\n
 * - GLFW_MOD_CONTROL\n
 * - GLFW_MOD_ALT\n
 * - GLFW_MOD_SUPER\n
 */
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

/**
 * @brief Callback for when the mouse is moved in the window.
 * @param window The GLFW window.
 * @param xPos The new horizontal position of the mouse.
 * @param yPos The new vertical position of the mouse.
 */
void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

/**
 * @brief Callback for when the mouse wheel is scrolled.
 * @param window The GLFW window.
 * @param xOffset How much the mouse moved in the horizontal direction.
 * @param yOffset How much the mouse moved in the vertical direction.
 */
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);