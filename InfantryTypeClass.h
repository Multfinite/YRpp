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

	ABSTRACTTYPE_ARRAY(InfantryTypeClass, 0xA8E348u);
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
	// Used for the bomb attack cursor...
	bool Ivan;
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
protected: DWORD align_ECC;
public:
	virtual ~InfantryTypeClass() JMP_THIS(0x5239D0);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x524C70);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x524960);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x524B60);

	RTTIType KindOf() const override JMP_THIS(0x524D40);
	int SizeOf() const override JMP_THIS(0x524D50);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x524840);
	int GetArrayIndex() const override JMP_THIS(0x524D60);

	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x5240A0);

	CoordStruct FixupCoord(CoordStruct& coord) const override JMP_THIS(0x5247D0);
	Point3D LeptonDimensions() const override JMP_THIS(0x524760);
	bool CreateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x523B40);
	ObjectClass* Create(HouseClass* pOwner) override JMP_THIS(0x523B10);
	CellStruct* OccupiedCells(bool placement) const override JMP_THIS(0x523C20);

	bool CanUseWaypoint() const override JMP_THIS(0x5247B0);
	bool CanAttackMove() const override JMP_THIS(0x5247C0);
	int GetRepairStepCost() const override JMP_THIS(0x5247A0);
	int GetRepairStep() const override JMP_THIS(0x524790);

protected:
	explicit __forceinline InfantryTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	InfantryTypeClass(noinit_t) noexcept : InfantryTypeClass(fake_noinit_t{}) JMP_THIS(0x523980);
	InfantryTypeClass(const char* pId) : InfantryTypeClass(fake_noinit_t{}) JMP_THIS(0x5236A0);
};
static_assert(sizeof(InfantryTypeClass) == InfantryTypeClass::ClassSize);