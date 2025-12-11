/***************************************************************************************************
 * @file  Ray.cpp
 * @brief Implementation of the Ray class
 **************************************************************************************************/

#include "culling/Ray.hpp"

float Ray::intersect_aabb(const AABB& aabb) {
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
