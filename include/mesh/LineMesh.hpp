/***************************************************************************************************
 * @file  LineMesh.hpp
 * @brief Declaration of the LineMesh class
 **************************************************************************************************/

#pragma once

#include <vector>
#include "engine/Shader.hpp"
#include "maths/vec3.hpp"

/**
 * @class LineMesh
 * @brief Represents a 3D mesh made out of lines that can be created and rendererd.
 */
class LineMesh {
public:
    struct Vertex {
        vec3 position;
        vec3 color;
        float thickness;
    };

    LineMesh();
    LineMesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
    explicit LineMesh(const std::vector<Vertex>& vertices);
    ~LineMesh();

    void draw();

    void addVertex(const Vertex& vertex);
    void addVertex(const vec3& position, const vec3& color = vec3(1.0f), float thickness = 1.0f);

    void addIndex(uint index);
    void addLine(uint start, uint end);

private:
    void bindBuffers();

    bool bound;

    std::vector<Vertex> vertices;
    std::vector<uint> indices;

    uint VAO;
    uint VBO;
    uint EBO;
};

