/***************************************************************************************************
 * @file  float3.hpp
 * @brief Declaration of the float3 class
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <iostream>

/**
 * @class float3
 * @brief
 */
struct float3 {
    float3();
    float3(float x, float y, float z);
    explicit float3(float value);

    bool operator==(const float3& other) const;
    bool operator!=(const float3& other) const;

    inline float& operator[](uint8_t index) { return (&x)[index]; };

    inline const float& operator[](uint8_t index) const { return (&x)[index]; };

    float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const float3& value);
std::istream& operator>>(std::istream& stream, float3& value);
