/***************************************************************************************************
 * @file  game_of_life.vert
 * @brief Vertex shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;

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
        vec3 pos = cellSize * (aPos + vec3(cellX, cellY, cellZ)) - cubeSize / 2.0f + cellSize / 2.0f;
        gl_Position = vpMatrix * vec4(pos, 1.0f);
    }
}