#pragma once

#include "TechnoTypeClass.h"

class TechnoClass;

class __declspec(uuid("DCBD42EA-0546-11D2-ACA4-006008055BB5"))
NOVTABLE UnitTypeClass : public TechnoTypeClass
{
public:
	using base_type = TechnoTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F6218;
			this->IRTTITypeInfo = 0x7F61FC;
			this->INoticeSink = 0x7F61F4;
			this->INoticeSource = 0x7F61EC;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::UnitType;
	static constexpr uintptr_t AbsVTable = 0x7F6218;
	static constexpr size_t ClassSize = 0xE78;

	//Array
	ABSTRACTTYPE_ARRAY(UnitTypeClass, 0xA83CE0u);
	//TechnoTypeClass

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	LandType MovementRestrictedTo;
	CoordStruct HalfDamageSmokeLocation;
	bool Passive;
	bool CrateGoodie;
	bool Harvester;
	bool Weeder;
	bool unknown_E10;
	bool HasTurret; //not read from the INIs
	bool DeployToFire;
	bool IsSimpleDeployer;
	bool IsTilter;
	bool UseTurretShadow;
	bool TooBigToFitUnderBridge;
	bool CanBeach;
	bool SmallVisceroid;
	bool LargeVisceroid;
	bool CarriesCrate;
	bool NonVehicle;
	int StandingFrames;
	int DeathFrames;
	int DeathFrameRate;
	int StartStandFrame;
	int StartWalkFrame;
	int StartFiringFrame;
	int StartDeathFrame;
	int MaxDeathCounter;
	int Facings;
	int FiringSyncFrame0;
	int FiringSyncFrame1;
	int BurstDelay0;
	int BurstDelay1;
	int BurstDelay2;
	int BurstDelay3;
	SHPStruct* AltImage;
	char WalkFrames;
	char FiringFrames;
	char AltImageFile [0x19];
public:
	virtual ~UnitTypeClass() JMP_THIS(0x7472F0);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x747F30);
	
	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x748010);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x7480B0);
	
	RTTIType WhatAmI() const override JMP_THIS(0x748170);
	int Size() const override JMP_THIS(0x748160);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x747F70);
	int GetArrayIndex() const override JMP_THIS(0x748180);
	
	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x747620);
	
	CoordStruct* __FixupCoord(CoordStruct& retstr, CoordStruct& coord) const override JMP_THIS(0x747EB0);
	Point3D* __PixelDimensions(Point3D& retstr) const override JMP_THIS(0x747590);
	Point3D* __LeptonDimensions(Point3D& retstr) const override JMP_THIS(0x7475D0);
	bool SpawnAtMapCoords(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x7474B0);
	ObjectClass* CreateObject(HouseClass* pOwner) override JMP_THIS(0x747560);
	
	bool CanUseWaypoint() const override JMP_THIS(0x7473C0);
	bool CanAttackMove() const override JMP_THIS(0x7473D0);
	int GetRepairStep() const override JMP_THIS(0x747F20);

protected:
	explicit __forceinline UnitTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	UnitTypeClass(noinit_t) noexcept : UnitTypeClass(fake_noinit_t{}) JMP_THIS(0x7472C0);
	UnitTypeClass(const char* pId) : UnitTypeClass(fake_noinit_t{}) JMP_THIS(0x7470D0);
};
static_assert(sizeof(UnitTypeClass) == UnitTypeClass::ClassSize);
