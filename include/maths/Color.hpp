/***************************************************************************************************
 * @file  Color.hpp
 * @brief Declaration of the Color struct
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <iostream>

struct Color {
    Color();
    Color(float r, float g, float b);
    explicit Color(float value);

    Color& operator+=(const Color& color);
    Color& operator-=(const Color& color);
    Color& operator*=(const Color& color);
    Color& operator/=(const Color& color);

    Color& operator*=(float value);
    Color& operator/=(float value);

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    float r; ///< The r component of the color.
    float g; ///< The g component of the color.
    float b; ///< The b component of the color.
};

std::ostream& operator<<(std::ostream& stream, const Color& color);
std::istream& operator>>(std::istream& stream, Color& color);

Color operator+(const Color& left, const Color& right);
Color operator-(const Color& left, const Color& right);
Color operator*(const Color& left, const Color& right);
Color operator/(const Color& left, const Color& right);

Color operator*(const Color& color, float value);
Color operator*(float value, const Color& color);
Color operator/(const Color& color, float value);
