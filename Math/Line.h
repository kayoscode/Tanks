#pragma once

#include "Vector3.h"

/// <summary>
/// Class to representa  line in 3D space.
/// Parametric form with a length.
/// <author>Bryce Young 1/28/2022</author>
/// </summary>
template<class T>
class Line
{
	Line(const Vector3<T>& start, const Vector3<T>& direction, T length)
		:start(start),
		direction(direction),
		length(length)
	{
		this->direction.normalize();
	}

	Vector3<T> getForward()
	{
		return direction.retNormalized();
	}

	Vector3<T> getUp()
	{
		return (getForward() % getRight()).retNormalized();
	}

	Vector3<T> getRight()
	{
		return (direction % Vector3<T>(0, 1, 0)).retNormalized();
	}

	Vector3<T> start;
	Vector3<T> direction;
	T length;
};

typedef Line<float> linef;
