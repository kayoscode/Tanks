#pragma once
#include <vector>

#include "Engine/GameManager.h"
#include "Render Engine/Scene.h"
#include "Render Engine/Camera.h"

#include "Engine/Input.h"
#include "Tanks/ResourceLoader.h"

class BulletMovement : public UpdateLoop
{
    void init(Entity* entity)
    {
        entity->getTransform()->Scale = Vector3f(.4f, .4f, .4f);

    }

    void update(Entity* entity)
    {
        entity->getTransform()->Position += entity->getTransform()->Rotation.forward() * 
            GameManager::getUpdateDeltaTime() * bulletSpeed;
    }

private:
    float bulletSpeed = 25;
};

class TankControl : public UpdateLoop
{
public:
    TankControl()
        :mMoveForward(Key::KEY_W),
        mMoveBackward(Key::KEY_S),
        mTurnLeft(Key::KEY_A),
        mTurnRight(Key::KEY_D),
        mShootBullet(Button::MOUSE_BUTTON_LEFT)
    {}

    void init(Entity* entity) 
    {
    } 

    void update(Entity* entity)
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

        float currentSpeed = speed * (rotating? speedWhileRotatingMultiplier : 1);

        if (mMoveForward)
        {
            moved = true;
            entity->getTransform()->Position +=
                entity->getTransform()->Rotation.forward() * GameManager::getUpdateDeltaTime() * currentSpeed;
        }

        if (mMoveBackward)
        {
            moved = true;
            currentSpeed *= reverseSpeedMultiplier;
            entity->getTransform()->Position -=
                entity->getTransform()->Rotation.forward() * GameManager::getUpdateDeltaTime() * currentSpeed;
        }

		// Spawn a bullet at the tank position towards the mouse.
		// Project the mouse coordinates into the game world, then point the bullet towards
		// that position.
        if (mShootBullet)
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

        if (moved || rotating)
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

    /// <summary>
    /// The renderer is responsible for clearing this.
    /// </summary>
    /// <returns></returns>
    std::vector<TransformComponent>& getTireTracks()
    {
        return mTireTracks;
    }

private:
    KeyDownInput mMoveForward;
    KeyDownInput mMoveBackward;
    KeyDownInput mTurnLeft;
    KeyDownInput mTurnRight;
    MouseClickedInput mShootBullet;

    float speed = 7;
    float rotationSpeed = 3;
    float speedWhileRotatingMultiplier = 0.7f;
    float reverseSpeedMultiplier = .5f;

    int bulletsRemaining = 600000;

    std::vector<TransformComponent> mTireTracks;

    // Time between tire tracks
    float tireTracksCoolDown = .12f;
    float currentTireTrackCoolDown = 0;
};

/// <summary>
/// Game scene for the tank game.
/// <author>Bryce Young 1/25/2022</author>
/// </summary>
class TankGameScene : public Scene
{
public:
	TankGameScene();

	virtual void update();

protected:
	void onInit();
};
