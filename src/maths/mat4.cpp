/***************************************************************************************************
 * @file  mat4.hpp
 * @brief Implementation of the mat4 struct
 **************************************************************************************************/

#include "maths/mat4.hpp"

mat4::mat4()
    : v {
          { 0.0, 0.0, 0.0, 0.0 },
          { 0.0, 0.0, 0.0, 0.0 },
          { 0.0, 0.0, 0.0, 0.0 },
          { 0.0, 0.0, 0.0, 0.0 }
} {}

mat4::mat4(float scalar)
    : v {
          { scalar, 0.0,    0.0,    0.0 },
          { 0.0,    scalar, 0.0,    0.0 },
          { 0.0,    0.0,    scalar, 0.0 },
          { 0.0,    0.0,    0.0,    1.0 }
} {}

mat4::mat4(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
    : v {
          { v00, v10, v20, 0.0 },
          { v01, v11, v21, 0.0 },
          { v02, v12, v22, 0.0 },
          { 0.0, 0.0, 0.0, 1.0 }
} {}

mat4::mat4(float v00,
           float v01,
           float v02,
           float v03,
           float v10,
           float v11,
           float v12,
           float v13,
           float v20,
           float v21,
           float v22,
           float v23)
    : v {
          { v00, v10, v20, 0.0 },
          { v01, v11, v21, 0.0 },
          { v02, v12, v22, 0.0 },
          { v03, v13, v23, 1.0 }
} {}

mat4::mat4(float v00,
           float v01,
           float v02,
           float v03,
           float v10,
           float v11,
           float v12,
           float v13,
           float v20,
           float v21,
           float v22,
           float v23,
           float v30,
           float v31,
           float v32,
           float v33)
    : v {
          { v00, v10, v20, v30 },
          { v01, v11, v21, v31 },
          { v02, v12, v22, v32 },
          { v03, v13, v23, v33 }
} {}

mat4::mat4(Vector column0, Vector column1, Vector column2)
    : v {
          { column0.x, column0.y, column0.z, 0.0 },
          { column1.x, column1.y, column1.z, 0.0 },
          { column2.x, column2.y, column2.z, 0.0 },
          { 0.0,       0.0,       0.0,       1.0 }
} {}

mat4::mat4(Vector column0, Vector column1, Vector column2, Vector column3)
    : v {
          { column0.x, column0.y, column0.z, 0.0 },
          { column1.x, column1.y, column1.z, 0.0 },
          { column2.x, column2.y, column2.z, 0.0 },
          { column3.x, column3.y, column3.z, 1.0 }
} {}

mat4::mat4(vec4 column0, vec4 column1, vec4 column2, vec4 column3)
    : v {
          { column0.x, column0.y, column0.z, column0.w },
          { column1.x, column1.y, column1.z, column1.w },
          { column2.x, column2.y, column2.z, column2.w },
          { column3.x, column3.y, column3.z, column3.w }
} {}

mat4::mat4(const mat3& mat)
    : v {
          { mat(0, 0), mat(1, 0), mat(2, 0), 0.0 },
          { mat(0, 1), mat(1, 1), mat(2, 1), 0.0 },
          { mat(0, 2), mat(1, 2), mat(2, 2), 0.0 },
          { 0.0, 0.0, 0.0, 1.0 }
} {}

float& mat4::operator()(unsigned int row, unsigned int col) {
    return v[col][row];
}

const float& mat4::operator()(unsigned int row, unsigned int col) const {
    return v[col][row];
}

Vector& mat4::operator[](unsigned int col) {
    return reinterpret_cast<Vector&>(v[col]);
}

const Vector& mat4::operator[](unsigned int col) const {
    return reinterpret_cast<const Vector&>(v[col]);
}

vec4& mat4::column(unsigned int col) {
    return reinterpret_cast<vec4&>(v[col]);
}

const vec4& mat4::column(unsigned int col) const {
    return reinterpret_cast<const vec4&>(v[col]);
}

std::ostream& mat4::print_memory_layout(std::ostream& stream) const {
    auto m = reinterpret_cast<const float*>(v);

    stream << "( " << m[0] << " ; " << m[1] << " ; " << m[2] << " ; " << m[3] << " )\n";
    stream << "( " << m[4] << " ; " << m[5] << " ; " << m[6] << " ; " << m[7] << " )\n";
    stream << "( " << m[8] << " ; " << m[9] << " ; " << m[10] << " ; " << m[11] << " )\n";
    stream << "( " << m[12] << " ; " << m[13] << " ; " << m[14] << " ; " << m[15] << " )\n";

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const mat4& mat) {
    stream << "( " << mat(0, 0) << " ; " << mat(0, 1) << " ; " << mat(0, 2) << " ; " << mat(0, 3) << " )\n";
    stream << "( " << mat(1, 0) << " ; " << mat(1, 1) << " ; " << mat(1, 2) << " ; " << mat(1, 3) << " )\n";
    stream << "( " << mat(2, 0) << " ; " << mat(2, 1) << " ; " << mat(2, 2) << " ; " << mat(2, 3) << " )\n";
    stream << "( " << mat(3, 0) << " ; " << mat(3, 1) << " ; " << mat(3, 2) << " ; " << mat(3, 3) << " )\n";

    return stream;
}

float determinant(const mat4& mat) {
    throw std::runtime_error("Unimplemented error\n");
}

float determinant_transform(const mat4& mat) {
    // Assumes the matrix is an affine transform, meaning its last row is ( 0 ; 0 ; 0 ; 1 )
    // This is equivalent to the determinant of the upper-left 3x3 matrix
    return dot(mat[0], cross(mat[1], mat[2]));
}

mat4 inverse(const mat4& mat) {
    throw std::runtime_error("Unimplemented error\n");
}

mat4 inverse_transform(const mat4& mat) {
    // Assumes the matrix is an affine transform, meaning its last row is ( 0 ; 0 ; 0 ; 1 )
    // Assumes the matrix has an inverse, if not it will result in a division by zero error

    const Vector& a = mat[0];
    const Vector& b = mat[1];
    const Vector& c = mat[2];
    const Vector& d = mat[3];

    Vector s = cross(a, b);
    Vector t = cross(c, d);
    float det_inv = 1.0f / dot(s, c);
    s *= det_inv;
    t *= det_inv;
    Vector v = c * det_inv;
    Vector row0 = cross(b, v);
    Vector row1 = cross(v, a);

    return mat4(row0.x, row0.y, row0.z, -dot(b, t), row1.x, row1.y, row1.z, dot(a, t), s.x, s.y, s.z, -dot(d, s));
}

mat4 transpose(const mat4& mat) {
    return mat4(mat(0, 0),
                mat(1, 0),
                mat(2, 0),
                mat(3, 0),
                mat(0, 1),
                mat(1, 1),
                mat(2, 1),
                mat(3, 1),
                mat(0, 2),
                mat(1, 2),
                mat(2, 2),
                mat(3, 2),
                mat(0, 3),
                mat(1, 3),
                mat(2, 3),
                mat(3, 3));
}

void operator+=(mat4& left, const mat4& right) {
    left(0, 0) += right(0, 0);
    left(1, 0) += right(1, 0);
    left(2, 0) += right(2, 0);
    left(3, 0) += right(3, 0);

    left(0, 1) += right(0, 1);
    left(1, 1) += right(1, 1);
    left(2, 1) += right(2, 1);
    left(3, 1) += right(3, 1);

    left(0, 2) += right(0, 2);
    left(1, 2) += right(1, 2);
    left(2, 2) += right(2, 2);
    left(3, 2) += right(3, 2);

    left(0, 3) += right(0, 3);
    left(1, 3) += right(1, 3);
    left(2, 3) += right(2, 3);
    left(3, 3) += right(3, 3);
}

void operator-=(mat4& left, const mat4& right) {
    left(0, 0) -= right(0, 0);
    left(1, 0) -= right(1, 0);
    left(2, 0) -= right(2, 0);
    left(3, 0) -= right(3, 0);

    left(0, 1) -= right(0, 1);
    left(1, 1) -= right(1, 1);
    left(2, 1) -= right(2, 1);
    left(3, 1) -= right(3, 1);

    left(0, 2) -= right(0, 2);
    left(1, 2) -= right(1, 2);
    left(2, 2) -= right(2, 2);
    left(3, 2) -= right(3, 2);

    left(0, 3) -= right(0, 3);
    left(1, 3) -= right(1, 3);
    left(2, 3) -= right(2, 3);
    left(3, 3) -= right(3, 3);
}

void operator*=(mat4& mat, float scalar) {
    mat(0, 0) *= scalar;
    mat(1, 0) *= scalar;
    mat(2, 0) *= scalar;
    mat(3, 0) *= scalar;

    mat(0, 1) *= scalar;
    mat(1, 1) *= scalar;
    mat(2, 1) *= scalar;
    mat(3, 1) *= scalar;

    mat(0, 2) *= scalar;
    mat(1, 2) *= scalar;
    mat(2, 2) *= scalar;
    mat(3, 2) *= scalar;

    mat(0, 3) *= scalar;
    mat(1, 3) *= scalar;
    mat(2, 3) *= scalar;
    mat(3, 3) *= scalar;
}

void operator/=(mat4& mat, float scalar) {
    float inv = 1.0 / scalar;

    mat(0, 0) *= inv;
    mat(1, 0) *= inv;
    mat(2, 0) *= inv;
    mat(3, 0) *= inv;

    mat(0, 1) *= inv;
    mat(1, 1) *= inv;
    mat(2, 1) *= inv;
    mat(3, 1) *= inv;

    mat(0, 2) *= inv;
    mat(1, 2) *= inv;
    mat(2, 2) *= inv;
    mat(3, 2) *= inv;

    mat(0, 3) *= inv;
    mat(1, 3) *= inv;
    mat(2, 3) *= inv;
    mat(3, 3) *= inv;
}

mat4 operator+(const mat4& left, const mat4& right) {
    return mat4(left(0, 0) + right(0, 0),
                left(0, 1) + right(0, 1),
                left(0, 2) + right(0, 2),
                left(0, 3) + right(0, 3),

                left(1, 0) + right(1, 0),
                left(1, 1) + right(1, 1),
                left(1, 2) + right(1, 2),
                left(1, 3) + right(1, 3),

                left(2, 0) + right(2, 0),
                left(2, 1) + right(2, 1),
                left(2, 2) + right(2, 2),
                left(2, 3) + right(2, 3),

                left(3, 0) + right(3, 0),
                left(3, 1) + right(3, 1),
                left(3, 2) + right(3, 2),
                left(3, 3) + right(3, 3));
}

mat4 operator-(const mat4& left, const mat4& right) {
    return mat4(left(0, 0) - right(0, 0),
                left(0, 1) - right(0, 1),
                left(0, 2) - right(0, 2),
                left(0, 3) - right(0, 3),

                left(1, 0) - right(1, 0),
                left(1, 1) - right(1, 1),
                left(1, 2) - right(1, 2),
                left(1, 3) - right(1, 3),

                left(2, 0) - right(2, 0),
                left(2, 1) - right(2, 1),
                left(2, 2) - right(2, 2),
                left(2, 3) - right(2, 3),

                left(3, 0) - right(3, 0),
                left(3, 1) - right(3, 1),
                left(3, 2) - right(3, 2),
                left(3, 3) - right(3, 3));
}

mat4 operator*(const mat4& left, const mat4& right) {
    return mat4(
        left(0, 0) * right(0, 0) + left(0, 1) * right(1, 0) + left(0, 2) * right(2, 0) + left(0, 3) * right(3, 0),
        left(0, 0) * right(0, 1) + left(0, 1) * right(1, 1) + left(0, 2) * right(2, 1) + left(0, 3) * right(3, 1),
        left(0, 0) * right(0, 2) + left(0, 1) * right(1, 2) + left(0, 2) * right(2, 2) + left(0, 3) * right(3, 2),
        left(0, 0) * right(0, 3) + left(0, 1) * right(1, 3) + left(0, 2) * right(2, 3) + left(0, 3) * right(3, 3),
        left(1, 0) * right(0, 0) + left(1, 1) * right(1, 0) + left(1, 2) * right(2, 0) + left(1, 3) * right(3, 0),
        left(1, 0) * right(0, 1) + left(1, 1) * right(1, 1) + left(1, 2) * right(2, 1) + left(1, 3) * right(3, 1),
        left(1, 0) * right(0, 2) + left(1, 1) * right(1, 2) + left(1, 2) * right(2, 2) + left(1, 3) * right(3, 2),
        left(1, 0) * right(0, 3) + left(1, 1) * right(1, 3) + left(1, 2) * right(2, 3) + left(1, 3) * right(3, 3),
        left(2, 0) * right(0, 0) + left(2, 1) * right(1, 0) + left(2, 2) * right(2, 0) + left(2, 3) * right(3, 0),
        left(2, 0) * right(0, 1) + left(2, 1) * right(1, 1) + left(2, 2) * right(2, 1) + left(2, 3) * right(3, 1),
        left(2, 0) * right(0, 2) + left(2, 1) * right(1, 2) + left(2, 2) * right(2, 2) + left(2, 3) * right(3, 2),
        left(2, 0) * right(0, 3) + left(2, 1) * right(1, 3) + left(2, 2) * right(2, 3) + left(2, 3) * right(3, 3),
        left(3, 0) * right(0, 0) + left(3, 1) * right(1, 0) + left(3, 2) * right(2, 0) + left(3, 3) * right(3, 0),
        left(3, 0) * right(0, 1) + left(3, 1) * right(1, 1) + left(3, 2) * right(2, 1) + left(3, 3) * right(3, 1),
        left(3, 0) * right(0, 2) + left(3, 1) * right(1, 2) + left(3, 2) * right(2, 2) + left(3, 3) * right(3, 2),
        left(3, 0) * right(0, 3) + left(3, 1) * right(1, 3) + left(3, 2) * right(2, 3) + left(3, 3) * right(3, 3));
}

mat4 operator*(float scalar, const mat4& mat) {
    return mat4(scalar * mat(0, 0),
                scalar * mat(0, 1),
                scalar * mat(0, 2),
                scalar * mat(0, 3),

                scalar * mat(1, 0),
                scalar * mat(1, 1),
                scalar * mat(1, 2),
                scalar * mat(1, 3),

                scalar * mat(2, 0),
                scalar * mat(2, 1),
                scalar * mat(2, 2),
                scalar * mat(2, 3),

                scalar * mat(3, 0),
                scalar * mat(3, 1),
                scalar * mat(3, 2),
                scalar * mat(3, 3));
}

vec4 operator*(const mat4& mat, const Point& point) {
    return vec4(mat(0, 0) * point.x + mat(0, 1) * point.y + mat(0, 2) * point.z + mat(0, 3),
                mat(1, 0) * point.x + mat(1, 1) * point.y + mat(1, 2) * point.z + mat(1, 3),
                mat(2, 0) * point.x + mat(2, 1) * point.y + mat(2, 2) * point.z + mat(2, 3),
                mat(3, 0) * point.x + mat(3, 1) * point.y + mat(3, 2) * point.z + mat(3, 3));
}

Vector operator*(const mat4& mat, const Vector& vec) {
    return Vector(mat(0, 0) * vec.x + mat(0, 1) * vec.y + mat(0, 2) * vec.z,
                  mat(1, 0) * vec.x + mat(1, 1) * vec.y + mat(1, 2) * vec.z,
                  mat(2, 0) * vec.x + mat(2, 1) * vec.y + mat(2, 2) * vec.z);
}
