#ifndef INCLUDE_MATRIX44_H
#define INCLUDE_MATRIX44_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>

template <typename T = float>
struct Matrix44{
    Matrix44(T m00 = 1, T m01 = 0, T m02 = 0, T m03 = 0,
                T m10 = 0, T m11 = 1, T m12 = 0, T m13 = 0,
                T m20 = 0, T m21 = 0, T m22 = 1, T m23 = 0,
                T m30 = 0, T m31 = 0, T m32 = 0, T m33 = 1)
    {
        data[0][0] = m00;
        data[1][0] = m10;
        data[2][0] = m20;
        data[3][0] = m30;

        data[0][1] = m01;
        data[1][1] = m11;
        data[2][1] = m21;
        data[3][1] = m31;

        data[0][2] = m02;
        data[1][2] = m12;
        data[2][2] = m22;
        data[3][2] = m32;

        data[0][3] = m03;
        data[1][3] = m13;
        data[2][3] = m23;
        data[3][3] = m33;
    }

    Matrix44(const Matrix44<T>& mat)
    {
        data[0][0] = mat.data[0][0];
        data[1][0] = mat.data[1][0];
        data[2][0] = mat.data[2][0];
        data[3][0] = mat.data[3][0];

        data[0][1] = mat.data[0][1];
        data[1][1] = mat.data[1][1];
        data[2][1] = mat.data[2][1];
        data[3][1] = mat.data[3][1];

        data[0][2] = mat.data[0][2];
        data[1][2] = mat.data[1][2];
        data[2][2] = mat.data[2][2];
        data[3][2] = mat.data[3][2];

        data[0][3] = mat.data[0][3];
        data[1][3] = mat.data[1][3];
        data[2][3] = mat.data[2][3];
        data[3][3] = mat.data[3][3];
    }

    Matrix44<T>& operator=(const Matrix44<T>& mat){
        data[0][0] = mat.data[0][0]; 
        data[0][1] = mat.data[0][1]; 
        data[0][2] = mat.data[0][2]; 
        data[0][3] = mat.data[0][3];

        data[1][0] = mat.data[1][0]; 
        data[1][1] = mat.data[1][1]; 
        data[1][2] = mat.data[1][2]; 
        data[1][3] = mat.data[1][3];

        data[2][0] = mat.data[2][0]; 
        data[2][1] = mat.data[2][1]; 
        data[2][2] = mat.data[2][2]; 
        data[2][3] = mat.data[2][3];

        data[3][0] = mat.data[3][0]; 
        data[3][1] = mat.data[3][1]; 
        data[3][2] = mat.data[3][2]; 
        data[3][3] = mat.data[3][3];

        return *this;
    }

    Matrix44<T>& negate(){
        data[0][0] = -data[0][0]; 
        data[0][1] = -data[0][1]; 
        data[0][2] = -data[0][2]; 
        data[0][3] = -data[0][3];

        data[1][0] = -data[1][0]; 
        data[1][1] = -data[1][1]; 
        data[1][2] = -data[1][2]; 
        data[1][3] = -data[1][3];

        data[2][0] = -data[2][0]; 
        data[2][1] = -data[2][1]; 
        data[2][2] = -data[2][2]; 
        data[2][3] = -data[2][3];

        data[3][0] = -data[3][0]; 
        data[3][1] = -data[3][1]; 
        data[3][2] = -data[3][2]; 
        data[3][3] = -data[3][3];

        return *this;
    }


    Matrix44<T>& setIdentity(){
        data[0][0] = 1; 
        data[0][1] = 0; 
        data[0][2] = 0; 
        data[0][3] = 0;

        data[1][0] = 0; 
        data[1][1] = 1; 
        data[1][2] = 0; 
        data[1][3] = 0;

        data[2][0] = 0; 
        data[2][1] = 0; 
        data[2][2] = 1; 
        data[2][3] = 0;

        data[3][0] = 0; 
        data[3][1] = 0; 
        data[3][2] = 0; 
        data[3][3] = 1;

        return *this;
    }

    Matrix44<T>& setForward(const Vector3<T>& forward)
    {
		this->data[2][0] = forward.x;
		this->data[2][1] = forward.y;
		this->data[2][2] = forward.z;

        return *this;
    }

    Matrix44<T>& setUp(const Vector3<T>& up)
    {
		this->data[1][0] = up.x;
		this->data[1][1] = up.y;
		this->data[1][2] = up.z;

        return *this;
    }

    Matrix44<T>& setRight(const Vector3<T>& right)
    {
		this->data[0][0] = right.x;
		this->data[0][1] = right.y;
		this->data[0][2] = right.z;

        return *this;
    }

