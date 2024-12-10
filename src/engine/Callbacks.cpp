/***************************************************************************************************
 * @file  Callbacks.cpp
 * @brief Implementation of the Callbacks class
 **************************************************************************************************/

#include "engine/Callbacks.hpp"

Callbacks::Callbacks() : windowSizeCallback(nullptr),
                         frameBufferSizeCallback(nullptr),
                         keyCallback(nullptr),
                         mouseButtonCallback(nullptr),
                         cursorPositionCallback(nullptr),
                         scrollCallback(nullptr) { }

void Callbacks::applyCallbacks(GLFWwindow* window) {
    if(windowSizeCallback) { glfwSetWindowSizeCallback(window, *windowSizeCallback); }
    if(frameBufferSizeCallback) { glfwSetFramebufferSizeCallback(window, *frameBufferSizeCallback); }
    if(keyCallback) { glfwSetKeyCallback(window, *keyCallback); }
    if(mouseButtonCallback) { glfwSetMouseButtonCallback(window, *mouseButtonCallback); }
    if(cursorPositionCallback) { glfwSetCursorPosCallback(window, *cursorPositionCallback); }
    if(scrollCallback) { glfwSetScrollCallback(window, *scrollCallback); }
}
