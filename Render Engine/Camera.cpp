#include "Camera.h"
#include <math.h>

void Camera3D::createProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane) {
    // OLD projection matrix calculation.
    /**
    this->fov = fov;
    this->aspectRatio = aspect;
    this->zNear = nearPlane;
    this->zFar = farPlane;

    projectionMatrix.setIdentity();
    float tanhfov = (float)tanf(fov / 2);

    projectionMatrix.data[0][0] = 1 / (aspect * tanhfov);
    projectionMatrix.data[1][1] = 1 / (tanhfov);
    projectionMatrix.data[2][2] = -(zNear + zFar) / (zFar - zNear);
    projectionMatrix.data[2][3] = -1;
    projectionMatrix.data[3][2] = -(2 * zFar * zNear) / (zFar - zNear);
    */

	float scaleY = (float)(1.0f / tan(fov / 2) * aspect);
	float scaleX = (float)scaleY / aspect;
	float frustLen = farPlane - nearPlane;

	projectionMatrix.setIdentity();
	projectionMatrix.data[0][0] = scaleX;
	projectionMatrix.data[2][3] = -1;
	projectionMatrix.data[2][2] = -((farPlane + nearPlane) / frustLen);
	projectionMatrix.data[3][3] = 0;
	projectionMatrix.data[3][2] = -((2 * nearPlane * farPlane) / frustLen);
	projectionMatrix.data[1][1] = scaleY;
}