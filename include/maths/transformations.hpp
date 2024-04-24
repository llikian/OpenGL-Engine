/***************************************************************************************************
 * @file  transformations.hpp
 * @brief Declaration of functions for 3D transformations
 **************************************************************************************************/

#include <glm/gtc/matrix_transform.hpp>
#include "Matrix4.hpp"
#include "vec4.hpp"
#include "vec3.hpp"

/**
 * @brief Calculates the scaling matrix that scales by the same factor in all 3 directions.
 * @param scalar The scaling factor.
 * @return The scaling matrix.
 */
Matrix4 scale(float scalar);

/**
 * @brief Calculates the scaling matrix that scales by a specific factor in each direction.
 * @param x The scaling factor in the x direction.
 * @param y The scaling factor in the y direction.
 * @param z The scaling factor in the z direction.
 * @return The scaling matrix.
 */
Matrix4 scale(float x, float y, float z);

/**
 * @brief Calculates the scaling matrix that only scales in the x direction.
 * @param scalar The scaling factor.
 * @return The scaling matrix.
 */
Matrix4 scaleX(float scalar);

/**
 * @brief Calculates the scaling matrix that only scales in the y direction.
 * @param scalar The scaling factor.
 * @return The scaling matrix.
 */
Matrix4 scaleY(float scalar);

/**
 * @brief Calculates the scaling matrix that only scales in the z direction.
 * @param scalar The scaling factor.
 * @return The scaling matrix.
 */
Matrix4 scaleZ(float scalar);

/**
 * @brief Calculates the translation matrix that displaces by a specific vector.
 * @param vector The translation vector.
 * @return The translation matrix.
 */
Matrix4 translate(const Vector& vector);

/**
 * @brief Calculates the translation matrix that displaces by a specific amount in each direction.
 * @param x The displacement in the x direction.
 * @param y The displacement in the y direction.
 * @param z The displacement in the z direction.
 * @return The translation matrix.
 */
Matrix4 translate(float x, float y, float z);

/**
 * @brief Calculates the translation matrix that only displaces in the x direction.
 * @param scalar The displacement amount.
 * @return The translation matrix.
 */
Matrix4 translateX(float scalar);

/**
 * @brief Calculates the translation matrix that only displaces in the y direction.
 * @param scalar The displacement amount.
 * @return The translation matrix.
 */
Matrix4 translateY(float scalar);

/**
 * @brief Calculates the translation matrix that only displaces in the z direction.
 * @param scalar The displacement amount.
 * @return The translation matrix.
 */
Matrix4 translateZ(float scalar);

/**
 * @brief Calculates the rotation matrix that rotates around an axis by a certain angle.
 * @param angle The rotation angle.
 * @param axis The rotation axis.
 * @return The rotation matrix.
 */
Matrix4 rotate(float angle, const Vector& axis);

/**
 * @brief Calculates the rotation matrix that rotates around the X axis by a certain angle.
 * @param angle The rotation angle.
 * @return The rotation matrix.
 */
Matrix4 rotateX(float angle);

/**
 * @brief Calculates the rotation matrix that rotates around the Y axis by a certain angle.
 * @param angle The rotation angle.
 * @return The rotation matrix.
 */
Matrix4 rotateY(float angle);

/**
 * @brief Calculates the rotation matrix that rotates around the Z axis by a certain angle.
 * @param angle The rotation angle.
 * @return The rotation matrix.
 */
Matrix4 rotateZ(float angle);