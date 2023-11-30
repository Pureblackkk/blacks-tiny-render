#ifndef MATRIX4_H
#define MATRIX4_H

#include<string>
#include<vector3.h>
#include<vector4.h>
// TODO: just for debugging
#include<iostream>
struct TransformParameters {
    TransformParameters(): scale(Vector3f(1., 1., 1.)) {};
    Vector3f translation;
    Vector3f rotation;
    Vector3f scale;
};

template <typename T>
class Matrix4 {
    public:
        Matrix4();
        Matrix4(T data);
        Matrix4(T data[4][4]);
        Matrix4(Vector3<T> row1, Vector3<T> row2, Vector3<T> row3, Vector3<T> row4);
        Matrix4(Vector4<T> row1, Vector4<T> row2, Vector4<T> row3, Vector4<T> row4);
        // Operator overload
        Matrix4<T> operator*(const Matrix4<T> &other) const;
        Vector4<T> operator*(const Vector4<T> &other) const;
        Matrix4<T> operator*(const T &other) const;
        // Transpose
        Matrix4<T> transpose() const;
        // TODO: inverse
        // Set
        void set(int row, int col, T value);
        // Print
        T get(int row, int col) const;
        // Generate scale matrix
        Matrix4<T> static scaleMatrix(T scaleX, T scaleY, T scaleZ);
        // Generate roate matrix
        Matrix4<float> static rotateMatrix(float alpha, float beta, float gamma);
        // Generate translate matrix
        Matrix4<T> static translateMatrix(T dx, T dy, T dz);
        // Generate transform matrix
        Matrix4<float> static transformMatrix(TransformParameters &transform);
        // Generate camera look at matrix
        Matrix4<float> static lookAt(const Vector3f &eye, const Vector3f &target, const Vector3f &up);
        // Generate orthogonal projection matrix
        Matrix4<float> static orthoProject(float left, float right, float bottom, float top, float near, float far);
        // TODO: Generate perspective projection matrix
        Matrix4<float> static perspectiveProject(float fov, float aspect, float near, float far);
        // Devices viewport matrix
        Matrix4<float> static deviceViewPort(float width, float height);
        void print() const;
    private:
        T matrix[4][4];
};

// ===== Constructor
template <typename T>
Matrix4<T>::Matrix4() {
    for(int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
        }
    }
}

template <typename T>
Matrix4<T>::Matrix4(T data) {
    for(int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = data;
        }
    }
}

template <typename T>
Matrix4<T>::Matrix4(T data[4][4]) {
    for(int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = data[i][j];
        }
    }
}
template <typename T>
Matrix4<T>::Matrix4(Vector3<T> row1, Vector3<T> row2, Vector3<T> row3, Vector3<T> row4) {
    matrix[0][0] = row1.x;
    matrix[0][1] = row1.y;
    matrix[0][2] = row1.z;
    matrix[0][3] = 0;

    matrix[1][0] = row2.x;
    matrix[1][1] = row2.y;
    matrix[1][2] = row2.z;
    matrix[1][3] = 0;

    matrix[2][0] = row3.x;
    matrix[2][1] = row3.y;
    matrix[2][2] = row3.z;
    matrix[2][3] = 0;

    matrix[3][0] = row4.x;
    matrix[3][1] = row4.y;
    matrix[3][2] = row4.z;
    matrix[3][3] = 0;
}

template <typename T>
Matrix4<T>::Matrix4(Vector4<T> row1, Vector4<T> row2, Vector4<T> row3, Vector4<T> row4) {
    matrix[0][0] = row1.x;
    matrix[0][1] = row1.y;
    matrix[0][2] = row1.z;
    matrix[0][3] = row1.w;

    matrix[1][0] = row2.x;
    matrix[1][1] = row2.y;
    matrix[1][2] = row2.z;
    matrix[1][3] = row2.w;

    matrix[2][0] = row3.x;
    matrix[2][1] = row3.y;
    matrix[2][2] = row3.z;
    matrix[2][3] = row3.w;

    matrix[3][0] = row4.x;
    matrix[3][1] = row4.y;
    matrix[3][2] = row4.z;
    matrix[3][3] = row4.w;
}

