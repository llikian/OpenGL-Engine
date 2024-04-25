/***************************************************************************************************
 * @file  Vertex.hpp
 * @brief Declaration of the Vertex struct
 **************************************************************************************************/

#pragma once

#include "maths/vec2.hpp"
#include "maths/vec3.hpp"

/**
 * @struct Vertex
 * @brief Holds all the attributes for a 3D vertex: position, normal and texture coordinates.
 */
struct Vertex {
    /**
     * @brief Default constructor.
     */
    Vertex() = default;

    /**
     * @brief Constructs a vertex with a specific value for its position, normal and texture
     * coordinates.
     * @param position The vertex's position.
     * @param normal The vertex's normal.
     * @param texCoord The vertex's texture coordinates.
     */
    Vertex(const Point& position, const Vector& normal, const TexCoord& texCoord);

    Point position;    ///< The vertex's position.
    Vector normal;     ///< The vertex's normal.
    TexCoord texCoord; ///< The vertex's texture coordinates.
};