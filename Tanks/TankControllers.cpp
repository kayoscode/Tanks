#include "TankControllers.h"
#include "Math/Math.h"

void BulletMovement::init(Entity* entity)
{
	entity->getTransform()->Scale = Vector3f(.4f, .4f, .4f);
}

void BulletMovement::update(Entity* entity)
{
	entity->getTransform()->Position += entity->getTransform()->Rotation.forward() * 
		GameManager::getUpdateDeltaTime() * bulletSpeed;
}

void TankControlBase::init(Entity* entity)
{

}

void TankControlBase::update(Entity* entity)
{
	if (updateControl(entity))
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

void TankControlBase::shoot(Entity* entity)
{
	if (bulletsRemaining)
	{
		bulletsRemaining--;

		std::unique_ptr<Entity> bulletEntity =
			std::make_unique<RenderableEntity>(GameManager::Resources.MeshResources.getRegistry(MODEL_BULLET),
				GameManager::Resources.TextureResources.getRegistry(TEXTURE_BULLET),
				"Bullet");

		bulletEntity->getTransform()->Rotation = entity->getTransform()->Rotation;
		bulletEntity->getTransform()->Position = entity->getTransform()->Position +
			(entity->getTransform()->Rotation.forward().normalize() * 2);
		bulletEntity->getTransform()->Position.y += 1;
		bulletEntity->addComponent("Movement", std::make_unique<BulletMovement>());

		GameManager::getScene()->addEntity(std::move(bulletEntity));
	}
}

PlayerTankControl::PlayerTankControl()
	:mMoveForward(Key::KEY_W),
	mMoveBackward(Key::KEY_S),
	mTurnLeft(Key::KEY_A),
	mTurnRight(Key::KEY_D),
	mShootBullet(Button::MOUSE_BUTTON_LEFT),
	mUpdateBulletTracker()
{
}

bool PlayerTankControl::updateControl(Entity* entity)
{
	mMoveForward.update();
	mMoveBackward.update();
	mTurnLeft.update();
	mTurnRight.update();
	mShootBullet.update();
	mUpdateBulletTracker.update();

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

	if (mUpdateBulletTracker)
	{
		Vector2f mouseCoords(Mouse::getPosX(), Mouse::getPosY());

		mouseCoords = GenMath::screenCoordsToGLCoords(mouseCoords,
			GameManager::getGameWindow()->getWidth(),
			GameManager::getGameWindow()->getHeight());
	}

	// Spawn a bullet at the tank position towards the mouse.
	// Project the mouse coordinates into the game world, then point the bullet towards
	// that position.
	if (mShootBullet)
	{
		shoot(entity);
	}

	return moved || rotating;
}

bool Enemy1TankControl::updateControl(Entity* entity)
{
	bool moved = true;
	entity->getTransform()->Position += entity->getTransform()->Rotation.forward() * 
		GameManager::getUpdateDeltaTime() * speed;
	return moved;
}
