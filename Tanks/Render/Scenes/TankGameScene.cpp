#include <memory>

#include "TankGameScene.h"
#include "Tanks/Render/Pipelines/SceneRenderPipeline.h"
#include "Engine/GameManager.h"

class PlayerSpin : public UpdateLoop
{
public:
	void init(Entity* object) 
	{ 
	}

	void update(Entity* object)
	{
		object->getTransform()->Rotation.rotate(Vector3f(0, 1, 0), GameManager::getUpdateDeltaTime());
	}

private:
};

TankGameScene::TankGameScene()
	:Scene(std::make_unique<RenderMainScenePipeline>())
{
}

void TankGameScene::onInit()
{
    std::unique_ptr<RenderableEntity> playerEntity =
        std::make_unique<RenderableEntity>(GameManager::Resources.MeshResources.getRegistry("Tank"),
            GameManager::Resources.TextureResources.getRegistry("Player"),
            "Player");

    playerEntity->getTransform()->Position.z = -7;
    playerEntity->getTransform()->Position.y = -3;

    playerEntity->addComponent("SpinPlayer", std::make_unique<PlayerSpin>());

    addEntity(std::move(playerEntity));
}

void TankGameScene::update()
{
	// Update each entity.
	for (auto entity = mEntities.begin(); entity != mEntities.end(); ++entity)
	{
		entity->get()->update();
	}
}