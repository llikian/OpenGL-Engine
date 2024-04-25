/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include "callbacks.hpp"
#include "Image.hpp"
#include "maths/transformations.hpp"
#include "mesh/Mesh.hpp"
#include "mesh/meshes.hpp"

Application::Application()
    : window(nullptr), width(800), height(600),
      wireframe(false),
      shader(nullptr),
      view(translate(0.0f, 0.0f, -3.0f)),
      projection(perspective(M_PI_4f, 800.0f / 600.0f, 0.1f, 100.0f)) {

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
    glEnable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);

    /**** Shaders & Uniforms ****/
    shader = new Shader("data/shaders/default.vert", "data/shaders/default.frag");
    shader->use();

    shader->setUniform("u_texture0", 0);

    setModel(Matrix4(1.0f));
    shader->setUniform("u_view", view);
    shader->setUniform("u_projection", projection);
}

Application::~Application() {
    delete shader;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run() {
    Mesh mesh = Meshes::cube();

    Point cubePositions[] {
        { 0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        Point eye = 10.0f * Point(glm::cos(glfwGetTime()), 0.5f, glm::sin(glfwGetTime()));
        shader->setUniform("u_view", lookAt(eye, Point(), Vector(0.0f, 1.0f, 0.0f)));

        glBindTexture(GL_TEXTURE_2D, textureID);

        for(const vec3& v : cubePositions) {
            setModel(translate(v));
            mesh.draw();
        }

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

    projection = perspective(M_PI_4f, static_cast<float>(width) / height, 0.1f, 100.0f);
}

void Application::handleEvents() {
    glfwPollEvents();
}

void Application::setModel(const Matrix4& model) {
    shader->setUniform("u_model", model);
}