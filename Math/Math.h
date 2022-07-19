#pragma once

#include "Matrix22.h"
#include "Matrix33.h"
#include "Matrix44.h"

#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Line.h"
#include "Plane.h"

class GenMath
{
public:
	/// <summary>
	/// The value of PI.
	/// </summary>
	static constexpr float PI = 3.14159265359f;

	/// <summary>
	/// the highest intger value.
	/// </summary>
	static constexpr int INT_INFINITY = 0x7FFFFFFF;

	/// <summary>
	/// the lowest integer value
	/// </summary>
	static constexpr int INT_NEG_INFINITY = -INT_INFINITY;

	/// <summary>
	/// Converts degrees to radians
	/// </summary>
	/// <param name="degrees"></param>
	/// <returns>
	/// returns Pi/180 * degrees
	/// </returns>
	static float toRadians(float degrees)
	{
		return (float)(PI / 180) * degrees;
	}

	/// <summary>
	/// Converts radians to degrees
	/// </summary>
	/// <param name="radians"></param>
	/// <returns>
	/// returns 180/pi * radisans
	/// </returns>
	static float toDegrees(float radians)
	{
		return (float)(180 / PI) * radians;
	}

	/// <summary>
	/// Linearly interpolates between two floats
	/// </summary>
	/// <param name="A">
	/// first point
	/// </param>
	/// <param name="B">
	/// second points
	/// </param>
	/// <param name="perc">
	/// value of the weighted average
	/// </param>
	/// <returns></returns>
	static float interpolate(float A, float B, float perc)
	{
		return (perc)*A + (1 - perc) * B;
	}

	/// <summary>
	/// Takes a point in window coordinates and converts it to a point in coordinates relative to the projection plane
	/// </summary>
	/// <param name="input">'
	/// The screen coordinates
	/// </param>
	/// <returns>
	/// Returns the converted coords
	/// </returns>
	/// <remarks>
	/// The return will have an inverted Y value because in opengl as you are moving your points up, the coordinates increase
	/// while in window coords, as you move the points us, the coords decrease
	/// </remarks>
	static Vector2f normalizeToWindowCoords(const Vector2f& input, int windowWidth, int windowHeight)
	{
		return Vector2f
		(
			((input.x - windowWidth) / (float)windowWidth) + 1,
			((input.y - windowHeight) / (float)windowHeight) + 1
		);
	}

	/// <summary>
	/// gets the mouse position relative to glcoords
	/// Middle (0,0)
	/// far left (-1, 0)
	/// far right (1, 0)
	/// top (0,1)
	/// bottom (0, -1)
	/// </summary>
	static Vector2f screenCoordsToGLCoords(const Vector2f& position, int windowWidth, int windowHeight)
	{
		Vector2f localPos(position);

		localPos.x = ((localPos.x - windowWidth) / (float)((float)windowWidth / 2)) + 1;
		localPos.y = ((localPos.y - windowHeight) / (float)((float)windowHeight / 2)) + 1;

		return localPos;
	}

	/// <summary>
	/// Takes a set of vectors on the screen and turns them into world coordinates
	/// keep in mind, the vectors will be on the near plane,
	/// Screen coords are in [-1, 1] format - not pixel format.
	/// </summary>
	/// <param name="camera">
	/// The camera that you will be using to unproject the data
	/// </param>
	/// <param name="screenCoords">
	/// These coordinates must be specified in opengl coords
	/// This function will invert the y axis as is necessary 
	/// </param>
	/// <returns>
	/// returns the world position of the screen coordinates
	/// </returns>
	static Vector3f unprojectScreenCoords(const Matrix44f& projectionMatrix, 
		const Matrix44f& viewMatrix, const Vector2f& screenCoords)
	{
		Vector4f screenCoordsHomogeneous(screenCoords.x, -screenCoords.y, 0, 1);

		Matrix44f projectionView = (projectionMatrix * viewMatrix).inverse();

		screenCoordsHomogeneous = projectionView * screenCoordsHomogeneous;

		screenCoordsHomogeneous.x /= screenCoordsHomogeneous.w;
		screenCoordsHomogeneous.y /= screenCoordsHomogeneous.w;
		screenCoordsHomogeneous.z /= screenCoordsHomogeneous.w;

		return screenCoordsHomogeneous.xyz();
	}

	/// <summary>
	/// Takes global coordinates and finds where they are located in the camera's near plane.
	/// </summary>
	/// <param name="camera">
	/// The camera to project against
	/// </param>
	/// <param name="globalCoords">
	/// The global coordinates of the point to 
	/// </param>
	/// <returns>
	/// Retruns a postion on the screen in coordinates from -1 to 1 on both axis
	/// </returns>
	static Vector2f projectGlobalCoords(const Matrix44f& projectionMatrix, 
		const Matrix44f& viewMatrix, const Vector3f& globalCoords)
	{
		Vector4f pos = projectionMatrix * viewMatrix * Vector4f(globalCoords, 1);
		pos = pos * (1 / pos.w);

		return pos.xy();
	}

	/// <summary>
	/// Finds the point in 3D space where a plane and a line intersect.
	/// </summary>
	/// <param name="plane"></param>
	/// <param name="line"></param>
	/// <returns></returns>
	static Vector3f findIntersectionPoint(const Planef& plane, const Linef& line)
	{
		// Create matrix to represent the plane.
		Matrix44f planeTranslation;
		planeTranslation.translate(plane.Position);

		Quaternionf planeRotation;
		planeRotation.lookRotation(plane.Normal % Vector3f(0, 0, -1), plane.Normal);

		Matrix44f planeMatrix = (planeTranslation * planeRotation.toMatrix());
		Matrix44f inversePlaneMatrix = planeMatrix.inverse();

		// Put line into plane space.
		Linef placeSpaceLine((inversePlaneMatrix * Vector4f(line.Start, 1)).xyz(),
			(inversePlaneMatrix * Vector4f(line.Direction, 0)).xyz(), line.Length);

		// Solve for y = 0 by solving for t.
		// t = -yi/dy where dy in the set of reals.

		if(!isnan(placeSpaceLine.Direction.y) && 
			placeSpaceLine.Direction.y != 0 && 
			!isinf(placeSpaceLine.Direction.y))
		{
			float t = -placeSpaceLine.Start.y / placeSpaceLine.Direction.y;
			Vector3f planeSpacePosition = placeSpaceLine.positionAt(t);

			return (planeMatrix * planeSpacePosition).xyz();
		}
		else
		{
			// We could not come up with a valid answer because the line and plane
			// were parallel.
			return Vector3f(INFINITY, INFINITY, INFINITY);
		}
	}
};
