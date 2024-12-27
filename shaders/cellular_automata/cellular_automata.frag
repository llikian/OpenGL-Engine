/***************************************************************************************************
 * @file  cellular_automata.frag
 * @brief Fragment shader for rendering a 3D game of life.
 **************************************************************************************************/

#version 460 core

in vec3 position;
in vec3 normal;

out vec4 fragColor;

uniform float cubeSize;
uniform int maxNeighbors;
uniform int neighbors;
uniform bool wireframeCube;

const vec3 LIGHT_POS = vec3(0.0f, 50.0f, 0.0f);

vec3 hsl(in float hue) {
    float h = mod(hue, 360.0f);

    float x = 1.0f - abs(mod(h / 60.0f, 2.0f) - 1.0f);

    switch(int(h / 60.0f)) {
        case 0:  return vec3(1.0f, x, 0.0f);
        case 1:  return vec3(x, 1.0f, 0.0f);
        case 2:  return vec3(0.0f, 1.0f, x);
        case 3:  return vec3(0.0f, x, 1.0f);
        case 4:  return vec3(x, 0.0f, 1.0f);
        case 5:  return vec3(1.0f, 0.0f, x);
        default: return vec3(0.0f);
    }
}

void main() {
    if(wireframeCube) {
        fragColor = vec4(0.7f, 0.2f, 0.8f, 1.0f);
    } else {
        float ambient = 0.3f;
        float diffuse = max(dot(normal, normalize(LIGHT_POS - position)), 0.0f);

        fragColor = vec4((ambient + diffuse) * normalize(position), 1.0f);
//        fragColor = vec4((ambient + diffuse) * hsl(360.0f * neighbors / maxNeighbors), 1.0f);
    }
}
