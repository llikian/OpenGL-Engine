/***************************************************************************************************
 * @file  GameOfLifeApp.cpp
 * @brief Implementation of the GameOfLifeApp class
 **************************************************************************************************/

#include "applications/GameOfLifeApp.hpp"

#include <cmath>
#include "maths/transformations.hpp"

GameOfLifeApp::GameOfLifeApp()
    : ApplicationBase(),
      wireframe(false), cullface(false), cursorVisible(false),
      shader(nullptr),
      projection(perspective(M_PI_4f, window.getRatio(), 0.1f, 100.0f)),
      camera(Point(0.0f, 2.0f, 5.0f)) {

    /* ---- Repeatable Keys ---- */
    repeatableKeys.emplace(GLFW_KEY_W, false);
    repeatableKeys.emplace(GLFW_KEY_S, false);
    repeatableKeys.emplace(GLFW_KEY_A, false);
    repeatableKeys.emplace(GLFW_KEY_D, false);
    repeatableKeys.emplace(GLFW_KEY_SPACE, false);
    repeatableKeys.emplace(GLFW_KEY_LEFT_SHIFT, false);

    /* ---- GLFW Callbacks ---- */
    setCallbacks<GameOfLifeApp>(window, true, true, true, false, true, false);

    /* ---- Shaders ---- */
    std::string paths[2]{"shaders/game_of_life/game_of_life.vert", "shaders/game_of_life/game_of_life.frag"};
    shader = new Shader(paths, 2, "Default");
    initUniforms();
}

GameOfLifeApp::~GameOfLifeApp() {
    delete shader;
}

void GameOfLifeApp::run() {
    while(!glfwWindowShouldClose(window)) {
        handleEvents();

        glClearColor(0.1, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        updateUniforms();

        calculateMVP(mat4(1.0f));

        glfwSwapBuffers(window);
    }
}

void GameOfLifeApp::handleWindowSizeCallback(int width, int height) {
    ApplicationBase::handleWindowSizeCallback(width, height);

    projection[0][0] = 1.0f / (tanf(M_PI_4f / 2.0f) * window.getRatio());
}

void GameOfLifeApp::handleCursorPositionCallback(double xPos, double yPos) {
    if(!cursorVisible) {
        camera.look(vec2(xPos - mousePos.x, yPos - mousePos.y));
    }

    ApplicationBase::handleCursorPositionCallback(xPos, yPos);
}

void GameOfLifeApp::handleKeyEvent(int key) {
    switch(key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_Z:
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
            wireframe = !wireframe;
            break;
        case GLFW_KEY_C:
            (cullface ? glDisable : glEnable)(GL_CULL_FACE);
            cullface = !cullface;
            break;
        case GLFW_KEY_TAB:
            glfwSetInputMode(window, GLFW_CURSOR, cursorVisible ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            cursorVisible = !cursorVisible;
            break;
        case GLFW_KEY_W:
            camera.move(CameraControls::forward, delta);
            break;
        case GLFW_KEY_S:
            camera.move(CameraControls::backward, delta);
            break;
        case GLFW_KEY_A:
            camera.move(CameraControls::left, delta);
            break;
        case GLFW_KEY_D:
            camera.move(CameraControls::right, delta);
            break;
        case GLFW_KEY_SPACE:
            camera.move(CameraControls::upward, delta);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            camera.move(CameraControls::downward, delta);
            break;
    }
}

void GameOfLifeApp::initUniforms() {
    shader->use();
}

void GameOfLifeApp::updateUniforms() {
    shader->setUniform("cameraPos", camera.getPosition());
}

void GameOfLifeApp::calculateMVP(const mat4& model) {
    shader->setUniform("mvp", camera.getVPmatrix(projection) * model);
    shader->setUniform("model", model);
}
