#ifndef INCLUDE_MATRIX33_H
#define INCLUDE_MATRIX33_H

#include <string>

template<typename T = float>

struct Matrix33 {
	Matrix33(T m00 = 1, T m01 = 0, T m02 = 0, T m10 = 0, T m11 = 1, T m12 = 0,
				T m20 = 0, T m21 = 0, T m22 = 1)
	{
		data[0][0] = m00;
		data[1][0] = m10;
		data[2][0] = m20;

		data[0][1] = m01;
		data[1][1] = m11;
		data[2][1] = m21;

		data[0][2] = m02;
		data[1][2] = m12;
		data[2][2] = m22;
	}

	Matrix33(const Matrix33<T>& mat)
	{
		data[0][0] = mat.data[0][0];
		data[1][0] = mat.data[1][0];
		data[2][0] = mat.data[2][0];

		data[0][1] = mat.data[0][1];
		data[1][1] = mat.data[1][1];
		data[2][1] = mat.data[2][1];

		data[0][2] = mat.data[0][2];
		data[1][2] = mat.data[1][2];
		data[2][2] = mat.data[2][2];
	}

	Matrix33<T>& operator=(const Matrix33<T>& mat){
		data[0][0] = mat.data[0][0];
		data[0][1] = mat.data[0][1];
		data[0][2] = mat.data[0][2];

		data[1][0] = mat.data[1][0];
		data[1][1] = mat.data[1][1];
		data[1][2] = mat.data[1][2];

		data[2][0] = mat.data[2][0];
		data[2][1] = mat.data[2][1];
		data[2][2] = mat.data[2][2];

		return *this;
	}

	Matrix33<T>& setIdentity(){
		data[0][0] = 1;
		data[0][1] = 0;
		data[0][2] = 0;

		data[1][0] = 0;
		data[1][1] = 1;
		data[1][2] = 0;

		data[2][0] = 0;
		data[2][1] = 0;
		data[2][2] = 0;

		return *this;
	}

	Matrix33<T>& setZero(){
		data[0][0] = 0;
		data[0][1] = 0;
		data[0][2] = 0;

		data[1][0] = 0;
		data[1][1] = 0;
		data[1][2] = 0;

		data[2][0] = 0;
		data[2][1] = 0;
		data[2][2] = 0;

		return *this;
	}

	Matrix33<T> operator+(const Matrix33<T>& right){
		Matrix33<T> ret;

		ret.data[0][0] = this->data[0][0] + right.data[0][0];
		ret.data[0][1] = this->data[0][1] + right.data[0][1];
		ret.data[0][2] = this->data[0][2] + right.data[0][2];
		ret.data[1][0] = this->data[1][0] + right.data[1][0];
		ret.data[1][1] = this->data[1][1] + right.data[1][1];
		ret.data[1][2] = this->data[1][2] + right.data[1][2];
		ret.data[2][0] = this->data[2][0] + right.data[2][0];
		ret.data[2][1] = this->data[2][1] + right.data[2][1];
		ret.data[2][2] = this->data[2][2] + right.data[2][2];

		return ret;
	}

	Matrix33<T>& operator+=(const Matrix33<T>& right){
		this->data[0][0] = this->data[0][0] + right.data[0][0];
		this->data[0][1] = this->data[0][1] + right.data[0][1];
		this->data[0][2] = this->data[0][2] + right.data[0][2];
		this->data[1][0] = this->data[1][0] + right.data[1][0];
		this->data[1][1] = this->data[1][1] + right.data[1][1];
		this->data[1][2] = this->data[1][2] + right.data[1][2];
		this->data[2][0] = this->data[2][0] + right.data[2][0];
		this->data[2][1] = this->data[2][1] + right.data[2][1];
		this->data[2][2] = this->data[2][2] + right.data[2][2];

		return *this;
	}

	Matrix33<T> operator-(const Matrix33<T>& right){
		Matrix33<T> ret;

		ret.data[0][0] = this->data[0][0] - right.data[0][0];
		ret.data[0][1] = this->data[0][1] - right.data[0][1];
		ret.data[0][2] = this->data[0][2] - right.data[0][2];
		ret.data[1][0] = this->data[1][0] - right.data[1][0];
		ret.data[1][1] = this->data[1][1] - right.data[1][1];
		ret.data[1][2] = this->data[1][2] - right.data[1][2];
		ret.data[2][0] = this->data[2][0] - right.data[2][0];
		ret.data[2][1] = this->data[2][1] - right.data[2][1];
		ret.data[2][2] = this->data[2][2] - right.data[2][2];

		return ret;
	}

