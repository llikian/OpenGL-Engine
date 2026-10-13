/***************************************************************************************************
 * @file  Point.hpp
 * @brief Declaration of the Point struct
 **************************************************************************************************/

#pragma once

#include "maths/float3.hpp"

struct Vector; // Forward-Declaration of Vector to avoid circular includes

struct Point : float3 {
    using float3::float3;

    explicit Point(const Vector& vec);

    Point& operator+=(const Vector& vec);
    Point& operator-=(const Vector& vec);

    inline Vector& as_vector() { return reinterpret_cast<Vector&>(x); }

    inline const Vector& as_vector() const { return reinterpret_cast<const Vector&>(x); }
};

Vector operator-(const Point& left, const Point& right);

Point operator+(const Point& point, const Vector& vec);
Point operator-(const Point& point, const Vector& vec);

Point midpoint(const Point& p0, const Point& p1);
Point midpoint(const Point& p0, const Point& p1, const Point& p2);
Point midpoint(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
Point midpoint(const Point& p0, const Point& p1, const Point& p2, const Point& p3, const Point& p4);

void cw_min(Point& p0, const Point& p1);
void cw_max(Point& p0, const Point& p1);
