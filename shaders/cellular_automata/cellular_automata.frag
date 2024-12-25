/***************************************************************************************************
 * @file  cellular_automata.frag
 * @brief Fragment shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

out vec4 fragColor;

uniform bool wireframeCube;

uniform float cubeSize;

void main() {
    if(wireframeCube) {
        fragColor = vec4(0.7f, 0.2f, 0.8f, 1.0f);
    } else {
        fragColor = vec4(1.0f);
    }
}
