/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "applications/Application.hpp"

#include <cmath>
#include "maths/geometry.hpp"
#include "maths/mat3.hpp"
#include "maths/transforms.hpp"
#include "maths/trigonometry.hpp"
#include "mesh/Mesh.hpp"
#include "mesh/meshes.hpp"

Application::Application()
    : ApplicationBase("OpenGL Engine"),
      wireframe(false), cullface(true), cursorVisible(false),
      areAxesDrawn(false), isGridDrawn(false), isGroundDrawn(true),
      hasGlobalLighting(false),
      shader(nullptr),
      projection(perspective(M_PI_4f, window.getRatio(), 0.1f, 100.0f)),
      camera(vec3(0.0f, 2.0f, 5.0f)) {
    /* ---- Repeatable Keys ---- */
    repeatableKeys.emplace(GLFW_KEY_W, false);
    repeatableKeys.emplace(GLFW_KEY_S, false);
    repeatableKeys.emplace(GLFW_KEY_A, false);
    repeatableKeys.emplace(GLFW_KEY_D, false);
    repeatableKeys.emplace(GLFW_KEY_SPACE, false);
    repeatableKeys.emplace(GLFW_KEY_LEFT_SHIFT, false);

    /* ---- GLFW Callbacks ---- */
    setCallbacks<Application>(window, true, true, true, false, true, false);

    /* ---- Shaders ---- */
    std::string paths[2]{ "shaders/application/default.vert", "shaders/application/default.frag" };
    shader = new Shader(paths, 2, "Default");
    initUniforms();
}

Application::~Application() {
    delete shader;
}

void Application::run() {
    LineMesh grid = Meshes::grid(10.0f, 10);
    LineMesh axes = Meshes::axes(1.0f);
    Mesh sphere = Meshes::sphere(16, 32);

    /* ---- Main Loop ---- */
    while(!glfwWindowShouldClose(window)) {
        handleEvents();

        glClearColor(0.1, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        updateUniforms();
        calculateMVP(mat4(1.0f));
        bindTexture(0);

        if(isGridDrawn) { grid.draw(); }

        if(areAxesDrawn) {
            calculateMVP(translate(camera.getPosition() + 2.0f * camera.getDirection()) * scale(0.5f));
            axes.draw();
        }

        calculateMVP(mat4(1.0f));
        sphere.draw();

        glfwSwapBuffers(window);
    }
}

void Application::handleWindowSizeCallback(int width, int height) {
    ApplicationBase::handleWindowSizeCallback(width, height);

    projection(0, 0) = 1.0f / (tanf(M_PI_4f / 2.0f) * window.getRatio());
}

void Application::handleCursorPositionCallback(double xPos, double yPos) {
    if(!cursorVisible) { camera.look(vec2(xPos - mousePos.x, yPos - mousePos.y)); }

    ApplicationBase::handleCursorPositionCallback(xPos, yPos);
}

void Application::handleKeyEvent(int key) {
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
        case GLFW_KEY_Q:
            areAxesDrawn = !areAxesDrawn;
            break;
        case GLFW_KEY_G:
            isGridDrawn = !isGridDrawn;
            break;
        case GLFW_KEY_H:
            isGroundDrawn = !isGroundDrawn;
            break;
        case GLFW_KEY_J:
            hasGlobalLighting = !hasGlobalLighting;
            shader->setUniform("globalLighting", hasGlobalLighting);
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
        default: break;
    }
}

void Application::initUniforms() {
    shader->use();
}

void Application::updateUniforms() {
    shader->setUniform("cameraPos", camera.getPosition());
}

void Application::calculateMVP(const mat4& model) const {
    shader->setUniform("mvp", camera.getVPmatrix(projection) * model);
    shader->setUniform("model", model);
    shader->setUniform("normalModel", transposeInverse(model));
}

void Application::bindTexture(const Texture& texture, unsigned int texUnit) {
    texture.bind(texUnit);
}

void Application::bindTexture(unsigned int textureID, unsigned int texUnit) {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Application::bindTexture(const Texture& texture) {
    texture.bind();
}

void Application::bindTexture(unsigned int textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
}
