/***************************************************************************************************
 * @file  pos_tex.vert
 * @brief Vertex shader that has 2 vertex attributes: Position and Texture Coordinates
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(aPos, 1.0f);
    texCoord = aTexCoord;
}
