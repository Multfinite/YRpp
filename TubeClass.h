#pragma once

#include <AbstractClass.h>

class NOVTABLE TubeClass : public AbstractClass
{
public:
	CellStruct StartCell;
	CellStruct EndCell;
	DWORD Facing;
	int Directions[100];
	DWORD DirectionCount;
};
