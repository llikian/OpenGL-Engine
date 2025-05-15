/***************************************************************************************************
 * @file  spotlight.frag
 * @brief Fragment shader to render an object aftected by a spotlight
 **************************************************************************************************/

#version 460 core

in vec3 position;

out vec4 fragColor;

struct Spotlight {
    vec3 position;
    vec3 direction;
    float umbra; // Cosinus of Cutoff Angle
    float penumbra; // Cosinus of Smooth Cutoff Angle
    vec3 color;
};

uniform Spotlight spotlight;

void main() {
    vec3 lightDir = normalize(position - spotlight.position);
    float cos_s = dot(normalize(spotlight.direction), lightDir);
    float t = clamp((cos_s - spotlight.umbra) / (spotlight.penumbra - spotlight.umbra), 0.0f, 1.0f);
    float falloff = t * t;

    fragColor = vec4(spotlight.color * falloff, 1.0f);
}