    Matrix44<T>& setZero(){
        data[0][0] = 0; 
        data[0][1] = 0; 
        data[0][2] = 0; 
        data[0][3] = 0;

        data[1][0] = 0; 
        data[1][1] = 0; 
        data[1][2] = 0; 
        data[1][3] = 0;

        data[2][0] = 0; 
        data[2][1] = 0; 
        data[2][2] = 0; 
        data[2][3] = 0;

        data[3][0] = 0; 
        data[3][1] = 0; 
        data[3][2] = 0; 
        data[3][3] = 0;

        return *this;
    }

    Matrix44<T> operator+(const Matrix44<T>& mat) const {
        Matrix44<T> ret;

        ret.data[0][0] = this->data[0][0] + mat.data[0][0];
        ret.data[0][1] = this->data[0][1] + mat.data[0][1];
        ret.data[0][2] = this->data[0][2] + mat.data[0][2];
        ret.data[0][3] = this->data[0][3] + mat.data[0][3];
        ret.data[1][0] = this->data[1][0] + mat.data[1][0];
        ret.data[1][1] = this->data[1][1] + mat.data[1][1];
        ret.data[1][2] = this->data[1][2] + mat.data[1][2];
        ret.data[1][3] = this->data[1][3] + mat.data[1][3];
        ret.data[2][0] = this->data[2][0] + mat.data[2][0];
        ret.data[2][1] = this->data[2][1] + mat.data[2][1];
        ret.data[2][2] = this->data[2][2] + mat.data[2][2];
        ret.data[2][3] = this->data[2][3] + mat.data[2][3];
        ret.data[3][0] = this->data[3][0] + mat.data[3][0];
        ret.data[3][1] = this->data[3][1] + mat.data[3][1];
        ret.data[3][2] = this->data[3][2] + mat.data[3][2];
        ret.data[3][3] = this->data[3][3] + mat.data[3][3];

        return ret;
    }

    Matrix44<T>& operator+=(const Matrix44<T>& mat){
        this->data[0][0] = this->data[0][0] + mat.data[0][0];
        this->data[0][1] = this->data[0][1] + mat.data[0][1];
        this->data[0][2] = this->data[0][2] + mat.data[0][2];
        this->data[0][3] = this->data[0][3] + mat.data[0][3];
        this->data[1][0] = this->data[1][0] + mat.data[1][0];
        this->data[1][1] = this->data[1][1] + mat.data[1][1];
        this->data[1][2] = this->data[1][2] + mat.data[1][2];
        this->data[1][3] = this->data[1][3] + mat.data[1][3];
        this->data[2][0] = this->data[2][0] + mat.data[2][0];
        this->data[2][1] = this->data[2][1] + mat.data[2][1];
        this->data[2][2] = this->data[2][2] + mat.data[2][2];
        this->data[2][3] = this->data[2][3] + mat.data[2][3];
        this->data[3][0] = this->data[3][0] + mat.data[3][0];
        this->data[3][1] = this->data[3][1] + mat.data[3][1];
        this->data[3][2] = this->data[3][2] + mat.data[3][2];
        this->data[3][3] = this->data[3][3] + mat.data[3][3];
    }

    Matrix44<T> operator-(const Matrix44<T>& mat) const {
        Matrix44<T> ret;

        ret.data[0][0] = this->data[0][0] - mat.data[0][0];
        ret.data[0][1] = this->data[0][1] - mat.data[0][1];
        ret.data[0][2] = this->data[0][2] - mat.data[0][2];
        ret.data[0][3] = this->data[0][3] - mat.data[0][3];
        ret.data[1][0] = this->data[1][0] - mat.data[1][0];
        ret.data[1][1] = this->data[1][1] - mat.data[1][1];
        ret.data[1][2] = this->data[1][2] - mat.data[1][2];
        ret.data[1][3] = this->data[1][3] - mat.data[1][3];
        ret.data[2][0] = this->data[2][0] - mat.data[2][0];
        ret.data[2][1] = this->data[2][1] - mat.data[2][1];
        ret.data[2][2] = this->data[2][2] - mat.data[2][2];
        ret.data[2][3] = this->data[2][3] - mat.data[2][3];
        ret.data[3][0] = this->data[3][0] - mat.data[3][0];
        ret.data[3][1] = this->data[3][1] - mat.data[3][1];
        ret.data[3][2] = this->data[3][2] - mat.data[3][2];
        ret.data[3][3] = this->data[3][3] - mat.data[3][3];

        return ret;
    }

