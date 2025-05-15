/***************************************************************************************************
 * @file  pos_normal.vert
 * @brief Vertex shader that has 2 vertex attributes: Position and Normal
 **************************************************************************************************/

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 position;
out vec3 normal;

uniform mat4 mvp;
uniform mat4 model;
uniform mat3 normalModel;

void main() {
    vec4 pos = vec4(aPos, 1.0f);

    gl_Position = mvp * pos;
    position = (model * pos).xyz;
    normal = normalize(normalModel * aNormal);
}
