/***************************************************************************************************
 * @file  trigonometry.cpp
 * @brief Implementation of functions regarding trigonometry
 **************************************************************************************************/

#include "maths/trigonometry.hpp"

#include <cmath>

float radians(float degrees) {
    return degrees * M_PIf / 180.0f;
}

float degrees(float radians) {
    return radians * 180.0f / M_PIf;
}