    Matrix44<T>& operator-=(const Matrix44<T>& mat){
        this->data[0][0] = this->data[0][0] - mat.data[0][0];
        this->data[0][1] = this->data[0][1] - mat.data[0][1];
        this->data[0][2] = this->data[0][2] - mat.data[0][2];
        this->data[0][3] = this->data[0][3] - mat.data[0][3];
        this->data[1][0] = this->data[1][0] - mat.data[1][0];
        this->data[1][1] = this->data[1][1] - mat.data[1][1];
        this->data[1][2] = this->data[1][2] - mat.data[1][2];
        this->data[1][3] = this->data[1][3] - mat.data[1][3];
        this->data[2][0] = this->data[2][0] - mat.data[2][0];
        this->data[2][1] = this->data[2][1] - mat.data[2][1];
        this->data[2][2] = this->data[2][2] - mat.data[2][2];
        this->data[2][3] = this->data[2][3] - mat.data[2][3];
        this->data[3][0] = this->data[3][0] - mat.data[3][0];
        this->data[3][1] = this->data[3][1] - mat.data[3][1];
        this->data[3][2] = this->data[3][2] - mat.data[3][2];
        this->data[3][3] = this->data[3][3] - mat.data[3][3];
    }

    Matrix44<T> operator*(const Matrix44<T>& mat) const {
        Matrix44<T> ret;

        T t00 = this->data[0][0] * mat.data[0][0] + this->data[1][0] * mat.data[0][1] + this->data[2][0] * mat.data[0][2] + this->data[3][0] * mat.data[0][3];
        T t01 = this->data[0][1] * mat.data[0][0] + this->data[1][1] * mat.data[0][1] + this->data[2][1] * mat.data[0][2] + this->data[3][1] * mat.data[0][3];
        T t02 = this->data[0][2] * mat.data[0][0] + this->data[1][2] * mat.data[0][1] + this->data[2][2] * mat.data[0][2] + this->data[3][2] * mat.data[0][3];
        T t03 = this->data[0][3] * mat.data[0][0] + this->data[1][3] * mat.data[0][1] + this->data[2][3] * mat.data[0][2] + this->data[3][3] * mat.data[0][3];
        T t10 = this->data[0][0] * mat.data[1][0] + this->data[1][0] * mat.data[1][1] + this->data[2][0] * mat.data[1][2] + this->data[3][0] * mat.data[1][3];
        T t11 = this->data[0][1] * mat.data[1][0] + this->data[1][1] * mat.data[1][1] + this->data[2][1] * mat.data[1][2] + this->data[3][1] * mat.data[1][3];
        T t12 = this->data[0][2] * mat.data[1][0] + this->data[1][2] * mat.data[1][1] + this->data[2][2] * mat.data[1][2] + this->data[3][2] * mat.data[1][3];
        T t13 = this->data[0][3] * mat.data[1][0] + this->data[1][3] * mat.data[1][1] + this->data[2][3] * mat.data[1][2] + this->data[3][3] * mat.data[1][3];
        T t20 = this->data[0][0] * mat.data[2][0] + this->data[1][0] * mat.data[2][1] + this->data[2][0] * mat.data[2][2] + this->data[3][0] * mat.data[2][3];
        T t21 = this->data[0][1] * mat.data[2][0] + this->data[1][1] * mat.data[2][1] + this->data[2][1] * mat.data[2][2] + this->data[3][1] * mat.data[2][3];
        T t22 = this->data[0][2] * mat.data[2][0] + this->data[1][2] * mat.data[2][1] + this->data[2][2] * mat.data[2][2] + this->data[3][2] * mat.data[2][3];
        T t23 = this->data[0][3] * mat.data[2][0] + this->data[1][3] * mat.data[2][1] + this->data[2][3] * mat.data[2][2] + this->data[3][3] * mat.data[2][3];
        T t30 = this->data[0][0] * mat.data[3][0] + this->data[1][0] * mat.data[3][1] + this->data[2][0] * mat.data[3][2] + this->data[3][0] * mat.data[3][3];
        T t31 = this->data[0][1] * mat.data[3][0] + this->data[1][1] * mat.data[3][1] + this->data[2][1] * mat.data[3][2] + this->data[3][1] * mat.data[3][3];
        T t32 = this->data[0][2] * mat.data[3][0] + this->data[1][2] * mat.data[3][1] + this->data[2][2] * mat.data[3][2] + this->data[3][2] * mat.data[3][3];
        T t33 = this->data[0][3] * mat.data[3][0] + this->data[1][3] * mat.data[3][1] + this->data[2][3] * mat.data[3][2] + this->data[3][3] * mat.data[3][3];

        ret.data[0][0] = t00;
        ret.data[0][1] = t01;
        ret.data[0][2] = t02;
        ret.data[0][3] = t03;
        ret.data[1][0] = t10;
        ret.data[1][1] = t11;
        ret.data[1][2] = t12;
        ret.data[1][3] = t13;
        ret.data[2][0] = t20;
        ret.data[2][1] = t21;
        ret.data[2][2] = t22;
        ret.data[2][3] = t23;
        ret.data[3][0] = t30;
        ret.data[3][1] = t31;
        ret.data[3][2] = t32;
        ret.data[3][3] = t33;

        return ret;
    }

