/***************************************************************************************************
 * @file  Node.hpp
 * @brief Declaration of the Node struct
 **************************************************************************************************/

#pragma once

#include <string>
#include <vector>

constexpr unsigned int INVALID_INDEX = ~0u;

struct Node {
    enum class Type : unsigned char {
        SIMPLE,           // NO DATA
        MESH,             // MESH, SHADER, AABB, (MATERIAL)
        GLTF_SCENE,       // MESH, SHADER, AABB, COLOR
    };

    Node(const std::string& name, int parent, Type type);

    Type type;        ///< The type of the node.
    std::string name; ///< The name of the node.

    unsigned int parent;                ///< The index of the node's parent. INVALID_INDEX if it is the root.
    std::vector<unsigned int> children; ///< The indices of the node's children.

    unsigned int drawable_index; ///< The index of node's drawable object. INVALID_INDEX if not drawable.
    unsigned int shader_index;   ///< The index of the node's shader. INVALID_INDEX if no shader.
    unsigned int color_index;    ///< The index of the node's color. INVALID_INDEX if no color.
    unsigned int scene_index;    ///< The index of the node's scene. INVALID_INDEX if no color.

    bool is_visible;  ///< Whether the node is visible.
    bool is_selected; ///< Whether the node is selected.
};
