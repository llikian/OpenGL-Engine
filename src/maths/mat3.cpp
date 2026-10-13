/***************************************************************************************************
 * @file  mat3.hpp
 * @brief Implementation of the mat3 struct
 **************************************************************************************************/

#include "maths/mat3.hpp"

#include "maths/mat4.hpp"

mat3::mat3()
    : v {
          { 0.0f, 0.0f, 0.0f },
          { 0.0f, 0.0f, 0.0f },
          { 0.0f, 0.0f, 0.0f }
} {}

mat3::mat3(float scalar)
    : v {
          { scalar, 0.0f,   0.0f   },
          { 0.0f,   scalar, 0.0f   },
          { 0.0f,   0.0f,   scalar }
} {}

mat3::mat3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
    : v {
          { v00, v10, v20 },
          { v01, v11, v21 },
          { v02, v12, v22 }
} {}

mat3::mat3(Vector column0, Vector column1, Vector column2)
    : v {
          { column0.x, column0.y, column0.z },
          { column1.x, column1.y, column1.z },
          { column2.x, column2.y, column2.z },
} {}

mat3::mat3(const mat4& mat)
    : v {
          { mat(0, 0), mat(1, 0), mat(2, 0) },
          { mat(0, 1), mat(1, 1), mat(2, 1) },
          { mat(0, 2), mat(1, 2), mat(2, 2) },
} {}

float& mat3::operator()(unsigned int row, unsigned int column) {
    return v[column][row];
}

const float& mat3::operator()(unsigned int row, unsigned int column) const {
    return v[column][row];
}

Vector& mat3::operator[](unsigned int column) {
    return reinterpret_cast<Vector&>(v[column]);
}

const Vector& mat3::operator[](unsigned int column) const {
    return reinterpret_cast<const Vector&>(v[column]);
}

std::ostream& mat3::print_memory_layout(std::ostream& stream) const {
    auto m = reinterpret_cast<const float*>(v);

    stream << "( " << m[0] << " ; " << m[1] << " ; " << m[2] << " )\n";
    stream << "( " << m[3] << " ; " << m[4] << " ; " << m[5] << " )\n";
    stream << "( " << m[6] << " ; " << m[7] << " ; " << m[8] << " )\n";

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const mat3& mat) {
    stream << "( " << mat(0, 0) << " ; " << mat(0, 1) << " ; " << mat(0, 2) << " )\n";
    stream << "( " << mat(1, 0) << " ; " << mat(1, 1) << " ; " << mat(1, 2) << " )\n";
    stream << "( " << mat(2, 0) << " ; " << mat(2, 1) << " ; " << mat(2, 2) << " )\n";

    return stream;
}

float determinant(const mat3& mat) {
    // This is equivalent to the scalar triple product of the 3 columns of the matrix
    return dot(mat[0], cross(mat[1], mat[2]));
}

mat3 inverse(const mat3& mat) {
    // This function assumes that the inverse exists and will result in a division by zero error if it isn't

    const Vector& a = mat[0];
    const Vector& b = mat[1];
    const Vector& c = mat[2];

    float det_inv = 1.0 / determinant(mat);

    Vector row0 = det_inv * cross(b, c);
    Vector row1 = det_inv * cross(c, a);
    Vector row2 = det_inv * cross(a, b);

    return mat3(row0.x, row0.y, row0.z, row1.x, row1.y, row1.z, row2.x, row2.y, row2.z);
}

void operator+=(mat3& left, const mat3& right) {
    left(0, 0) += right(0, 0);
    left(1, 0) += right(1, 0);
    left(2, 0) += right(2, 0);

    left(0, 1) += right(0, 1);
    left(1, 1) += right(1, 1);
    left(2, 1) += right(2, 1);

    left(0, 2) += right(0, 2);
    left(1, 2) += right(1, 2);
    left(2, 2) += right(2, 2);
}

