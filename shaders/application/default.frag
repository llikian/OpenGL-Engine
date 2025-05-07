/***************************************************************************************************
 * @file  default.frag
 * @brief Default fragment shader
 **************************************************************************************************/

#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

//uniform vec3 cameraPos;

const vec3 LIGHT_POS = vec3(10.0f);
const vec3 LIGHT_COLOR = vec3(1.0f);

void main() {
    float ambient = 0.2f;
    float diffuse = max(dot(normal, normalize(LIGHT_POS)), 0.0f);

    fragColor = vec4((ambient + diffuse) * LIGHT_COLOR , 1.0f);
}