    Matrix44<T>& operator*=(const Matrix44<T>& mat){
        T t00 = this->data[0][0] * mat.data[0][0] + this->data[1][0] * mat.data[0][1] + this->data[2][0] * mat.data[0][2] + this->data[3][0] * mat.data[0][3];
        T t01 = this->data[0][1] * mat.data[0][0] + this->data[1][1] * mat.data[0][1] + this->data[2][1] * mat.data[0][2] + this->data[3][1] * mat.data[0][3];
        T t02 = this->data[0][2] * mat.data[0][0] + this->data[1][2] * mat.data[0][1] + this->data[2][2] * mat.data[0][2] + this->data[3][2] * mat.data[0][3];
        T t03 = this->data[0][3] * mat.data[0][0] + this->data[1][3] * mat.data[0][1] + this->data[2][3] * mat.data[0][2] + this->data[3][3] * mat.data[0][3];
        T t10 = this->data[0][0] * mat.data[1][0] + this->data[1][0] * mat.data[1][1] + this->data[2][0] * mat.data[1][2] + this->data[3][0] * mat.data[1][3];
        T t11 = this->data[0][1] * mat.data[1][0] + this->data[1][1] * mat.data[1][1] + this->data[2][1] * mat.data[1][2] + this->data[3][1] * mat.data[1][3];
        T t12 = this->data[0][2] * mat.data[1][0] + this->data[1][2] * mat.data[1][1] + this->data[2][2] * mat.data[1][2] + this->data[3][2] * mat.data[1][3];
        T t13 = this->data[0][3] * mat.data[1][0] + this->data[1][3] * mat.data[1][1] + this->data[2][3] * mat.data[1][2] + this->data[3][3] * mat.data[1][3];
        T t20 = this->data[0][0] * mat.data[2][0] + this->data[1][0] * mat.data[2][1] + this->data[2][0] * mat.data[2][2] + this->data[3][0] * mat.data[2][3];
        T t21 = this->data[0][1] * mat.data[2][0] + this->data[1][1] * mat.data[2][1] + this->data[2][1] * mat.data[2][2] + this->data[3][1] * mat.data[2][3];
        T t22 = this->data[0][2] * mat.data[2][0] + this->data[1][2] * mat.data[2][1] + this->data[2][2] * mat.data[2][2] + this->data[3][2] * mat.data[2][3];
        T t23 = this->data[0][3] * mat.data[2][0] + this->data[1][3] * mat.data[2][1] + this->data[2][3] * mat.data[2][2] + this->data[3][3] * mat.data[2][3];
        T t30 = this->data[0][0] * mat.data[3][0] + this->data[1][0] * mat.data[3][1] + this->data[2][0] * mat.data[3][2] + this->data[3][0] * mat.data[3][3];
        T t31 = this->data[0][1] * mat.data[3][0] + this->data[1][1] * mat.data[3][1] + this->data[2][1] * mat.data[3][2] + this->data[3][1] * mat.data[3][3];
        T t32 = this->data[0][2] * mat.data[3][0] + this->data[1][2] * mat.data[3][1] + this->data[2][2] * mat.data[3][2] + this->data[3][2] * mat.data[3][3];
        T t33 = this->data[0][3] * mat.data[3][0] + this->data[1][3] * mat.data[3][1] + this->data[2][3] * mat.data[3][2] + this->data[3][3] * mat.data[3][3];

        this->data[0][0] = t00;
        this->data[0][1] = t01;
        this->data[0][2] = t02;
        this->data[0][3] = t03;
        this->data[1][0] = t10;
        this->data[1][1] = t11;
        this->data[1][2] = t12;
        this->data[1][3] = t13;
        this->data[2][0] = t20;
        this->data[2][1] = t21;
        this->data[2][2] = t22;
        this->data[2][3] = t23;
        this->data[3][0] = t30;
        this->data[3][1] = t31;
        this->data[3][2] = t32;
        this->data[3][3] = t33;

        return *this;
    }

