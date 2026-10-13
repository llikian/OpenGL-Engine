/***************************************************************************************************
 * @file  Random.hpp
 * @brief Declaration of the Random class
 **************************************************************************************************/

#pragma once

#include <random>
#include "maths/vec2.hpp"
#include "maths/vec4.hpp"
#include "maths/Vector.hpp"

/**
 * @class Random
 * @brief Utility class providing static methods for generating random integers and real numbers.
 */
class Random {
public:
    /**
     * @brief Generate a random integer between min and max (inclusive).
     * @param min The minimum value of the output.
     * @param max The maximum value of the output.
     */
    template <std::integral Type>
    static float integer(float min, float max) {
        return std::uniform_int_distribution<Type>(min, max)(generator);
    }

    /**
     * @brief Generate a random real number between min and max (inclusive).
     * @param min The minimum value of the output.
     * @param max The maximum value of the output.
     */
    template <typename Type>
    static float real(float min, float max) {
        return std::uniform_real_distribution<Type>(min, max)(generator);
    }

    /**
     * @brief Generate a random 2D vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    static vec2 real2(const vec2& min, const vec2& max) {
        return vec2(std::uniform_real_distribution<float>(min.x, max.x)(generator),
                    std::uniform_real_distribution<float>(min.y, max.y)(generator));
    }

    /**
     * @brief Generate a random 2D vector with a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    static vec2 real2(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return vec2(distribution(generator), distribution(generator));
    }

    /**
     * @brief Generate a random 3D vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    static Vector real3(const Vector& min, const Vector& max) {
        return Vector(std::uniform_real_distribution<float>(min.x, max.x)(generator),
                      std::uniform_real_distribution<float>(min.y, max.y)(generator),
                      std::uniform_real_distribution<float>(min.z, max.z)(generator));
    }

    /**
     * @brief Generate a random 3D vector with a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    static Vector real3(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return Vector(distribution(generator), distribution(generator), distribution(generator));
    }

    /**
     * @brief Generate a random 4D vector with component-wise ranges.
     * @param min The minimum values of each component of the output.
     * @param max The maximum values of each component of the output.
     */
    static vec4 real4(const vec4& min, const vec4& max) {
        return vec4(std::uniform_real_distribution<float>(min.x, max.x)(generator),
                    std::uniform_real_distribution<float>(min.y, max.y)(generator),
                    std::uniform_real_distribution<float>(min.z, max.z)(generator),
                    std::uniform_real_distribution<float>(min.w, max.w)(generator));
    }

    /**
     * @brief Generate a random 4D vector with a uniform range for all components.
     * @param min The minimum value of each component of the output.
     * @param max The maximum value of each component of the output.
     */
    static vec4 real4(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return vec4(distribution(generator), distribution(generator), distribution(generator), distribution(generator));
    }

private:
    /// Random seed sourced from hardware entropy.
    inline static std::random_device seed {};

    /// Shared random engine used across all random generation methods.
    inline static std::default_random_engine generator { seed() };
};
