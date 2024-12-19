/***************************************************************************************************
 * @file  ApplicationBase.cpp
 * @brief Implementation of the ApplicationBase class
 **************************************************************************************************/

#include "engine/ApplicationBase.hpp"

ApplicationBase::ApplicationBase()
    : window(this),
      mousePos(window.getWidth() / 2.0f, window.getHeight() / 2.0f),
      time(0.0f), delta(0.0f) { }

void ApplicationBase::handleWindowSizeCallback(int width, int height) {
    window.updateSize(width, height);
}

void ApplicationBase::handleFrameBufferSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}

void ApplicationBase::handleKeyCallback(int key, int scancode, int action, int mods) {
    if(repeatableKeys.contains(key)) { // Key is repeatable
        if(action == GLFW_PRESS) {
            repeatableKeys[key] = true;
        } else if(action == GLFW_RELEASE) {
            repeatableKeys[key] = false;
        }
    } else { // Key is not repeatable
        if(action == GLFW_PRESS) {
            keyEvents.push(key);
        }
    }
}

void ApplicationBase::handleMouseButtonCallback(int button, int action, int mods) { }

void ApplicationBase::handleCursorPositionCallback(double xPos, double yPos) {
    mousePos.x = xPos;
    mousePos.y = yPos;
}

void ApplicationBase::handleScrollCallback(double xOffset, double yOffset) { }

void ApplicationBase::handleEvents() {
    glfwPollEvents();

    while(!keyEvents.empty()) {
        handleKeyEvent(keyEvents.front());
        keyEvents.pop();
    }

    for(auto [key, isKeyActive] : repeatableKeys) {
        if(isKeyActive) {
            handleKeyEvent(key);
        }
    }
}