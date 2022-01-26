#pragma once

#include "Render Engine/Shader.h"
#include "Math/Math.h"

class ModelShader : public ShaderProgram {
    public:
        ModelShader();

        ~ModelShader() 
        {
        }

        void setUniformLocations();

        void loadCameraViewMatrix(const Matrix44f& viewMatrix);
        void loadCameraProjection(const Matrix44f& projectionMatrix);
        void loadModelMatrix(const Matrix44f& modelMatrix);
        void loadDiffuseTexture(int textureIndex);
        void loadLightPosition(const Vector3f& lightPos);

    protected:
        int locationProjectionMatrix;
        int locationViewMatrix;
        int locationModelMatrix;
        int locationDiffuseTexture;
        int locationLightPos;
};