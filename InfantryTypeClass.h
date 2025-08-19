/*
	AnimTypes are initialized by INI files.
*/

#pragma once

#include "TechnoTypeClass.h"

struct SubSequenceStruct
{
	int StartFrame;
	int CountFrames;
	int FacingMultiplier;
	SequenceFacing Facing;
	int SoundCount;
	int Sound1StartFrame;
	int Sound1Index; // VocClass
	int Sound2StartFrame;
	int Sound2Index; // VocClass
};

struct SequenceStruct
{
	SubSequenceStruct& GetSequence(Sequence sequence) {
		return this->Sequences[static_cast<int>(sequence)];
	}

	const SubSequenceStruct& GetSequence(Sequence sequence) const {
		return this->Sequences[static_cast<int>(sequence)];
	}

	SubSequenceStruct Sequences[42];
};

class __declspec(uuid("AE8B33D8-061C-11D2-ACA4-006008055BB5"))
NOVTABLE InfantryTypeClass : public TechnoTypeClass
{
public:
	using base_type = TechnoTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EB610;
			this->IRTTITypeInfo = 0x7EB5F4;
			this->INoticeSink = 0x7EB5EC;
			this->INoticeSource = 0x7EB5E4;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::InfantryType;
	static constexpr uintptr_t AbsVTable = 0x7EB610;
	static constexpr size_t ClassSize = 0xED0;

	//Array
	ABSTRACTTYPE_ARRAY(InfantryTypeClass, 0xA8E348u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~InfantryTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	PipIndex Pip;
	PipIndex OccupyPip;
	WeaponStruct OccupyWeapon;
	WeaponStruct EliteOccupyWeapon;
	SequenceStruct* Sequence;
	int FireUp;
	int FireProne;
	int SecondaryFire;
	int SecondaryProne;
	TypeList<AnimTypeClass*> DeadBodies;
	TypeList<AnimTypeClass*> DeathAnims;
	TypeList<int> VoiceComment;
	int EnterWaterSound;
	int LeaveWaterSound;
	bool Cyborg;
	bool NotHuman;
	bool Ivan; //used for the bomb attack cursor...
	int DirectionDistance;
	bool Occupier;
	bool Assaulter;
	int HarvestRate;
	bool Fearless;
	bool Crawls;
	bool Infiltrate;
	bool Fraidycat;
	bool TiberiumProof;
	bool Civilian;
	bool C4;
	bool Engineer;
	bool Agent;
	bool Thief;
	bool VehicleThief;
	bool Doggie;
	bool Deployer;
	bool DeployedCrushable;
	bool UseOwnName;
	bool JumpJetTurn;
private: DWORD align_ECC;
protected:
	explicit __forceinline InfantryTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	InfantryTypeClass(noinit_t) noexcept : InfantryTypeClass(fake_noinit_t{}) JMP_THIS(0x523980);
	InfantryTypeClass(const char* pId) : InfantryTypeClass(fake_noinit_t{}) JMP_THIS(0x5236A0);
};
static_assert(sizeof(InfantryTypeClass) == InfantryTypeClass::ClassSize);
