/*
	Radar notifications
*/

#pragma once

#include "GeneralDefinitions.h"

class RadarEventClass
{
public:
	static bool Create(RadarEventType nType, ::Cell nMapCoords)
		{ PUSH_VAR32(nMapCoords); SET_REG32(ecx, nType); CALL(0x65FA70); }

private:
	//Constructor, Destructor
	RadarEventClass(int nType, ::Cell nMapCoords)
		{ JMP_THIS(0x65FB80); }

	~RadarEventClass()
		{ JMP_THIS(0x65B2F0); }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	RadarEventType Type;
	int RadarX;	//not sure
	int RadarY;	//not sure
	float Speed;
	float RotationValue;
	float RotationSpeed;
	float ColorValue;
	float ColorSpeed;
	::Cell MapCoords;
	CDTimerClass DurationTimer;	//Rotation timer?
	CDTimerClass VisibilityTimer;	//Color timer?
	bool Rotating;
	bool Visible;
};
