/***************************************************************************************************
 * @file  Vector.cpp
 * @brief Implementation of the Vector struct
 **************************************************************************************************/

#include "maths/Vector.hpp"

#include <cmath>

Vector::Vector(const Point& point) : float3(point.x, point.y, point.z) {}

Vector::Vector(const Point& A, const Point& B) : float3(B.x - A.x, B.y - A.y, B.z - A.z) {}

Vector& Vector::operator+=(const Vector& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

Vector& Vector::operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;

    return *this;
}

Vector& Vector::operator/=(float value) {
    float inv = 1.0f / value;

    x *= inv;
    y *= inv;
    z *= inv;

    return *this;
}

Vector operator+(const Vector& left, const Vector& right) {
    return Vector(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector operator-(const Vector& left, const Vector& right) {
    return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector operator*(const Vector& vec, float value) {
    return Vector(vec.x * value, vec.y * value, vec.z * value);
}

Vector operator*(float value, const Vector& vec) {
    return Vector(value * vec.x, value * vec.y, value * vec.z);
}

Vector operator/(const Vector& vec, float value) {
    return Vector(vec.x / value, vec.y / value, vec.z / value);
}

Vector operator-(const Vector& vec) {
    return Vector(-vec.x, -vec.y, -vec.z);
}

float length(const Vector& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float length_sqr(const Vector& vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

Vector normalize(const Vector& vec) {
    float length_inv = 1.0f / length(vec);
    return Vector(length_inv * vec.x, length_inv * vec.y, length_inv * vec.z);
}

float dot(const Vector& left, const Vector& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector cross(const Vector& left, const Vector& right) {
    return Vector(left.y * right.z - left.z * right.y,
                  left.z * right.x - left.x * right.z,
                  left.x * right.y - left.y * right.x);
}
