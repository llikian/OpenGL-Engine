/***************************************************************************************************
 * @file  Point.hpp
 * @brief Declaration of the Point struct
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <iostream>

struct Vector; // Forward-Declaration of Vector to avoid circular includes

struct Point {
    Point();

    Point(float x, float y, float z);

    explicit Point(float value);

    float& operator[](uint8_t index);
    const float& operator[](uint8_t index) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    Point& operator+=(const Vector& vec);
    Point& operator-=(const Vector& vec);

    inline Vector& as_vector() { return reinterpret_cast<Vector&>(x); }

    inline const Vector& as_vector() const { return reinterpret_cast<const Vector&>(x); }

    float x; ///< The x component of the point.
    float y; ///< The y component of the point.
    float z; ///< The z component of the point.
};

std::ostream& operator<<(std::ostream& stream, const Point& point);
std::istream& operator>>(std::istream& stream, Point& point);

Vector operator-(const Point& left, const Point& right);

Point operator+(const Point& point, const Vector& vec);
Point operator-(const Point& point, const Vector& vec);
