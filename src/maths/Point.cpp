/***************************************************************************************************
 * @file  Point.cpp
 * @brief Implementation of the Point struct
 **************************************************************************************************/

#include "maths/Point.hpp"

#include "maths/Vector.hpp"

Point::Point() : x(0.0f), y(0.0f), z(0.0) {}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point::Point(float value) : x(value), y(value), z(value) {}

float& Point::operator[](uint8_t index) {
    return (&x)[index];
}

const float& Point::operator[](uint8_t index) const {
    return (&x)[index];
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool Point::operator!=(const Point& other) const {
    return x != other.x || y != other.y || z != other.z;
}

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

std::ostream& operator<<(std::ostream& stream, const Point& point) {
    stream << "( " << point.x << " ; " << point.y << " ; " << point.z << " )";
    return stream;
}

std::istream& operator>>(std::istream& stream, Point& point) {
    stream >> point.x >> point.y >> point.z;
    return stream;
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
