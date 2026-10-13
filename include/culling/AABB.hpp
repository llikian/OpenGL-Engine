/***************************************************************************************************
 * @file  AABB.hpp
 * @brief Declaration of the AABB struct
 **************************************************************************************************/

#pragma once

#include "maths/Transform.hpp"
#include "Frustum.hpp"

struct AABB {
    AABB();
    AABB(const Point& min_point, const Point& max_point);

    bool is_in_frustum(const Frustum& frustum) const;
    float get_size() const;
    Point get_center() const;
    mat4 get_global_model_matrix() const;

    void set(const Point& min, const Point& max);
    void set(const AABB& aabb, const Transform& transform);

    Point min_point;
    Point max_point;
};
