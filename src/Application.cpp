/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include <cmath>

#include "callbacks.hpp"
#include "Image.hpp"

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
    float vertices[] = {
        // Positions         // Colors            // Texture Coordinates
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,   // Bottom Right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f,   // Bottom Left
        -0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    0.0f, 1.0f,   // Top Left
        0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f    // Top Right
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader shader("data/shaders/default.vert", "data/shaders/default.frag");

    /**** EBO (Element Buffer Objects) ****/
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    /**** VAO (Vertex Array Object) ****/
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    int size = sizeof(float);
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * size, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * size, reinterpret_cast<void*>(size * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * size, reinterpret_cast<void*>(size * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /**** Texture ****/
    Image im("data/textures/container.jpg");
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.getWidth(), im.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, im.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    Image im2("data/textures/wall.jpg");
    unsigned int textureID2;
    glGenTextures(1, &textureID2);
    glBindTexture(GL_TEXTURE_2D, textureID2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im2.getWidth(), im2.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, im2.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    /**** Main Loop ****/
    while(!glfwWindowShouldClose(window)) {
        handleEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        seconds = glfwGetTime();

        shader.use();
        shader.setUniform("u_texture0", 0);
        shader.setUniform("u_texture0", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureID2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

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