	Matrix33<T>& operator-=(const Matrix33<T>& right){
		this->data[0][0] = this->data[0][0] - right.data[0][0];
		this->data[0][1] = this->data[0][1] - right.data[0][1];
		this->data[0][2] = this->data[0][2] - right.data[0][2];
		this->data[1][0] = this->data[1][0] - right.data[1][0];
		this->data[1][1] = this->data[1][1] - right.data[1][1];
		this->data[1][2] = this->data[1][2] - right.data[1][2];
		this->data[2][0] = this->data[2][0] - right.data[2][0];
		this->data[2][1] = this->data[2][1] - right.data[2][1];
		this->data[2][2] = this->data[2][2] - right.data[2][2];

		return *this;
	}

	Matrix33<T> operator*(const Matrix33<T>& right){
		Matrix33<T> ret;

		T m00 = this->data[0][0] * right.data[0][0] + this->data[1][0] * right.data[0][1] + this->data[2][0] * right.data[0][2];
		T m01 = this->data[0][1] * right.data[0][0] + this->data[1][1] * right.data[0][1] + this->data[2][1] * right.data[0][2];
		T m02 = this->data[0][2] * right.data[0][0] + this->data[1][2] * right.data[0][1] + this->data[2][2] * right.data[0][2];
		T m10 = this->data[0][0] * right.data[1][0] + this->data[1][0] * right.data[1][1] + this->data[2][0] * right.data[1][2];
		T m11 = this->data[0][1] * right.data[1][0] + this->data[1][1] * right.data[1][1] + this->data[2][1] * right.data[1][2];
		T m12 = this->data[0][2] * right.data[1][0] + this->data[1][2] * right.data[1][1] + this->data[2][2] * right.data[1][2];
		T m20 = this->data[0][0] * right.data[2][0] + this->data[1][0] * right.data[2][1] + this->data[2][0] * right.data[2][2];
		T m21 = this->data[0][1] * right.data[2][0] + this->data[1][1] * right.data[2][1] + this->data[2][1] * right.data[2][2];
		T m22 = this->data[0][2] * right.data[2][0] + this->data[1][2] * right.data[2][1] + this->data[2][2] * right.data[2][2];

		ret.data[0][0] = m00;
		ret.data[0][1] = m01;
		ret.data[0][2] = m02;
		ret.data[1][0] = m10;
		ret.data[1][1] = m11;
		ret.data[1][2] = m12;
		ret.data[2][0] = m20;
		ret.data[2][1] = m21;
		ret.data[2][2] = m22;

		return ret;
	}

	Matrix33<T>& operator*=(const Matrix33<T>& right){
		T m00 = this->data[0][0] * right.data[0][0] + this->data[1][0] * right.data[0][1] + this->data[2][0] * right.data[0][2];
		T m01 = this->data[0][1] * right.data[0][0] + this->data[1][1] * right.data[0][1] + this->data[2][1] * right.data[0][2];
		T m02 = this->data[0][2] * right.data[0][0] + this->data[1][2] * right.data[0][1] + this->data[2][2] * right.data[0][2];
		T m10 = this->data[0][0] * right.data[1][0] + this->data[1][0] * right.data[1][1] + this->data[2][0] * right.data[1][2];
		T m11 = this->data[0][1] * right.data[1][0] + this->data[1][1] * right.data[1][1] + this->data[2][1] * right.data[1][2];
		T m12 = this->data[0][2] * right.data[1][0] + this->data[1][2] * right.data[1][1] + this->data[2][2] * right.data[1][2];
		T m20 = this->data[0][0] * right.data[2][0] + this->data[1][0] * right.data[2][1] + this->data[2][0] * right.data[2][2];
		T m21 = this->data[0][1] * right.data[2][0] + this->data[1][1] * right.data[2][1] + this->data[2][1] * right.data[2][2];
		T m22 = this->data[0][2] * right.data[2][0] + this->data[1][2] * right.data[2][1] + this->data[2][2] * right.data[2][2];

		this->data[0][0] = m00;
		this->data[0][1] = m01;
		this->data[0][2] = m02;
		this->data[1][0] = m10;
		this->data[1][1] = m11;
		this->data[1][2] = m12;
		this->data[2][0] = m20;
		this->data[2][1] = m21;
		this->data[2][2] = m22;

		return *this;
	}

