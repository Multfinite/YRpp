#pragma once

#include "GeneralStructures.h"
#include "YRMathVector.h"

/*!
* Ballistic trajectory data used by Animations and Voxel Animations.
*/
class BounceClass
{
public:
	enum class Status : int {
		None = 0,
		Bounce = 1,
		Impact = 2
	};
public:
	double Elasticity{ 0.0 }; // speed multiplier when bouncing off the ground
	double Gravity{ 0.0 }; // subtracted from the Z coords every frame
	double MaxVelocity{ 0.0 }; // 0.0 disables check
	Vector3D<float> Coords; // position with precision
	Vector3D<float> Velocity; // speed components
	Quaternion CurrentAngle; // quaternion for drawing
	Quaternion AngularVelocity; // second quaternion as per-frame delta
public:
	BounceClass() = default;
	BounceClass(const CoordStruct& coords, double elasticity, double gravity,
		double maxVelocity, const Vector3D<float>& velocity, double angularVelocity)
	{
		this->Initialize(coords, elasticity, gravity, maxVelocity, velocity, angularVelocity);
	}

	void Initialize(const CoordStruct& coords, double elasticity, double gravity,
			double maxVelocity, const Vector3D<float>& velocity, double angularVelocity) JMP_THIS(0x4397E0);

	CoordStruct Center() const JMP_THIS(0x4399A0);
	double Distance() JMP_THIS(0x439A10);
	Matrix3D GetDrawingMatrix() const JMP_THIS(0x4399E0);

	Status AI() JMP_THIS(0x439B00);
};

