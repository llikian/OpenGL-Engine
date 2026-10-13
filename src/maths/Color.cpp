/***************************************************************************************************
 * @file  Color.cpp
 * @brief Implementation of the Color struct
 **************************************************************************************************/

#include "maths/Color.hpp"

Color::Color() : r(), g(), b() {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::Color(float value) : r(value), g(value), b(value) {}

Color& Color::operator+=(const Color& color) {
    r += color.r;
    g += color.g;
    b += color.b;

    return *this;
}

Color& Color::operator-=(const Color& color) {
    r -= color.r;
    g -= color.g;
    b -= color.b;

    return *this;
}

Color& Color::operator*=(const Color& color) {
    r *= color.r;
    g *= color.g;
    b *= color.b;

    return *this;
}

Color& Color::operator/=(const Color& color) {
    r /= color.r;
    g /= color.g;
    b /= color.b;

    return *this;
}

Color& Color::operator*=(float value) {
    r *= value;
    g *= value;
    b *= value;

    return *this;
}

Color& Color::operator/=(float value) {
    float inv = 1.0f / value;

    r *= inv;
    g *= inv;
    b *= inv;

    return *this;
}

bool Color::operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b;
}

bool Color::operator!=(const Color& other) const {
    return r != other.r || g != other.g || b != other.b;
}

std::ostream& operator<<(std::ostream& stream, const Color& color) {
    stream << "( " << color.r << " ; " << color.g << " ; " << color.b << " )";
    return stream;
}

std::istream& operator>>(std::istream& stream, Color& color) {
    stream >> color.r >> color.g >> color.b;
    return stream;
}

Color operator+(const Color& left, const Color& right) {
    return Color(left.r + right.r, left.g + right.g, left.b + right.b);
}

Color operator-(const Color& left, const Color& right) {
    return Color(left.r - right.r, left.g - right.g, left.b - right.b);
}

Color operator*(const Color& left, const Color& right) {
    return Color(left.r * right.r, left.g * right.g, left.b * right.b);
}

Color operator/(const Color& left, const Color& right) {
    return Color(left.r / right.r, left.g / right.g, left.b / right.b);
}

Color operator*(const Color& color, float value) {
    return Color(color.r * value, color.g * value, color.b * value);
}

Color operator*(float value, const Color& color) {
    return Color(value * color.r, value * color.g, value * color.b);
}

Color operator/(const Color& color, float value) {
    return Color(color.r / value, color.g / value, color.b / value);
}
