#ifndef VECTOR4_H
#define VECTOR4_H

#include<string>
#include<cmath>
#include<vector3.h>

template <typename T>
class Vector4 {
    public:
        T x, y, z, w;
        Vector4();
        Vector4(T data);
        Vector4(T x, T y, T z, T w);
        Vector4(T data[4]);
        Vector4(Vector3<T> vector3, T w);
        Vector4(T x, Vector3<T> vector3);
        // Operator overload
        Vector4<T> operator+(const T &other) const;
        Vector4<T> operator+(const Vector4<T> &other) const;
        void operator+=(const T &other);
        void operator+=(const Vector4<T> &other);
        Vector4<T> operator-() const;
        Vector4<T> operator-(const T &other) const;
        Vector4<T> operator-(const Vector4<T> &other) const;
        void operator-=(const T &other);
        void operator-=(const Vector4<T> &other);
        Vector4<T> operator*(const T &other) const;
        Vector4<T> operator*(const Vector4<T> &other) const;
        void operator*=(const T &other);
        void operator*=(const Vector4<T> &other);
        // Dot product
        T dot(const Vector4<T> &other) const;
        // Length
        T length() const;
        // Normalized
        Vector4<T> &normalized();
        // Zero
        void zero();
        // Print
        void print() const;
};

// ===== Constructor
template <typename T>
Vector4<T>::Vector4(): x(0), y(0), z(0) {};

template <typename T>
Vector4<T>::Vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {};

template <typename T>
Vector4<T>::Vector4(T data[4]): x(data[0]), y(data[1]), z(data[2]), w(data[3]) {};

template <typename T>
Vector4<T>::Vector4(Vector3<T> vector3, T w): x(vector3.x), y(vector3.y), z(vector3.z), w(w) {};

template <typename T>
Vector4<T>::Vector4(T x, Vector3<T> vector3): x(x), y(vector3.x), z(vector3.y), w(vector3.z) {};

// ===== Operator overload
// +
template <typename T>
Vector4<T> Vector4<T>::operator+(const T &other) const {
    return Vector4<T>(x + other, y + other, z + other, w + other);
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T> &other) const {
    return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

// +=
template <typename T>
void Vector4<T>::operator+=(const T &other) {
    x += other;
    y += other;
    z += other;
    w += other;
}

template <typename T>
void Vector4<T>::operator+=(const Vector4<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}

// -
template <typename T>
Vector4<T> Vector4<T>::operator-() const {
    return Vector4<T>(-x, -y, -z, -w);
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const T &other) const {
    return Vector4<T>(x - other, y - other, z - other, w - other);
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T> &other) const {
    return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
}

// -=
template <typename T>
void Vector4<T>::operator-=(const T &other) {
   x -= other;
   y -= other;
   z -= other;
   w -= other;
}

template <typename T>
void Vector4<T>::operator-=(const Vector4<T> &other) {
   x -= other.x;
   y -= other.y;
   z -= other.z;
   w -= other.w;
}

// *
template <typename T>
Vector4<T> Vector4<T>::operator*(const T &other) const {
    return Vector4<T>(x * other, y * other, z * other, w * other);
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const Vector4<T> &other) const {
    return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
}

// *=
template <typename T>
void Vector4<T>::operator*=(const T &other) {
   x *= other;
   y *= other;
   z *= other;
   w *= other;
}

template <typename T>
void Vector4<T>::operator*=(const Vector4<T> &other) {
   x *= other.x;
   y *= other.y;
   z *= other.z;
   w *= other.w;
}

// ===== Method
// Dot product
template <typename T>
T Vector4<T>::dot(const Vector4<T> &other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

// Length
template <typename T>
T Vector4<T>::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// Normalized
template <typename T>
Vector4<T>& Vector4<T>::normalized() {
    T len = length();
    T factor = 1.0f / len;
    x *= factor;
    y *= factor;
    z *= factor;
    w *= factor;

    return *this;
}

// Zero
template <typename T>
void Vector4<T>::zero() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

// Print
template <typename T>
void Vector4<T>::print() const{
    std::string str;
    if(std::is_same<T,float>::value){
        str = "Vecf:(%f, %f, %f, %f)\n";
        
    }
    else if(std::is_same<T,int>::value) {
        str = "Veci:(%d, %d, %d, %d)\n";    
    }
    printf(str.c_str(), x, y, z, w);
}

typedef Vector4<float> Vector4f; 
typedef Vector4<int> Vector4i;

#endif

