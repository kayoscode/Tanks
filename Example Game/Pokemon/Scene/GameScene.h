#pragma once
#include <vector>

#include "Engine/GameManager.h"
#include "Render Engine/Camera.h"
#include "Example Game/Pokemon/ResourceLoader.h"

/// <summary>
/// Game scene for the tank game.
/// <author>Bryce Young 1/25/2022</author>
/// </summary>
class GameScene : public Scene
{
public:
	GameScene();

	virtual void update();

	Camera3D* getCamera() { return mCamera; }

protected:
	void onInit();
	Camera3D* mCamera;
};
