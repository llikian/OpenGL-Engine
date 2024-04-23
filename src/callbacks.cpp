/***************************************************************************************************
 * @file  callbacks.cpp
 * @brief Implementation of the callback functions for OpenGL
 **************************************************************************************************/

#include "callbacks.hpp"

void windowSizeCallback(GLFWwindow* /* window */, int width, int height) {
    app.setWindowSize(width, height);
}

void frameBufferSizeCallback(GLFWwindow* /* window */, int width, int height) {
    glViewport(0, 0, width, height);
}
