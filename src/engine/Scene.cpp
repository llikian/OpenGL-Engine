/***************************************************************************************************
 * @file  Scene.cpp
 * @brief Implementation of the Scene class
 **************************************************************************************************/

#include "engine/Scene.hpp"

#include <glad/glad.h>

#include <imgui.h>

Scene::Scene(const Camera& camera, const mat4& projection): camera(camera), projection(projection) { }

void Scene::draw() {
    ImGui::Begin("Scene");

    ImGui::Text("Shaders");
    ImGui::BeginTable("Shaders", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit);
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn("Name");
    ImGui::TableHeadersRow();
    for(auto& [name, shader] : shaders) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", shader->getID());
        ImGui::TableNextColumn();
        ImGui::Text("%s", name.c_str());
    }
    ImGui::EndTable();

    ImGui::NewLine();
    ImGui::Text("Meshes");
    ImGui::BeginTable("Meshes", 1, ImGuiTableFlags_Borders);
    ImGui::TableSetupColumn("Name");
    ImGui::TableHeadersRow();
    for(auto& [name, _] : meshes) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%s", name.c_str());
    }
    ImGui::EndTable();

    ImGui::NewLine();
    ImGui::Text("Elements");
    ImGui::BeginTable("Elements", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit);
    ImGui::TableSetupColumn("n°");
    ImGui::TableSetupColumn("Shader Name");
    ImGui::TableSetupColumn("Mesh Name");
    ImGui::TableSetupColumn("Is Active ?");
    ImGui::TableHeadersRow();
    uint i = 0;
    for(auto& [shaderName, meshName, model, isActive] : elements) {
        if(isActive) {
            std::shared_ptr<Shader> shader = shaders.at(shaderName);
            std::shared_ptr<Mesh> mesh = meshes.at(meshName);

            shader->use();
            shader->setUniform("mvp", camera.getVPmatrix(projection) * model);

            if(mesh->getPrimitive() == GL_TRIANGLES) {
                shader->setUniform("model", model);
                shader->setUniform("normalModel", transposeInverse(model));
            }

            mesh->draw();
        }

        ImGui::PushID(i);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%02d", ++i);
        ImGui::TableNextColumn();
        ImGui::Text("%s", shaderName.c_str());
        ImGui::TableNextColumn();
        ImGui::Text("%s", meshName.c_str());
        ImGui::TableNextColumn();
        ImGui::Checkbox("Is Active", &isActive);
        ImGui::PopID();
    }
    ImGui::EndTable();

    ImGui::End();
}

uint Scene::add(const std::string& shaderName, const std::string& meshName, const mat4& model) {
    elements.emplace_back(shaderName, meshName, model, true);
    return elements.size() - 1;
}

void Scene::add(std::shared_ptr<Shader> shader) {
    shaders.emplace(shader->getName(), shader);
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

Element& Scene::getElement(uint index) {
    return elements.at(index);
}
