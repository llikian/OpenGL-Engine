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

    /**
     * @brief Creates the mesh for a grid on the XZ plane.
     * @param size Size of one line of the grid.
     * @param divisions Number of divisions on the grid.
     */
    Mesh grid(float size, int divisions);
}