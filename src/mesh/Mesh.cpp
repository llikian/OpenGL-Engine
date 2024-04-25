/***************************************************************************************************
 * @file  Mesh.cpp
 * @brief Implementation of the Mesh class
 **************************************************************************************************/

#include "mesh/Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(unsigned int primitive) : shouldBind(true), primitive(primitive) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

Mesh::Mesh(unsigned int primitive, const Vertices& vertices)
    : shouldBind(true),
      primitive(primitive),
      vertices(vertices) { }

Mesh::Mesh(unsigned int primitive, const Vertices& vertices, const Indices& indices)
    : shouldBind(true),
      primitive(primitive),
      vertices(vertices),
      indices(indices) { }

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::draw() {
    if(shouldBind) {
        bindBuffers();
        shouldBind = false;
    }

    glBindVertexArray(VAO);

    if(indices.empty()) {
        glDrawArrays(primitive, 0, vertices.size());
    } else {
        glDrawElements(primitive, indices.size(), GL_UNSIGNED_INT, nullptr);
    }
}

void Mesh::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
}

void Mesh::addVertex(const Point& position, const Vector& normal, const TexCoord& texCoord) {
    vertices.emplace_back(position, normal, texCoord);
}

void Mesh::addIndex(unsigned int index) {
    indices.push_back(index);
}

void Mesh::addTriangle(unsigned int top, unsigned int right, unsigned int left) {
    addIndex(top);
    addIndex(right);
    addIndex(left);
}

void Mesh::addFace(unsigned int topL, unsigned int topR,
                   unsigned int bottomR, unsigned int bottomL) {

    addTriangle(topL, topR, bottomR);
    addTriangle(bottomR, bottomL, topL);
}

void Mesh::bindBuffers() {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    void* offset;

    // Positions
    offset = reinterpret_cast<int*>(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), offset);
    glEnableVertexAttribArray(0);

    // Normals
    offset = reinterpret_cast<int*>(3);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), offset);
    glEnableVertexAttribArray(1);

    // Texture Coordinates
    offset = reinterpret_cast<int*>(6);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), offset);
    glEnableVertexAttribArray(2);

    if(!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}
