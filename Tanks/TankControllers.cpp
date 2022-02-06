#include "TankControllers.h"
#include "Math/Math.h"
#include "Tanks/Render/Scenes/TankGameScene.h"

void BulletMovement::init(Entity* entity, Scene* scene)
{
	entity->getTransform()->Scale = Vector3f(.4f, .4f, .4f);
	entity->getTransform()->lookAt(entity->getTransform()->Position + mDirection * 5);
}

void BulletMovement::update(Entity* entity, Scene* scene)
{
	//entity->getTransform()->Position += entity->getTransform()->Rotation.forward() * 
	entity->getTransform()->Position += mDirection *
		GameManager::getUpdateDeltaTime() * bulletSpeed;
}

void TankControlBase::init(Entity* entity, Scene* scene)
{
	mPlayerEntity = scene->getEntityWithTag("Player");
}

void TankControlBase::update(Entity* entity, Scene* scene)
{
	if (currentShootCooldown > 0)
	{
		currentShootCooldown -= GameManager::getUpdateDeltaTime();
	}

	float currentSpeed = speed;

	if (updateControl(entity, scene))
	{
		if (mCurrentTurnFactor < 1)
		{
			mCurrentTurnFactor += rotationSpeed * GameManager::getUpdateDeltaTime();
			mCurrentTurnFactor = std::fminf(mCurrentTurnFactor, 1);

			entity->getTransform()->Rotation = Quaternionf::slerp(mRotationStartingTurn,
				mRotationLookDirection,
				mCurrentTurnFactor);
		}

		if (currentShootMoveCooldown <= 0)
		{
			entity->getTransform()->Position +=
				entity->getTransform()->Rotation.forward() * currentSpeed * GameManager::getUpdateDeltaTime();
			currentTireTrackCoolDown -= GameManager::getUpdateDeltaTime();

			if (currentTireTrackCoolDown <= 0)
			{
				TransformComponent trackPosition = *entity->getTransform();
				trackPosition.Position += trackPosition.Rotation.forward() * 2;
				mTireTracks.push_back(trackPosition);

				currentTireTrackCoolDown = tireTracksCoolDown;
			}
		}
		else
		{
			currentShootMoveCooldown -= GameManager::getUpdateDeltaTime();
		}
	}
}

void TankControlBase::setMoveDirection(Entity* entity, Scene* scene, const Quaternionf& newRotation)
{
	//if (newRotation.x != mRotationLookDirection.x || newRotation.y != mRotationLookDirection.y ||
		//newRotation.z != mRotationLookDirection.z || newRotation.w != mRotationLookDirection.w)
	//{
		mCurrentTurnFactor = 0;
		mRotationStartingTurn = entity->getTransform()->Rotation;
		mRotationLookDirection = newRotation;
	//}
}

void TankControlBase::shoot(Entity* entity, Scene* scene, const Vector3f& worldGroundPosition)
{

	if (currentShootCooldown <= 0 && bulletsRemaining)
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

		GameManager::getScene()->addEntity(std::move(bulletEntity));

		currentShootMoveCooldown = shootMoveCooldown;
		currentShootCooldown = shootCooldown;
	}
}

PlayerTankControl::PlayerTankControl()
	: mShootBullet(Button::MOUSE_BUTTON_LEFT),
	mUpDir(Key::KEY_W),
	mDownDir(Key::KEY_S),
	mLeftDir(Key::KEY_A),
	mRightDir(Key::KEY_D),
	mUpRot(),
	mDownRot(),
	mRightRot(),
	mLeftRot()
{
	mUpRot.rotate(Vector3f(0, 1, 0), 0);
	mDownRot.rotate(Vector3f(0, 1, 0), GenMath::toRadians(180));
	mLeftRot.rotate(Vector3f(0, 1, 0), GenMath::toRadians(90));
	mRightRot.rotate(Vector3f(0, 1, 0), GenMath::toRadians(270));
}

Vector3f PlayerTankControl::getCurrentWorldMouseCoords(Scene* scene)
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

	return worldGroundPosition;
}

bool PlayerTankControl::updateControl(Entity* entity, Scene* scene)
{
	mShootBullet.update();
	mUpDir.update();
	mDownDir.update();
	mLeftDir.update();
	mRightDir.update();

	bool moved = false;
	Quaternionf moveDirection;

	// Move the player towards the selected move vector.
	if (mRightDir)
	{
		moveDirection = mRightRot;
		moved = true;
	}
	else if (mLeftDir)
	{
		moveDirection = mLeftRot;
		moved = true;
	}

	if (mUpDir)
	{
		if (moved)
		{
			moveDirection = Quaternionf::slerp(mUpRot, moveDirection, .5f);
		}
		else
		{
			moveDirection = mUpRot;
		}

		moved = true;
	}
	else if (mDownDir)
	{
		if (moved)
		{
			moveDirection = Quaternionf::slerp(mDownRot, moveDirection, .5f);
		}
		else
		{
			moveDirection = mDownRot;
		}

		moved = true;
	}

	if (moved)
	{
		setMoveDirection(entity, scene, moveDirection);
	}

	// Spawn a bullet at the tank position towards the mouse.
	// Project the mouse coordinates into the game world, then point the bullet towards
	// that position.
	if (mShootBullet)
	{
		shoot(entity, scene, getCurrentWorldMouseCoords(scene));
	}

	return moved;
}

bool Enemy1TankControl::updateControl(Entity* entity, Scene* scene)
{
	bool moved = false;

	Quaternionf movementDirection = entity->getTransform()->
		getLookAtRotation(mPlayerEntity->getTransform()->Position);

	//setMoveDirection(entity, scene, movementDirection);

	//shoot(entity, scene, mPlayerEntity->getTransform()->Position + Vector3f(0, 1, 0));

	return moved;
}