	Matrix33<T>& transpose(){
		T m00 = this->data[0][0];
		T m01 = this->data[1][0];
		T m02 = this->data[2][0];
		T m10 = this->data[0][1];
		T m11 = this->data[1][1];
		T m12 = this->data[2][1];
		T m20 = this->data[0][2];
		T m21 = this->data[1][2];
		T m22 = this->data[2][2];

		this->data[0][0] = m00;
		this->data[0][1] = m01;
		this->data[0][2] = m02;
		this->data[1][0] = m10;
		this->data[1][1] = m11;
		this->data[1][2] = m12;
		this->data[2][0] = m20;
		this->data[2][1] = m21;
		this->data[2][2] = m22;

		return *this;
	}

	T det(){
		return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
		+ data[0][1] * (data[1][2] * data[2][0] - data[1][0] * data[2][2])
		+ data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
	}

	operator std::string(){
		char buff[100];
		snprintf(buff, sizeof(buff), "\n"
									"[%4.4f] [%4.4f] [%4.4f]\n"
									"[%4.4f] [%4.4f] [%4.4f]\n"
									"[%4.4f] [%4.4f] [%4.4f]",
									data[0][0], data[0][1], data[0][2], data[1][0], data[1][1], data[1][2], data[2][0], data[2][1], data[2][2]);

		return std::string(buff);
	}

	Matrix33<T>& invert(){
		T determinant = this->det();

		if(determinant != 0){
			T determinant_inv = (T)1/determinant;

			T t00 = this->data[1][1] * this->data[2][2] - this->data[1][2]* this->data[2][1];
			T t01 = - this->data[1][0] * this->data[2][2] + this->data[1][2] * this->data[2][0];
			T t02 = this->data[1][0] * this->data[2][1] - this->data[1][1] * this->data[2][0];
			T t10 = - this->data[0][1] * this->data[2][2] + this->data[0][2] * this->data[2][1];
			T t11 = this->data[0][0] * this->data[2][2] - this->data[0][2] * this->data[2][0];
			T t12 = - this->data[0][0] * this->data[2][1] + this->data[0][1] * this->data[2][0];
			T t20 = this->data[0][1] * this->data[1][2] - this->data[0][2] * this->data[1][1];
			T t21 = -this->data[0][0] * this->data[1][2] + this->data[0][2] * this->data[1][0];
			T t22 = this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0];

			this->data[0][0] = t00*determinant_inv;
			this->data[1][1] = t11*determinant_inv;
			this->data[2][2] = t22*determinant_inv;
			this->data[0][1] = t10*determinant_inv;
			this->data[1][0] = t01*determinant_inv;
			this->data[2][0] = t02*determinant_inv;
			this->data[0][2] = t20*determinant_inv;
			this->data[1][2] = t21*determinant_inv;
			this->data[2][1] = t12*determinant_inv;
		}

		return *this;
	}

	Matrix33<T>& negate(){
		data[0][0] = -data[0][0];
		data[0][1] = -data[0][1];
		data[0][2] = -data[0][2];

		data[1][0] = -data[1][0];
		data[1][1] = -data[1][1];
		data[1][2] = -data[1][2];

		data[2][0] = -data[2][0];
		data[2][1] = -data[2][1];
		data[2][2] = -data[2][2];

		return *this;
	}

	/**
	 * TODO: create vector3 transform
	 * */
	
	
	T data[3][3];
	//T data[0][0], data[0][1], data[0][2];
	//T data[1][0], data[1][1], data[1][2];
	//T data[2][0], data[2][1], data[2][2];
};

typedef Matrix33<float> Matrix33f;
typedef Matrix33<double> Matrix33d;
typedef Matrix33<int> Matrix33i;

#endif