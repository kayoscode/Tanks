#pragma once
#include <vector>

#include "Engine/GameManager.h"
#include "Render Engine/Scene.h"
#include "Render Engine/Camera.h"

#include "Tanks/TankControllers.h"

/// <summary>
/// Game scene for the tank game.
/// <author>Bryce Young 1/25/2022</author>
/// </summary>
class TankGameScene : public Scene
{
public:
	TankGameScene();

	virtual void update();

protected:
	void onInit();
};
