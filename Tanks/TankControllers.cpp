#include "TankControllers.h"
#include "Math/Math.h"
#include "Tanks/Render/Scenes/TankGameScene.h"

void BulletMovement::init(Entity* entity, Scene* scene)
{
	entity->getTransform()->Scale = Vector3f(.4f, .4f, .4f);
	entity->getTransform()->lookAt(entity->getTransform()->Position + mDirection * 5);

	StaticLogger::instance.trace("{f} {f} {f}", mDirection.x, mDirection.y, mDirection.z);
}

void BulletMovement::update(Entity* entity, Scene* scene)
{
	//entity->getTransform()->Position += entity->getTransform()->Rotation.forward() * 
	entity->getTransform()->Position += mDirection *
		GameManager::getUpdateDeltaTime() * bulletSpeed;
}

void TankControlBase::init(Entity* entity, Scene* scene)
{

}

void TankControlBase::update(Entity* entity, Scene* scene)
{
	if (updateControl(entity, scene))
	{
		currentTireTrackCoolDown -= GameManager::getUpdateDeltaTime();

		if (currentTireTrackCoolDown <= 0)
		{
			TransformComponent trackPosition = *entity->getTransform();
			trackPosition.Position += trackPosition.Rotation.forward() * 2;
			mTireTracks.push_back(trackPosition);

			currentTireTrackCoolDown = tireTracksCoolDown;
		}
	}
}

void TankControlBase::shoot(Entity* entity, Scene* scene)
{
	TankGameScene* gameScene = static_cast<TankGameScene*>(scene);
	Camera3D* sceneCamera = gameScene->getCamera();

	// Move the player target.
	Vector2f mouseCoords((float)Mouse::getPosX(), (float)Mouse::getPosY());

	mouseCoords = GenMath::screenCoordsToGLCoords(mouseCoords,
		GameManager::getGameWindow()->getWidth(),
		GameManager::getGameWindow()->getHeight());

	Vector3f mouseWorldCoords = GenMath::unprojectScreenCoords(sceneCamera->getProjection(),
		sceneCamera->getViewMatrix(), mouseCoords);

	Vector3f toGroundVector = (sceneCamera->getTransform()->Position - mouseWorldCoords).retNormalized();
	float groundCollisionTValue = -(sceneCamera->getTransform()->Position.y - 1) / toGroundVector.y;
	Vector3f worldGroundPosition = sceneCamera->getTransform()->Position + toGroundVector * groundCollisionTValue;

	if (bulletsRemaining)
	{
		bulletsRemaining--;

		std::unique_ptr<Entity> bulletEntity =
			std::make_unique<RenderableEntity>(GameManager::Resources.MeshResources.getRegistry(MODEL_BULLET),
				GameManager::Resources.TextureResources.getRegistry(TEXTURE_BULLET),
				"Bullet");

		bulletEntity->getTransform()->Rotation = entity->getTransform()->Rotation;
		bulletEntity->getTransform()->Position = entity->getTransform()->Position;
		bulletEntity->getTransform()->Position.y += 1;
		bulletEntity->addComponent("Movement", 
			std::make_unique<BulletMovement>(
				(worldGroundPosition - bulletEntity->getTransform()->Position).retNormalized()));
		bulletEntity->init(scene);

		StaticLogger::instance.trace("{string}\n {string}", ((std::string)worldGroundPosition).c_str(),
			((std::string)bulletEntity->getTransform()->Position).c_str());


		GameManager::getScene()->addEntity(std::move(bulletEntity));
	}
}

PlayerTankControl::PlayerTankControl()
	:mMoveForward(Key::KEY_W),
	mMoveBackward(Key::KEY_S),
	mTurnLeft(Key::KEY_A),
	mTurnRight(Key::KEY_D),
	mShootBullet(Button::MOUSE_BUTTON_LEFT)
{
}

bool PlayerTankControl::updateControl(Entity* entity, Scene* scene)
{
	mMoveForward.update();
	mMoveBackward.update();
	mTurnLeft.update();
	mTurnRight.update();
	mShootBullet.update();

	bool rotating = false;
	bool moved = false;

	if (mTurnLeft)
	{
		entity->getTransform()->Rotation.rotate(entity->getTransform()->Rotation.up(), GameManager::getUpdateDeltaTime() * rotationSpeed);
		rotating = true;
	}

	if (mTurnRight)
	{
		entity->getTransform()->Rotation.rotate(entity->getTransform()->Rotation.up(), -GameManager::getUpdateDeltaTime() * rotationSpeed);
		rotating = true;
	}

	float currentSpeed = speed * (rotating ? speedWhileRotatingMultiplier : 1);

	if (mMoveForward)
	{
		moved = true;
		entity->getTransform()->Position +=
			entity->getTransform()->Rotation.forward() *
			(GameManager::getUpdateDeltaTime() * currentSpeed);
	}

	if (mMoveBackward)
	{
		moved = true;
		currentSpeed *= reverseSpeedMultiplier;
		entity->getTransform()->Position -=
			entity->getTransform()->Rotation.forward() *
			GameManager::getUpdateDeltaTime() * currentSpeed;
	}

	// Spawn a bullet at the tank position towards the mouse.
	// Project the mouse coordinates into the game world, then point the bullet towards
	// that position.
	if (mShootBullet)
	{
		shoot(entity, scene);
	}

	return moved || rotating;
}

bool Enemy1TankControl::updateControl(Entity* entity, Scene* scene)
{
	bool moved = true;
	entity->getTransform()->Position += entity->getTransform()->Rotation.forward() *
		GameManager::getUpdateDeltaTime() * speed;
	return moved;
}
