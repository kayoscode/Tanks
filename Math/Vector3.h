#ifndef INCLUDE_VECTOR3_H
#define INCLUDE_VECTOR3_H

#include <cmath>
#include "Vector2.h"

template <typename T = float>
struct Vector3 {
    //assignment constructors
    Vector3(T x) :x(x), y(x), z(x) {
    }

    Vector3(T x = 0, T y = 0, T z = 0) :x(x), y(y), z(z) {
    }

    Vector3(const Vector2<T>& other, T z = 0) :x(other.x), y(other.y), z(z) {
    }

    //copy constructor
    Vector3(const Vector3<T>& other) :x(other.x), y(other.y), z(other.z) {
    }

    //implicit casts
    operator std::string() const {
        std::stringstream builder;
        builder << "X: " << x << " |Y: " << y << " |Z: " << z;
        return builder.str();
    }

    //equals operator
    Vector3<T>& operator =(const Vector3<T>& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    //addition operators
    Vector3<T> operator +(const Vector3<T>& other) const {
        return Vector3<T>(x + other.x, y + other.y, z + other.z);
    }
    Vector3<T>& operator +=(const Vector3<T>& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vector3<T> operator -(const Vector3<T>& other) const {
        return Vector3<T>(x - other.x, y - other.y, z - other.z);
    }
    Vector3<T>& operator -=(const Vector3<T>& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    //scaling
    Vector3<T> operator *(const T& scale) const {
        return Vector3<T>(x * scale, y * scale, z * scale);
    }

    Vector3<T>& operator *=(const T& scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    //dot product
    T operator *(const Vector3<T>& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    //cross product
    Vector3<T> operator %(const Vector3<T>& other) const {
        return Vector3<T>(
            other.y * z - other.z * y, 
            other.z * x - other.x * z, 
            other.x * y - other.y * x
        );

                //public static Vector3 operator %(Vector3 right, Vector3 left)
                                //left.y * right.z - left.z * right.y,
								//right.x * left.z - right.z * left.x,
								//left.x* right.y - left.y * right.x);
    }

    //normalize
    Vector3<T>& normalize() {
        T mag = magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
        return *this;
    }
    Vector3<T> retNormalized() {
        T mag = magnitude();
        return Vector3<T>(x / mag, y / mag, z / mag);
    }

    //magnitude
    T magnitude() const {
        return (T)sqrtl(x * x + y * y + z * z);
    }

    T magnitudeSquared() const {
        return x * x + y * y + z * z;
    }

    //negate
    Vector3<T> negate() {
        return Vector3<T>(x * -1, y * -1, z * -1);
    }

    //3d swizzle
    Vector3<T> xzy() const { return Vector3<T>(x, z, y); }
    Vector3<T> yxz() const { return Vector3<T>(y, x, z); }
    Vector3<T> yzx() const { return Vector3<T>(y, z, x); }
    Vector3<T> zxy() const { return Vector3<T>(z, x, y); }
    Vector3<T> zyx() const { return Vector3<T>(z, y, x); }
    //2d swizzle
    Vector2<T> xy() const { return Vector2<T>(x, y); }
    Vector2<T> xz() const { return Vector2<T>(x, z); }
    Vector2<T> yx() const { return Vector2<T>(y, x); }
    Vector2<T> yz() const { return Vector2<T>(y, z); }
    Vector2<T> zx() const { return Vector2<T>(z, x); }
    Vector2<T> zy() const { return Vector2<T>(z, y); }

    T x, y, z;
};

typedef Vector3<> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;


#endif