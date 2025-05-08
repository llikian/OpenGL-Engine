/***************************************************************************************************
 * @file  point_mesh.frag
 * @brief Fragment shader for rendering meshes made out of points
 **************************************************************************************************/

#version 460 core

in vec3 color;

out vec4 fragColor;

void main() {
    fragColor = vec4(color , 1.0f);
}
