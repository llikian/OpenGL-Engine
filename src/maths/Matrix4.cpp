/***************************************************************************************************
 * @file  Matrix4.cpp
 * @brief Implementation of the Matrix4 struct
 **************************************************************************************************/

#include "maths/Matrix4.hpp"

Matrix4::Matrix4()
    : values{{0.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 0.0f}} { }

Matrix4::Matrix4(float v00, float v01, float v02, float v03,
                 float v10, float v11, float v12, float v13,
                 float v20, float v21, float v22, float v23,
                 float v30, float v31, float v32, float v33)
    : values{{v00, v01, v02, v03},
             {v10, v11, v12, v13},
             {v20, v21, v22, v23},
             {v30, v31, v32, v33}} { }

Matrix4::Matrix4(float v00, float v01, float v02,
                 float v10, float v11, float v12,
                 float v20, float v21, float v22)
    : values{{v00,  v01,  v02,  0.0f},
             {v10,  v11,  v12,  0.0f},
             {v20,  v21,  v22,  0.0f},
             {0.0f, 0.0f, 0.0f, 1.0f}} { }

Matrix4::Matrix4(float scalar)
    : values{{scalar, 0.0f, 0.0f, 0.0f},
             {0.0f, scalar, 0.0f, 0.0f},
             {0.0f, 0.0f, scalar, 0.0f},
             {0.0f, 0.0f, 0.0f, scalar}} { }

float* Matrix4::operator [](int row) {
    return values[row];
}

const float* Matrix4::operator [](int row) const {
    return values[row];
}

Matrix4& Matrix4::operator +=(const Matrix4& mat) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] += mat[i][j];
        }
    }
    
    return *this;
}

Matrix4& Matrix4::operator -=(const Matrix4& mat) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] -= mat[i][j];
        }
    }

    return *this;
}

Matrix4& Matrix4::operator *=(const Matrix4& mat) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] *= mat[i][j];
        }
    }

    return *this;
}

Matrix4& Matrix4::operator /=(const Matrix4& mat) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] /= mat[i][j];
        }
    }

    return *this;
}

Matrix4& Matrix4::operator +=(float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] += scalar;
        }
    }

    return *this;
}

Matrix4& Matrix4::operator -=(float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] -= scalar;
        }
    }

    return *this;
}

Matrix4& Matrix4::operator *=(float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] *= scalar;
        }
    }

    return *this;
}

Matrix4& Matrix4::operator /=(float scalar) {
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            values[i][j] /= scalar;
        }
    }

    return *this;
}

std::ostream& operator <<(std::ostream& stream, const Matrix4& mat) {
    for(int i = 0 ; i < 4 ; ++i) {
        stream << "( ";

        for(int j = 0 ; j < 3 ; ++j) {
            stream << ' ' << mat[i][j] << " ; ";
        }

        stream << mat[i][3] << " )\n";
    } 
    return stream;
}

Matrix4 operator +(const Matrix4& left, const Matrix4& right) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = left[i][j] + right[i][j];
        }
    }

    return result;
}

Matrix4 operator -(const Matrix4& left, const Matrix4& right) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = left[i][j] - right[i][j];
        }
    }

    return result;
}

Matrix4 operator *(const Matrix4& left, const Matrix4& right) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = left[i][j] * right[i][j];
        }
    }

    return result;
}

Matrix4 operator /(const Matrix4& left, const Matrix4& right) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = left[i][j] / right[i][j];
        }
    }

    return result;
}

Matrix4 operator +(const Matrix4& mat, float scalar) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = mat[i][j] + scalar;
        }
    }

    return result;
}

Matrix4 operator -(const Matrix4& mat, float scalar) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = mat[i][j] - scalar;
        }
    }

    return result;
}

Matrix4 operator *(const Matrix4& mat, float scalar) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = mat[i][j] * scalar;
        }
    }

    return result;
}

Matrix4 operator *(float scalar, const Matrix4& mat) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = scalar * mat[i][j];
        }
    }

    return result;
}

Matrix4 operator /(const Matrix4& mat, float scalar) {
    Matrix4 result;

    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            result[i][j] = mat[i][j] / scalar;
        }
    }

    return result;
}
