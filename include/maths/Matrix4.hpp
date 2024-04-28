/***************************************************************************************************
 * @file  Matrix4.hpp
 * @brief Declaration of the Matrix4 struct
 **************************************************************************************************/

#pragma once

#include <ostream>

/**
 * @struct Matrix4
 * @brief Represents a 4 by 4 matrix.
 */
struct Matrix4 {
    /**
     * @brief Constructs a Matrix4 with all components equal to 0.
     */
    Matrix4();

    /**
     * @brief Constructs a Matrix4 with a specific value for each component.
     * @param v00, v01, v02, v03 The values of the components of the first row.
     * @param v10, v11, v12, v13 The values of the components of the second row.
     * @param v20, v21, v22, v23 The values of the components of the third row.
     * @param v30, v31, v32, v33 The values of the components of the fourth row.
     */
    Matrix4(float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23,
            float v30, float v31, float v32, float v33);

    /**
     * @brief Constructs a Matrix4 with a specific value for each component of the 3 first columns
     * and rows. The fourth column and row are the same as the identity matrix.
     * @param v00, v01, v02 The values of the first three components of the first row.
     * @param v10, v11, v12 The values of the first three components of the second row.
     * @param v20, v21, v22 The values of the first three components of the third row.
     */
    Matrix4(float v00, float v01, float v02,
            float v10, float v11, float v12,
            float v20, float v21, float v22);

    /**
     * @brief Constructs a Matrix4 which is the identity matrix multiplied by a scalar.
     * Each value of the diagonal is equal to the scalar and the rest is zeros.
     * @param scalar The value for the components on the diagonal.
     */
    Matrix4(float scalar);

    /**
     * @brief Accesses a row in the underlying 2D array of values.
     * @param row The row's index.
     * @return The row with the given index.
     */
    float* operator [](int row);

    /**
     * @brief Accesses a row in the underlying 2D array of values.
     * @param row The row's index.
     * @return The row with the given index.
     */
    const float* operator [](int row) const;

    /**
     * @brief Adds another Matrix4's components to the current instance's components.
     * @param mat The Matrix4 to add.
     * @return A reference to this instance.
     */
    Matrix4& operator +=(const Matrix4& mat);

    /**
     * @brief Subtracts the current instance's components by another Matrix4's components.
     * @param mat The Matrix4 to subtract by.
     * @return A reference to this instance.
     */
    Matrix4& operator -=(const Matrix4& mat);

    /**
     * @brief Multiplies the current instance's components by another Matrix4's components.
     * @param mat The Matrix4 to multiply by.
     * @return A reference to this instance.
     */
    Matrix4& operator *=(const Matrix4& mat);

    /**
     * @brief Divides the current instance's components by another Matrix4's components.
     * @param mat The Matrix4 to divide by.
     * @return A reference to this instance.
     */
    Matrix4& operator /=(const Matrix4& mat);

    /**
     * @brief Adds a scalar to all of the current instance's components.
     * @param scalar The scalar to add.
     * @return A reference to this instance.
     */
    Matrix4& operator +=(float scalar);

    /**
     * @brief Subtracts all of the current instance's components by a scalar.
     * @param scalar The scalar to subtract by.
     * @return A reference to this instance.
     */
    Matrix4& operator -=(float scalar);

    /**
     * @brief Multiplies all of the current instance's components by a scalar.
     * @param scalar The scalar to multiply by.
     * @return A reference to this instance.
     */
    Matrix4& operator *=(float scalar);

    /**
     * @brief Divides all of the current instance's components by a scalar.
     * @param scalar The scalar to divide by.
     * @return A reference to this instance.
     */
    Matrix4& operator /=(float scalar);

    float values[4][4]; ///< The values of the matrix.
};

/**
 * @brief Writes the components of the given Matrix4 to the output stream in the format:\n
 * "( v00 ; v01 ; v02 ; v03 )\\n"\n
 * "( v10 ; v11 ; v12 ; v13 )\\n"\n
 * "( v20 ; v21 ; v22 ; v23 )\\n"\n
 * "( v30 ; v31 ; v32 ; v33 )\\n"\n
 * @param stream The output stream to write to.
 * @param Matrix The Matrix4 to write to the stream.
 * @return A reference to the output stream after writing the Matrix4.
 */
std::ostream& operator <<(std::ostream& stream, const Matrix4& mat);

/** @brief Adds a Matrix4's components to another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise sum of the two Matrix4.
 */
Matrix4 operator+(const Matrix4& left, const Matrix4& right);

/** @brief Subtracts a Matrix4's components by another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise subtraction of the first Matrix4 by the second.
 */
Matrix4 operator-(const Matrix4& left, const Matrix4& right);

/** @brief Multiplies a Matrix4's components by another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise product of the two Matrix4.
 */
Matrix4 operator*(const Matrix4& left, const Matrix4& right);

/** @brief Divides a Matrix4's components by another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise division of the first Matrix4 by the second.
 */
Matrix4 operator/(const Matrix4& left, const Matrix4& right);

/** @brief Adds a scalar to each of a Matrix4's components.
 *  @param Matrix The Matrix4.
 *  @param scalar The scalar.
 *  @return The component-wise sum of a Matrix4 by a scalar.
 */
Matrix4 operator+(const Matrix4& mat, float scalar);

/** @brief Subtracts each of a Matrix4's components by a scalar.
 *  @param Matrix The Matrix4.
 *  @param scalar The scalar.
 *  @return The component-wise subtraction of a Matrix4 by a scalar.
 */
Matrix4 operator-(const Matrix4& mat, float scalar);

/** @brief Multiplies each of a Matrix4's components by a scalar.
 *  @param Matrix The Matrix4.
 *  @param scalar The scalar.
 *  @return The component-wise product of a Matrix4 by a scalar.
 */
Matrix4 operator*(const Matrix4& mat, float scalar);

/** @brief Multiplies each of a Matrix4's components by a scalar.
 *  @param scalar The scalar.
 *  @param Matrix The Matrix4.
 *  @return The component-wise product of a Matrix4 by a scalar.
 */
Matrix4 operator*(float scalar, const Matrix4& mat);

/** @brief Divides each of a Matrix4's components by a scalar.
 *  @param Matrix The Matrix4.
 *  @param scalar The scalar.
 *  @return The component-wise division of a Matrix4 by a scalar.
 */
Matrix4 operator/(const Matrix4& mat, float scalar);
