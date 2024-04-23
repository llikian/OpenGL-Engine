/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include "callbacks.hpp"

Application::Application()
    : window(nullptr), width(800), height(600) {

    /**** GLFW ****/
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "OpenGL Engine", nullptr, nullptr);
    if(!window) {
        throw std::runtime_error("Failed to create window.");
    }

    glfwMakeContextCurrent(window);

    /**** GLFW Callbacks ****/
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    /**** GLAD ****/
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    /**** OpenGL ****/
    glViewport(0, 0, width, height);
}

Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run() {
    while(!glfwWindowShouldClose(window)) {
        handleEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }
}

void Application::handleEvents() {
    glfwPollEvents();

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Application::setWindowSize(int width, int height) {
    this->width = width;
    this->height = height;
}
