/***************************************************************************************************
 * @file  Vector.hpp
 * @brief Declaration of the Vector struct
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <iostream>
#include "Point.hpp"

struct Vector {
    Vector();
    Vector(float x, float y, float z);
    Vector(const Point& A, const Point& B);
    explicit Vector(float value);

    float& operator[](uint8_t index);
    const float& operator[](uint8_t index) const;

    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(float value);
    Vector& operator/=(float value);

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    inline Point& as_point() { return reinterpret_cast<Point&>(x); }

    inline const Point& as_point() const { return reinterpret_cast<const Point&>(x); }

    float x; ///< The x component of the vector3.
    float y; ///< The y component of the vector3.
    float z; ///< The z component of the vector3.
};

std::ostream& operator<<(std::ostream& stream, const Vector& vec);
std::istream& operator>>(std::istream& stream, Vector& vec);

Vector operator+(const Vector& left, const Vector& right);
Vector operator-(const Vector& left, const Vector& right);

Vector operator*(const Vector& vec, float value);
Vector operator*(float value, const Vector& vec);
Vector operator/(const Vector& vec, float value);

Vector operator-(const Vector& vec);

float length(const Vector& vec);
float length_sqr(const Vector& vec);

Vector normalize(const Vector& vec);

float dot(const Vector& left, const Vector& right);
Vector cross(const Vector& left, const Vector& right);
