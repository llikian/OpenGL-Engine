/***************************************************************************************************
 * @file  point_mesh.vert
 * @brief Vertex shader for rendering meshes made out of points
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aSize;

out vec3 color;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(aPos, 1.0f);
    color = aColor;
    gl_PointSize = aSize;
}
