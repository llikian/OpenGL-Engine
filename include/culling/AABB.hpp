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

    template <typename T1, typename T2>
    static void axis_aligned_min(T1& A, const T2& B) {
        A.x = std::min(A.x, B.x);
        A.y = std::min(A.y, B.y);
        A.z = std::min(A.z, B.z);
    }

    template <typename T1, typename T2>
    static void axis_aligned_max(T1& A, const T2& B) {
        A.x = std::max(A.x, B.x);
        A.y = std::max(A.y, B.y);
        A.z = std::max(A.z, B.z);
    }

    void set(const Point& min, const Point& max);
    void set(const AABB& aabb, const Transform& transform);

    Point min_point;
    Point max_point;
};
