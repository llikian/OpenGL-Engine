/***************************************************************************************************
 * @file  Scene.cpp
 * @brief Implementation of the Scene class
 **************************************************************************************************/

#include "engine/Scene.hpp"

Scene::Scene(const Camera& camera, const mat4& projection): camera(camera), projection(projection) { }

void Scene::draw() {
    for(auto& [shader, mesh, model] : elements) {
        shader.use();
        shader.setUniform("mvp", camera.getVPmatrix(projection) * model);
        shader.setUniform("model", model);
        shader.setUniform("normalModel", transposeInverse(model));
        mesh->draw();
    }
}

void Scene::add(Shader& shader, std::shared_ptr<Mesh> mesh, const mat4& model) {
    elements.emplace_back(shader, mesh, model);
}
