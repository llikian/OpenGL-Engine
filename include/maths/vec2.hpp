/***************************************************************************************************
 * @file  vec2.hpp
 * @brief Declaration of the vec2 struct
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <iostream>

struct vec2 {
    vec2();
    vec2(float x, float y);

    float& operator[](uint8_t index);
    const float& operator[](uint8_t index) const;

    vec2& operator+=(const vec2& vec);
    vec2& operator-=(const vec2& vec);
    vec2& operator*=(float value);
    vec2& operator/=(float value);

    bool operator==(const vec2& other) const;
    bool operator!=(const vec2& other) const;

    float x; ///< The x component of the vector3.
    float y; ///< The y component of the vector3.
};

std::ostream& operator<<(std::ostream& stream, const vec2& vec);
std::istream& operator>>(std::istream& stream, vec2& vec);

vec2 operator+(const vec2& left, const vec2& right);
vec2 operator-(const vec2& left, const vec2& right);

vec2 operator*(const vec2& vec, float value);
vec2 operator*(float value, const vec2& vec);
vec2 operator/(const vec2& vec, float value);

vec2 operator-(const vec2& vec);

float length(const vec2& vec);
float length_sqr(const vec2& vec);

vec2 normalize(const vec2& vec);

float dot(const vec2& left, const vec2& right);
