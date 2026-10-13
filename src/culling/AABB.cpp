/***************************************************************************************************
 * @file  AABB.cpp
 * @brief Implementation of the AABB struct
 **************************************************************************************************/

#include "culling/AABB.hpp"

#include <cmath>
#include <limits>
#include "maths/constants.hpp"

AABB::AABB() : min_point(FLOAT_MAX), max_point(FLOAT_MIN) {}

AABB::AABB(const Point& min_point, const Point& max_point) : min_point(min_point), max_point(max_point) {}

bool AABB::is_in_frustum(const Frustum& frustum) const {
    unsigned int planes[6] { 0, 0, 0, 0, 0, 0 };

    vec4 points[8] { frustum.view_projection * Point(min_point.x, min_point.y, min_point.z),
                     frustum.view_projection * Point(min_point.x, min_point.y, max_point.z),
                     frustum.view_projection * Point(min_point.x, max_point.y, min_point.z),
                     frustum.view_projection * Point(min_point.x, max_point.y, max_point.z),
                     frustum.view_projection * Point(max_point.x, min_point.y, min_point.z),
                     frustum.view_projection * Point(max_point.x, min_point.y, max_point.z),
                     frustum.view_projection * Point(max_point.x, max_point.y, min_point.z),
                     frustum.view_projection * Point(max_point.x, max_point.y, max_point.z) };

    for(const vec4& point : points) {
        if(point.x < -point.w) { ++planes[0]; }
        if(point.x > point.w) { ++planes[1]; }
        if(point.y < -point.w) { ++planes[2]; }
        if(point.y > point.w) { ++planes[3]; }
        if(point.z < -point.w) { ++planes[4]; }
        if(point.z > point.w) { ++planes[5]; }
    }

    for(unsigned int points_above_plane : planes) {
        if(points_above_plane == 8) { return false; }
    }

    return true;
}

float AABB::get_size() const {
    return length(max_point - min_point);
}

Point AABB::get_center() const {
    return min_point + 0.5f * (max_point - min_point);
}

mat4 AABB::get_global_model_matrix() const {
    Point center = get_center();

    return mat4(max_point.x - center.x,
                0.0f,
                0.0f,
                center.x,
                0.0f,
                max_point.y - center.y,
                0.0f,
                center.y,
                0.0f,
                0.0f,
                max_point.z - center.z,
                center.z,
                0.0f,
                0.0f,
                0.0f,
                1.0f);
}

void AABB::set(const Point& min, const Point& max) {
    min_point = min;
    max_point = max;
}

void AABB::set(const AABB& aabb, const Transform& transform) {
    const mat4& model = transform.get_global_model_const_reference();

    vec4 corners[8] { model * Point(aabb.min_point.x, aabb.min_point.y, aabb.min_point.z),
                      model * Point(aabb.min_point.x, aabb.min_point.y, aabb.max_point.z),
                      model * Point(aabb.min_point.x, aabb.max_point.y, aabb.min_point.z),
                      model * Point(aabb.min_point.x, aabb.max_point.y, aabb.max_point.z),
                      model * Point(aabb.max_point.x, aabb.min_point.y, aabb.min_point.z),
                      model * Point(aabb.max_point.x, aabb.min_point.y, aabb.max_point.z),
                      model * Point(aabb.max_point.x, aabb.max_point.y, aabb.min_point.z),
                      model * Point(aabb.max_point.x, aabb.max_point.y, aabb.max_point.z) };

    min_point.x = min_point.y = min_point.z = FLOAT_MAX;
    max_point.x = max_point.y = max_point.z = FLOAT_MIN;

    for(const vec4& point : corners) {
        axis_aligned_min(min_point, point);
        axis_aligned_max(max_point, point);
    }
}
