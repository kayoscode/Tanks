#ifndef INCLUDE_MATRIX22_H
#define INCLUDE_MATRIX22_H

#include <string>
#include <sstream>

template<class T>
struct Matrix22 {
    public:
        /**
         * constructor
         * */
        Matrix22(T m00 = 1, T m01 = 0, T m10 = 0, T m11 = 1)
        {
            data[0][0] = m00;
            data[1][0] = m10;
            data[0][1] = m01;
            data[1][1] = m11;
        }

        /**
         * copy constructor
         * */
        Matrix22(const Matrix22<T>& mat)
        {
            data[0][0] = mat.data[0][0];
            data[1][0] = mat.data[1][0];
            data[0][1] = mat.data[0][1];
            data[1][1] = mat.data[1][1];
        }

        /**
         * assignment operator
         * */
        Matrix22<T>& operator=(const Matrix22<T>& mat){
            data[0][0] = mat.data[0][0];
            data[0][1] = mat.data[0][1];
            data[1][0] = mat.data[1][0];
            data[1][1] = mat.data[1][1];

            return *this;
        }

        /**
         * addition operator
         * */
        Matrix22<T> operator+(const Matrix22<T>& mat){
            Matrix22<T> ret;

            ret.data[0][0] = data[0][0] + mat.data[0][0];
            ret.data[0][1] = data[0][1] + mat.data[0][1];
            ret.data[1][0] = data[1][0] + mat.data[1][0];
            ret.data[1][1] = data[1][1] + mat.data[1][1];

            return ret;
        }

        /**
         * addition operator
         * */
        Matrix22<T>& operator+=(const Matrix22<T>& mat){
            data[0][0] += mat.data[0][0];
            data[0][1] += mat.data[0][1];
            data[0][1] += mat.data[1][0];
            data[1][1] += mat.data[1][1];

            return *this;
        }

        /**
         * subtraction operator
         * */
        Matrix22<T> operator-(const Matrix22<T>& mat){
            Matrix22<T> ret;

            ret.data[0][0] = data[0][0] - mat.data[0][0];
            ret.data[0][1] = data[0][1] - mat.data[0][1];
            ret.data[1][0] = data[1][0] - mat.data[1][0];
            ret.data[1][1] = data[1][1] - mat.data[1][1];

            return ret;
        }

        /**
         * subtracts a matrix
         * */
        Matrix22<T>& operator-=(const Matrix22<T>& mat){
            data[0][0] -= mat.data[0][0];
            data[0][1] -= mat.data[0][1];
            data[0][1] -= mat.data[1][0];
            data[1][1] -= mat.data[1][1];

            return *this;
        }

        /**
         * multiply by a matrix
         * */
        Matrix22<T> operator*(const Matrix22<T>& mat){
            Matrix22<T> ret;

            T m00 = this->data[0][0] * mat.data[0][0] + this->data[1][0] * mat.data[0][1];
            T m01 = this->data[0][1] * mat.data[0][0] + this->data[1][1] * mat.data[0][1];
            T m10 = this->data[0][0] * mat.data[1][0] + this->data[1][0] * mat.data[1][1];
            T m11 = this->data[0][1] * mat.data[1][0] + this->data[1][1] * mat.data[1][1];

            ret.data[0][0] = m00;
            ret.data[0][1] = m01;
            ret.data[1][0] = m10;
            ret.data[1][1] = m11;
        
            return ret;
        }

        /**
         * multiply by another 2x2 matrix
         * */
        Matrix22<T> operator*=(const Matrix22<T>& mat){
            T m00 = this->data[0][0] * mat.data[0][0] + this->data[1][0] * mat.data[0][1];
            T m01 = this->data[0][1] * mat.data[0][0] + this->data[1][1] * mat.data[0][1];
            T m10 = this->data[0][0] * mat.data[1][0] + this->data[1][0] * mat.data[1][1];
            T m11 = this->data[0][1] * mat.data[1][0] + this->data[1][1] * mat.data[1][1];

            this->data[0][0] = m00;
            this->data[0][1] = m01;
            this->data[1][0] = m10;
            this->data[1][1] = m11;

            return *this;
        }

        /**
         * TODO: transform to vector2
         * */

        /**
         * gets the matrix's transpose
         * */
        Matrix22<T>& transpose(){
            T m01 = this->data[1][0];
            T m10 = this->data[0][1];

            this->data[0][1] = m01;
            this->data[1][0] = m10;

            return *this;
        }

        /**
         * inverts the matrix
         * */
        Matrix22<T>& invert(){
            //set to the determinant
            T determinant = det();

            if(determinant != 0) {
                T determinant_inv = ((T)1)/determinant;

                T t00 =  this->data[1][1]*determinant_inv;
                T t01 = -this->data[0][1]*determinant_inv;
                T t11 =  this->data[0][0]*determinant_inv;
                T t10 = -this->data[1][0]*determinant_inv;

                this->data[0][0] = t00;
                this->data[0][1] = t01;
                this->data[1][0] = t10;
                this->data[1][1] = t11;
            }

            return *this;
        }

        /**
         * sets the matrix to identity
         * */
        Matrix22<T>& setIdentity(){
            data[0][0] = 1;
            data[0][1] = 0;
            data[1][0] = 0;
            data[1][1] = 1;

            return *this;
        }

        /**
         * negates the matrix
         * */
        Matrix22<T>& negate(){
            data[0][0] = -data[0][0];
            data[0][1] = -data[0][1];
            data[1][0] = -data[1][0];
            data[1][1] = -data[1][1];

            return *this;
        }

        /**
         * sets the matrix to 0
         * */
        Matrix22<T>& setZero(){
            data[0][0] = 0;
            data[0][1] = 0;
            data[1][0] = 0;
            data[1][1] = 0;

            return *this;
        }

        /**
         * gets the determinant of the 2x2 matrix
         * */
        T det(){
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }

        /**
         * converts the matrix to a printable string
         * */
        operator std::string(){
            char buff[100];
            snprintf(buff, sizeof(buff), "\n[%4.4f] [%4.4f]\n[%4.4f] [%4.4f]", data[0][0], data[0][1], data[1][0], data[1][1]);

            return std::string(buff);
        }

        T data[2][2];
        //T data[0][0], data[0][1];
        //T data[1][0], data[1][1];
};

typedef Matrix22<float> Matrix22f;
typedef Matrix22<double> Matrix22d;
typedef Matrix22<int> Matrix22i;

#endif