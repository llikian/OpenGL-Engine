/***************************************************************************************************
 * @file  Shader.hpp
 * @brief Declaration of the Shader class
 **************************************************************************************************/

#pragma once

#include <string>

/**
 * @class Shader
 * @brief
 */
class Shader {
public:
    /**
     * @brief Compiles then links and creates the shader program from the vertex and fragment
     * shaders located at the given paths.
     * @param vertexShaderPath The path to the vertex shader.
     * @param fragmentShaderPath The path to the fragment shader.
     */
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

    /**
     * @brief Deletes the shader program.
     */
    ~Shader();

    /**
     * @brief Uses the shader program.
     */
    void use();

private:
    unsigned int id; ///< The shader program's id.
};