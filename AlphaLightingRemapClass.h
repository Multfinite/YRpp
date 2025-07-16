#pragma once

#include "YRPP.h"
#include "Helpers/CompileTime.h"
#include "ArrayClasses.h"

class AlphaLightingRemapClass
{
public:
	DEFINE_REFERENCE(DynamicVectorClass<AlphaLightingRemapClass*>, Array, 0x88A080)
public:
	uint16_t Table[256][256];
	int IntensityCount;
	int RefCount;
public:
	// Notice:
	// When a ConvertClass is constructed by the game, it will generate [IntensityCount] color
	// tables from dark to bright. Each of them just changes the intensity of the source palette.
	//
	// If we have a point, whose value in ABuffer is A
	constexpr static AlphaLightingRemapClass* __stdcall FindOrAllocate(int intensityCount) JMP_STD(0x420140);
	constexpr static void __stdcall Release(AlphaLightingRemapClass* pItem) JMP_STD(0x420270);

	// The game never directly called this function, it just call FindOrAllocate and this CTOR is inlined!
	explicit AlphaLightingRemapClass(int intensityCount) noexcept JMP_THIS(0x4202F0);
};
