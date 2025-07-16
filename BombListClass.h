#pragma once

#include "AbstractClass.h"
#include "ArrayClasses.h"
#include "BombClass.h"
#include "Helpers/CompileTime.h"

class ObjectClass;
class TechnoClass;

//this class contains a vector of BombClass, a vector of bomb-revealing TechnoClass, and some other properties
class BombListClass
{
public:
	DEFINE_REFERENCE(BombListClass, Instance, 0x87F5D8u)
public:
	// all the BombClass instances on the map
	DynamicVectorClass<BombClass*> Bombs;
	// all the BombSight'ed objects currently on the map
	DynamicVectorClass<TechnoClass*> Detectors;
	// defaults to 100, some iterators set it to 1
	int UpdateDelay;
public:
	// draws all the visible bombs, expires the outdated ones
	void AI() JMP_THIS(0x438BF0);
	// the main one, ivan planting a bomb (creates a BombClass inside)
	void Plant(TechnoClass *SourceObject, ObjectClass *TargetObject) JMP_THIS(0x438E70);
	void AddDetector(TechnoClass *Detector) JMP_THIS(0x439080);
	void RemoveDetector(TechnoClass *Detector) JMP_THIS(0x4390D0);
	void PointerGotInvalid(AbstractClass* pInvalid) JMP_THIS(0x439150);
};
