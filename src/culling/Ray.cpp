/***************************************************************************************************
 * @file  Ray.cpp
 * @brief Implementation of the Ray class
 **************************************************************************************************/

#include "culling/Ray.hpp"

vec3 Ray::get_point(float distance) const {
    return origin + distance * direction;
}

float Ray::intersect_aabb(const AABB& aabb) const {
    float tmin = -infinity;
    float tmax = infinity;

    for(uint8_t i = 0 ; i < 3 ; ++i) {
        if(direction[i] != 0) {
            float t1 = (aabb.min_point[i] - origin[i]) / direction[i];
            float t2 = (aabb.max_point[i] - origin[i]) / direction[i];
            if(t1 > t2) { std::swap(t1, t2); }

            tmin = std::max(tmin, t1);
            tmax = std::min(tmax, t2);
            if(tmin > tmax) { return -infinity; }
        } else if(origin[i] < aabb.min_point[i] || origin[i] > aabb.max_point[i]) {
            return -infinity;
        }
    }

    return tmin;
}

// float Ray::intersect_triangle(const vec3& A, const vec3& B, const vec3& C) const {
//     vec3 normal = normalize(cross(B - A, C - A));
//     float distance = dot(normal, A - origin) / dot(normal, direction);
//
//     if(distance < 0.0f) { return -infinity; }
//     vec3 point = get_point(distance);
//
//     if(dot(normal, cross(B - A, point - A)) < 0.0f) { return -infinity; }
//     if(dot(normal, cross(C - B, point - B)) < 0.0f) { return -infinity; }
//     if(dot(normal, cross(A - C, point - C)) < 0.0f) { return -infinity; }
//
//     return distance;
// }

float Ray::intersect_triangle(const vec3& A, const vec3& B, const vec3& C) const {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    vec3 edge1 = B - A;
    vec3 edge2 = C - A;

    vec3 ray_cross_e2 = cross(direction, edge2);
    float det = dot(edge1, ray_cross_e2);
    if(det > -epsilon && det < epsilon) { return -infinity; }
    float inv_det = 1.0f / det;

    vec3 s = origin - A;
    float u = inv_det * dot(s, ray_cross_e2);
    if(u < 0.0f || u > 1.0f) { return -infinity; }

    vec3 s_cross_e1 = cross(s, edge1);
    float v = inv_det * dot(direction, s_cross_e1);
    if (v < 0.0f || u + v > 1.0f) { return -infinity; }

    float t = inv_det * dot(edge2, s_cross_e1);
    return t > 0.0f ? t : -infinity;
}
