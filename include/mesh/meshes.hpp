/***************************************************************************************************
 * @file  meshes.hpp
 * @brief Declaration of functions to create meshes
 **************************************************************************************************/

#pragma once

#include "Mesh.hpp"

namespace Meshes {
    /**
     * @brief Creates the mesh for a cube where all the faces will have the same texture.
     * The cube will have a side of size 1.
     */
    Mesh cube();

    /**
     * @brief Creates the mesh for a wireframe cube. The cube will have a side of size 1.
     */
    Mesh wireframeCube();

    /**
     * @brief Creates the mesh for a grid on the XZ plane.
     * @param size Size of one line of the grid.
     * @param divisions Number of divisions on the grid.
     */
    Mesh grid(float size, int divisions);

    /**
     * @brief Creates the mesh for the axes. The x axis is red, the y axis is green and the z axis
     * is blue.
     * @param size The size of the line for each axis.
     */
    Mesh axis(float size);

    /**
     * @brief Creates the mesh for a sphere with a radius of 1.
     * @param divTheta
     * @param divPhi
     */
    Mesh sphere(int divTheta, int divPhi);
}