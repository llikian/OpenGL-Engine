/***************************************************************************************************
 * @file  meshes.cpp
 * @brief Implementation of functions to create meshes
 **************************************************************************************************/

#include "mesh/meshes.hpp"

#include <cmath>

TriangleMesh Meshes::cube() {
    TriangleMesh mesh;

    /* Vertices' index
     *  0───1
     *  │╲  │╲
     *  │ 3───2
     *  4─│─5 │
     *   ╲│  ╲│
     *    7───6
     *
     * Faces & Template
     *      0┌─────┐1
     *       │  0  │
     * 0    3│ TOP │2    1     0
     * ┌─────┼─────┼─────┬─────┐
     * │  1  │  2  │  3  │  4  │
     * │ LEF │ FRO │ RIG │ BAC │
     * └─────┼─────┼─────┴─────┘
     * 4    7│  5  │6    5     4
     *       │ BOT │
     *      4└─────┘5
     */

    unsigned int faces[6][4]{
        { 0, 3, 2, 1 },
        { 0, 4, 7, 3 },
        { 3, 7, 6, 2 },
        { 2, 6, 5, 1 },
        { 1, 5, 4, 0 },
        { 7, 4, 5, 6 }
    };

    vec3 positions[8]{
        vec3(-0.5f, 0.5f, -0.5f),
        vec3(0.5f, 0.5f, -0.5f),
        vec3(0.5f, 0.5f, 0.5f),
        vec3(-0.5f, 0.5f, 0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f, 0.5f),
        vec3(-0.5f, -0.5f, 0.5f)
    };

    vec3 normals[6]{
        vec3(0.0f, 1.0f, 0.0f),
        vec3(-1.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, 1.0f),
        vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, -1.0f),
        vec3(0.0f, -1.0f, 0.0f)
    };

    for(int i = 0 ; i < 6 ; ++i) {
        mesh.addVertex(positions[faces[i][0]], normals[i], vec2(0.0f, 1.0f));
        mesh.addVertex(positions[faces[i][1]], normals[i], vec2(0.0f, 0.0f));
        mesh.addVertex(positions[faces[i][2]], normals[i], vec2(1.0f, 0.0f));
        mesh.addVertex(positions[faces[i][3]], normals[i], vec2(1.0f, 1.0f));

        mesh.addFace(i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
    }

    return mesh;
}

TriangleMesh Meshes::texturedCube() {
    TriangleMesh mesh;

    /* Vertices' index
     *  0───1
     *  │╲  │╲
     *  │ 3───2
     *  4─│─5 │
     *   ╲│  ╲│
     *    7───6
     *
     * Faces & Template
     *      0┌─────┐1
     *       │  0  │
     * 0    3│ TOP │2    1     0
     * ┌─────┼─────┼─────┬─────┐
     * │  1  │  2  │  3  │  4  │
     * │ LEF │ FRO │ RIG │ BAC │
     * └─────┼─────┼─────┴─────┘
     * 4    7│  5  │6    5     4
     *       │ BOT │
     *      4└─────┘5
     */

    unsigned int faces[6][4]{
        { 0, 3, 2, 1 },
        { 0, 4, 7, 3 },
        { 3, 7, 6, 2 },
        { 2, 6, 5, 1 },
        { 1, 5, 4, 0 },
        { 7, 4, 5, 6 }
    };

    vec3 positions[8]{
        vec3(-0.5f, 0.5f, -0.5f),
        vec3(0.5f, 0.5f, -0.5f),
        vec3(0.5f, 0.5f, 0.5f),
        vec3(-0.5f, 0.5f, 0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f, 0.5f),
        vec3(-0.5f, -0.5f, 0.5f)
    };

    vec3 normals[6]{
        vec3(0.0f, 1.0f, 0.0f),
        vec3(-1.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, 1.0f),
        vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, -1.0f),
        vec3(0.0f, -1.0f, 0.0f)
    };

    vec2 texCoords[6]{
        vec2(0.25f, 1.0f),
        vec2(0.00f, (2.0f / 3.0f)),
        vec2(0.25f, (2.0f / 3.0f)),
        vec2(0.50f, (2.0f / 3.0f)),
        vec2(0.75f, (2.0f / 3.0f)),
        vec2(0.25f, (1.0f / 3.0f))
    };

    for(int i = 0 ; i < 6 ; ++i) {

        mesh.addVertex(positions[faces[i][0]], normals[i], texCoords[i]);
        mesh.addVertex(positions[faces[i][1]], normals[i], vec2(texCoords[i].x, texCoords[i].y - 1.0f / 3.0f));
        mesh.addVertex(positions[faces[i][2]], normals[i], vec2(texCoords[i].x + 0.25f, texCoords[i].y - 1.0f / 3.0f));
        mesh.addVertex(positions[faces[i][3]], normals[i], vec2(texCoords[i].x + 0.25f, texCoords[i].y));

        mesh.addFace(i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
    }

    return mesh;
}

