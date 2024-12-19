/***************************************************************************************************
 * @file  game_of_life.vert
 * @brief Vertex shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;
out vec3 color;

uniform mat4 mvp;
uniform mat4 model;

void main() {
    vec4 pos = vec4(aPos, 1.0f);

    gl_Position = mvp * pos;
    position = (model * pos).xyz;
    normal = normalize(transpose(inverse(mat3(model))) * aNormal);
    texCoord = aTexCoord;
}