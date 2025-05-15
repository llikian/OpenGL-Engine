/***************************************************************************************************
 * @file  pos.vert
 * @brief Vertex shader that has only one vertex attribute: Position
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(aPos, 1.0f);
}
