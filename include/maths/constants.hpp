/***************************************************************************************************
 * @file  constants.hpp
 * @brief Declaration of some mathematical constants such as PI,
 **************************************************************************************************/

#pragma once

#include <numbers>

constexpr float PI_F = std::numbers::pi_v<float>;
constexpr float PI_HALF_F = std::numbers::pi_v<float> * 0.5f;
constexpr float TAU_F = std::numbers::pi_v<float> * 2.0f;
constexpr float GOLDEN_RATIO_F = std::numbers::phi_v<float>;
constexpr float INV_GOLDEN_RATIO_F = 1.0f / std::numbers::phi_v<float>;
