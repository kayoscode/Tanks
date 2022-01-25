#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "Math/Math.h"

/**
 * Class representing a camera
 * All its derivatives have details which are used to calculate the 
 * projection and view matrix which are ultimately what renders the scene
 * @author Bryce Young 5/30/2021
 * */
class Camera {
    public:
        Camera() :
            projectionMatrix(),
            viewMatrix(),
            aspectRatio(0)
        {
        }

        ~Camera() {

        }

        /**
         * Overridable function to calculate the view matrix
         * using internal representations of rotations, and positions
         * */
        virtual void calculateViewMatrix() {
        }

        inline const Matrix44f& getProjection() {
            return projectionMatrix;
        }

        inline const Matrix44f& getViewMatrix() {
            return viewMatrix;
        }

    protected:
        Matrix44f projectionMatrix;
        Matrix44f viewMatrix;
        float aspectRatio;
};

/**
 * A 2d camera using an orthographic projection
 * TODO when doing shadows
 * */
class Camera2D : public Camera { 
    public:
    protected:
    private:
};

/**
 * Class containing a 3D camera
 * FOV, near and far make up the projection plane which calculates the projection matrix
 * @author Bryce Young 5/30/2021
 * */
class Camera3D : public Camera {
    public:
        inline Vector3f& getPosition() {
            return pos;
        }

        inline Quaternionf& getRotation(){
            return rotation;
        }

        /**
         * Calculates the view matrix from a rotation and position
         * */
        void calculateViewMatrix() {
            viewMatrix = rotation.toMatrix();
            viewMatrix.translate(pos);
            viewMatrix.invert();
        }

        /**
         * Calculates projection matrix based on all necessary variables and sets camera internals
         * */
        void createProjectionMatrix(float fov, float aspectRatio, float nearPlan, float farPlane);

        inline float getFOV() {
            return fov;
        }

        inline float getNearPlane() {
            return zNear;
        }

        inline float getFarPlane() {
            return zFar;
        }

    protected:
        float fov;
        float zNear;
        float zFar;
        Vector3f pos;
        Quaternionf rotation;
};

#endif