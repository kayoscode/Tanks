#include "ModelShader.h"
#include "Engine/GameManager.h"

ModelShader::ModelShader()
    :ShaderProgram({"position", "texCoord", "normal"})
{
    loadShaders(GameManager::resPath() + "shaders/ModelShader.vert",
        GameManager::resPath() + "shaders/ModelShader.frag");
}

void ModelShader::setUniformLocations() 
{
    locationProjectionMatrix = getUniformLocation("projectionMatrix");
    locationViewMatrix = getUniformLocation("viewMatrix");
    locationModelMatrix = getUniformLocation("modelMatrix");
    locationDiffuseTexture = getUniformLocation("diffuseTexture");
    locationLightPos = getUniformLocation("lightPos");
}

void ModelShader::loadLightPosition(const Vector3f& lightPos) 
{
    loadUniformVec3f(locationLightPos, lightPos);
}

void ModelShader::loadCamera(const Matrix44f& viewMatrix) 
{
    loadMatrix44f(locationViewMatrix, viewMatrix);
}

void ModelShader::loadCameraProjection(const Matrix44f& projection) 
{
    loadMatrix44f(locationProjectionMatrix, projection);
}

void ModelShader::loadModelMatrix(const Matrix44f& modelMatrix) 
{
    loadMatrix44f(locationModelMatrix, modelMatrix);
}

void ModelShader::loadDiffuseTexture(int textureIndex) 
{
    loadUniformi(locationDiffuseTexture, textureIndex);
}