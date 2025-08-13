/***************************************************************************************************
 * @file  SceneGraph.hpp
 * @brief Declaration of the SceneGraph class
 **************************************************************************************************/

#pragma once

#include <vector>
#include "assets/Shader.hpp"
#include "culling/AABB.hpp"
#include "mesh/Mesh.hpp"
#include "Node.hpp"

#define ADD_NODE_PARAMETERS const std::string& name, unsigned int parent

struct SceneGraph {
    SceneGraph();

    Node& operator[](unsigned int node_index);

    void draw(const Frustum& frustum);

    unsigned int add_simple_node(ADD_NODE_PARAMETERS);
    unsigned int add_mesh_node(ADD_NODE_PARAMETERS, unsigned int mesh_index, unsigned int shader_index);
    unsigned int add_mesh_node(ADD_NODE_PARAMETERS, const Mesh* mesh, const Shader* shader);
    unsigned int add_flat_shaded_mesh_node(ADD_NODE_PARAMETERS, unsigned int mesh_index, const vec4& color);
    unsigned int add_flat_shaded_mesh_node(ADD_NODE_PARAMETERS, const Mesh* mesh, const vec4& color);

    unsigned int add_mesh(const Mesh* mesh);
    unsigned int add_shader(const Shader* shader);

    void add_imgui_node_tree();
    void add_object_editor_to_imgui_window();

    void set_visibility(unsigned int node_index, bool is_visible);
    void set_is_selected(unsigned int node_index, bool is_selected);

    std::vector<Node> nodes; ///< The scene graph's nodes. The root is always at index 0.
    std::vector<Transform> transforms;
    std::vector<AABB> AABBs;
    std::vector<int> is_in_frustum;

    unsigned int flat_shader_index;

    std::vector<const Mesh*> meshes;
    std::vector<const Shader*> shaders;
    std::vector<vec4> colors;

    bool are_AABBs_drawn;
    unsigned int total_drawn_objects;

private:
    void draw(const Frustum& frustum, unsigned int node_index);
    void draw(const mat4& view_projection, const Shader* shader, unsigned int node_index) const;

    void update_transform_and_children(unsigned int node_index = 0);
    void force_update_transform_and_children(unsigned int node_index = 0);
    void update_AABBs(unsigned int node_index = 0);

    unsigned int add_node(ADD_NODE_PARAMETERS, Node::Type type);

    void add_node_to_imgui_node_tree(unsigned int node_index);

    unsigned int selected_node;
};
