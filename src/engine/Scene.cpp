/***************************************************************************************************
 * @file  Scene.cpp
 * @brief Implementation of the Scene class
 **************************************************************************************************/

#include "engine/Scene.hpp"

#include <glad/glad.h>

Scene::Scene(const Camera& camera, const mat4& projection): camera(camera), projection(projection) { }

void Scene::draw() {
    for(auto& [shader, mesh, model, isActive] : elements) {
        if(isActive) {
            shader->use();
            shader->setUniform("mvp", camera.getVPmatrix(projection) * model);

            if(mesh->getPrimitive() == GL_TRIANGLES) {
                shader->setUniform("model", model);
                shader->setUniform("normalModel", transposeInverse(model));
            }

            mesh->draw();
        }
    }
}

Element& Scene::add(const std::string& shaderName, const std::string& meshName, const mat4& model) {
    elements.emplace_back(shaders.at(shaderName), meshes.at(meshName), model, true);
    return elements.back();
}

void Scene::add(const std::string& name, std::shared_ptr<Shader> shader) {
    shaders.emplace(name, shader);
}

void Scene::add(const std::string& name, std::shared_ptr<Mesh> mesh) {
    meshes.emplace(name, mesh);
}

std::shared_ptr<Shader> Scene::getShader(const std::string& name) {
    return shaders.at(std::string(name));
}

std::shared_ptr<Mesh> Scene::getMesh(const std::string& name) {
    return meshes.at(std::string(name));
}
