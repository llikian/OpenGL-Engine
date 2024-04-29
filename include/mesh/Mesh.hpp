/***************************************************************************************************
 * @file  Mesh.hpp
 * @brief Declaration of the Mesh class
 **************************************************************************************************/

#pragma once

#include <vector>
#include "maths/vec2.hpp"
#include "maths/vec3.hpp"
#include "maths/vec4.hpp"
#include "Shader.hpp"

using Indices = std::vector<unsigned int>;

/**
 * @class Mesh
 * @brief
 */
class Mesh {
public:
    Mesh(unsigned int primitive);

    ~Mesh();

    void draw(const Shader* shader);

    void addPosition(float x, float y, float z);
    void addPosition(const Point& position);

    void addNormal(float x, float y, float z);
    void addNormal(const Vector& normal);

    void addTexCoord(float x, float y);
    void addTexCoord(const TexCoord& texCoord);

    void addColor(float r, float g, float b);
    void addColor(const Color& color);

    void addIndex(unsigned int index);
    void addTriangle(unsigned int top, unsigned int right, unsigned int left);
    void addFace(unsigned int topL, unsigned int topR, unsigned int bottomR, unsigned int bottomL);

private:
    void bindBuffers();

    /**
     * @brief Calculates the stride according to which attributes are enabled.
     * @return The stride between a vertex attribute's value and the next.
     */
    unsigned int getStride() const;

    bool shouldBind; ///< Whether the buffer should be bound before drawing.

    const unsigned int primitive; ///< 3D Primitive used to draw. e.g. GL_TRIANGLES, GL_LINES, etc…

    /**
     * @brief Attributes data. The currently available attributes are:\n
     *   0 - Position\n
     *   1 - Normal\n
     *   2 - Texture Coordinates\n
     *   3 - Color
     */
    std::vector<float> data;

    /**
     * @brief Bit masks for which attributes are enabled. For now the attributes are from right to
     * left (in little endian) :\n
     *   Position (vec3) : Is always enabled.\n
     *   Normal (vec3)\n
     *   Texture Coordinates (vec2)\n
     *   Color (vec3)
     */
    u_int8_t attributes;

    /**
     * Vector that can contain vertex indices in order to draw them according to the active
     * primitive. So for example if the primitive is GL_TRIANGLES, then the vertices corresponding
     * to 3 consecutive indices will form a triangle.\n
     * Filling this vector up is optional, if it is empty, the consecutive Vertex in the vertices
     * vector will be drawn according to the primitive. // TODO : update comment
     */
    Indices indices;

    unsigned int VAO; ///< Vertex Array Object
    unsigned int VBO; ///< Vertex Buffer Object
    unsigned int EBO; ///< Element Buffer Object
};