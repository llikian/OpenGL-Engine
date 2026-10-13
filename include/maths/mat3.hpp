/***************************************************************************************************
 * @file  mat3.hpp
 * @brief Declaration of the mat3 struct
 **************************************************************************************************/

#pragma once

#include "Vector.hpp"

struct mat4; // Forward-Definition of mat4

/**
 * @struct mat3
 * @brief Represents a 3x3 matrix of floating point numbers.
 *
 * In memory, values are stored in a column-major order but to respect the convention of indexing
 * matrix elements first by their row then by their column, all function parameters behave as if the
 * matrix was in row-major order, for example, matrix elements are accessed using the parenthesis
 * operator like so: M(i, j) which accesses the element in column j and row i. The constructor that
 * takes all 9 values of the matrix also expects the values to be given row by row and not column
 * by column. The output function (using operator << and std::ostream) also transposes the values
 * again since the matrix the output needs to be row by row.
 */
struct mat3 {
public:
    mat3();
    explicit mat3(float scalar);
    mat3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22);
    mat3(Vector column0, Vector column1, Vector column2);
    explicit mat3(const mat4& mat);

    float& operator()(unsigned int row, unsigned int column);
    const float& operator()(unsigned int row, unsigned int column) const;

    Vector& operator[](unsigned int column);
    const Vector& operator[](unsigned int column) const;

    std::ostream& print_memory_layout(std::ostream& stream) const;

private:
    float v[3][3]; ///< The values of the mat3.
};

std::ostream& operator<<(std::ostream& stream, const mat3& mat);

float determinant(const mat3& mat);

mat3 inverse(const mat3& mat);

void operator+=(mat3& left, const mat3& right);
void operator-=(mat3& left, const mat3& right);

void operator*=(mat3& mat, float scalar);
void operator/=(mat3& mat, float scalar);

mat3 operator+(const mat3& left, const mat3& right);
mat3 operator-(const mat3& left, const mat3& right);

mat3 operator*(const mat3& left, const mat3& right);
mat3 operator*(float scalar, const mat3& mat);

Vector operator*(const mat3& mat, const Vector& vec);
