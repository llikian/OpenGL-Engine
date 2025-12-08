/***************************************************************************************************
 * @file  SceneGraph.hpp
 * @brief Declaration of the SceneGraph class
 **************************************************************************************************/

#pragma once

#include <vector>
#include "imgui_internal.h"
#include "Node.hpp"
#include "assets/AssetManager.hpp"
#include "assets/GLTF.hpp"
#include "assets/Shader.hpp"
#include "culling/AABB.hpp"
#include "mesh/Mesh.hpp"

#define ADD_NODE_PARAMETERS const std::string& name, unsigned int parent

bool is_mouse_hovering_imgui();

class SceneGraph {
public:
    SceneGraph();

    Node& operator[](unsigned int node_index);

    void draw(const Frustum& frustum);

    unsigned int add_simple_node(ADD_NODE_PARAMETERS);
    unsigned int add_mesh_node(ADD_NODE_PARAMETERS, unsigned int mesh_index, ShaderName shader_name);
    unsigned int add_mesh_node(ADD_NODE_PARAMETERS, const Mesh* mesh, ShaderName shader_name);
    unsigned int add_gltf_scene_node(ADD_NODE_PARAMETERS, const std::filesystem::path& scene_path);

    unsigned int add_mesh(const Mesh* mesh);
    unsigned int add_color_to_node(unsigned int node_index, const vec4& color);
    unsigned int add_material_to_node(unsigned int node_index, Material* material);

    void add_imgui_node_tree();
    void add_object_editor_to_imgui_window();

    void set_visibility(unsigned int node_index, bool is_visible);
    void set_is_selected(unsigned int node_index, bool is_selected);

    std::vector<Node> nodes; ///< The scene graph's nodes. The root is always at index 0.
    std::vector<Transform> transforms;
    std::vector<AABB> AABBs;
    std::vector<int> is_in_frustum;

    std::vector<const Mesh*> meshes;
    std::vector<Material*> materials;
    std::vector<vec4> colors;
    std::vector<GLTF::Scene> gltf_scenes;

    bool are_AABBs_drawn;
    unsigned int total_drawn_objects;

private:
    unsigned int light_node_index;
    vec3 light_position;
    vec3 light_color;

    void draw(const Frustum& frustum, unsigned int node_index);
    void draw(const mat4& view_projection, const Shader& shader, unsigned int node_index) const;

    void update_transform_and_children(unsigned int node_index = 0);
    void force_update_transform_and_children(unsigned int node_index = 0);
    void update_AABBs(unsigned int node_index = 0);

    unsigned int add_node(ADD_NODE_PARAMETERS, Node::Type type);

    void add_node_to_imgui_node_tree(unsigned int node_index);

    unsigned int selected_node;
};
