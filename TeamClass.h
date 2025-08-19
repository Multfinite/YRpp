#pragma once

#include "TeamTypeClass.h"
#include "AbstractClass.h"

class HouseClass;
class FootClass;
class CellClass;
class ScriptClass;
class TagClass;

class __declspec(uuid("0E272DCF-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE TeamClass : public AbstractClass
{
public:
	using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F4730;
            this->IRTTITypeInfo = 0x7F4714;
            this->INoticeSink = 0x7F470C;
            this->INoticeSource = 0x7F4704;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Team;
    static constexpr uintptr_t AbsVTable = 0x7F4730;
    static constexpr size_t ClassSize = 0xA0;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<TeamClass*>, Array, 0x8B40E8u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TeamClass() RX;

	// fills dest with all types needed to complete this team. each type is
	// included as often as it is needed.
	void GetTaskForceMissingMemberTypes(DynamicVectorClass<TechnoTypeClass*>& dest) const
		JMP_THIS(0x6EF4D0);

	void LiberateMember(FootClass* pFoot, int idx = -1, byte count = 0)
		JMP_THIS(0x6EA870);

	// if bKeepQuantity is false, this will not change the quantity of each techno member
	bool AddMember(FootClass* pFoot, bool bForce)
		JMP_THIS(0x6EA500);

	void AssignMissionTarget(AbstractClass* pTarget)
		JMP_THIS(0x6E9050);

	void ScanLimit()
		JMP_THIS(0x6EC3A0);

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;


protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TeamClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
public:
	TeamTypeClass* Type;
	ScriptClass*   CurrentScript;
	HouseClass*    Owner;
	HouseClass*    Target;
	CellClass*     SpawnCell;
	FootClass*     ClosestMember;
	AbstractClass* QueuedFocus;
	AbstractClass* Focus;
	int            unknown_44;
	int            TotalObjects;
	int            TotalThreatValue;
	int            CreationFrame;
	FootClass*     FirstUnit;
	CDTimerClass   GuardAreaTimer;
	CDTimerClass   SuspendTimer;
	TagClass*      Tag;
	bool           IsTransient;
	bool           NeedsReGrouping;
	bool           GuardSlowerIsNotUnderStrength;
	bool           IsForcedActive;

	bool           IsHasBeen;
	bool           IsFullStrength;
	bool           IsUnderStrength;
	bool           IsReforming;

	bool           IsLagging;
	bool           NeedsToDisappear;
	bool           JustDisappeared;
	bool           IsMoving;

	bool           StepCompleted; // can proceed to the next step of the script
	bool           TargetNotAssigned;
	bool           IsLeavingMap;
	bool           IsSuspended;

	bool           AchievedGreatSuccess; // executed script action 49, 0

	int CountObjects[6]; // counts of each object specified in the Type
    TeamClass(TeamTypeClass* pType, HouseClass* pOwner, int _unknown_44) : TeamClass(fake_noinit_t{})
        JMP_THIS(0x6E8A90);
	TeamClass(noinit_t) noexcept  : TeamClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(TeamClass) == TeamClass::ClassSize);
