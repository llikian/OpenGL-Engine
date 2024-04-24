/***************************************************************************************************
 * @file  Image.cpp
 * @brief Implementation of the Image class
 **************************************************************************************************/

#include "maths/transformations.hpp"

Matrix4 scale(float scalar) {
    return Matrix4(
        scalar, 0.0f, 0.0f, 0.0f,
        0.0f, scalar, 0.0f, 0.0f,
        0.0f, 0.0f, scalar, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4 scale(float x, float y, float z) {
    return Matrix4(
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4 translate(const Vector& vector) {
    return Matrix4(
        1.0f, 0.0f, 0.0f, vector.x,
        0.0f, 1.0f, 0.0f, vector.y,
        0.0f, 0.0f, 1.0f, vector.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4 translate(float x, float y, float z) {
    return Matrix4(
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4 rotate(float angle, const Vector& axis) {

    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vector nAxis = axis;
    if(nAxis != Vector(0.0f, 0.0f, 0.0f)) {
        nAxis = normalize(axis);
    }

    Vector temp = (1.0f - cosine) * nAxis;

    return Matrix4(
        cosine + temp[0] * nAxis[0],
        temp[0] * nAxis[1] + sine * nAxis[2],
        temp[0] * nAxis[2] - sine * nAxis[1],
        0.0f,

        temp[1] * nAxis[0] - sine * nAxis[2],
        cosine + temp[1] * nAxis[1],
        temp[1] * nAxis[2] + sine * nAxis[0],
        0.0f,

        temp[2] * nAxis[0] + sine * nAxis[1],
        temp[2] * nAxis[1] - sine * nAxis[0],
        cosine + temp[2] * nAxis[2],
        0.0f,

        0.0f,
        0.0f,
        0.0f,
        1.0f
    );
}

Matrix4 rotateX(float angle) {
    const float cosine = glm::cos(angle);
    const float sine = glm::sin(angle);

    return Matrix4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosine, -sine, 0.0f,
        0.0f, sine, cosine, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4 rotateY(float angle) {
    const float cosine = glm::cos(angle);
    const float sine = glm::sin(angle);

    return Matrix4(
        cosine, 0.0f, sine, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sine, 0.0f, cosine, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4 rotateZ(float angle) {
    const float cosine = glm::cos(angle);
    const float sine = glm::sin(angle);

    return Matrix4(
        cosine, -sine, 0.0f, 0.0f,
        sine, cosine, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
