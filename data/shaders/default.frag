#version 460 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

void main() {
    FragColor = mix(texture(u_texture0, texCoord), texture(u_texture1, texCoord), 0.5);
}