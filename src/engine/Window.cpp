/***************************************************************************************************
 * @file  Window.cpp
 * @brief Implementation of the Window class
 **************************************************************************************************/

#include "engine/Window.hpp"

#include <stdexcept>
#include "stb_image.h"

Window::Window(const std::string& name, void* windowUserPointer)
    : window(nullptr) {
    /* ---- GLFW ---- */
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwSetErrorCallback([](int code, const char* message) {
        std::cerr << "GLFW Error '" << code << "' : " << message << '\n';
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1, 1, name.c_str(), nullptr, nullptr);
    if(!window) {
        throw std::runtime_error("Failed to create window.");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, windowUserPointer);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMaximizeWindow(window);
    glfwGetWindowSize(window, reinterpret_cast<int*>(&width), reinterpret_cast<int*>(&height));

    /* ---- GLAD ---- */
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    /* ---- OpenGL ---- */
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE0);

    // Sets the default texture to a plain white color
    const unsigned char white[3]{ 255, 255, 255 };
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, white);

    /* ---- OpenGL Error Callback ---- */
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(
        [](uint source, uint type, uint id, uint severity, int length, const GLchar* message, const void* userParam) {
            if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) { return; }

            std::cerr << "OpenGL Message:"
                << "\n\tID: " << id
                << "\n\tSeverity: ";
            switch(severity) {
                case GL_DEBUG_SEVERITY_LOW:
                    std::cerr << "Low";
                    break;
                case GL_DEBUG_SEVERITY_MEDIUM:
                    std::cerr << "Medium";
                    break;
                case GL_DEBUG_SEVERITY_HIGH:
                    std::cerr << "High";
                    break;
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                default:
                    std::cerr << "Notification";
                    break;
            }

            std::cerr << "\n\tType: ";
            switch(type) {
                case GL_DEBUG_TYPE_ERROR:
                    std::cerr << "Error";
                    break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                    std::cerr << "Deprecated Behavior";
                    break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    std::cerr << "Undefined Behavior";
                    break;
                case GL_DEBUG_TYPE_PORTABILITY:
                    std::cerr << "Portability";
                    break;
                case GL_DEBUG_TYPE_PERFORMANCE:
                    std::cerr << "Performance";
                    break;
                case GL_DEBUG_TYPE_MARKER:
                    std::cerr << "Marker";
                    break;
                case GL_DEBUG_TYPE_PUSH_GROUP:
                    std::cerr << "Push Group";
                    break;
                case GL_DEBUG_TYPE_POP_GROUP:
                    std::cerr << "Pop Group";
                    break;
                case GL_DEBUG_TYPE_OTHER:
                default:
                    std::cerr << "Other";
                    break;
            }

            std::cerr << "\n\tSource: ";
            switch(source) {
                case GL_DEBUG_SOURCE_API:
                    std::cerr << "API";
                    break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                    std::cerr << "Window System";
                    break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER:
                    std::cerr << "Shader Compiler";
                    break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:
                    std::cerr << "Third Party";
                    break;
                case GL_DEBUG_SOURCE_APPLICATION:
                    std::cerr << "Applitcation";
                    break;
                case GL_DEBUG_SOURCE_OTHER:
                default:
                    std::cerr << "Other";
                    break;
            }

            std::cerr << "\n\tMessage: " << message << '\n';
        }, windowUserPointer);

    /* ---- STB ---- */
    stbi_set_flip_vertically_on_load(true);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

Window::operator GLFWwindow*() {
    return window;
}

void Window::updateSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

unsigned int Window::getWidth() const {
    return width;
}

unsigned int Window::getHeight() const {
    return height;
}

vec2 Window::getResolution() const {
    return vec2(static_cast<float>(width), static_cast<float>(height));
}

float Window::getRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}
