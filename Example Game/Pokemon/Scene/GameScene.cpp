#include <memory>

#include "Math/Math.h"
#include "GameScene.h"
#include "Example Game/Pokemon/Render/SceneRenderPipeline.h"
#include "Engine/GameManager.h"

GameScene::GameScene()
	:Scene(std::make_unique<RenderMainScenePipeline>()),
    mCamera(nullptr)
{
}

void GameScene::onInit()
{
    // Create camera.
    std::unique_ptr<Camera3D> sceneCamera = std::make_unique<Camera3D>();
    mCamera = sceneCamera.get();
	sceneCamera->createProjectionMatrix(1.5,
		GameManager::getGameWindow()->getAspectRatio(),
		.5f, 100);

    sceneCamera->getTransform()->Position.y = 55;
    sceneCamera->getTransform()->Position.z = 15;
    sceneCamera->getTransform()->lookAt(Vector3f(0, 0, 0));

    addEntity(std::move(sceneCamera));
}

void GameScene::update()
{
    for (int i = 0; i < mEntities.size(); i++)
    {
        mEntities[i]->update(this);
    }
}