/***************************************************************************************************
 * @file  Scene.hpp
 * @brief Declaration of the Scene class
 **************************************************************************************************/

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "Camera.hpp"
#include "Shader.hpp"
#include "mesh/Mesh.hpp"

struct Element {
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Mesh> mesh;
    mat4 model;
    bool isActive;
};

class Scene {
public:
    Scene(const Camera& camera, const mat4& projection);

    void draw();

    uint add(const std::string& shaderName, const std::string& meshName, const mat4& model);
    void add(std::shared_ptr<Shader> shader);
    void add(const std::string& name, std::shared_ptr<Mesh> mesh);

    std::shared_ptr<Shader> getShader(const std::string& name);
    std::shared_ptr<Mesh> getMesh(const std::string& name);
    Element& getElement(uint index);

private:
    const Camera& camera;
    const mat4& projection;

    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;

    std::vector<Element> elements;
};
