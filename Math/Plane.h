#pragma once

#include "Vector3.h"

template<typename T>
/// <summary>
/// Represents a plane in 3D space.
/// <author>Bryce Young 1/28/2022</author>
/// </summary>
/// <typeparam name="T"></typeparam>
class Plane
{
public:
	Plane(const Vector3<T>& position, const Vector3<T>& normal)
		:Position(position),
		Normal(normal)
	{}

	Vector3<T> Position;
	Vector3<T> Normal;
};

typedef Plane<float> Planef;
