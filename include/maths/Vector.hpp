/***************************************************************************************************
 * @file  Vector.hpp
 * @brief Declaration of the Vector struct
 **************************************************************************************************/

#pragma once

#include "Point.hpp"

struct Vector : float3 {
    using float3::float3;

    explicit Vector(const Point& point);
    Vector(const Point& A, const Point& B);

    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(float value);
    Vector& operator/=(float value);

    inline Point& as_point() { return reinterpret_cast<Point&>(x); }

    inline const Point& as_point() const { return reinterpret_cast<const Point&>(x); }
};

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
