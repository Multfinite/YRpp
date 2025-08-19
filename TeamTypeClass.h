/*
	[TeamTypes]
*/

#pragma once

#include "AbstractTypeClass.h"
#include "ScriptTypeClass.h"
#include "TaskForceClass.h"

class FootClass;
class TagClass;
class TeamClass;
class TechnoTypeClass;

class __declspec(uuid("D1DBA64E-0778-11D2-ACA5-006008055BB5"))
NOVTABLE TeamTypeClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;
    
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F47D0;
            this->IRTTITypeInfo = 0x7F47B4;
            this->INoticeSink = 0x7F47AC;
            this->INoticeSource = 0x7F47A4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::TeamType;
    static constexpr uintptr_t AbsVTable = 0x7F47D0;
    static constexpr size_t ClassSize = 0xF8;

	//Array
	ABSTRACTTYPE_ARRAY(TeamTypeClass, 0xA8ECA0u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TeamTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	static bool LoadFromINIList(CCINIClass *pINI, bool IsGlobal)
		{ PUSH_VAR8(IsGlobal); SET_REG32(ECX, pINI); CALL(0x6F19B0); }

	TeamClass * CreateTeam(HouseClass *pHouse)
		{ JMP_THIS(0x6F09C0); }

	void DestroyAllInstances()
		{ JMP_THIS(0x6F0A70); }

	int GetGroup() const
		{ JMP_THIS(0x6F1870); }

	CellStruct* GetWaypoint(CellStruct *buffer) const
		{ JMP_THIS(0x6F18A0); }

	CellStruct* GetTransportWaypoint(CellStruct *buffer) const
		{ JMP_THIS(0x6F18E0); }

	bool CanRecruitUnit(FootClass* pUnit, HouseClass* pOwner) const
		{ JMP_THIS(0x6F1320); }

	void FlashAllInstances(int Duration)
		{ JMP_THIS(0x6F1F30); }

	TeamClass * FindFirstInstance() const
		{ JMP_THIS(0x6F1F70); }

	void ProcessTaskForce()
		{ JMP_THIS(0x6F1FA0); }

	static void ProcessAllTaskforces()
		{ JMP_STD(0x6F2040); }

	HouseClass* GetHouse() const
		{ JMP_THIS(0x6F2070); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline TeamTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}

public:

	int      ArrayIndex;
	int      Group;
	int      VeteranLevel;
	bool     Loadable;
	bool     Full;
	bool     Annoyance;
	bool     GuardSlower;
	bool     Recruiter;
	bool     Autocreate;
	bool     Prebuild;
	bool     Reinforce;
	bool     Whiner;
	bool     Aggressive;
	bool     LooseRecruit;
	bool     Suicide;
	bool     Droppod;
	bool     UseTransportOrigin;
	bool     DropshipLoadout;
	bool     OnTransOnly;
	int      Priority;
	int      Max;
	int      field_BC;
	int      MindControlDecision;
	HouseClass *     Owner;
	int      idxHouse; // idx for MP
	int      TechLevel;
	TagClass* Tag;
	int      Waypoint;
	int      TransportWaypoint;
	int      cntInstances;
	ScriptTypeClass*  ScriptType;
	TaskForceClass*   TaskForce;
	int      IsGlobal;
	int      field_EC;
	bool     field_F0;
	bool     field_F1;
	bool     AvoidThreats;
	bool     IonImmune;
	bool     TransportsReturnOnUnload;
	bool     AreTeamMembersRecruitable;
	bool     IsBaseDefense;
	bool     OnlyTargetHouseEnemy;

    TeamTypeClass(const char* pID) : TeamTypeClass(fake_noinit_t{}) JMP_THIS(0x6F06E0);
};
static_assert(sizeof(TeamTypeClass) == TeamTypeClass::ClassSize);
