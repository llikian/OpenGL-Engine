/***************************************************************************************************
 * @file  Ray.cpp
 * @brief Implementation of the Ray class
 **************************************************************************************************/

#include "culling/Ray.hpp"

#include "maths/constants.hpp"

Point Ray::get_point(float distance) const {
    return origin + distance * direction;
}

bool Ray::intersect_aabb(const AABB& aabb, float& tmin, float& tmax) const {
    tmin = -INFINITY_F;
    tmax = INFINITY_F;

    for(uint8_t i = 0; i < 3; ++i) {
        if(direction[i] != 0) {
            float t1 = (aabb.min_point[i] - origin[i]) / direction[i];
            float t2 = (aabb.max_point[i] - origin[i]) / direction[i];
            if(t1 > t2) { std::swap(t1, t2); }

            tmin = std::max(tmin, t1);
            tmax = std::min(tmax, t2);
            if(tmin > tmax) { return false; }
        } else if(origin[i] < aabb.min_point[i] || origin[i] > aabb.max_point[i]) {
            return false;
        }
    }

    return true;
}

float Ray::intersect_triangle(const Point& A, const Point& B, const Point& C) const {
    Vector edge1 = B - A;
    Vector edge2 = C - A;
    Vector origin_cross_edge2 = cross(direction, edge2);

    float determinent = dot(edge1, origin_cross_edge2);
    if(std::abs(determinent) < EPSILON_F) { return -INFINITY_F; }
    float determinent_inv = 1.0f / determinent;

    Vector A_to_origin = origin - A;
    float u = determinent_inv * dot(A_to_origin, origin_cross_edge2);
    if(u < 0.0f || u > 1.0f) { return -INFINITY_F; }

    Vector s_cross_edge1 = cross(A_to_origin, edge1);
    float v = determinent_inv * dot(direction, s_cross_edge1);
    if(v < 0.0f || u + v > 1.0f) { return -INFINITY_F; }

    float t = determinent_inv * dot(edge2, s_cross_edge1);
    return t > 0.0f ? t : -INFINITY_F;
}

float Ray::intersect_triangle(const vec4& A, const vec4& B, const vec4& C) const {
    return intersect_triangle(Point(A.x / A.w, A.y / A.w, A.z / A.w),
                              Point(B.x / B.w, B.y / B.w, B.z / B.w),
                              Point(C.x / C.w, C.y / C.w, C.z / C.w));
}
