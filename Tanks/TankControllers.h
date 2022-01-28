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
	void init(Entity* entity);
	void update(Entity* entity);

private:
    float bulletSpeed = 25;
};

/// <summary>
/// Class responsible for handling tank controls.
/// Should be applied to all tank AI's and the player.
/// </summary>
class TankControlBase : public UpdateLoop
{
public:
    TankControlBase() {  }
    virtual ~TankControlBase() { }

	void init(Entity* entity);

	void update(Entity* entity);

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
    virtual bool updateControl(Entity* entity) = 0;

private:
    std::vector<TransformComponent> mTireTracks;

    // Time between tire tracks
    float tireTracksCoolDown = .12f;
    float currentTireTrackCoolDown = 0;

protected:
    /// <summary>
    /// Shoots a bullet if possible.
    /// </summary>
	void shoot(Entity* entity);

	float speed = 7;
	float rotationSpeed = 3;
	float speedWhileRotatingMultiplier = 0.7f;
	float reverseSpeedMultiplier = .5f;

	int bulletsRemaining = 5;
};

class PlayerTankControl : public TankControlBase
{
public:
	PlayerTankControl();

	bool updateControl(Entity* entity);

private:
	KeyDownInput mMoveForward;
	KeyDownInput mMoveBackward;
	KeyDownInput mTurnLeft;
	KeyDownInput mTurnRight;
	MouseClickedInput mShootBullet;
    MouseMoveInput mUpdateBulletTracker;
};

class Enemy1TankControl : public TankControlBase
{
public:
	Enemy1TankControl() { }
    
    bool updateControl(Entity* entity);
};
