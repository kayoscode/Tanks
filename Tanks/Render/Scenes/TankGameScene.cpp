#include <memory>

#include "Math/Math.h"
#include "TankGameScene.h"
#include "Tanks/Render/Pipelines/SceneRenderPipeline.h"
#include "Engine/GameManager.h"

#include "Engine/Input.h"

class TankControl : public UpdateLoop
{
public:
    TankControl()
        :mMoveForward(Key::KEY_W),
        mMoveBackward(Key::KEY_S),
        mTurnLeft(Key::KEY_A),
        mTurnRight(Key::KEY_D)
    {}

    void init(Entity* entity) {} 

    void update(Entity* entity)
    {
        mMoveForward.update();
        mMoveBackward.update();
        mTurnLeft.update();
        mTurnRight.update();

        bool rotating = false;

        if (mTurnLeft)
        {
            entity->getTransform()->Rotation.rotate(Vector3f(0, 1, 0), GameManager::getUpdateDeltaTime() * rotationSpeed);
            rotating = true;
        }

        if (mTurnRight)
        {
            entity->getTransform()->Rotation.rotate(Vector3f(0, 1, 0), -GameManager::getUpdateDeltaTime() * rotationSpeed);
            rotating = true;
        }

        float currentSpeed = speed * (rotating? speedWhileRotatingMultiplier : 1);

        if (mMoveForward)
        {
            entity->getTransform()->Position +=
                entity->getTransform()->Rotation.forward() * GameManager::getUpdateDeltaTime() * currentSpeed;
        }

        if (mMoveBackward)
        {
            currentSpeed *= reverseSpeedMultiplier;
            entity->getTransform()->Position -=
                entity->getTransform()->Rotation.forward() * GameManager::getUpdateDeltaTime() * currentSpeed;
        }
    }

private:
    KeyDownInput mMoveForward;
    KeyDownInput mMoveBackward;
    KeyDownInput mTurnLeft;
    KeyDownInput mTurnRight;

    float speed = 7;
    float rotationSpeed = 3;
    float speedWhileRotatingMultiplier = 0.7f;
    float reverseSpeedMultiplier = .5f;
};

TankGameScene::TankGameScene()
	:Scene(std::make_unique<RenderMainScenePipeline>())
{
}

void TankGameScene::onInit()
{
    // Create camera.
    std::unique_ptr<Camera3D> sceneCamera = std::make_unique<Camera3D>();
	sceneCamera->createProjectionMatrix(1.0,
		GameManager::getGameWindow()->getAspectRatio(),
		.01f, 1000);

    sceneCamera->getTransform()->Position.y = 40;
    sceneCamera->getTransform()->Position.z = 5;
    sceneCamera->getTransform()->lookAt(Vector3f(0, 0, 0));

    addEntity(std::move(sceneCamera));

    std::unique_ptr<RenderableEntity> playerEntity =
        std::make_unique<RenderableEntity>(GameManager::Resources.MeshResources.getRegistry("Tank"),
            GameManager::Resources.TextureResources.getRegistry("Player"),
            "Player");
    playerEntity->getTransform()->Scale = Vector3f(.5, .5, .5);
    playerEntity->addComponent("Movement", std::make_unique<TankControl>());

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