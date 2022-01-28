#ifndef INCLUDE_VECTOR4_H
#define INCLUDE_VECTOR4_H

#include <cmath>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix44.h"

template <typename T = float>
struct Vector4 {
    //assignment constructors

    Vector4(T x = 0, T y = 0, T z = 0, T w = 0) :x(x), y(y), z(z), w(w) {
    }

    Vector4(const Vector2<T>& other, T z = 0, T w = 0) :x(other.x), y(other.y), z(z), w(w) {
    }

    Vector4(const Vector3<T>& other, T w = 0) :x(other.x), y(other.y), z(other.z), w(w) {
    }

    //copy constructor
    Vector4(const Vector4<T>& other): x(other.x), y(other.y), z(other.z), w(other.w) {
    }

    //implicit casts
    operator std::string() {
        std::stringstream builder;
        builder << "X: " << x << " |Y: " << y << " |Z: " << z << " |W: " << w;
        return builder.str();
    }

    //equals operator
    Vector4<T>& operator =(const Vector4<T>& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    //addition operators
    Vector4<T> operator +(Vector4<T>& other) {
        return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    Vector4<T>& operator +=(const Vector4<T>& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }
    Vector4<T> operator -(const Vector4<T>& other) {
        return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    Vector4<T>& operator -=(const Vector4<T>& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    //scaling
    Vector4<T> operator *(const T& scale) {
        return Vector4<T>(x * scale, y * scale, z * scale, w * scale);
    }

    Vector4<T>& operator *=(const T& scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
        return *this;
    }

    //dot product
    T operator *(const Vector4<T>& other) {
        return x * other.x + y * other.y + z * other.z + w + other.w;
    }

    //normalize
    Vector4<T>& normalize() {
        T mag = magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
        return *this;
    }
    Vector4<T> retNormalized() const  {
        T mag = magnitude();
        return Vector4<T>(x / mag, y / mag, z / mag, w / mag);
    }

    //magnitude
    T magnitude() const {
        return sqrtl(x * x + y * y + z * z + w * w);
    }
    T magnitudeSquared() const {
        return x * x + y * y + z * z + w * w;
    }

    //negate
    Vector4<T> negate() {
        return Vector4<T>(x * -1, y * -1, z * -1, w * -1);
    }

    //4d swizzle
    Vector4<T> wxyz() const { return Vector4<T>(w, x, y, z); }
    Vector4<T> wxzy() const { return Vector4<T>(w, x, z, y); }
    Vector4<T> wyxz() const { return Vector4<T>(w, y, x, z); }
    Vector4<T> wyzx() const { return Vector4<T>(w, y, z, x); }
    Vector4<T> wzxy() const { return Vector4<T>(w, z, x, y); }
    Vector4<T> wzyx() const { return Vector4<T>(w, z, y, x); }
    Vector4<T> xwyz() const { return Vector4<T>(x, w, y, z); }
    Vector4<T> xwzy() const { return Vector4<T>(x, w, z, y); }
    Vector4<T> xywz() const { return Vector4<T>(x, y, w, z); }
    Vector4<T> xyzw() const { return Vector4<T>(x, y, z, w); }
    Vector4<T> xzwy() const { return Vector4<T>(x, z, w, y); }
    Vector4<T> xzyw() const { return Vector4<T>(x, z, y, w); }
    Vector4<T> ywxz() const { return Vector4<T>(y, w, x, z); }
    Vector4<T> ywzx() const { return Vector4<T>(y, w, z, x); }
    Vector4<T> yxwz() const { return Vector4<T>(y, x, w, z); }
    Vector4<T> yxzw() const { return Vector4<T>(y, x, z, w); }
    Vector4<T> yzwx() const { return Vector4<T>(y, z, w, x); }
    Vector4<T> yzxw() const { return Vector4<T>(y, z, x, w); }
    Vector4<T> zwxy() const { return Vector4<T>(z, w, x, y); }
    Vector4<T> zwyx() const { return Vector4<T>(z, w, y, x); }
    Vector4<T> zxwy() const { return Vector4<T>(z, x, w, y); }
    Vector4<T> zxyw() const { return Vector4<T>(z, x, y, w); }
    Vector4<T> zywx() const { return Vector4<T>(z, y, w, x); }
    Vector4<T> zyxw() const { return Vector4<T>(z, y, x, w); }
    //3d swizzle
    Vector3<T> wxy() const { return Vector3<T>(w, x, y); }
    Vector3<T> wxz() const { return Vector3<T>(w, x, z); }
    Vector3<T> wyx() const { return Vector3<T>(w, y, x); }
    Vector3<T> wyz() const { return Vector3<T>(w, y, z); }
    Vector3<T> wzx() const { return Vector3<T>(w, z, x); }
    Vector3<T> wzy() const { return Vector3<T>(w, z, y); }
    Vector3<T> xwy() const { return Vector3<T>(x, w, y); }
    Vector3<T> xwz() const { return Vector3<T>(x, w, z); }
    Vector3<T> xyw() const { return Vector3<T>(x, y, w); }
    Vector3<T> xyz() const { return Vector3<T>(x, y, z); }
    Vector3<T> xzw() const { return Vector3<T>(x, z, w); }
    Vector3<T> xzy() const { return Vector3<T>(x, z, y); }
    Vector3<T> ywx() const { return Vector3<T>(y, w, x); }
    Vector3<T> ywz() const { return Vector3<T>(y, w, z); }
    Vector3<T> yxw() const { return Vector3<T>(y, x, w); }
    Vector3<T> yxz() const { return Vector3<T>(y, x, z); }
    Vector3<T> yzw() const { return Vector3<T>(y, z, w); }
    Vector3<T> yzx() const { return Vector3<T>(y, z, x); }
    Vector3<T> zwx() const { return Vector3<T>(z, w, x); }
    Vector3<T> zwy() const { return Vector3<T>(z, w, y); }
    Vector3<T> zxw() const { return Vector3<T>(z, x, w); }
    Vector3<T> zxy() const { return Vector3<T>(z, x, y); }
    Vector3<T> zyw() const { return Vector3<T>(z, y, w); }
    Vector3<T> zyx() const { return Vector3<T>(z, y, x); }
    //2s swizzle
    Vector2<T> wx() const { return Vector2<T>(w, x); }
    Vector2<T> wy() const { return Vector2<T>(w, y); }
    Vector2<T> wz() const { return Vector2<T>(w, z); }
    Vector2<T> xw() const { return Vector2<T>(x, w); }
    Vector2<T> xy() const { return Vector2<T>(x, y); }
    Vector2<T> xz() const { return Vector2<T>(x, z); }
    Vector2<T> yw() const { return Vector2<T>(y, w); }
    Vector2<T> yx() const { return Vector2<T>(y, x); }
    Vector2<T> yz() const { return Vector2<T>(y, z); }
    Vector2<T> zw() const { return Vector2<T>(z, w); }
    Vector2<T> zx() const { return Vector2<T>(z, x); }
    Vector2<T> zy() const { return Vector2<T>(z, y); }

    T x, y, z, w;
};

typedef Vector4<> Vector4f;
typedef Vector4<double> Vector4d;
typedef Vector4<int> Vector4i;

#endif