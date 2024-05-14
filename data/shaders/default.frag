/***************************************************************************************************
 * @file  default.frag
 * @brief Default fragment shader
 **************************************************************************************************/

#version 460 core

out vec4 fragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in vec3 color;

uniform uint attributes;
uniform sampler2D texture0;
uniform vec3 cameraPos;
uniform vec3 lightPos;

vec3 phongLighting() {
    const vec3 lightColor = vec3(1.0f);

    // Ambient Lighting
    const float ambient = 0.25f;

    // Diffuse Lighting
    const vec3 lightDirection = normalize(lightPos - position);
    const float diffuse = max(dot(normal, lightDirection), 0.0f);

    // Specular lighting
    const float specularStreght = 0.25f;
    const vec3 viewDirection = normalize(cameraPos - position);
    const vec3 reflectionDir = reflect(-lightDirection, normal);
    float specular = specularStreght * pow(max(dot(viewDirection, reflectionDir), 0.0f), 32.0f);

    return (ambient + diffuse + specular) * lightColor;
}

void main() {
    fragColor = vec4(1.0f);

    if (((attributes >> 1) & 1u) == 1u) {
        fragColor.xyz = phongLighting();
    }

    if (((attributes >> 2) & 1u) == 1u) {
        fragColor *= texture(texture0, texCoord);
    }

    if (((attributes >> 3) & 1u) == 1u) {
        fragColor.xyz *= color;
    }
}