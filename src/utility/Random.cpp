/***************************************************************************************************
 * @file  Random.cpp
 * @brief Implementation of the Random class
 **************************************************************************************************/

#include "utility/Random.hpp"

float Random::Float(float min, float max) {
    return std::uniform_real_distribution<float>(min, max)(generator);
}

vec2 Random::Vec2(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return vec2(distribution(generator), distribution(generator));
}

vec2 Random::Vec2(vec2 min, vec2 max) {
    return vec2(Float(min.x, max.x), Float(min.y, max.y));
}

vec3 Random::Vec3(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return vec3(distribution(generator), distribution(generator), distribution(generator));
}

vec3 Random::Vec3(vec3 min, vec3 max) {
    return vec3(Float(min.x, max.x), Float(min.y, max.y), Float(min.z, max.z));
}

vec4 Random::Vec4(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return vec4(distribution(generator), distribution(generator), distribution(generator), distribution(generator));
}

vec4 Random::Vec4(vec4 min, vec4 max) {
    return vec4(Float(min.x, max.x), Float(min.y, max.y), Float(min.z, max.z), Float(min.w, max.w));
}