LineMesh Meshes::wireframeCube() {
    LineMesh mesh;

    mesh.addVertex(vec3(-0.5f, 0.5f, -0.5f), vec3());
    mesh.addVertex(vec3(0.5f, 0.5f, -0.5f), vec3());
    mesh.addVertex(vec3(0.5f, 0.5f, 0.5f), vec3());
    mesh.addVertex(vec3(-0.5f, 0.5f, 0.5f), vec3());
    mesh.addVertex(vec3(-0.5f, -0.5f, -0.5f), vec3());
    mesh.addVertex(vec3(0.5f, -0.5f, -0.5f), vec3());
    mesh.addVertex(vec3(0.5f, -0.5f, 0.5f), vec3());
    mesh.addVertex(vec3(-0.5f, -0.5f, 0.5f), vec3());

    /* Vertices' index
     *  0───1
     *  │╲  │╲
     *  │ 3───2
     *  4─│─5 │
     *   ╲│  ╲│
     *    7───6
     */

    mesh.addLine(0, 1);
    mesh.addLine(0, 3);
    mesh.addLine(0, 4);
    mesh.addLine(1, 2);
    mesh.addLine(1, 5);
    mesh.addLine(2, 3);
    mesh.addLine(2, 6);
    mesh.addLine(3, 7);
    mesh.addLine(4, 5);
    mesh.addLine(4, 7);
    mesh.addLine(5, 6);
    mesh.addLine(6, 7);

    return mesh;
}

LineMesh Meshes::grid(float size, int divisions) {
    LineMesh mesh;

    float square = -size / 2.0f;
    const float squareSize = size / divisions;

    for(int i = 0 ; i <= divisions ; ++i) {
        mesh.addVertex(vec3(square, 0.0f, -size / 2.0f));
        mesh.addVertex(vec3(square, 0.0f, size / 2.0f));

        mesh.addVertex(vec3(-size / 2.0f, 0.0f, square));
        mesh.addVertex(vec3(size / 2.0f, 0.0f, square));

        square += squareSize;
    }

    return mesh;
}

LineMesh Meshes::axes(float size) {
    LineMesh mesh;

    const vec3 axes[3]{
        vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 0.0f, 1.0f)
    };

    for(const vec3& point : axes) {
        mesh.addVertex(vec3(0.0f, 0.0f, 0.0f), point);
        mesh.addVertex(size * point, point);
    }

    return mesh;
}

TriangleMesh Meshes::sphere(int divTheta, int divPhi) {
    TriangleMesh mesh;

    const double thetaStep = M_PI / divTheta;
    const double phiStep = 2.0 * M_PI / divPhi;

    double theta = -M_PI_2 + thetaStep;
    double phi = 0.0;

    for(int i = 0 ; i < divTheta ; ++i) {
        phi = 0.0;

        for(int j = 0 ; j <= divPhi ; ++j) {
            vec3 point(std::cos(theta) * std::cos(phi), std::sin(theta), std::cos(theta) * std::sin(phi));
            mesh.addVertex(point, point, vec2(static_cast<float>(j) / divPhi, 0.5 + point.y / 2.0));

            phi += phiStep;
        }

        theta += thetaStep;
    }

    auto index = [&](int column, int row) -> int {
        return row + column * (divPhi + 1);
    };

    for(int i = 0 ; i < divTheta - 1 ; ++i) {
        for(int j = 0 ; j < divPhi ; ++j) {
            mesh.addFace(
                index(i, j),
                index(i + 1, j),
                index(i + 1, j + 1),
                index(i, j + 1)
            );
        }
    }

    return mesh;
}

TriangleMesh Meshes::plane(float size) {
    TriangleMesh mesh;

    size /= 2;

    mesh.addVertex(vec3(-size, 0.0f, size), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, size));
    mesh.addVertex(vec3(size, 0.0f, size), vec3(0.0f, 1.0f, 0.0f), vec2(size, size));
    mesh.addVertex(vec3(size, 0.0f, -size), vec3(0.0f, 1.0f, 0.0f), vec2(size, 0.0f));
    mesh.addVertex(vec3(-size, 0.0f, -size), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f));

    mesh.addFace(0, 1, 2, 3);

    return mesh;
}

TriangleMesh Meshes::screen() {
    TriangleMesh mesh;

    mesh.addVertex(vec3(-1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(-1.0f, 1.0f));
    mesh.addVertex(vec3(-1.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(-1.0f, -1.0f));
    mesh.addVertex(vec3(1.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, -1.0f));
    mesh.addVertex(vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f));

    mesh.addFace(0, 1, 2, 3);

    return mesh;
}
