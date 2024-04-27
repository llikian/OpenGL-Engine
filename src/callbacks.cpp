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

void mouseButtonCallback(GLFWwindow* /* window */, int button, int action, int mods) {

}

void cursorPositionCallback(GLFWwindow* /* window */, double xPos, double yPos) {
    app.handleCursorPositionEvent(xPos, yPos);
}

void scrollCallback(GLFWwindow* /* window */, double xOffset, double yOffset) {

}
