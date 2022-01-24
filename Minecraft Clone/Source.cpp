
#include "../Engine/GameManager.h"
#include "../Logger/StaticLogger.h"

int main()
{
	if (GameManager::getPlatform().os == OperatingSystem::LINUX || 
		GameManager::getPlatform().os == OperatingSystem::MAC) {
		GameManager::setResPath("../res/");
		GameManager::createWindow(GameManager::resPath() + "settings.json");
	}
	else if (GameManager::getPlatform().os == OperatingSystem::WINDOWS) {
		GameManager::setResPath("res/");
		GameManager::createWindow(GameManager::resPath() + "settings.json");
	}

	GameManager::executeGameLoop();

	GameManager::cleanupResources();
	StaticLogger::instance.trace("Total program runtime (seconds): [ts]");

	return 0;
	return 0;
}