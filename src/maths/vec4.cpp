/***************************************************************************************************
 * @file  vec4.cpp
 * @brief Implementation of the vec4 struct
 **************************************************************************************************/

#include "maths/vec4.hpp"

#include <cmath>

vec4::vec4() : x(), y(), z(), w() {}

vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

vec4::vec4(const Point& point) : x(point.x), y(point.y), z(point.z), w(1.0f) {}

vec4::vec4(const Vector& vec) : x(vec.x), y(vec.y), z(vec.z), w(0.0f) {}

float& vec4::operator[](uint8_t index) {
    return (&x)[index];
}

const float& vec4::operator[](uint8_t index) const {
    return (&x)[index];
}

vec4& vec4::operator+=(const vec4& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;

    return *this;
}

vec4& vec4::operator-=(const vec4& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;

    return *this;
}

vec4& vec4::operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;
    w *= value;

    return *this;
}

vec4& vec4::operator/=(float value) {
    float inv = 1.0f / value;

    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;

    return *this;
}

bool vec4::operator==(const vec4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool vec4::operator!=(const vec4& other) const {
    return x != other.x || y != other.y || z != other.z || w != other.w;
}

std::ostream& operator<<(std::ostream& stream, const vec4& vec) {
    stream << "( " << vec.x << " ; " << vec.y << " ; " << vec.z << " ; " << vec.w << " )";
    return stream;
}

std::istream& operator>>(std::istream& stream, vec4& vec) {
    stream >> vec.x >> vec.y >> vec.z >> vec.w;
    return stream;
}

vec4 operator+(const vec4& left, const vec4& right) {
    return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

vec4 operator-(const vec4& left, const vec4& right) {
    return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

vec4 operator*(const vec4& vec, float value) {
    return vec4(vec.x * value, vec.y * value, vec.z * value, vec.w * value);
}

vec4 operator*(float value, const vec4& vec) {
    return vec4(value * vec.x, value * vec.y, value * vec.z, value * vec.w);
}

vec4 operator/(const vec4& vec, float value) {
    float inv = 1.0f / value;
    return vec4(vec.x / inv, vec.y / inv, vec.z / inv, vec.w / inv);
}

vec4 operator-(const vec4& vec) {
    return vec4(-vec.x, -vec.y, -vec.z, -vec.w);
}

float length(const vec4& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

float length_sqr(const vec4& vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

vec4 normalize(const vec4& vec) {
    float length_inv = 1.0f / length(vec);
    return vec4(length_inv * vec.x, length_inv * vec.y, length_inv * vec.z, length_inv * vec.w);
}

float dot(const vec4& left, const vec4& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}
