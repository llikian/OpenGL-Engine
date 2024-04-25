/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include "callbacks.hpp"
#include "Image.hpp"
#include "maths/transformations.hpp"
#include "mesh/Mesh.hpp"

Application::Application()
    : window(nullptr), width(800), height(600),
      wireframe(false) {

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
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, scrollCallback);

    /**** GLAD ****/
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    /**** OpenGL ****/
    glViewport(0, 0, width, height);

    /**** Other ****/
//    keys.fill(false);
}

Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run() {
    Shader shader("data/shaders/default.vert", "data/shaders/default.frag");

    Mesh mesh(GL_TRIANGLES);
    mesh.addVertex(Point(-0.5f, 0.5f, 0.0f),
                   Vector(1.0f, 0.0f, 0.0f),
                   TexCoord(0.0f, 1.0f));

    mesh.addVertex(Point(0.5f, 0.5f, 0.0f),
                   Vector(0.0f, 1.0f, 0.0f),
                   TexCoord(1.0f, 1.0f));

    mesh.addVertex(Point(0.5f, -0.5f, 0.0f),
                   Vector(0.0f, 0.0f, 1.0f),
                   TexCoord(1.0f, 0.0f));

    mesh.addVertex(Point(-0.5f, -0.5f, 0.0f),
                   Vector(1.0f, 0.0f, 1.0f),
                   TexCoord(0.0f, 0.0f));

    mesh.addFace(0, 1, 2, 3);

    /**** Texture ****/
    Image im("data/textures/container.jpg");
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.getWidth(), im.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, im.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    /**** Main Loop ****/
    while(!glfwWindowShouldClose(window)) {
        handleEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        seconds = glfwGetTime();

        shader.use();
        shader.setUniform("u_transform", Matrix4(1.0f));
        shader.setUniform("u_texture0", 0);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, textureID);

        mesh.draw();

        glfwSwapBuffers(window);
    }
}

void Application::handleKeyEvent(int key, int action, int /* mods */) {
    switch(action) {
        case GLFW_PRESS:
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
                case GLFW_KEY_W:
                    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
                    wireframe = !wireframe;
                    break;
                default:
                    break;
            }
            break;
        case GLFW_RELEASE:
            break;
        case GLFW_REPEAT:
            break;
    }
}

void Application::setWindowSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Application::handleEvents() {
    glfwPollEvents();
}
