#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;

out vec3 position;
out vec3 normal;
out vec2 texCoord;
out vec3 color;

uniform mat4 mvp;
uniform mat4 model;

void main() {
    gl_Position = mvp * vec4(aPos, 1.0f);
    position = (model * vec4(aPos, 1.0f)).xyz;
    normal = normalize(transpose(inverse(mat3(model))) * aNormal);
    texCoord = aTexCoord;
    color = aColor;
}