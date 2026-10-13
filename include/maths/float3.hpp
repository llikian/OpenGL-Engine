/***************************************************************************************************
 * @file  float3.hpp
 * @brief Declaration of the float3 class
 **************************************************************************************************/

#pragma once

/**
 * @class float3
 * @brief
 */
struct float3 {
    float3() : x(0.0f), y(0.0f), z(0.0f) {}

    float3(float x, float y, float z) : x(x), y(y), z(z) {}

    explicit float3(float value) : x(value), y(value), z(value) {}

    float x, y, z;
};
