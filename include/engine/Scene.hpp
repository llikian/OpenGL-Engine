/***************************************************************************************************
 * @file  Scene.hpp
 * @brief Declaration of the Scene class
 **************************************************************************************************/

#pragma once

#include <memory>
#include <vector>
#include "Camera.hpp"
#include "Shader.hpp"
#include "mesh/Mesh.hpp"

struct Element {
    Shader& shader;
    std::shared_ptr<Mesh> mesh;
    mat4 model;
};

struct Scene {
    Scene(const Camera& camera, const mat4& projection);

    void draw();

    void add(Shader& shader, std::shared_ptr<Mesh> mesh, const mat4& model);

    const Camera& camera;
    const mat4& projection;
    std::vector<Shader> shaders;
    std::vector<Element> elements;
};