    void transform(const Vector4<T>& right, Vector4<T>& dest) {
        T x = data[0][0] * right.x + data[1][0] * right.y + data[2][0] * right.z + data[3][0] * right.w;
        T y = data[0][1] * right.x + data[1][1] * right.y + data[2][1] * right.z + data[3][1] * right.w;
        T z = data[0][2] * right.x + data[1][2] * right.y + data[2][2] * right.z + data[3][2] * right.w;
        T w = data[0][3] * right.x + data[1][3] * right.y + data[2][3] * right.z + data[3][3] * right.w;

        dest.x = x;
        dest.y = y;
        dest.z = z;
        dest.w = w;
    }

    Vector4<T> operator*(const Vector4<T>& right) {
        Vector4<T> ret;
        
        T x = data[0][0] * right.x + data[1][0] * right.y + data[2][0] * right.z + data[3][0] * right.w;
        T y = data[0][1] * right.x + data[1][1] * right.y + data[2][1] * right.z + data[3][1] * right.w;
        T z = data[0][2] * right.x + data[1][2] * right.y + data[2][2] * right.z + data[3][2] * right.w;
        T w = data[0][3] * right.x + data[1][3] * right.y + data[2][3] * right.z + data[3][3] * right.w;

        ret.x = x;
        ret.y = y;
        ret.z = z;
        ret.w = w;

        return ret;
    }

    void scale(const Vector3<T>& scale) {
        this->data[0][0] = this->data[0][0] * scale.x;
        this->data[0][1] = this->data[0][1] * scale.x;
        this->data[0][2] = this->data[0][2] * scale.x;
        this->data[0][3] = this->data[0][3] * scale.x;
        this->data[1][0] = this->data[1][0] * scale.y;
        this->data[1][1] = this->data[1][1] * scale.y;
        this->data[1][2] = this->data[1][2] * scale.y;
        this->data[1][3] = this->data[1][3] * scale.y;
        this->data[2][0] = this->data[2][0] * scale.z;
        this->data[2][1] = this->data[2][1] * scale.z;
        this->data[2][2] = this->data[2][2] * scale.z;
        this->data[2][3] = this->data[2][3] * scale.z;
    }

    void translate(const Vector3<T>& vec) {
        this->data[3][0] += this->data[0][0] * vec.x + this->data[1][0] * vec.y + this->data[2][0] * vec.z;
        this->data[3][1] += this->data[0][1] * vec.x + this->data[1][1] * vec.y + this->data[2][1] * vec.z;
        this->data[3][2] += this->data[0][2] * vec.x + this->data[1][2] * vec.y + this->data[2][2] * vec.z;
        this->data[3][3] += this->data[0][3] * vec.x + this->data[1][3] * vec.y + this->data[2][3] * vec.z;
    }

    void rotate(const Vector3<T>& axis, T angle) {
        T c = (T)cos(angle);
        T s = (T)sin(angle);

        T oneminusc = (T)1 - c;
        T xy = axis.x * axis.y;
        T yz = axis.y * axis.z;
        T xz = axis.x * axis.z;
        T xs = axis.x * s;
        T ys = axis.y * s;
        T zs = axis.z * s;

        T f00 = axis.x * axis.x * oneminusc + c;
        T f01 = xy * oneminusc + zs;
        T f02 = xz * oneminusc - ys;

        T f10 = xy * oneminusc - zs;
        T f11 = axis.y * axis.y * oneminusc + c;
        T f12 = yz * oneminusc + xs;

        T f20 = xz * oneminusc + ys;
        T f21 = yz * oneminusc - xs;
        T f22 = axis.z * axis.z * oneminusc + c;

        T t00 = this->data[0][0] * f00 + this->data[1][0] * f01 + this->data[2][0] * f02;
        T t01 = this->data[0][1] * f00 + this->data[1][1] * f01 + this->data[2][1] * f02;
        T t02 = this->data[0][2] * f00 + this->data[1][2] * f01 + this->data[2][2] * f02;
        T t03 = this->data[0][3] * f00 + this->data[1][3] * f01 + this->data[2][3] * f02;
        T t10 = this->data[0][0] * f10 + this->data[1][0] * f11 + this->data[2][0] * f12;
        T t11 = this->data[0][1] * f10 + this->data[1][1] * f11 + this->data[2][1] * f12;
        T t12 = this->data[0][2] * f10 + this->data[1][2] * f11 + this->data[2][2] * f12;
        T t13 = this->data[0][3] * f10 + this->data[1][3] * f11 + this->data[2][3] * f12;

        this->data[2][0] = this->data[0][0] * f20 + this->data[1][0] * f21 + this->data[2][0] * f22;
        this->data[2][1] = this->data[0][1] * f20 + this->data[1][1] * f21 + this->data[2][1] * f22;
        this->data[2][2] = this->data[0][2] * f20 + this->data[1][2] * f21 + this->data[2][2] * f22;
        this->data[2][3] = this->data[0][3] * f20 + this->data[1][3] * f21 + this->data[2][3] * f22;
        this->data[0][0] = t00;
        this->data[0][1] = t01;
        this->data[0][2] = t02;
        this->data[0][3] = t03;
        this->data[1][0] = t10;
        this->data[1][1] = t11;
        this->data[1][2] = t12;
        this->data[1][3] = t13;
    }

