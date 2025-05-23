/***************************************************************************************************
 * @file  transforms.cpp
 * @brief Implementation of the Image class
 **************************************************************************************************/

#include "maths/transforms.hpp"

#include <cmath>
#include "maths/geometry.hpp"
#include "maths/trigonometry.hpp"

mat4 scale(float factor) {
    return mat4(
        factor, 0.0f, 0.0f,
        0.0f, factor, 0.0f,
        0.0f, 0.0f, factor
    );
}

mat4 scale(float x, float y, float z) {
    return mat4(
        x, 0.0f, 0.0f,
        0.0f, y, 0.0f,
        0.0f, 0.0f, z
    );
}

mat4 scale(const vec3& factors) {
    return mat4(
        factors.x, 0.0f, 0.0f,
        0.0f, factors.y, 0.0f,
        0.0f, 0.0f, factors.z
    );
}

mat4 scaleX(float factor) {
    return mat4(
        factor, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}

mat4 scaleY(float factor) {
    return mat4(
        1.0f, 0.0f, 0.0f,
        0.0f, factor, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}

mat4 scaleZ(float factor) {
    return mat4(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, factor
    );
}

mat4 translate(const vec3& vector) {
    return mat4(1.0f, 0.0f, 0.0f, vector.x,
                0.0f, 1.0f, 0.0f, vector.y,
                0.0f, 0.0f, 1.0f, vector.z,
                0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 translate(float x, float y, float z) {
    return mat4(1.0f, 0.0f, 0.0f, x,
                0.0f, 1.0f, 0.0f, y,
                0.0f, 0.0f, 1.0f, z,
                0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 translateX(float scalar) {
    return mat4(1.0f, 0.0f, 0.0f, scalar,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 translateY(float scalar) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, scalar,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 translateZ(float scalar) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, scalar,
                0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 rotate(float angle, vec3 axis) {
    angle = radians(angle);
    float cosine = cosf(angle);
    float sine = sinf(angle);

    if(float len = length(axis) ; len != 0.0f) { axis /= len; }
    vec3 temp = (1.0f - cosine) * axis;

    return mat4(
        axis.x * temp.x + cosine, axis.x * temp.y - axis.z * sine, axis.x * temp.z + axis.y * sine,
        axis.y * temp.x + axis.z * sine, axis.y * temp.y + cosine, axis.y * temp.z - axis.x * sine,
        axis.z * temp.x - axis.y * sine, axis.z * temp.y + axis.x * sine, axis.z * temp.z + cosine
    );
}

mat4 rotateX(float angle) {
    angle = radians(angle);

    const float cosine = cosf(angle);
    const float sine = sinf(angle);

    return mat4(
        1.0f, 0.0f, 0.0f,
        0.0f, cosine, -sine,
        0.0f, sine, cosine
    );
}

mat4 rotateY(float angle) {
    angle = radians(angle);

    const float cosine = cosf(angle);
    const float sine = sinf(angle);

    return mat4(
        cosine, 0.0f, sine,
        0.0f, 1.0f, 0.0f,
        -sine, 0.0f, cosine
    );
}

mat4 rotateZ(float angle) {
    angle = radians(angle);

    const float cosine = cosf(angle);
    const float sine = sinf(angle);

    return mat4(
        cosine, -sine, 0.0f,
        sine, cosine, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}

mat4 lookAt(const vec3& eye, const vec3& target, const vec3& up) {
    const vec3 FRONT = normalize(eye - target); // vec3 from the target to the camera
    const vec3 RIGHT = normalize(cross(up, FRONT));
    const vec3 UP = cross(FRONT, RIGHT);

    return mat4(
        RIGHT.x, RIGHT.y, RIGHT.z, -dot(eye, RIGHT),
        UP.x, UP.y, UP.z, -dot(eye, UP),
        FRONT.x, FRONT.y, FRONT.z, -dot(eye, FRONT),
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 perspective(float fov, float aspect, float near, float far) {
    return mat4(
        1.0f / (aspect * tanf(0.5f * fov)), 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f / tanf(0.5f * fov), 0.0f, 0.0f,
        0.0f, 0.0f, -(far + near) / (far - near), -(2.0f * far * near) / (far - near),
        0.0f, 0.0f, -1.0f, 0.0f
    );
}
