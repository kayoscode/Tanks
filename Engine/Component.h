#pragma once

#include <string>
#include "Math/Math.h"

class Entity;
class Scene;

/// <summary>
/// Interface to represent all components which can be attached to game entities.
/// <author>Bryce Young 1/25/2022</author>
/// </summary>
class IComponent
{
public:
	IComponent() {}
	virtual ~IComponent() {}

	virtual void init(Entity* object, Scene* scene) {}
	virtual void update(Entity* object, Scene* scene) {}

protected:
private:
};

/// <summary>
/// Contains information about the transform of an entity.
/// Does not appear on the object as a true component for update optimization.
/// </summary>
class TransformComponent : public IComponent
{
public:
	TransformComponent(Vector3f position = Vector3f(),
		Vector3f scale = Vector3f(1, 1, 1),
		Quaternionf rotation = Quaternionf());

	const Matrix44f& getTransformationMatrix()
	{
		return mTransformationMatrix;
	}

	const Matrix44f& calculateTransformationMatrix();

	/// <summary>
	/// Points the transform towards a specific point.
	/// </summary>
	/// <param name="point"></param>
	void lookAt(const Vector3f& point);
	
	Quaternionf getLookAtRotation(const Vector3f& point);

	Vector3f Position;
	Vector3f Scale;
	Quaternionf Rotation;

protected:
	Matrix44f mTransformationMatrix;
private:
};

/// <summary>
/// A basic component for handling AI and updates for gameobjects.
/// </summary>
class UpdateLoop : public IComponent {
    public:
        virtual void init(Entity* object, Scene* scene) = 0;
        virtual void update(Entity* object, Scene* scene) = 0;

    protected:
};
