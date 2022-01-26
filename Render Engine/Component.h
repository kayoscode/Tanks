#pragma once

#include <string>
#include "Math/Math.h"

class Entity;

/// <summary>
/// Interface to represent all components which can be attached to game entities.
/// <author>Bryce Young 1/25/2022</author>
/// </summary>
class IComponent
{
public:
	IComponent() {}
	virtual ~IComponent() {}

	virtual void init(Entity* object) {}
	virtual void update(Entity* object) {}

protected:
private:
};

class TransformComponent : public IComponent
{
public:
	TransformComponent(Vector3f position = Vector3f(), 
		Vector3f scale = Vector3f(1, 1, 1), 
		Quaternionf rotation = Quaternionf())
		:Position(position),
		Scale(scale),
		Rotation(rotation)
	{

	}

	const Matrix44f& getTransformationMatrix()
	{
		return mTransformationMatrix;
	}

	void calculateTransformationMatrix()
	{
		Matrix44f translation;
		Matrix44f rotation(this->Rotation.toMatrix());
		Matrix44f scale;

		translation.translate(this->Position);
		scale.scale(this->Scale);

		mTransformationMatrix = translation * rotation * scale;
	}

	/// <summary>
	/// Points the transform towards a specific point.
	/// </summary>
	/// <param name="point"></param>
	void lookAt(Vector3f point)
	{
		Vector3f forward(Position - point);
		forward.normalize();

		Vector3f right = forward % Vector3f(0, 1, 0);
		Vector3f up = right % forward;

		Rotation.lookRotation(forward, up);
	}

	Vector3f Position;
	Vector3f Scale;
	Quaternionf Rotation;

protected:
	Matrix44f mTransformationMatrix;
private:
};

class UpdateLoop : public IComponent {
    public:
        virtual void init(Entity* object) = 0;
        virtual void update(Entity* object) = 0;

    protected:
};
