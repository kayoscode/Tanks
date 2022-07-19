#include <vector>
#include <string>

#include "Engine/GameManager.h"
#include "Scene/GameScene.h"
#include "Logger/StaticLogger.h"
#include "Serializers/OBJ Serializer/ModelLoader.h"
#include "Render/ModelShader.h"
#include "Render/SceneRenderPipeline.h"
#include "ResourceLoader.h"
#include "Sim.h"

#include "Types.h"

using namespace Pkmn;

int main()
{
	/**
	GameManager::setResPath("res/");
	GameManager::setScene(std::make_unique<GameScene>());
	GameManager::createWindow(GameManager::resPath("settings.json"));

	ResourceLoader loader;
	GameManager::loadResources(loader);
	GameManager::start();

	*/

	BattleSimSingleBattle battleSim;
	StaticLogger::instance.trace("Total program runtime (seconds): [ts]");

	return 0;
}