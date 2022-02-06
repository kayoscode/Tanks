/**
 * Handles player and AI control of tanks.
 * @author: Bryce Young 1/28/2022
 */
#pragma once

#include "Engine/GameManager.h"
#include "ResourceLoader.h"
#include "Engine/Input.h"

/// <summary>
/// Handles tank bullet movement.
/// </summary>
class BulletMovement : public UpdateLoop
{
public:
    BulletMovement(const Vector3f& direction)
        :mDirection(direction)
    {

    }

	void init(Entity* entity, Scene* scene);
	void update(Entity* entity, Scene* scene);

private:
    float bulletSpeed = 25;
    Vector3f mDirection;
};

/// <summary>
/// Class responsible for handling tank controls.
/// Should be applied to all tank AI's and the player.
/// </summary>
class TankControlBase : public UpdateLoop
{
public:
    TankControlBase() 
    {  }
    virtual ~TankControlBase() { }

	void init(Entity* entity, Scene* scene);

	void update(Entity* entity, Scene* scene);

    /// <summary>
    /// The renderer is responsible for clearing this.
    /// </summary>
    /// <returns></returns>
    std::vector<TransformComponent>& getTireTracks()
    {
        return mTireTracks;
    }

    /// <summary>
    /// Updates the position of the tank based on its specific movement algorithm.
    /// Returns true if the tank has moved or turned.
    /// </summary>
    /// <returns></returns>
    virtual bool updateControl(Entity* entity, Scene* scene) = 0;

protected:
    std::vector<TransformComponent> mTireTracks;

    // Time between tire tracks
    float tireTracksCoolDown = .12f;
    float currentTireTrackCoolDown = 0;
    float shootMoveCooldown = .25f;
    float currentShootMoveCooldown = 0;
    float shootCooldown = .15;
    float currentShootCooldown = 0;
    float mCurrentTurnFactor = 0;
    Quaternionf mRotationStartingTurn;
    Quaternionf mRotationLookDirection;

    /// <summary>
    /// Shoots a bullet if possible.
    /// </summary>
	void shoot(Entity* entity, Scene* scene, const Vector3f& position);
    void setMoveDirection(Entity* entity, Scene* scene, const Quaternionf& newRotation);

	float speed = 7;
	float rotationSpeed = 4;

	int bulletsRemaining = 500;
    Entity* mPlayerEntity;
};

class PlayerTankControl : public TankControlBase
{
public:
	PlayerTankControl();

	bool updateControl(Entity* entity, Scene* scene);

private:
    Vector3f getCurrentWorldMouseCoords(Scene* scene);

	MousePressedInput mShootBullet;
    KeyDownInput mUpDir;
    KeyDownInput mDownDir;
    KeyDownInput mLeftDir;
    KeyDownInput mRightDir;

    Quaternionf mUpRot;
    Quaternionf mDownRot;
    Quaternionf mRightRot;
    Quaternionf mLeftRot;
};

class Enemy1TankControl : public TankControlBase
{
public:
	Enemy1TankControl() 
    { 
        shootCooldown *= 5;
    }
    
    bool updateControl(Entity* entity, Scene* scene);
private:
};
