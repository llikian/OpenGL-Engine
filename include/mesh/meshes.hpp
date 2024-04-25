/***************************************************************************************************
 * @file  meshes.hpp
 * @brief Declaration of functions to create meshes
 **************************************************************************************************/

#pragma once

#include "Mesh.hpp"

namespace Meshes {
    /**
     * @brief Creates the mesh for a cube where all the face will have the same texture.
     * The cube will have a side of size 1.
     */
    Mesh cube();
}