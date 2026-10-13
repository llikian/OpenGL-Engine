/***************************************************************************************************
 * @file  Ray.hpp
 * @brief Declaration of the Ray struct
 **************************************************************************************************/

#pragma once

#include "AABB.hpp"

/**
 * @struct Ray
 * @brief
 */
struct Ray {
    explicit Ray(const Point& origin) : origin(origin), direction(0.0f, 1.0f, 0.0f) {}

    Ray(const Point& origin, const Vector& direction) : origin(origin), direction(normalize(direction)) {}

    Ray(const vec4& start, const vec4& end)
        : origin(start.x / start.w, start.y / start.w, start.z / start.w),
          direction(normalize(Point(end.x / end.w, end.y / end.w, end.z / end.w) - origin)) {}

    Point get_point(float distance) const;

    bool intersect_aabb(const AABB& aabb, float& tmin, float& tmax) const;

    float intersect_triangle(const Point& A, const Point& B, const Point& C) const;
    float intersect_triangle(const vec4& A, const vec4& B, const vec4& C) const;

    Point origin;
    Vector direction;
};
