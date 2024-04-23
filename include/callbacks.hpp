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