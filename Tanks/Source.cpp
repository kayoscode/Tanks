#include <vector>
#include <string>

#include "Engine/GameManager.h"
#include "Render/Scenes/TankGameScene.h"
#include "Logger/StaticLogger.h"
#include "Serializers/OBJ Serializer/ModelLoader.h"
#include "Render/Shaders/ModelShader.h"
#include "Render/Pipelines/SceneRenderPipeline.h"
#include "ResourceLoader.h"

int main()
{
	GameManager::setResPath("res/");
	GameManager::setScene(std::make_unique<TankGameScene>());
	GameManager::createWindow(GameManager::resPath() + "settings.json");

	ResourceLoader loader;
	GameManager::loadResources(loader);
	GameManager::start();

	StaticLogger::instance.trace("Total program runtime (seconds): [ts]");

	return 0;
}