/***************************************************************************************************
 * @file  float3.cpp
 * @brief Implementation of the float3 class
 **************************************************************************************************/

#include "maths/float3.hpp"

float3::float3() : x(0.0f), y(0.0f), z(0.0f) {}

float3::float3(float x, float y, float z) : x(x), y(y), z(z) {}

float3::float3(float value) : x(value), y(value), z(value) {}

bool float3::operator==(const float3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool float3::operator!=(const float3& other) const {
    return x != other.x || y != other.y || z != other.z;
};

std::ostream& operator<<(std::ostream& stream, const float3& value) {
    stream << "( " << value.x << " ; " << value.y << " ; " << value.z << " )";
    return stream;
}

std::istream& operator>>(std::istream& stream, float3& value) {
    stream >> value.x >> value.y >> value.z;
    return stream;
}
