/***************************************************************************************************
 * @file  SceneGraph.hpp
 * @brief Declaration of the SceneGraph class
 **************************************************************************************************/

#pragma once

#include "Node.hpp"
#include "assets/AssetManager.hpp"
#include "assets/GLTF.hpp"
#include "assets/Shader.hpp"
#include "culling/AABB.hpp"
#include "mesh/Mesh.hpp"
#include <vector>

#define ADD_NODE_PARAMETERS const std::string &name, std::size_t parent

bool is_mouse_hovering_imgui();

class SceneGraph {
public:
  SceneGraph();

  Node &operator[](std::size_t node_index);

  void draw(const Frustum &frustum);

  std::size_t add_simple_node(ADD_NODE_PARAMETERS);
  std::size_t add_mesh_node(ADD_NODE_PARAMETERS, std::size_t mesh_index,
                            ShaderName shader_name);
  std::size_t add_mesh_node(ADD_NODE_PARAMETERS, const Mesh *mesh,
                            ShaderName shader_name);
  std::size_t add_gltf_scene_node(ADD_NODE_PARAMETERS,
                                  const std::filesystem::path &scene_path);

  std::size_t add_mesh(const Mesh *mesh);
  std::size_t add_color_to_node(std::size_t node_index, const vec4 &color);
  std::size_t add_material_to_node(std::size_t node_index, Material *material);

  void add_imgui_node_tree();
  void add_object_editor_to_imgui_window();

  void set_visibility(std::size_t node_index, bool is_visible);
  void set_is_selected(std::size_t node_index, bool is_selected);

  std::vector<Node>
      nodes; ///< The scene graph's nodes. The root is always at index 0.
  std::vector<Transform> transforms;
  std::vector<AABB> AABBs;
  std::vector<int> is_in_frustum;

  std::vector<const Mesh *> meshes;
  std::vector<Material *> materials;
  std::vector<vec4> colors;
  std::vector<GLTF::Scene> gltf_scenes;

  bool are_AABBs_drawn;
  bool are_normals_drawn;
  bool is_wireframe_drawn;
  std::size_t total_drawn_objects;

private:
  std::size_t light_node_index;
  vec3 light_position;
  vec3 light_color;

  void draw(const Frustum &frustum, std::size_t node_index);
  void draw(const mat4 &view_projection, const Shader &shader,
            std::size_t node_index) const;

  void update_transform_and_children(std::size_t node_index = 0);
  void force_update_transform_and_children(std::size_t node_index = 0);
  void update_AABBs(std::size_t node_index = 0);

  std::size_t add_node(ADD_NODE_PARAMETERS, Node::Type type);

  void add_node_to_imgui_node_tree(std::size_t node_index);

  std::size_t selected_node;
};
