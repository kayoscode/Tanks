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
public:
	Line(const Vector3<T>& start, const Vector3<T>& direction, T length)
		:Start(start),
		Direction(direction),
		Length(length)
	{
		this->Direction.normalize();
	}

	Vector3<T> getForward()
	{
		return Direction.retNormalized();
	}

	Vector3<T> getUp()
	{
		return (getForward() % getRight()).retNormalized();
	}

	Vector3<T> getRight()
	{
		return (Direction % Vector3<T>(0, 1, 0)).retNormalized();
	}

	Vector3<T> positionAt(float t)
	{
		return Start + (Direction * t);
	}

	Vector3<T> Start;
	Vector3<T> Direction;
	T Length;
};

typedef Line<float> Linef;
