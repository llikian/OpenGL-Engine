/***************************************************************************************************
 * @file  cellular_automata.frag
 * @brief Fragment shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

in vec3 position;
in vec3 normal;

out vec4 fragColor;

uniform bool wireframeCube;

uniform float cubeSize;

const vec3 LIGHT_POS = vec3(0.0f, 50.0f, 0.0f);

void main() {
    if(wireframeCube) {
        fragColor = vec4(0.7f, 0.2f, 0.8f, 1.0f);
    } else {
        /* Ambient */
        float ambient = 0.3f;

        /* Diffuse */
        vec3 lightDir = normalize(LIGHT_POS - position);
        float diffuse = max(dot(normal, lightDir), 0.0f);

        fragColor = vec4(vec3(ambient + diffuse), 1.0f);
    }
}
