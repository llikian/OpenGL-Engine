#version 460 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D u_texture0;

void main() {
    FragColor = texture(u_texture0, texCoord) * vec4(color, 1.0f);
}