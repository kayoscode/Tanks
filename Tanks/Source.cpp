#include <vector>
#include <string>

#include "Engine/GameManager.h"
#include "GameScene.h"
#include "Logger/StaticLogger.h"
#include "Serializers/OBJ Serializer/ModelLoader.h"
#include "Render/Shaders/ModelShader.h"
#include "Render/Pipelines/SceneRenderPipeline.h"

int main()
{
	GameManager::setResPath("res/");
	GameManager::setScene(std::make_unique<GameScene>());
	GameManager::createWindow(GameManager::resPath() + "settings.json");

	GameManager::executeInputLoop();

	StaticLogger::instance.trace("Total program runtime (seconds): [ts]");

	return 0;
}