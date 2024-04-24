/***************************************************************************************************
 * @file  Shader.cpp
 * @brief Implementation of the Shader class
 **************************************************************************************************/

#include "Shader.hpp"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
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

void Shader::setUniform(const std::string& uniform, int value) const {
    glUniform1i(glGetUniformLocation(id, uniform.c_str()), value);
}

void Shader::setUniform(const std::string& uniform, bool value) const {
    glUniform1i(glGetUniformLocation(id, uniform.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string& uniform, float value) const {
    glUniform1f(glGetUniformLocation(id, uniform.c_str()), value);
}

void Shader::setUniform(const std::string& uniform, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, uniform.c_str()), x, y);
}

void Shader::setUniform(const std::string& uniform, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, uniform.c_str()), x, y, z);
}

void Shader::setUniform(const std::string& uniform, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(id, uniform.c_str()), x, y, z, w);
}

void Shader::setUniform(const std::string& uniform, const vec2& vec) const {
    glUniform2fv(glGetUniformLocation(id, uniform.c_str()), 1, &vec.x);
}

void Shader::setUniform(const std::string& uniform, const vec3& vec) const {
    glUniform3fv(glGetUniformLocation(id, uniform.c_str()), 1, &vec.x);
}

void Shader::setUniform(const std::string& uniform, const vec4& vec) const {
    glUniform4fv(glGetUniformLocation(id, uniform.c_str()), 1, &vec.x);
}

void Shader::setUniform(const std::string& uniform, const Matrix4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id, uniform.c_str()), 1, true, &matrix[0].x);
}