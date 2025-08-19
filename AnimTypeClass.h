/*
	AnimTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class OverlayTypeClass;
class ParticleTypeClass;
class WarheadTypeClass;

class __declspec(uuid("2EBB6D66-0D4D-11D2-8172-006008055BB5"))
NOVTABLE AnimTypeClass : public ObjectTypeClass
{
public:
	using base_type = ObjectTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E3608;
			this->IRTTITypeInfo = 0x7E35EC;
			this->INoticeSink = 0x7E35E4;
			this->INoticeSource = 0x7E35DC;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::AnimType;
	static constexpr uintptr_t AbsVTable = 0x7E3608;
	static constexpr size_t ClassSize = 0x378;

	//Array
	ABSTRACTTYPE_ARRAY(AnimTypeClass, 0x8B4150u);
	static AnimTypeClass* __fastcall FindOrAllocate(const char* id)
	{ JMP_STD(0x428B80); }
	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords,HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* owner) R0; // ! this just returns NULL instead of creating the anim, fucking slackers

	//AnimTypeClass
	virtual SHPStruct* LoadImage() R0;
	virtual void Load2DArt() RX;

	//Destructor
	virtual ~AnimTypeClass() RX;

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	int MiddleFrameIndex;
	int MiddleFrameWidth;
	int MiddleFrameHeight;
	BYTE unknown_2A4;
	double Damage;
	int Rate;
	int Start;
	int LoopStart;
	int LoopEnd;
	int End;
	int LoopCount;
	AnimTypeClass* Next;
	int SpawnsParticle; // index of that ParticleTypeClass
	int NumParticles;
	int DetailLevel;
	int TranslucencyDetailLevel;
	RandomStruct RandomLoopDelay;
	RandomStruct RandomRate;
	int Translucency;
	AnimTypeClass* Spawns;
	int SpawnCount;
	int Report;		//VocClass index
	int StopSound;		//VocClass index
	AnimTypeClass* BounceAnim;
	AnimTypeClass* ExpireAnim;
	AnimTypeClass* TrailerAnim;
	int TrailerSeperation;	//MISTYPE BY WESTWOOD!
	double Elasticity;
	double MinZVel;
	double unknown_double_320;
	double MaxXYVel;
	WarheadTypeClass* Warhead;
	int DamageRadius;
	OverlayTypeClass* TiberiumSpawnType;
	int TiberiumSpreadRadius;
	int YSortAdjust;
	int YDrawOffset;
	int ZAdjust;
	int MakeInfantry;
	int RunningFrames;
	bool IsFlamingGuy;
	bool IsVeins;
	bool IsMeteor;
	bool TiberiumChainReaction;
	bool IsTiberium;
	bool HideIfNoOre;
	bool Bouncer;
	bool Tiled;
	bool ShouldUseCellDrawer;
	bool UseNormalLight;
	bool DemandLoad; // not loaded from ini anymore
	bool FreeLoad;  // not loaded from ini anymore
	bool IsAnimatedTiberium;
	bool AltPalette;
	bool Normalized;
	Layer Layer;
	bool DoubleThick;
	bool Flat;
	bool Translucent;
	bool Scorch;
	bool Flamer;
	bool Crater;
	bool ForceBigCraters;
	bool Sticky;
	bool PingPong;
	bool Reverse;
	bool Shadow;
	bool PsiWarning;
	bool ShouldFogRemove;
protected:
	explicit __forceinline AnimTypeClass(fake_noinit_t) noexcept : ObjectTypeClass(fake_noinit_t{}) {}
public:
	AnimTypeClass(noinit_t) noexcept  : AnimTypeClass(fake_noinit_t{}) JMP_THIS(0x427850);
	AnimTypeClass(const char* pId) : AnimTypeClass(fake_noinit_t{}) JMP_THIS(0x427530);
};
static_assert(sizeof(AnimTypeClass) == AnimTypeClass::ClassSize);
