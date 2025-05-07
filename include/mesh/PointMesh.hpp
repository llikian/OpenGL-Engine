/***************************************************************************************************
 * @file  PointMesh.hpp
 * @brief Declaration of the PointMesh class
 **************************************************************************************************/

#pragma once

#include <vector>
#include "engine/Shader.hpp"
#include "maths/vec3.hpp"

/**
 * @class PointMesh
 * @brief Represents a 3D mesh made out of points that can be created and rendererd.
 */
class PointMesh {
public:
    struct Vertex {
        vec3 position;
        vec3 color;
        float size;
    };

    PointMesh();
    explicit PointMesh(const std::vector<Vertex>& vertices);
    ~PointMesh();

    void draw();

    void addVertex(const Vertex& vertex);
    void addVertex(const vec3& position, const vec3& color = vec3(1.0f), float size = 1.0f);

private:
    void bindBuffers();

    bool bound;

    std::vector<Vertex> vertices;

    uint VAO;
    uint VBO;
};