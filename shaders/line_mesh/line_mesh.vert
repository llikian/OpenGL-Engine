/***************************************************************************************************
 * @file  line_mesh.vert
 * @brief Vertex shader for rendering meshes made out of lines
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(aPos, 1.0f);
    color = aColor;
}
