/***************************************************************************************************
 * @file  Ray.hpp
 * @brief Declaration of the Ray struct
 **************************************************************************************************/

#pragma once

#include "AABB.hpp"
#include "maths/geometry.hpp"
#include "maths/vec3.hpp"

/**
 * @struct Ray
 * @brief
 */
struct Ray {
    explicit Ray(const vec3& origin) : origin(origin), direction(0.0f, 1.0f, 0.0f) { }

    Ray(const vec3& origin, const vec3& direction) : origin(origin), direction(normalize(direction)) { }

    Ray(const vec4& start, const vec4& end)
        : origin(start / start.w),
          direction(normalize(vec3(end / end.w) - origin)) { }

    vec3 get_point(float distance) const;

    float intersect_aabb(const AABB& aabb) const;

    float intersect_triangle(const vec3& A, const vec3& B, const vec3& C) const;


    vec3 origin;
    vec3 direction;
};
