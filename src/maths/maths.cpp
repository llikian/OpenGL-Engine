/***************************************************************************************************
 * @file  maths.cpp
 * @brief Implementation of maths functions
 **************************************************************************************************/

#include "maths/maths.hpp"

#include "maths/constants.hpp"

float degrees_to_radians(float deg) {
    return deg * PI_F / 180.0f;
}

float radians_to_degrees(float rad) {
    return rad * 180.0f / PI_F;
}
