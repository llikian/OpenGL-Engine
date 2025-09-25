/***************************************************************************************************
 * @file  GLTF.hpp
 * @brief Declaration of the GLTF namespace
 **************************************************************************************************/

#pragma once

#include <filesystem>
#include "tiny_gltf.h"
#include "mesh/Mesh.hpp"
#include "utility/HeapArray.hpp"

class SceneGraph;

namespace GLTF {
    using Primitive = ::Mesh;

    struct Mesh {
        std::string name;
        HeapArray<Primitive> primitives;
    };

    struct AttributeInfo {
        std::string name;

        Attribute attribute;
        AttributeType attribute_type;

        size_t values_count;
        const float* data;
        size_t stride_in_floats;
        unsigned char elements_count;
    };

    /**
    * @class Scene
    * @brief
    */
    class Scene {
    public:
        Scene(const std::filesystem::path& path, SceneGraph* scene_graph, unsigned int scene_node_index);

        void load(const std::filesystem::path& path, SceneGraph* scene_graph, unsigned int scene_node_index);

        void add_node(const std::vector<tinygltf::Node>& t_nodes,
                      const tinygltf::Node& t_node,
                      SceneGraph* scene_graph,
                      int sg_parent_index);

    private:
        HeapArray<Mesh> meshes;
    };
}
