/***************************************************************************************************
 * @file  vec2.cpp
 * @brief Implementation of the vec2 struct
 **************************************************************************************************/

#include "maths/vec2.hpp"

#include <cmath>

vec2::vec2() : x(), y() {}

vec2::vec2(float x, float y) : x(x), y(y) {}

float& vec2::operator[](uint8_t index) {
    return (&x)[index];
}

const float& vec2::operator[](uint8_t index) const {
    return (&x)[index];
}

vec2& vec2::operator+=(const vec2& vec) {
    x += vec.x;
    y += vec.y;

    return *this;
}

vec2& vec2::operator-=(const vec2& vec) {
    x -= vec.x;
    y -= vec.y;

    return *this;
}

vec2& vec2::operator*=(float value) {
    x *= value;
    y *= value;

    return *this;
}

vec2& vec2::operator/=(float value) {
    float inv = 1.0f / value;

    x *= inv;
    y *= inv;

    return *this;
}

bool vec2::operator==(const vec2& other) const {
    return x == other.x && y == other.y;
}

bool vec2::operator!=(const vec2& other) const {
    return x != other.x || y != other.y;
}

std::ostream& operator<<(std::ostream& stream, const vec2& vec) {
    stream << "( " << vec.x << " ; " << vec.y << " )";
    return stream;
}

std::istream& operator>>(std::istream& stream, vec2& vec) {
    stream >> vec.x >> vec.y;
    return stream;
}

vec2 operator+(const vec2& left, const vec2& right) {
    return vec2(left.x + right.x, left.y + right.y);
}

vec2 operator-(const vec2& left, const vec2& right) {
    return vec2(left.x - right.x, left.y - right.y);
}

vec2 operator*(const vec2& vec, float value) {
    return vec2(vec.x * value, vec.y * value);
}

vec2 operator*(float value, const vec2& vec) {
    return vec2(value * vec.x, value * vec.y);
}

vec2 operator/(const vec2& vec, float value) {
    return vec2(vec.x / value, vec.y / value);
}

vec2 operator-(const vec2& vec) {
    return vec2(-vec.x, -vec.y);
}

float length(const vec2& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float length_sqr(const vec2& vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

vec2 normalize(const vec2& vec) {
    float length_inv = 1.0f / length(vec);
    return vec2(length_inv * vec.x, length_inv * vec.y);
}

float dot(const vec2& left, const vec2& right) {
    return left.x * right.x + left.y * right.y;
}
