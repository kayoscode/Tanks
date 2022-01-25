#include <vector>
#include <string>

#include "Engine/GameManager.h"
#include "Logger/StaticLogger.h"
#include "Serializers/OBJ Serializer/ModelLoader.h"
#include "Render/Shaders/ModelShader.h"
#include "Render/Pipelines/SceneRenderPipeline.h"

int main()
{
	GameManager::setResPath("res/");

	// Create and set scene.
	std::unique_ptr<RenderPipeline> mainSceneRenderPipeline =
		std::make_unique<RenderMainScenePipeline>();

	std::unique_ptr<Scene> mainScene = std::make_unique<Scene>(std::move(mainSceneRenderPipeline));
	GameManager::setScene(std::move(mainScene));

	GameManager::createWindow(GameManager::resPath() + "settings.json");

	GameManager::executeInputLoop();

	StaticLogger::instance.trace("Total program runtime (seconds): [ts]");

	return 0;
}