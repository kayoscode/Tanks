#include "GUIShader.h"

GUIShader::GUIShader() 
    :ShaderProgram({"position"})
{
}

GUIShader::~GUIShader() {

}

void GUIShader::setUniformLocations() {
    locationPosition = getUniformLocation("pos");
    locationScale = getUniformLocation("scale");
    locationTexture = getUniformLocation("guiTexture");
}

void GUIShader::loadTransformVars(const Vector2f& pos, const Vector2f& scale) {
    loadUniformVec2f(locationPosition, pos);
    loadUniformVec2f(locationScale, scale);
}

void GUIShader::loadTexture(int textureIndex) {
    loadUniformi(locationTexture, textureIndex);
}