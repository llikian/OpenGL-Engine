/***************************************************************************************************
 * @file  Point.cpp
 * @brief Implementation of the Point struct
 **************************************************************************************************/

#include "maths/Point.hpp"

#include "maths/Vector.hpp"

Point::Point(const Vector& vec) : float3(vec.x, vec.y, vec.z) {}

Point& Point::operator+=(const Vector& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Point& Point::operator-=(const Vector& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

Vector operator-(const Point& left, const Point& right) {
    return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}

Point operator+(const Point& point, const Vector& vec) {
    return Point(point.x + vec.x, point.y + vec.y, point.z + vec.z);
}

Point operator-(const Point& point, const Vector& vec) {
    return Point(point.x - vec.x, point.y - vec.y, point.z - vec.z);
}

Point midpoint(const Point& p0, const Point& p1) {
    return Point(0.5f * (p0.x + p1.x), //
                 0.5f * (p0.y + p1.y),
                 0.5f * (p0.z + p1.z));
}

Point midpoint(const Point& p0, const Point& p1, const Point& p2) {
    constexpr float one_third = 1.0f / 3.0f;
    return Point(one_third * (p0.x + p1.x + p2.x), //
                 one_third * (p0.y + p1.y + p2.y),
                 one_third * (p0.z + p1.z + p2.z));
}

Point midpoint(const Point& p0, const Point& p1, const Point& p2, const Point& p3) {
    return Point(0.25f * (p0.x + p1.x + p2.x + p3.x), //
                 0.25f * (p0.y + p1.y + p2.y + p3.y),
                 0.25f * (p0.z + p1.z + p2.z + p3.z));
}

Point midpoint(const Point& p0, const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    return Point(0.2f * (p0.x + p1.x + p2.x + p3.x + p4.x), //
                 0.2f * (p0.y + p1.y + p2.y + p3.y + p4.y),
                 0.2f * (p0.z + p1.z + p2.z + p3.z + p4.z));
}

void cw_min(Point& p0, const Point& p1) {
    p0.x = std::min(p0.x, p1.x);
    p0.y = std::min(p0.y, p1.y);
    p0.z = std::min(p0.z, p1.z);
}

void cw_max(Point& p0, const Point& p1) {
    p0.x = std::max(p0.x, p1.x);
    p0.y = std::max(p0.y, p1.y);
    p0.z = std::max(p0.z, p1.z);
}
