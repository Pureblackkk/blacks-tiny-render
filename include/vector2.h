#ifndef VECTOR2_H
#define VECTOR2_H

#include<string>
#include<cmath>

template <typename T>
class Vector2 {
    public:
        T x, y;
        Vector2();
        Vector2(T data);
        Vector2(T x, T y);
        Vector2(T data[2]);
        // Operator overload
        Vector2<T> operator+(const T &other) const;
        Vector2<T> operator+(const Vector2<T> &other) const;
        void operator+=(const T &other);
        void operator+=(const Vector2<T> &other);
        Vector2<T> operator-() const;
        Vector2<T> operator-(const T &other) const;
        Vector2<T> operator-(const Vector2<T> &other) const;
        void operator-=(const T &other);
        void operator-=(const Vector2<T> &other);
        Vector2<T> operator*(const T &other) const;
        Vector2<T> operator*(const Vector2<T> &other) const;
        void operator*=(const T &other);
        void operator*=(const Vector2<T> &other);
        Vector2<T> operator/(const T &other) const;
        Vector2<T> operator/(const Vector2<T> &other) const;
        // Dot product
        T dot(const Vector2<T> &other) const;
        // Cross product
        T cross(const Vector2<T> &other) const;
        // Length
        T length() const;
        // Normalized
        Vector2<T> &normalized();
        // Zero
        void zero();
        // Print
        void print() const;
};

// ===== Constructor
template <typename T>
Vector2<T>::Vector2(): x(0), y(0) {};

template <typename T>
Vector2<T>::Vector2(T x, T y): x(x), y(y) {};

template <typename T>
Vector2<T>::Vector2(T data[2]): x(data[0]), y(data[1]) {};

// ===== Operator overload
// +
template <typename T>
Vector2<T> Vector2<T>::operator+(const T &other) const {
    return Vector2<T>(x + other, y + other);
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &other) const {
    return Vector2<T>(x + other.x, y + other.y);
}

// +=
template <typename T>
void Vector2<T>::operator+=(const T &other) {
    x += other;
    y += other;
}

template <typename T>
void Vector2<T>::operator+=(const Vector2<T> &other) {
    x += other.x;
    y += other.y;
}

// -
template <typename T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2<T>(-x, -y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const T &other) const {
    return Vector2<T>(x - other, y - other);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> &other) const {
    return Vector2<T>(x - other.x, y - other.y);
}

// -=
template <typename T>
void Vector2<T>::operator-=(const T &other) {
   x -= other;
   y -= other;
}

template <typename T>
void Vector2<T>::operator-=(const Vector2<T> &other) {
   x -= other.x;
   y -= other.y;
}

// *
template <typename T>
Vector2<T> Vector2<T>::operator*(const T &other) const {
    return Vector2<T>(x * other, y * other);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T> &other) const {
    return Vector2<T>(x * other.x, y * other.y);
}

// *=
template <typename T>
void Vector2<T>::operator*=(const T &other) {
   x *= other;
   y *= other;
}

template <typename T>
void Vector2<T>::operator*=(const Vector2<T> &other) {
   x *= other.x;
   y *= other.y;
}

// /
template <typename T>
Vector2<T> Vector2<T>::operator/(const T &other) const {
    return Vector2<T>(x / other, y / other);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T> &other) const {
    return Vector2<T>(x / other.x, y / other.y);
}

// ===== Methods
// Dot product
template <typename T>
T Vector2<T>::dot(const Vector2<T> &other) const {
    return x * other.x + y * other.y;
}

// Cross product
template <typename T>
T Vector2<T>::cross(const Vector2<T> &other) const {
    return x * other.y - y * other.x;
}

// Length
template <typename T>
T Vector2<T>::length() const {
    return std::sqrt(x * x + y * y);
}

// Normalized
template <typename T>
Vector2<T>& Vector2<T>::normalized() {
    T len = length();
    T factor = 1.0f / len;
    x *= factor;
    y *= factor;

    return *this;
}

// Zero
template <typename T>
void Vector2<T>::zero() {
    x = 0;
    y = 0;
}

// Print
template <typename T>
void Vector2<T>::print() const{
    std::string str;
    if(std::is_same<T,float>::value){
        str = "Vecf:(%f, %f)\n";
        
    }
    else if(std::is_same<T,int>::value) {
        str = "Veci:(%d, %d)\n";    
    }
    printf(str.c_str(), x, y);
}

typedef Vector2<float> Vector2f; 
typedef Vector2<int> Vector2i;

#endif

