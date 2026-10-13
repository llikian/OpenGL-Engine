/***************************************************************************************************
 * @file  vec4.hpp
 * @brief Declaration of the vec4 struct
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <iostream>
#include "Point.hpp"
#include "Vector.hpp"

struct vec4 {
    vec4();
    vec4(float x, float y, float z, float w);
    explicit vec4(const Point& point);
    explicit vec4(const Vector& vec);

    float& operator[](uint8_t index);
    const float& operator[](uint8_t index) const;

    vec4& operator+=(const vec4& vec);
    vec4& operator-=(const vec4& vec);
    vec4& operator*=(float value);
    vec4& operator/=(float value);

    bool operator==(const vec4& other) const;
    bool operator!=(const vec4& other) const;

    float x; ///< The x component of the vector3.
    float y; ///< The y component of the vector3.
    float z; ///< The z component of the vector3.
    float w; ///< The w component of the vector3.
};

std::ostream& operator<<(std::ostream& stream, const vec4& vec);
std::istream& operator>>(std::istream& stream, vec4& vec);

vec4 operator+(const vec4& left, const vec4& right);
vec4 operator-(const vec4& left, const vec4& right);

vec4 operator*(const vec4& vec, float value);
vec4 operator*(float value, const vec4& vec);
vec4 operator/(const vec4& vec, float value);

vec4 operator-(const vec4& vec);

float length(const vec4& vec);
float length_sqr(const vec4& vec);

vec4 normalize(const vec4& vec);

float dot(const vec4& left, const vec4& right);
