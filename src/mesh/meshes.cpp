/***************************************************************************************************
 * @file  meshes.cpp
 * @brief Implementation of functions to create meshes
 **************************************************************************************************/

#include "mesh/meshes.hpp"

#include <cmath>
#include <glad/glad.h>

Mesh Meshes::cube() {
    Mesh mesh(GL_TRIANGLES);

    Point positions[8]{
        {-0.5f, 0.5f,  -0.5f},
        {0.5f,  0.5f,  -0.5f},
        {0.5f,  0.5f,  0.5f},
        {-0.5f, 0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f},
        {0.5f,  -0.5f, -0.5f},
        {0.5f,  -0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f}
    };

    Vector normals[6]{
        {0.0f,  0.0f,  -1.0f},
        {-1.0f, 0.0f,  0.0f},
        {0.0f,  -1.0f, 0.0f},
        {1.0f,  0.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  0.0f,  1.0f}
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
     *      0┌─────┐1
     *       │  0  │
     * 0    4│ BAC │5    1     0
     * ┌─────┼─────┼─────┬─────┐
     * │  1  │  2  │  3  │  4  │
     * │ LEF │ BOT │ RIG │ TOP │
     * └─────┼─────┼─────┴─────┘
     * 3    7│  5  │6    2     3
     *       │ FRO │
     *      3└─────┘2
     */

    unsigned int faces[6][4]{
        {0, 1, 5, 4},
        {0, 4, 7, 3},
        {4, 5, 6, 7},
        {5, 1, 2, 6},
        {1, 0, 3, 2},
        {7, 6, 2, 3}
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

Mesh Meshes::wireframeCube() {
    Mesh mesh(GL_LINES);

    mesh.addPosition(-0.5f, 0.5f, -0.5f);
    mesh.addPosition(0.5f, 0.5f, -0.5f);
    mesh.addPosition(0.5f, 0.5f, 0.5f);
    mesh.addPosition(-0.5f, 0.5f, 0.5f);
    mesh.addPosition(-0.5f, -0.5f, -0.5f);
    mesh.addPosition(0.5f, -0.5f, -0.5f);
    mesh.addPosition(0.5f, -0.5f, 0.5f);
    mesh.addPosition(-0.5f, -0.5f, 0.5f);

    /* Vertices' index
     *  0───1
     *  │╲  │╲
     *  │ 3───2
     *  4─│─5 │
     *   ╲│  ╲│
     *    7───6
     */

    unsigned int lines[12][2]{
        {0, 1},
        {0, 3},
        {0, 4},
        {1, 2},
        {1, 5},
        {2, 3},
        {2, 6},
        {3, 7},
        {4, 5},
        {4, 7},
        {5, 6},
        {6, 7}
    };

    for(int i = 0 ; i < 12 ; ++i) {
        mesh.addIndex(lines[i][0]);
        mesh.addIndex(lines[i][1]);
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

Mesh Meshes::axis(float size) {
    Mesh mesh(GL_LINES);

    const Point axes[3]{
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    for(const Point& p: axes) {
        mesh.addPosition(0.0f, 0.0f, 0.0f);
        mesh.addColor(p);

        mesh.addPosition(p);
        mesh.addColor(p);
    }

    return mesh;
}

Mesh Meshes::sphere(int divTheta, int divPhi) {
    Mesh mesh(GL_TRIANGLES);

    const double thetaStep = M_PI /  divTheta;
    const double phiStep =  2.0f * M_PI / divPhi;

    double theta = -M_PI_2 + thetaStep;
    double phi = 0.0f;

    vec3 point;
    for(int i = 0 ; i < divTheta - 1; ++i) {
        phi = 0.0;

        for(int j = 0 ; j < divPhi ; ++j) {
            point.x = cos(theta) * cos(phi);
            point.y = sin(theta);
            point.z = cos(theta) * sin(phi);

            mesh.addPosition(point);
            mesh.addNormal(point);

            phi += phiStep;
        }

        theta += thetaStep;
    }

    auto index = [&](int column, int row) -> int {
        return row + column * divPhi;
    };

    for(int i = 0 ; i < divTheta - 2 ; ++i) {
        for(int j = 0 ; j < divPhi ; ++j) {
            mesh.addFace(
                index(i, j),
                index(i + 1, j),
                index(i + 1, (j + 1) % divPhi),
                index(i, (j + 1) % divPhi)
            );
        }
    }

    mesh.addPosition(0.0f, -1.0f, 0.0f);
    mesh.addNormal(0.0f, -1.0f, 0.0f);

    mesh.addPosition(0.0f, 1.0f, 0.0f);
    mesh.addNormal(0.0f, 1.0f, 0.0f);

    for(int i = 0 ; i < divPhi ; ++i) {
        mesh.addTriangle(
            index(divTheta - 1, 0),
            index(0, i),
            index(0, (i + 1) % divPhi)
        );

        mesh.addTriangle(
            index(divTheta - 2, i),
            index(divTheta - 1, 0) + 1,
            index(divTheta - 2, (i + 1) % divPhi)
        );
    }

    return mesh;
}

