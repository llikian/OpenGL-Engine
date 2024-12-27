/***************************************************************************************************
 * @file  cellular_automata.vert
 * @brief Vertex shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 position;
out vec3 normal;

uniform mat4 vpMatrix;

uniform int cellX;
uniform int cellY;
uniform int cellZ;

uniform float cubeSize;
uniform float cellSize;
uniform bool wireframeCube;

void main() {
    if(wireframeCube) {
        gl_Position = vpMatrix * vec4(cubeSize * aPos, 1.0f);
    } else {
        position = cellSize * (aPos + vec3(cellX, cellY, cellZ)) + (cellSize - cubeSize) / 2.0f;
        normal = aNormal;
        gl_Position = vpMatrix * vec4(position, 1.0f);
    }
}