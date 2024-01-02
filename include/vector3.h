#ifndef VECTOR3_H
#define VECTOR3_H

#include<string>
#include<cmath>
#include<vector2.h>

template <typename T>
class Vector3 {
    public:
        T x, y, z;
        Vector3();
        Vector3(T data);
        Vector3(T x, T y, T z);
        Vector3(T data[3]);
        Vector3(const Vector2<T> vector2, T z);
        Vector3(T x, const Vector2<T> vector2);
        // Operator overload
        Vector3<T> operator+(const T &other) const;
        Vector3<T> operator+(const Vector3<T> &other) const;
        void operator+=(const T &other);
        void operator+=(const Vector3<T> &other);
        Vector3<T> operator-() const;
        Vector3<T> operator-(const T &other) const;
        Vector3<T> operator-(const Vector3<T> &other) const;
        void operator-=(const T &other);
        void operator-=(const Vector3<T> &other);
        Vector3<T> operator*(const T &other) const;
        Vector3<T> operator*(const Vector3<T> &other) const;
        void operator*=(const T &other);
        void operator*=(const Vector3<T> &other);
        Vector3<T> operator/(const T &other) const;
        Vector3<T> operator/(const Vector3<T> &other) const;
        void operator/=(const T &other);
        void operator/=(const Vector3<T> &other);
        // Dot product
        T dot(const Vector3<T> &other) const;
        // Cross product
        Vector3<T> cross(const Vector3<T> &other) const;
        // Length
        T length() const;
        // Normalized
        Vector3<T> &normalized();
        // Zero
        void zero();
        // Print
        void print() const;
};

// ===== Constructor
template <typename T>
Vector3<T>::Vector3(): x(0), y(0), z(0) {};

template <typename T>
Vector3<T>::Vector3(T data): x(data), y(data), z(data) {};

template <typename T>
Vector3<T>::Vector3(T x, T y, T z): x(x), y(y), z(z) {};

template <typename T>
Vector3<T>::Vector3(T data[3]): x(data[0]), y(data[1]), z(data[2]) {};

template <typename T>
Vector3<T>::Vector3(const Vector2<T> vector2, T z): x(vector2.x), y(vector2.y), z(z) {};

template <typename T>
Vector3<T>::Vector3(T x, const Vector2<T> vector2): x(x), y(vector2.x), z(vector2.y) {};

// ===== Operator overload
// +
template <typename T>
Vector3<T> Vector3<T>::operator+(const T &other) const {
    return Vector3<T>(x + other, y + other, z + other);
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T> &other) const {
    return Vector3<T>(x + other.x, y + other.y, z + other.z);
}

// +=
template <typename T>
void Vector3<T>::operator+=(const T &other) {
    x += other;
    y += other;
    z += other;
}

template <typename T>
void Vector3<T>::operator+=(const Vector3<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

// -
template <typename T>
Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const T &other) const {
    return Vector3<T>(x - other, y - other, z - other);
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T> &other) const {
    return Vector3<T>(x - other.x, y - other.y, z - other.z);
}

// -=
template <typename T>
void Vector3<T>::operator-=(const T &other) {
   x -= other;
   y -= other;
   z -= other;
}

template <typename T>
void Vector3<T>::operator-=(const Vector3<T> &other) {
   x -= other.x;
   y -= other.y;
   z -= other.z;
}

// *
template <typename T>
Vector3<T> Vector3<T>::operator*(const T &other) const {
    return Vector3<T>(x * other, y * other, z * other);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T> &other) const {
    return Vector3<T>(x * other.x, y * other.y, z * other.z);
}

// *=
template <typename T>
void Vector3<T>::operator*=(const T &other) {
   x *= other;
   y *= other;
   z *= other;
}

template <typename T>
void Vector3<T>::operator*=(const Vector3<T> &other) {
   x *= other.x;
   y *= other.y;
   z *= other.z;
}

// /
template <typename T>
Vector3<T> Vector3<T>::operator/(const T &other) const {
    return Vector3<T>(x / other, y / other, z / other);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T> &other) const {
    return Vector3<T>(x / other.x, y / other.y, z / other.z);
}

// /=
template <typename T>
void Vector3<T>::operator/=(const T &other) {
    x /= other;
    y /= other;
    z /= other;
}

template <typename T>
void Vector3<T>::operator/=(const Vector3<T> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
}

// ===== Methods
// Dot product
template <typename T>
T Vector3<T>::dot(const Vector3<T> &other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Cross product
template <typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T> &other) const {
    return Vector3<T>(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// Length
template <typename T>
T Vector3<T>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalized
template <typename T>
Vector3<T>& Vector3<T>::normalized() {
    T len = length();
    T factor = 1.0f / len;
    x *= factor;
    y *= factor;
    z *= factor;

    return *this;
}

// Zero
template <typename T>
void Vector3<T>::zero() {
    x = 0;
    y = 0;
    z = 0;
}

// Print
template <typename T>
void Vector3<T>::print() const{
    std::string str;
    if(std::is_same<T,float>::value){
        str = "Vecf:(%f, %f, %f)\n";
        
    }
    else if(std::is_same<T,int>::value) {
        str = "Veci:(%d, %d, %d)\n";    
    }
    printf(str.c_str(),x,y,z);
}

typedef Vector3<float> Vector3f; 
typedef Vector3<int> Vector3i;

#endif

