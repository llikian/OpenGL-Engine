/***************************************************************************************************
 * @file  Mesh.hpp
 * @brief Declaration of the Mesh class
 **************************************************************************************************/

#pragma once

#include <vector>
#include "Vertex.hpp"

typedef std::vector<Vertex> Vertices;
typedef std::vector<unsigned int> Indices;

/**
 * @class Mesh
 * @brief
 */
class Mesh {
public:
    Mesh(unsigned int primitive);
    Mesh(unsigned int primitive, const Vertices& vertices);
    Mesh(unsigned int primitive, const Vertices& vertices, const Indices& indices);

    ~Mesh();

    void draw();

    void addVertex(const Vertex& vertex);
    void addVertex(const Point& position, const Vector& normal, const TexCoord& texCoord);

    void addIndex(unsigned int index);
    void addTriangle(unsigned int top, unsigned int right, unsigned int left);
    void addFace(unsigned int topL, unsigned int topR, unsigned int bottomR, unsigned int bottomL);

private:
    void bindBuffers();

    bool shouldBind; ///< Whether the buffer should be bound before drawing.

    const unsigned int primitive; ///< 3D Primitive used to draw. e.g. GL_TRIANGLES, GL_LINES, etc…

    /**
     * @brief Vector that holds the attributes for each 3D vertex in the mesh:
     * position, normal and texture coordinates.
     */
    Vertices vertices;

    /**
     * @brief Vector that can contain vertex indices in order to draw them according to the active
     * primitive. So for example if the primitive is GL_TRIANGLES, then the vertices corresponding
     * to 3 consecutive indices will form a triangle.\n
     * Filling this vector up is optional, if it is empty, the consecutive Vertex in the vertices
     * vector will be drawn according to the primitive.
     */
    Indices indices;

    unsigned int VAO; ///< Vertex Array Object
    unsigned int VBO; ///< Vertex Buffer Object
    unsigned int EBO; ///< Element Buffer Object
};