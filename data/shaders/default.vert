#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec2 texCoord;

uniform mat4 u_transform;

void main() {
    gl_Position = u_transform * vec4(aPos, 1.0f);
    normal = aNormal;
    texCoord = aTexCoord;
}