// ===== Operator overload
// *
template <typename T>
Matrix4<T> Matrix4<T>::operator*(const Matrix4<T> &other) const {
    T results[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            T sum = 0;
            for (int k = 0; k < 4; ++k) {
                sum += matrix[i][k] * other.get(k, j);
            }
            results[i][j] = sum;
        } 
    }
    return Matrix4<T>(results);
}

template <typename T>
Vector4<T> Matrix4<T>::operator*(const Vector4<T> &other) const {
    T data[4];
    for (int i = 0; i < 4; ++i) {
        T sum = 0;
        sum += matrix[i][0] * other.x;
        sum += matrix[i][1] * other.y;
        sum += matrix[i][2] * other.z;
        sum += matrix[i][3] * other.w;
        data[i] = sum;
    }
    return Vector4<T>(data);
}

template <typename T>
Matrix4<T> Matrix4<T>::operator*(const T &other) const {
    Matrix4<T> results;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; j++) {
            results.set(i, j, matrix[i][j] * other);
        }
    }
    return results;
}

// ===== Methods
// Transpose
template <typename T>
Matrix4<T> Matrix4<T>::transpose() const {
    Matrix4<T> transposedMatrix;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            transposedMatrix.set(i, j, matrix[j][i]);
        }
    }
    return transposedMatrix;
}

// Get matrix value
template <typename T>
T Matrix4<T>::get(int row, int col) const {
    return matrix[row][col];
}

// Set matrix value
template <typename T>
void Matrix4<T>::set(int row, int col, T value) {
    matrix[row][col] = value;
}

