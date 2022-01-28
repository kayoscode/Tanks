#include <memory>

#include "Math/Math.h"
#include "TankGameScene.h"
#include "Tanks/Render/Pipelines/SceneRenderPipeline.h"
#include "Engine/GameManager.h"

TankGameScene::TankGameScene()
	:Scene(std::make_unique<RenderMainScenePipeline>())
{
}

void TankGameScene::onInit()
{
    // Create camera.
    std::unique_ptr<Camera3D> sceneCamera = std::make_unique<Camera3D>();
	sceneCamera->createProjectionMatrix(1.5,
		GameManager::getGameWindow()->getAspectRatio(),
		.01f, 1000);

    sceneCamera->getTransform()->Position.y = 30;
    sceneCamera->getTransform()->Position.z = 5;
    sceneCamera->getTransform()->lookAt(Vector3f(0, 0, 0));

    addEntity(std::move(sceneCamera));

    std::unique_ptr<RenderableEntity> playerEntity =
        std::make_unique<RenderableEntity>(GameManager::Resources.MeshResources.getRegistry(MODEL_TANK),
            GameManager::Resources.TextureResources.getRegistry(TEXTURE_PLAYER),
            "Player");
    playerEntity->getTransform()->Scale = Vector3f(.5, .5, .5);
    playerEntity->addComponent("Movement", std::make_unique<TankControl>());

    addEntity(std::move(playerEntity));

    // Add the floor background for perspective.
    std::unique_ptr<RenderableEntity> floorEntity =
        std::make_unique<RenderableEntity>(
            GameManager::Resources.MeshResources.getRegistry(MODEL_FLAT_SQUARE),
            GameManager::Resources.FramebufferResources.getRegistry(FRAMEBUFFER_BG)->getColorTexture(),
            "Floor");
    floorEntity->getTransform()->Scale = Vector3f(40, 1, 20);
    addEntity(std::move(floorEntity));
}

void TankGameScene::update()
{
    for (int i = 0; i < mEntities.size(); i++)
    {
        mEntities[i]->update();
    }
}