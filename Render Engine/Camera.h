#pragma once

#include "../Math/Math.h"

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

        virtual ~Camera() 
        {
        }

        /**
         * Overridable function to calculate the view matrix
         * using internal representations of rotations, and positions
         * */
        virtual void calculateViewMatrix() {
        }

        /// <summary>
        /// Returns the projection matrix.
        /// </summary>
        /// <returns></returns>
        inline const Matrix44f& getProjection() {
            return projectionMatrix;
        }

        /// <summary>
        /// Returns the view matrix.
        /// </summary>
        /// <returns></returns>
        inline const Matrix44f& getViewMatrix() {
            return viewMatrix;
        }

    protected:
        Matrix44f projectionMatrix;
        Matrix44f viewMatrix;
        float aspectRatio;
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

        /// <summary>
        /// Calculates the view matrix from a rotation and position.
        /// </summary>
        void calculateViewMatrix() {
            viewMatrix = rotation.toMatrix();
            viewMatrix.translate(pos);
            viewMatrix.invert();
        }

        /// <summary>
        /// Calculates projection matrix based on all necessary variables and sets camera internals.
        /// </summary>
        /// <param name="fov"></param>
        /// <param name="aspectRatio"></param>
        /// <param name="nearPlan"></param>
        /// <param name="farPlane"></param>
        void createProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

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