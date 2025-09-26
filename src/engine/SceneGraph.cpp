/***************************************************************************************************
 * @file  SceneGraph.cpp
 * @brief Implementation of the SceneGraph class
 **************************************************************************************************/

#include "engine/SceneGraph.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "assets/AssetManager.hpp"
#include "engine/Node.hpp"
#include "mesh/primitives.hpp"

SceneGraph::SceneGraph()
    : are_AABBs_drawn(false),
      light_node_index(INVALID_INDEX),
      selected_node(INVALID_INDEX) {
    /* ---- Asset Manager ---- */
    /* Meshes */
    AssetManager::add_mesh("sphere 8 16", create_sphere_mesh, 8, 16);
    AssetManager::add_mesh("sphere 16 32", create_sphere_mesh, 16, 32);
    AssetManager::add_mesh("icosphere 0", create_icosphere_mesh, 0);
    AssetManager::add_mesh("icosphere 1", create_icosphere_mesh, 1);
    AssetManager::add_mesh("icosphere 2", create_icosphere_mesh, 2);
    AssetManager::add_mesh("cube", create_cube_mesh);
    AssetManager::add_mesh("wireframe cube", create_wireframe_cube_mesh);
    AssetManager::add_mesh("screen", create_screen_mesh);
    AssetManager::add_mesh("axes", create_axes_mesh, 0.5f);
    AssetManager::add_mesh("camera pyramid", create_pyramid_mesh,
                           vec3(1.0f, 1.0f, -1.0f), vec3(1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), 1.0f);

    /* Textures */
    AssetManager::add_texture("default", vec3(1.0f));
    AssetManager::add_texture("red", vec3(1.0f, 0.0f, 0.0f));
    AssetManager::add_texture("green", vec3(0.0f, 1.0f, 0.0f));
    AssetManager::add_texture("blue", vec3(0.0f, 0.0f, 1.0f));

    /* ---- Root ---- */
    add_simple_node("Scene Graph", INVALID_INDEX);

    /* ---- Light ---- */
    light_node_index = add_mesh_node("Light",
                                     0,
                                     AssetManager::get_mesh_ptr("icosphere 1"),
                                     SHADER_FLAT);
    add_color_to_node(light_node_index, vec4(1.0f));
    transforms[light_node_index].set_local_position(0.0f, 100.0f, 0.0f);
}

Node& SceneGraph::operator[](unsigned int node_index) { return nodes[node_index]; }

void SceneGraph::draw(const Frustum& frustum) {
    total_drawn_objects = 0;

    light_color = colors[nodes[light_node_index].color_index];
    light_position = transforms[light_node_index].get_global_position();

    update_transform_and_children();
    update_AABBs();

    draw(frustum, 0);
}

unsigned int SceneGraph::add_simple_node(const std::string& name, unsigned int parent) {
    return add_node(name, parent, Node::Type::SIMPLE);
}

unsigned int SceneGraph::add_mesh_node(const std::string& name,
                                       unsigned int parent,
                                       unsigned int mesh_index,
                                       ShaderName shader_name) {
    unsigned int index = add_node(name, parent, Node::Type::MESH);

    nodes[index].drawable_index = mesh_index;
    nodes[index].shader_name = shader_name;

    return index;
}

unsigned int SceneGraph::add_mesh_node(const std::string& name,
                                       unsigned int parent,
                                       const Mesh* mesh,
                                       ShaderName shader_name) {
    meshes.push_back(mesh);

    return add_mesh_node(name, parent, meshes.size() - 1, shader_name);
}

unsigned int SceneGraph::add_gltf_scene_node(const std::string& name,
                                             unsigned int parent,
                                             const std::filesystem::path& scene_path) {
    unsigned int index = add_node(name, parent, Node::Type::GLTF_SCENE);

    gltf_scenes.emplace_back(scene_path, this, index);
    nodes[index].scene_index = gltf_scenes.size() - 1;

    return index;
}

unsigned int SceneGraph::add_mesh(const Mesh* mesh) {
    meshes.push_back(mesh);
    return meshes.size() - 1;
}

unsigned int SceneGraph::add_color_to_node(unsigned int node_index, const vec4& color) {
    colors.push_back(color);
    unsigned int color_index = colors.size() - 1;
    nodes[node_index].color_index = color_index;
    return color_index;
}