// Print matrix for debug
template <typename T>
void Matrix4<T>::print() const {
    if(std::is_same<T,float>::value) {
        printf("Matrix4f\n");
    } else if(std::is_same<T,int>::value) {
        printf("Matrix4i\n");
    }

    for (int i = 0; i < 4; ++i) {
        std::string str;
        if(std::is_same<T,float>::value) {
            str = "(%f, %f, %f, %f)\n";
        } else if(std::is_same<T,int>::value) {
            str = "(%d, %d, %d, %d)\n";    
        }
        printf(str.c_str(), matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
    }
}

// ===== Static Methods
// Generate scale matrix
template <typename T>
Matrix4<T> Matrix4<T>::scaleMatrix(T scaleX, T scaleY, T scaleZ) {
    Matrix4<T> result;
    result.set(0, 0, scaleX);
    result.set(1, 1, scaleY);
    result.set(2, 2, scaleZ);
    return result;
}

// Generate rotation matrix in the order of Z-Y-X
template <typename T>
Matrix4<float> Matrix4<T>::rotateMatrix(float alpha, float beta, float gamma) {
    float ca = std::cos(alpha);
    float sa = std::sin(alpha);

    float cb = std::cos(beta);
    float sb = std::sin(beta);

    float cg = std::cos(gamma);
    float sg = std::sin(gamma);

    Matrix4<float> rotationMatrix;

    // Row1
    rotationMatrix.set(0, 0, ca * cb);
    rotationMatrix.set(0, 1, -sa * cg + ca * sb * sg);
    rotationMatrix.set(0, 2, sa * sg + ca * sb * cg);

    // Row2
    rotationMatrix.set(1, 0, sa * cb);
    rotationMatrix.set(1, 1, ca * cg + sa * sb * sg);
    rotationMatrix.set(1, 2, -ca * sg + sa * sb * cg);

    // Row3
    rotationMatrix.set(2, 0, -sb);
    rotationMatrix.set(2, 1, cb * sg);
    rotationMatrix.set(2, 2, cb * cg);

    return rotationMatrix;
}

// Generate translate matrix
template <typename T>
Matrix4<T> Matrix4<T>::translateMatrix(T dx, T dy, T dz) {
    Matrix4<T> translateMatrix;
    translateMatrix.set(0, 3, dx);
    translateMatrix.set(1, 3, dy);
    translateMatrix.set(2, 3, dz);

    return translateMatrix;
}

// Generate transform matrix
template <typename T>
Matrix4<float> Matrix4<T>::transformMatrix(TransformParameters &transform) {
    Matrix4<float> translation = Matrix4<float>::translateMatrix(
        transform.translation.x,
        transform.translation.y,
        transform.translation.z
    );

    Matrix4<float> rotation = Matrix4<float>::rotateMatrix(
        transform.rotation.x,
        transform.rotation.y,
        transform.rotation.z
    );

    Matrix4<float> scale = Matrix4<float>::scaleMatrix(
        transform.scale.x,
        transform.scale.y,
        transform.scale.z
    );

    return translation * rotation * scale;
}

// Generate transform matrix
template <typename T>
Matrix4<float> Matrix4<T>::lookAt(const Vector3f &eye, const Vector3f &target, const Vector3f &up) {
    Vector3f direction = (eye - target).normalized();
    Vector3f side = (up.cross(direction)).normalized();
    Vector3f head = (direction.cross(side)).normalized();
    Vector3f t = -eye;

    Matrix4<float> lookAtMatrix;
    // Row1
    lookAtMatrix.set(0, 0, side.x);
    lookAtMatrix.set(0, 1, side.y);
    lookAtMatrix.set(0, 2, side.z);
    lookAtMatrix.set(0, 3, side.dot(t));

    // Row2
    lookAtMatrix.set(1, 0, head.x);
    lookAtMatrix.set(1, 1, head.y);
    lookAtMatrix.set(1, 2, head.z);
    lookAtMatrix.set(1, 3, head.dot(t));

    // Row3
    lookAtMatrix.set(2, 0, direction.x);
    lookAtMatrix.set(2, 1, direction.y);
    lookAtMatrix.set(2, 2, direction.z);
    lookAtMatrix.set(2, 3, direction.dot(t));
    
    return lookAtMatrix;
}

// Generate orthogonal projection matrix
template <typename T>
Matrix4<float> Matrix4<T>::orthoProject(float left, float right, float bottom, float top, float near, float far) {
    float lr = 1 / (right - left);
    float br = 1 / (top - bottom);
    float nr = 1 / (far - near);

    Matrix4<float> orthoProject;

    // Row1
    orthoProject.set(0, 0, 2 * lr);
    orthoProject.set(0, 3, -(right + left) * lr);
    
    // Row2
    orthoProject.set(1, 1, 2 * br);
    orthoProject.set(1, 3, -(top + bottom) * br);

    // Row3
    orthoProject.set(2, 2, -2 * nr);
    orthoProject.set(2, 3, -(near + far) * nr);

    return orthoProject;
}

// Generate perspective projection
template <typename T>
Matrix4<float> Matrix4<T>::perspectiveProject(float fov, float aspect, float near, float far) {
    float fovPI = M_PI * fov / 180;

    Matrix4<float> compressMatrix;
    compressMatrix.set(0, 0, near);
    compressMatrix.set(1, 1, near);
    compressMatrix.set(2, 2, near + far);
    compressMatrix.set(2, 3, near * far);
    compressMatrix.set(3, 2, -1.0);
    compressMatrix.set(3, 3, 0.0);

    float halfHeight = near * std::tan(fovPI / 2);
    float halfWidth = halfHeight * aspect;
    Matrix4<float> orthoProject = Matrix4<float>::orthoProject(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);

    return orthoProject * compressMatrix;
}

// Devices viewport matrix
template<typename T>
Matrix4<float> Matrix4<T>::deviceViewPort(float width, float height) {
    Matrix4<float> viewPortMatrix;
    viewPortMatrix.set(0, 0, width / 2);
    viewPortMatrix.set(0, 3, width / 2);
    viewPortMatrix.set(1, 1, height / 2);
    viewPortMatrix.set(1, 3, height / 2);
    return viewPortMatrix;
}

typedef Matrix4<int> Matrix4i;
typedef Matrix4<float> Matrix4f;
#endif