/***************************************************************************************************
 * @file  mat4.hpp
 * @brief Declaration of the mat4 struct
 **************************************************************************************************/

#pragma once

#include "mat3.hpp"
#include "vec4.hpp"

/**
 * @struct mat4
 * @brief Represents a 4x4 matrix of floating point numbers.
 *
 * In memory, values are stored in a column-major order but to respect the convention of indexing
 * matrix elements first by their row then by their column, all function parameters behave as if the
 * matrix was in row-major order, for example, matrix elements are accessed using the parenthesis
 * operator like so: M(i, j) which accesses the element in column j and row i. The constructor that
 * takes all 16 values of the matrix also expects the values to be given row by row and not column
 * by column. The output function (using operator << and std::ostream) also transposes the values
 * again since the matrix the output needs to be row by row.
 */
struct mat4 {
public:
    mat4();
    explicit mat4(float scalar);
    mat4(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22);

    mat4(float v00,
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
         float v23);

    mat4(float v00,
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
         float v33);

    mat4(Vector column0, Vector column1, Vector column2);
    mat4(Vector column0, Vector column1, Vector column2, Vector column3);
    mat4(vec4 column0, vec4 column1, vec4 column2, vec4 column3);
    explicit mat4(const mat3& mat);

    float& operator()(unsigned int row, unsigned int col);
    const float& operator()(unsigned int row, unsigned int col) const;

    Vector& operator[](unsigned int col);
    const Vector& operator[](unsigned int col) const;

    vec4& column(unsigned int col);
    const vec4& column(unsigned int col) const;

    std::ostream& print_memory_layout(std::ostream& stream) const;

private:
    float v[4][4]; ///< The values of the mat4.
};

std::ostream& operator<<(std::ostream& stream, const mat4& mat);

float determinant(const mat4& mat);
float determinant_transform(const mat4& mat);

mat4 inverse(const mat4& mat);
mat4 inverse_transform(const mat4& mat);

mat4 transpose(const mat4& mat);

void operator+=(mat4& left, const mat4& right);
void operator-=(mat4& left, const mat4& right);

void operator*=(mat4& mat, float scalar);
void operator/=(mat4& mat, float scalar);

mat4 operator+(const mat4& left, const mat4& right);
mat4 operator-(const mat4& left, const mat4& right);
mat4 operator*(const mat4& left, const mat4& right);

mat4 operator*(float scalar, const mat4& mat);

vec4 operator*(const mat4& mat, const Point& point);

Vector operator*(const mat4& mat, const Vector& vec);
