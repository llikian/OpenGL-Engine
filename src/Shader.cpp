/***************************************************************************************************
 * @file  Shader.cpp
 * @brief Implementation of the Shader class
 **************************************************************************************************/

#include "Shader.hpp"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
    int messageLength;

    /**** Vertex Shader ****/
    std::ifstream vertexShaderFile(vertexShaderPath);
    if(!vertexShaderFile.is_open()) {
        throw std::runtime_error("Failed to open vertex shader.");
    }

    std::string vertexShaderCode = (std::stringstream() << vertexShaderFile.rdbuf()).str();
    const char* vertexShader = vertexShaderCode.c_str();
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
    glCompileShader(vertexShaderID);

    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &messageLength);
    if(messageLength > 0) {
        char* message = new char[messageLength];
        glGetShaderInfoLog(vertexShaderID, messageLength, nullptr, message);

        std::string errorMessage = "Failed to compile vertex shader :\n";
        errorMessage += message;

        delete[] message;

        throw std::runtime_error(errorMessage);
    }

    /**** Fragment Shader ****/
    std::ifstream fragmentShaderFile(fragmentShaderPath);
    if(!fragmentShaderFile.is_open()) {
        throw std::runtime_error("Failed to open fragment shader.");
    }

    std::string fragmentShaderCode = (std::stringstream() << fragmentShaderFile.rdbuf()).str();
    const char* fragmentShader = fragmentShaderCode.c_str();
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShader, nullptr);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &messageLength);
    if(messageLength > 0) {
        char* message = new char[messageLength];
        glGetShaderInfoLog(fragmentShaderID, messageLength, nullptr, message);

        std::string errorMessage = "Failed to compile fragment shader :\n";
        errorMessage += message;

        delete[] message;

        throw std::runtime_error(errorMessage);
    }

    /**** Shader Program ****/
    id = glCreateProgram();
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    glLinkProgram(id);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &messageLength);
    if(messageLength > 0) {
        char* message = new char[messageLength];
        glGetProgramInfoLog(id, messageLength, nullptr, message);

        std::string errorMessage = "Failed to link shader program :\n";
        errorMessage += message;

        delete[] message;

        throw std::runtime_error(errorMessage);
    }
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}