unsigned int SceneGraph::add_material_to_node(unsigned int node_index, const Material* material) {
    materials.push_back(material);
    unsigned int material_index = materials.size() - 1;
    nodes[node_index].color_index = material_index;
    return material_index;
}

void SceneGraph::add_imgui_node_tree() {
    add_node_to_imgui_node_tree(0);
}

void SceneGraph::add_object_editor_to_imgui_window() {
    if(selected_node < nodes.size()) {
        Node& node = nodes[selected_node];
        Transform& transform = transforms[selected_node];

        ImGui::Text("Node");
        ImGui::SameLine();
        ImGui::PushID(&node.name);
        ImGui::InputText("", &node.name);
        ImGui::PopID();
        ImGui::NewLine();

        if(ImGui::Button("UNSELECT")) {
            set_is_selected(selected_node, false);
            selected_node = INVALID_INDEX;
        }

        if(ImGui::Checkbox("Is Object Visible", &node.is_visible)) { set_visibility(selected_node, node.is_visible); }

        bool is_dirty = ImGui::DragFloat3("Local Position", &transform.get_local_position_reference().x);

        quaternion& orientation = transform.get_local_orientation_reference();
        if(ImGui::DragFloat4("Local Orientation", &orientation.x, 0.1f)) {
            is_dirty = true;
            orientation.normalize();
        }

        is_dirty = is_dirty || ImGui::DragFloat3("Local Scale", &transform.get_local_scale_reference().x, 0.1f, 0.1f);

        if(is_dirty) { transform.set_local_model_to_dirty(); }

        ImGui::NewLine();
        if(node.shader_name != SHADER_NONE) {
            ImGui::Text("Shader: '%s'", AssetManager::get_shader(node.shader_name).get_name().c_str());
        }
        if(node.color_index != INVALID_INDEX) { ImGui::ColorEdit4("Color", &colors[node.color_index].x); }
    } else {
        ImGui::Text("No Node is Selected");
    }
}

void SceneGraph::set_visibility(unsigned int node_index, bool is_visible) {
    nodes[node_index].is_visible = is_visible;
    for(unsigned int index : nodes[node_index].children) {
        set_visibility(index, is_visible);
    }
}

void SceneGraph::set_is_selected(unsigned int node_index, bool is_selected) {
    nodes[node_index].is_selected = is_selected;
    for(unsigned int index : nodes[node_index].children) {
        set_is_selected(index, is_selected);
    }
}

void SceneGraph::draw(const Frustum& frustum, unsigned int node_index) {
    const Node& node = nodes[node_index];

    if(!node.is_visible) { return; }

    if(AABBs[node_index].is_in_frustum(frustum)) {
        if(node.drawable_index != INVALID_INDEX) {
            ++total_drawn_objects;
            draw(frustum.view_projection, AssetManager::get_shader(node.shader_name), node_index);
        }

        if(are_AABBs_drawn || node.is_selected) {
            const Shader& shader = AssetManager::get_shader(SHADER_FLAT);
            shader.use();
            shader.set_uniform("u_mvp", frustum.view_projection * AABBs[node_index].get_global_model_matrix());

            if(node.is_selected) {
                if(node.parent == INVALID_INDEX || !nodes[node.parent].is_selected) {
                    shader.set_uniform("u_color", vec4(0.0f, 1.0f, 1.0f, 1.0f));
                } else {
                    shader.set_uniform("u_color", vec4(0.0f, 0.0f, 1.0f, 1.0f));
                }
            } else if(node.drawable_index == INVALID_INDEX) { // Not a drawable node.
                shader.set_uniform("u_color", vec4(0.0f, 1.0f, 0.0f, 1.0f));
            } else {
                shader.set_uniform("u_color", vec4(1.0f, 0.0f, 0.0f, 1.0f));
            }

            glLineWidth(3.0f);
            AssetManager::get_mesh("wireframe cube").draw();
            glLineWidth(1.0f);
        }

        for(unsigned int index : node.children) { draw(frustum, index); }
    }
}

