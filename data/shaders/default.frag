#version 460 core

out vec4 FragColor;

in vec3 normal;
in vec2 texCoord;
in vec3 color;

uniform uint attributes;
uniform sampler2D texture0;

void main() {
    FragColor = vec4(1.0f);

    if (((attributes >> 2) & 1u) == 1u) {
        FragColor = texture(texture0, texCoord);
    }

    if (((attributes >> 3) & 1u) == 1u) {
        FragColor *= vec4(color, 1.0f);
    }
}