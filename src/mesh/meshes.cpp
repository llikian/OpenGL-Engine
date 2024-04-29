/***************************************************************************************************
 * @file  meshes.cpp
 * @brief Implementation of functions to create meshes
 **************************************************************************************************/

#include "mesh/meshes.hpp"

#include <glad/glad.h>

Mesh Meshes::cube() {
    Mesh mesh(GL_TRIANGLES);

    Point positions[8]{
        {-0.5f, 0.5f,  -0.5f},
        {-0.5f, 0.5f,  0.5f},
        {0.5f,  0.5f,  0.5f},
        {0.5f,  0.5f,  -0.5f},
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, 0.5f},
        {0.5f,  -0.5f, 0.5f},
        {0.5f,  -0.5f, -0.5f}
    };

    Vector normals[6]{
        {0.0f,  1.0f,  0.0f},
        {-1.0f, 0.0f,  0.0f},
        {0.0f,  0.0f,  1.0f},
        {1.0f,  0.0f,  0.0f},
        {0.0f,  0.0f,  -1.0f},
        {0.0f,  -1.0f, 0.0f}
    };

    /* Vertices' index
     *  0───1
     *  │╲  │╲
     *  │ 3───2
     *  4─│─5 │
     *   ╲│  ╲│
     *    7───6
     */

    /* Faces & Template
     *      4┌─────┐5
     *       │  0  │
     * 4    0│     │1    5     4
     * ┌─────┼─────┼─────┬─────┐
     * │  1  │  2  │  3  │  4  │
     * └─────┼─────┼─────┴─────┘
     * 7    3│     │2    6     7
     *       │  5  │
     *      7└─────┘6
     */

    int faces[6][4]{
        {1, 0, 4, 5},
        {0, 3, 7, 4},
        {0, 1, 2, 3},
        {2, 1, 5, 6},
        {7, 6, 5, 4},
        {3, 2, 6, 7}
    };

    for(int i = 0 ; i < 6 ; ++i) {
        mesh.addPosition(positions[faces[i][0]]);
        mesh.addNormal(normals[i]);
        mesh.addTexCoord(0.0f, 1.0f);

        mesh.addPosition(positions[faces[i][1]]);
        mesh.addNormal(normals[i]);
        mesh.addTexCoord(0.0f, 0.0f);

        mesh.addPosition(positions[faces[i][2]]);
        mesh.addNormal(normals[i]);
        mesh.addTexCoord(1.0f, 0.0f);

        mesh.addPosition(positions[faces[i][3]]);
        mesh.addNormal(normals[i]);
        mesh.addTexCoord(1.0f, 1.0f);

        mesh.addFace((i * 4), (i * 4) + 1, (i * 4) + 2, (i * 4) + 3);
    }

    return mesh;
}

Mesh Meshes::grid(float size, int divisions) {
    Mesh mesh(GL_LINES);

    float square = -size / 2.0f;
    const float squareSize = size / divisions;

    for(int i = 0 ; i <= divisions ; ++i) {
        mesh.addPosition(square, 0.0f, -size / 2.0f);
        mesh.addPosition(square, 0.0f, size / 2.0f);

        mesh.addPosition(-size / 2.0f, 0.0f, square);
        mesh.addPosition(size / 2.0f, 0.0f, square);

        square += squareSize;
    }

    return mesh;
}
