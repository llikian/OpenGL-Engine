/***************************************************************************************************
 * @file  game_of_life.frag
 * @brief Fragment shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

uniform vec3 cameraPos;

void main() {
    fragColor = vec4(1.0f);
}
