/***************************************************************************************************
 * @file  mat4.hpp
 * @brief Declaration of the mat4 struct
 **************************************************************************************************/

#pragma once

#include <ostream>

/**
 * @struct mat4
 * @brief Represents a 4 by 4 matrix.
 */
struct mat4 {
    /**
     * @brief Constructs a mat4 with all components equal to 0.
     */
    mat4();

    /**
     * @brief Constructs a mat4 with a specific value for each component.
     * @param v00, v01, v02, v03 The values of the components of the first row.
     * @param v10, v11, v12, v13 The values of the components of the second row.
     * @param v20, v21, v22, v23 The values of the components of the third row.
     * @param v30, v31, v32, v33 The values of the components of the fourth row.
     */
    mat4(float v00, float v01, float v02, float v03,
         float v10, float v11, float v12, float v13,
         float v20, float v21, float v22, float v23,
         float v30, float v31, float v32, float v33);

    /**
     * @brief Constructs a mat4 with a specific value for each component of the 3 first columns
     * and rows. The fourth column and row are the same as the identity matrix.
     * @param v00, v01, v02 The values of the first three components of the first row.
     * @param v10, v11, v12 The values of the first three components of the second row.
     * @param v20, v21, v22 The values of the first three components of the third row.
     */
    mat4(float v00, float v01, float v02,
         float v10, float v11, float v12,
         float v20, float v21, float v22);

    /**
     * @brief Constructs a mat4 which is the identity matrix multiplied by a scalar.
     * Each value of the diagonal is equal to the scalar and the rest is zeros.
     * @param scalar The value for the components on the diagonal.
     */
    mat4(float scalar);

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
     * @brief Adds another mat4's components to the current instance's components.
     * @param mat The mat4 to add.
     * @return A reference to this instance.
     */
    mat4& operator +=(const mat4& mat);

    /**
     * @brief Subtracts the current instance's components by another mat4's components.
     * @param mat The mat4 to subtract by.
     * @return A reference to this instance.
     */
    mat4& operator -=(const mat4& mat);

    /**
     * @brief Multiplies the current instance's components by another mat4's components.
     * @param mat The mat4 to multiply by.
     * @return A reference to this instance.
     */
    mat4& operator *=(const mat4& mat);

    /**
     * @brief Divides the current instance's components by another mat4's components.
     * @param mat The mat4 to divide by.
     * @return A reference to this instance.
     */
    mat4& operator /=(const mat4& mat);

    /**
     * @brief Adds a scalar to all of the current instance's components.
     * @param scalar The scalar to add.
     * @return A reference to this instance.
     */
    mat4& operator +=(float scalar);

    /**
     * @brief Subtracts all of the current instance's components by a scalar.
     * @param scalar The scalar to subtract by.
     * @return A reference to this instance.
     */
    mat4& operator -=(float scalar);

    /**
     * @brief Multiplies all of the current instance's components by a scalar.
     * @param scalar The scalar to multiply by.
     * @return A reference to this instance.
     */
    mat4& operator *=(float scalar);

    /**
     * @brief Divides all of the current instance's components by a scalar.
     * @param scalar The scalar to divide by.
     * @return A reference to this instance.
     */
    mat4& operator /=(float scalar);

    float values[4][4]; ///< The values of the matrix.
};

/**
 * @brief Writes the components of the given mat4 to the output stream in the format:\n
 * "( v00 ; v01 ; v02 ; v03 )\\n"\n
 * "( v10 ; v11 ; v12 ; v13 )\\n"\n
 * "( v20 ; v21 ; v22 ; v23 )\\n"\n
 * "( v30 ; v31 ; v32 ; v33 )\\n"\n
 * @param stream The output stream to write to.
 * @param Matrix The mat4 to write to the stream.
 * @return A reference to the output stream after writing the mat4.
 */
std::ostream& operator <<(std::ostream& stream, const mat4& mat);

/** @brief Adds a mat4's components to another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise sum of the two mat4.
 */
mat4 operator +(const mat4& left, const mat4& right);

/** @brief Subtracts a mat4's components by another's.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The component-wise subtraction of the first mat4 by the second.
 */
mat4 operator -(const mat4& left, const mat4& right);

/** @brief Multiplies a mat4 by another.
 *  @param left The left operand.
 *  @param right The right operand.
 *  @return The product of the two mat4.
 */
mat4 operator *(const mat4& left, const mat4& right);

/** @brief Adds a scalar to each of a mat4's components.
 *  @param Matrix The mat4.
 *  @param scalar The scalar.
 *  @return The component-wise sum of a mat4 by a scalar.
 */
mat4 operator +(const mat4& mat, float scalar);

/** @brief Subtracts each of a mat4's components by a scalar.
 *  @param Matrix The mat4.
 *  @param scalar The scalar.
 *  @return The component-wise subtraction of a mat4 by a scalar.
 */
mat4 operator -(const mat4& mat, float scalar);

/** @brief Multiplies each of a mat4's components by a scalar.
 *  @param Matrix The mat4.
 *  @param scalar The scalar.
 *  @return The component-wise product of a mat4 by a scalar.
 */
mat4 operator *(const mat4& mat, float scalar);

/** @brief Multiplies each of a mat4's components by a scalar.
 *  @param scalar The scalar.
 *  @param Matrix The mat4.
 *  @return The component-wise product of a mat4 by a scalar.
 */
mat4 operator *(float scalar, const mat4& mat);

/** @brief Divides each of a mat4's components by a scalar.
 *  @param Matrix The mat4.
 *  @param scalar The scalar.
 *  @return The component-wise division of a mat4 by a scalar.
 */
mat4 operator /(const mat4& mat, float scalar);