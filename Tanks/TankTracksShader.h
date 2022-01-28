#pragma once

#include "Engine/GameManager.h"
#include "Render Engine/Shader.h"
#include "Math/Math.h"

class TextureCombineShader : public ShaderProgram
{
public:
	TextureCombineShader()
		:ShaderProgram({ "position" })
	{
		loadShaders(GameManager::resPath() + "shaders/TankBG/TextureCombine.vert",
			GameManager::resPath() + "shaders/TankBG/TextureCombine.frag");
	}

	void setUniformLocations()
	{
		locationBgTexture = getUniformLocation("backgroundTexture");
		locationTankTracksTexture = getUniformLocation("tankTracksTexture");
	}

	void loadTextureLocations(int bgTexture, int tankTracksTexture)
	{
		loadUniformi(locationBgTexture, bgTexture);
		loadUniformi(locationTankTracksTexture, tankTracksTexture);
	}

protected:
	int locationBgTexture;
	int locationTankTracksTexture;
};

/// <summary>
/// Class responsible for 
/// </summary>
class TireTracksShader : public ShaderProgram
{
public:
	TireTracksShader()
		:ShaderProgram({ "position", "texCoord", "normal"})
	{
		loadShaders(GameManager::resPath() + "shaders/TankBG/TireTrack.vert",
			GameManager::resPath() + "shaders/TankBG/TireTrack.frag");
	}

	void setUniformLocations()
	{
		locationModelMatrix = getUniformLocation("modelMatrix");
		locationTankTracksTexture = getUniformLocation("tankTracksTexture");
	}

	void loadModelMatrix(const Matrix44f& matrix)
	{
		loadMatrix44f(locationModelMatrix, matrix);
	}

	void loadTextureTankTracks(int tankTracksTexture)
	{
		loadUniformi(locationTankTracksTexture, tankTracksTexture);
	}

protected:
	int locationModelMatrix;
	int locationTankTracksTexture;
};