    Matrix44<T>& transpose(){
        T t00 = this->data[0][0];
        T t01 = this->data[1][0];
        T t02 = this->data[2][0];
        T t03 = this->data[3][0];
        T t10 = this->data[0][1];
        T t11 = this->data[1][1];
        T t12 = this->data[2][1];
        T t13 = this->data[3][1];
        T t20 = this->data[0][2];
        T t21 = this->data[1][2];
        T t22 = this->data[2][2];
        T t23 = this->data[3][2];
        T t30 = this->data[0][3];
        T t31 = this->data[1][3];
        T t32 = this->data[2][3];
        T t33 = this->data[3][3];

        this->data[0][0] = t00;
        this->data[0][1] = t01;
        this->data[0][2] = t02;
        this->data[0][3] = t03;
        this->data[1][0] = t10;
        this->data[1][1] = t11;
        this->data[1][2] = t12;
        this->data[1][3] = t13;
        this->data[2][0] = t20;
        this->data[2][1] = t21;
        this->data[2][2] = t22;
        this->data[2][3] = t23;
        this->data[3][0] = t30;
        this->data[3][1] = t31;
        this->data[3][2] = t32;
        this->data[3][3] = t33;

        return *this;
    }

    T det() {
        T f = data[0][0] * ((data[1][1] * data[2][2] * data[3][3] + data[1][2] * data[2][3] * data[3][1] + data[1][3] * data[2][1] * data[3][2])
                - data[1][3] * data[2][2] * data[3][1]
                - data[1][1] * data[2][3] * data[3][2]
                - data[1][2] * data[2][1] * data[3][3]);

        f -= data[0][1] * ((data[1][0] * data[2][2] * data[3][3] + data[1][2] * data[2][3] * data[3][0] + data[1][3] * data[2][0] * data[3][2])
            - data[1][3] * data[2][2] * data[3][0]
            - data[1][0] * data[2][3] * data[3][2]
            - data[1][2] * data[2][0] * data[3][3]);

        f += data[0][2] * ((data[1][0] * data[2][1] * data[3][3] + data[1][1] * data[2][3] * data[3][0] + data[1][3] * data[2][0] * data[3][1])
            - data[1][3] * data[2][1] * data[3][0]
            - data[1][0] * data[2][3] * data[3][1]
            - data[1][1] * data[2][0] * data[3][3]);

        f -= data[0][3] * ((data[1][0] * data[2][1] * data[3][2] + data[1][1] * data[2][2] * data[3][0] + data[1][2] * data[2][0] * data[3][1])
            - data[1][2] * data[2][1] * data[3][0]
            - data[1][0] * data[2][2] * data[3][1]
            - data[1][1] * data[2][0] * data[3][2]);

        return f;
    }

    static T det33(T t00, T t01, T t02,
                            T t10, T t11, T t12,
                            T t20, T t21, T t22)
    {
        return   t00 * (t11 * t22 - t12 * t21)
            + t01 * (t12 * t20 - t10 * t22)
            + t02 * (t10 * t21 - t11 * t20);
    }