void SceneGraph::draw(const mat4& view_projection, const Shader& shader, unsigned int node_index) const {
    const Node& node = nodes[node_index];

    shader.use();

    const mat4& global_model = transforms[node_index].get_global_model_const_reference();
    shader.set_uniform_if_exists("u_model", global_model);

    int u_mvp_location = shader.get_uniform_location("u_mvp");
    if(u_mvp_location != -1) {
        Shader::set_uniform(u_mvp_location, view_projection * global_model);
    }

    int u_normals_model_matrix_location = shader.get_uniform_location("u_normals_model_matrix");
    if(u_normals_model_matrix_location != -1) {
        Shader::set_uniform(u_normals_model_matrix_location, transpose_inverse(global_model));
    }

    shader.set_uniform_if_exists("u_light.color", light_color);
    shader.set_uniform_if_exists("u_light.position", light_position);

    if(node.color_index != INVALID_INDEX) { shader.set_uniform_if_exists("u_color", colors[node.color_index]); }
    if(node.material_index != INVALID_INDEX) { materials[node.material_index]->update_shader_uniforms(&shader); }

    switch(node.type) {
        case Node::Type::MESH:
            meshes[node.drawable_index]->draw();
            break;
        default: break;
    }
}

void SceneGraph::update_transform_and_children(unsigned int node_index) {
    if(transforms[node_index].is_local_model_dirty()) {
        force_update_transform_and_children(node_index);
    } else {
        for(unsigned int child : nodes[node_index].children) {
            update_transform_and_children(child);
        }
    }
}

void SceneGraph::force_update_transform_and_children(unsigned int node_index) {
    Node& node = nodes[node_index];
    if(nodes[node_index].parent != INVALID_INDEX) {
        transforms[node_index].update_global_model(transforms[node.parent].get_global_model());
    } else {
        transforms[node_index].update_global_model();
    }

    for(unsigned int child : nodes[node_index].children) {
        force_update_transform_and_children(child);
    }
}

void SceneGraph::update_AABBs(unsigned int node_index) {
    for(unsigned int index : nodes[node_index].children) { update_AABBs(index); }

    vec3 min(std::numeric_limits<float>::max());
    vec3 max(std::numeric_limits<float>::lowest());

    switch(nodes[node_index].type) {
        case Node::Type::MESH:
            AABBs[node_index].set(meshes[nodes[node_index].drawable_index]->get_AABB(), transforms[node_index]);
            break;
        case Node::Type::SIMPLE:
        case Node::Type::GLTF_SCENE:
            for(unsigned int index : nodes[node_index].children) {
                AABB::axis_aligned_min(min, AABBs[index].min_point);
                AABB::axis_aligned_max(max, AABBs[index].max_point);
            }
            AABBs[node_index].set(min, max);
            break;
    }
}

unsigned int SceneGraph::add_node(const std::string& name, unsigned int parent, Node::Type type) {
    nodes.emplace_back(name, parent, type);
    transforms.emplace_back();
    AABBs.emplace_back();
    is_in_frustum.push_back(false);

    unsigned int index = nodes.size() - 1;
    if(parent != INVALID_INDEX) { nodes[parent].children.push_back(index); }

    return nodes.size() - 1;
}

void SceneGraph::add_node_to_imgui_node_tree(unsigned int node_index) {
    const Node& node = nodes[node_index];

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
    if(node.children.empty()) { flags |= ImGuiTreeNodeFlags_Leaf; }
    if(selected_node == node_index) { flags |= ImGuiTreeNodeFlags_Selected; }

    std::string label;
    switch(node.type) {
        case Node::Type::SIMPLE:
            label += " o";
            break;
        case Node::Type::MESH:
            label += " M";
            break;
        case Node::Type::GLTF_SCENE:
            label += " S";
            break;
        default:
            label += " ?";
            break;
    }
    label += ' ' + node.name;

    ImGui::PushID(&node);
    if(ImGui::TreeNodeEx(label.c_str(), flags)) {
        if(ImGui::IsItemClicked()) {
            if(selected_node != INVALID_INDEX) { set_is_selected(selected_node, false); }
            selected_node = node_index;
            set_is_selected(selected_node, true);
        }

        for(unsigned int index : node.children) { add_node_to_imgui_node_tree(index); }
        ImGui::TreePop();
    } else if(ImGui::IsItemClicked()) {
        if(selected_node != INVALID_INDEX) { set_is_selected(selected_node, false); }
        selected_node = node_index;
        set_is_selected(selected_node, true);
    }
    ImGui::PopID();
}
