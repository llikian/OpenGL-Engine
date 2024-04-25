/***************************************************************************************************
 * @file  Vertex.cpp
 * @brief Implementation of the Vertex class
 **************************************************************************************************/

#include "mesh/Vertex.hpp"

Vertex::Vertex(const Point& position, const Vector& normal, const TexCoord& texCoord)
    : position(position), normal(normal), texCoord(texCoord) { }