    Matrix44<T> inverse() {
        T determinant = this->det();
        Matrix44<T> ret;

        if (determinant != 0) {
            T determinant_inv = (T)1/determinant;

            //first row
            T t00 =  det33(this->data[1][1], this->data[1][2], this->data[1][3], this->data[2][1], this->data[2][2], this->data[2][3], this->data[3][1], this->data[3][2], this->data[3][3]);
            T t01 = -det33(this->data[1][0], this->data[1][2], this->data[1][3], this->data[2][0], this->data[2][2], this->data[2][3], this->data[3][0], this->data[3][2], this->data[3][3]);
            T t02 =  det33(this->data[1][0], this->data[1][1], this->data[1][3], this->data[2][0], this->data[2][1], this->data[2][3], this->data[3][0], this->data[3][1], this->data[3][3]);
            T t03 = -det33(this->data[1][0], this->data[1][1], this->data[1][2], this->data[2][0], this->data[2][1], this->data[2][2], this->data[3][0], this->data[3][1], this->data[3][2]);

            // second row
            T t10 = -det33(this->data[0][1], this->data[0][2], this->data[0][3], this->data[2][1], this->data[2][2], this->data[2][3], this->data[3][1], this->data[3][2], this->data[3][3]);
            T t11 =  det33(this->data[0][0], this->data[0][2], this->data[0][3], this->data[2][0], this->data[2][2], this->data[2][3], this->data[3][0], this->data[3][2], this->data[3][3]);
            T t12 = -det33(this->data[0][0], this->data[0][1], this->data[0][3], this->data[2][0], this->data[2][1], this->data[2][3], this->data[3][0], this->data[3][1], this->data[3][3]);
            T t13 =  det33(this->data[0][0], this->data[0][1], this->data[0][2], this->data[2][0], this->data[2][1], this->data[2][2], this->data[3][0], this->data[3][1], this->data[3][2]);

            // third row
            T t20 =  det33(this->data[0][1], this->data[0][2], this->data[0][3], this->data[1][1], this->data[1][2], this->data[1][3], this->data[3][1], this->data[3][2], this->data[3][3]);
            T t21 = -det33(this->data[0][0], this->data[0][2], this->data[0][3], this->data[1][0], this->data[1][2], this->data[1][3], this->data[3][0], this->data[3][2], this->data[3][3]);
            T t22 =  det33(this->data[0][0], this->data[0][1], this->data[0][3], this->data[1][0], this->data[1][1], this->data[1][3], this->data[3][0], this->data[3][1], this->data[3][3]);
            T t23 = -det33(this->data[0][0], this->data[0][1], this->data[0][2], this->data[1][0], this->data[1][1], this->data[1][2], this->data[3][0], this->data[3][1], this->data[3][2]);

            // fourth row
            T t30 = -det33(this->data[0][1], this->data[0][2], this->data[0][3], this->data[1][1], this->data[1][2], this->data[1][3], this->data[2][1], this->data[2][2], this->data[2][3]);
            T t31 =  det33(this->data[0][0], this->data[0][2], this->data[0][3], this->data[1][0], this->data[1][2], this->data[1][3], this->data[2][0], this->data[2][2], this->data[2][3]);
            T t32 = -det33(this->data[0][0], this->data[0][1], this->data[0][3], this->data[1][0], this->data[1][1], this->data[1][3], this->data[2][0], this->data[2][1], this->data[2][3]);
            T t33 =  det33(this->data[0][0], this->data[0][1], this->data[0][2], this->data[1][0], this->data[1][1], this->data[1][2], this->data[2][0], this->data[2][1], this->data[2][2]);

            //transpose and divide by the determinant
            ret.data[0][0] = t00*determinant_inv;
            ret.data[1][1] = t11*determinant_inv;
            ret.data[2][2] = t22*determinant_inv;
            ret.data[3][3] = t33*determinant_inv;
            ret.data[0][1] = t10*determinant_inv;
            ret.data[1][0] = t01*determinant_inv;
            ret.data[2][0] = t02*determinant_inv;
            ret.data[0][2] = t20*determinant_inv;
            ret.data[1][2] = t21*determinant_inv;
            ret.data[2][1] = t12*determinant_inv;
            ret.data[0][3] = t30*determinant_inv;
            ret.data[3][0] = t03*determinant_inv;
            ret.data[1][3] = t31*determinant_inv;
            ret.data[3][1] = t13*determinant_inv;
            ret.data[3][2] = t23*determinant_inv;
            ret.data[2][3] = t32*determinant_inv;
        }

        return ret;
    }