void operator-=(mat3& left, const mat3& right) {
    left(0, 0) -= right(0, 0);
    left(1, 0) -= right(1, 0);
    left(2, 0) -= right(2, 0);

    left(0, 1) -= right(0, 1);
    left(1, 1) -= right(1, 1);
    left(2, 1) -= right(2, 1);

    left(0, 2) -= right(0, 2);
    left(1, 2) -= right(1, 2);
    left(2, 2) -= right(2, 2);
}

void operator*=(mat3& mat, float scalar) {
    mat(0, 0) *= scalar;
    mat(1, 0) *= scalar;
    mat(2, 0) *= scalar;

    mat(0, 1) *= scalar;
    mat(1, 1) *= scalar;
    mat(2, 1) *= scalar;

    mat(0, 2) *= scalar;
    mat(1, 2) *= scalar;
    mat(2, 2) *= scalar;
}

void operator/=(mat3& mat, float scalar) {
    float inv = 1.0 / scalar;

    mat(0, 0) *= inv;
    mat(1, 0) *= inv;
    mat(2, 0) *= inv;

    mat(0, 1) *= inv;
    mat(1, 1) *= inv;
    mat(2, 1) *= inv;

    mat(0, 2) *= inv;
    mat(1, 2) *= inv;
    mat(2, 2) *= inv;
}

mat3 operator+(const mat3& left, const mat3& right) {
    return mat3(left(0, 0) + right(0, 0),
                left(0, 1) + right(0, 1),
                left(0, 2) + right(0, 2),

                left(1, 0) + right(1, 0),
                left(1, 1) + right(1, 1),
                left(1, 2) + right(1, 2),

                left(2, 0) + right(2, 0),
                left(2, 1) + right(2, 1),
                left(2, 2) + right(2, 2));
}

mat3 operator-(const mat3& left, const mat3& right) {
    return mat3(left(0, 0) + right(0, 0),
                left(0, 1) + right(0, 1),
                left(0, 2) + right(0, 2),

                left(1, 0) + right(1, 0),
                left(1, 1) + right(1, 1),
                left(1, 2) + right(1, 2),

                left(2, 0) + right(2, 0),
                left(2, 1) + right(2, 1),
                left(2, 2) + right(2, 2));
}

mat3 operator*(const mat3& left, const mat3& right) {
    return mat3(left(0, 0) * right(0, 0) + left(0, 1) * right(1, 0) + left(0, 2) * right(2, 0),
                left(0, 0) * right(0, 1) + left(0, 1) * right(1, 1) + left(0, 2) * right(2, 1),
                left(0, 0) * right(0, 2) + left(0, 1) * right(1, 2) + left(0, 2) * right(2, 2),

                left(1, 0) * right(0, 0) + left(1, 1) * right(1, 0) + left(1, 2) * right(2, 0),
                left(1, 0) * right(0, 1) + left(1, 1) * right(1, 1) + left(1, 2) * right(2, 1),
                left(1, 0) * right(0, 2) + left(1, 1) * right(1, 2) + left(1, 2) * right(2, 2),

                left(2, 0) * right(0, 0) + left(2, 1) * right(1, 0) + left(2, 2) * right(2, 0),
                left(2, 0) * right(0, 1) + left(2, 1) * right(1, 1) + left(2, 2) * right(2, 1),
                left(2, 0) * right(0, 2) + left(2, 1) * right(1, 2) + left(2, 2) * right(2, 2));
}

mat3 operator*(float scalar, const mat3& mat) {
    return mat3(scalar * mat(0, 0),
                scalar * mat(0, 1),
                scalar * mat(0, 2),

                scalar * mat(1, 0),
                scalar * mat(1, 1),
                scalar * mat(1, 2),

                scalar * mat(2, 0),
                scalar * mat(2, 1),
                scalar * mat(2, 2));
}

Vector operator*(const mat3& mat, const Vector& vec) {
    return Vector(mat(0, 0) * vec.x + mat(0, 1) * vec.y + mat(0, 2) * vec.z,
                  mat(1, 0) * vec.x + mat(1, 1) * vec.y + mat(1, 2) * vec.z,
                  mat(2, 0) * vec.x + mat(2, 1) * vec.y + mat(2, 2) * vec.z);
}
