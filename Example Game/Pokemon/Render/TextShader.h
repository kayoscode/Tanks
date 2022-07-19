#pragma once

#include "Render Engine/Shader.h"
#include "Math/Math.h"

class GUITextShader : public ShaderProgram {
	public:
		GUITextShader() 
			: ShaderProgram({ "position", "texCoords"} )
		{
		}

		~GUITextShader() {

		}

		void setUniformLocations() 
		{
			locationTranslation = getUniformLocation("translation");
			locationTextColor = getUniformLocation("textColor");
			locationTextureAtlas = getUniformLocation("textureAtlas");
		}

		void loadTextColor(float r, float g, float b, float a = 1) 
		{
			loadUniformVec4f(locationTextColor, Vector4f(r, g, b, a));
		}

		void loadTranslation(const Vector2f& translation) 
		{
			loadUniformVec2f(locationTranslation, translation);
		}

		void loadTextureAtlas(int textureUnit) 
		{
			loadUniformi(locationTextureAtlas, textureUnit);
		}

	private:
		int locationTranslation;
		int locationTextureAtlas;
		int locationTextColor;
};