    Matrix44<T>& invert(){
        T determinant = this->det();

        if (determinant != 0) {
            T determinant_inv = (T)1/determinant;

            //first row
            T t00 =  det33(this->data[1][1], this->data[1][2], this->data[1][3], this->data[2][1], this->data[2][2], this->data[2][3], this->data[3][1], this->data[3][2], this->data[3][3]);
            T t01 = -det33(this->data[1][0], this->data[1][2], this->data[1][3], this->data[2][0], this->data[2][2], this->data[2][3], this->data[3][0], this->data[3][2], this->data[3][3]);
            T t02 =  det33(this->data[1][0], this->data[1][1], this->data[1][3], this->data[2][0], this->data[2][1], this->data[2][3], this->data[3][0], this->data[3][1], this->data[3][3]);
            T t03 = -det33(this->data[1][0], this->data[1][1], this->data[1][2], this->data[2][0], this->data[2][1], this->data[2][2], this->data[3][0], this->data[3][1], this->data[3][2]);

            // second row
            T t10 = -det33(this->data[0][1], this->data[0][2], this->data[0][3], this->data[2][1], this->data[2][2], this->data[2][3], this->data[3][1], this->data[3][2], this->data[3][3]);
            T t11 =  det33(this->data[0][0], this->data[0][2], this->data[0][3], this->data[2][0], this->data[2][2], this->data[2][3], this->data[3][0], this->data[3][2], this->data[3][3]);
            T t12 = -det33(this->data[0][0], this->data[0][1], this->data[0][3], this->data[2][0], this->data[2][1], this->data[2][3], this->data[3][0], this->data[3][1], this->data[3][3]);
            T t13 =  det33(this->data[0][0], this->data[0][1], this->data[0][2], this->data[2][0], this->data[2][1], this->data[2][2], this->data[3][0], this->data[3][1], this->data[3][2]);

            // third row
            T t20 =  det33(this->data[0][1], this->data[0][2], this->data[0][3], this->data[1][1], this->data[1][2], this->data[1][3], this->data[3][1], this->data[3][2], this->data[3][3]);
            T t21 = -det33(this->data[0][0], this->data[0][2], this->data[0][3], this->data[1][0], this->data[1][2], this->data[1][3], this->data[3][0], this->data[3][2], this->data[3][3]);
            T t22 =  det33(this->data[0][0], this->data[0][1], this->data[0][3], this->data[1][0], this->data[1][1], this->data[1][3], this->data[3][0], this->data[3][1], this->data[3][3]);
            T t23 = -det33(this->data[0][0], this->data[0][1], this->data[0][2], this->data[1][0], this->data[1][1], this->data[1][2], this->data[3][0], this->data[3][1], this->data[3][2]);

            // fourth row
            T t30 = -det33(this->data[0][1], this->data[0][2], this->data[0][3], this->data[1][1], this->data[1][2], this->data[1][3], this->data[2][1], this->data[2][2], this->data[2][3]);
            T t31 =  det33(this->data[0][0], this->data[0][2], this->data[0][3], this->data[1][0], this->data[1][2], this->data[1][3], this->data[2][0], this->data[2][2], this->data[2][3]);
            T t32 = -det33(this->data[0][0], this->data[0][1], this->data[0][3], this->data[1][0], this->data[1][1], this->data[1][3], this->data[2][0], this->data[2][1], this->data[2][3]);
            T t33 =  det33(this->data[0][0], this->data[0][1], this->data[0][2], this->data[1][0], this->data[1][1], this->data[1][2], this->data[2][0], this->data[2][1], this->data[2][2]);

            //transpose and divide by the determinant
            this->data[0][0] = t00*determinant_inv;
            this->data[1][1] = t11*determinant_inv;
            this->data[2][2] = t22*determinant_inv;
            this->data[3][3] = t33*determinant_inv;
            this->data[0][1] = t10*determinant_inv;
            this->data[1][0] = t01*determinant_inv;
            this->data[2][0] = t02*determinant_inv;
            this->data[0][2] = t20*determinant_inv;
            this->data[1][2] = t21*determinant_inv;
            this->data[2][1] = t12*determinant_inv;
            this->data[0][3] = t30*determinant_inv;
            this->data[3][0] = t03*determinant_inv;
            this->data[1][3] = t31*determinant_inv;
            this->data[3][1] = t13*determinant_inv;
            this->data[3][2] = t23*determinant_inv;
            this->data[2][3] = t32*determinant_inv;
        }

        return *this;
    }

    operator std::string() const {
        char buff[200];
        snprintf(buff, sizeof(buff), "\n"
                                    "[%4.4f] [%4.4f] [%4.4f] [%4.4f]\n"
                                    "[%4.4f] [%4.4f] [%4.4f] [%4.4f]\n"
                                    "[%4.4f] [%4.4f] [%4.4f] [%4.4f]\n"
                                    "[%4.4f] [%4.4f] [%4.4f] [%4.4f]",
                                    data[0][0], data[0][1], data[0][2], data[0][3], 
                                    data[1][0], data[1][1], data[1][2], data[1][3],
                                    data[2][0], data[2][1], data[2][2], data[2][3],
                                    data[3][0], data[3][1], data[3][2], data[3][3]);

        return std::string(buff);
    }

    T data[4][4];
    //T data[0][0], data[0][1], data[0][2], data[0][3];
    //T data[1][0], data[1][1], data[1][2], data[1][3];
    //T data[2][0], data[2][1], data[2][2], data[2][3];
    //T data[3][0], data[3][1], data[3][2], data[3][3];
};

typedef Matrix44<float> Matrix44f;
typedef Matrix44<double> Matrix44d;
typedef Matrix44<int> Matrix44i;

#endif