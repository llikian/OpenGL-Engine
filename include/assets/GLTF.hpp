/***************************************************************************************************
 * @file  GLTF.hpp
 * @brief Declaration of the GLTF namespace
 **************************************************************************************************/

#pragma once

#include <filesystem>

#include "materials/MRMaterial.hpp"
#include "mesh/Mesh.hpp"
#include "utility/Array.hpp"
#include "Shader.hpp"
#include "tiny_gltf.h"

class SceneGraph;

namespace GLTF {
    struct Primitive {
        ::Mesh primitive;
        MRMaterial* material;
        const Shader* shader;
    };

    struct Mesh {
        std::string name;
        Array<Primitive> primitives;
    };

    struct AttributeInfo {
        Attribute attribute;

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
        ~Scene();

        void load(const std::filesystem::path& path, SceneGraph* scene_graph, unsigned int scene_node_index);

        void add_node(const std::vector<tinygltf::Node>& t_nodes,
                      const tinygltf::Node& t_node,
                      SceneGraph* scene_graph,
                      int sg_parent_index);

    private:
        Array<Mesh> meshes;
    };
}
