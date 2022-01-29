#include "Component.h"
#include "Entity.h"
#include "Scene.h"

TransformComponent::TransformComponent(Vector3f position,
	Vector3f scale, Quaternionf rotation)
	:Position(position),
	Scale(scale),
	Rotation(rotation)
{
}

const Matrix44f& TransformComponent::calculateTransformationMatrix()
{
	Matrix44f translation;
	Matrix44f rotation(this->Rotation.toMatrix());
	Matrix44f scale;

	translation.translate(this->Position);
	scale.scale(this->Scale);

	mTransformationMatrix = translation * rotation * scale;
	return mTransformationMatrix;
}

void TransformComponent::lookAt(const Vector3f& point)
{
	Vector3f forward(Position - point);
	forward.normalize();

	Vector3f right = forward % Vector3f(0, 1, 0);
	Vector3f up = right % forward;

	Rotation.lookRotation(forward, up);
}