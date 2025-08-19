/*
	Base class for all game objects with missions (yeah... not many).
*/

#pragma once

#include "ObjectClass.h"

class CCINIClass;

class MissionControlClass
{
	public:
		DEFINE_ARRAY_REFERENCE(MissionControlClass, [0x20], Array, 0xA8E3A8)
		DEFINE_ARRAY_REFERENCE(const char*, [0x20], Names, 0xA8E3A8)

		static MissionControlClass* __fastcall Find(const char* pName)
			{ JMP_STD(0x5B3910); }

		static Mission __fastcall FindIndex(const char* pName)
			{ JMP_STD(0x5B3910); }

		static const char* __fastcall FindName(const Mission& index)
			{ JMP_STD(0x5B3740); }

		MissionControlClass()
			{ JMP_THIS(0x5B3700); }

		const char* GetName()
			{ JMP_THIS(0x5B3740); }

		void LoadFromINI(CCINIClass* pINI)
			{ JMP_THIS(0x5B3760); }

		//Properties
		int ArrayIndex;
		bool NoThreat;
		bool Zombie;
		bool Recruitable;
		bool Paralyzed;
		bool Retaliate;
		bool Scatter;
		double Rate; //default 0.016
		double AARate; //default 0.016
};

class NOVTABLE MissionClass : public ObjectClass
{
public:
	//Destructor
	virtual ~MissionClass() { /* ~ObjectClass() */ }

	//MissionClass
	virtual bool QueueMission(Mission mission, bool start_mission) R0;
	virtual bool NextMission() R0;
	virtual void ForceMission(Mission mission) RX;

	virtual void Override_Mission(Mission mission, AbstractClass* target, AbstractClass* destination) RX;
	virtual bool Mission_Revert() R0;
	virtual bool MissionIsOverriden() const R0;
	virtual bool ReadyToNextMission() const R0;

	virtual int Mission_Sleep() R0;
	virtual int Mission_Harmless() R0;
	virtual int Mission_Ambush() R0;
	virtual int Mission_Attack() R0;
	virtual int Mission_Capture() R0;
	virtual int Mission_Eaten() R0;
	virtual int Mission_Guard() R0;
	virtual int Mission_AreaGuard() R0;
	virtual int Mission_Harvest() R0;
	virtual int Mission_Hunt() R0;
	virtual int Mission_Move() R0;
	virtual int Mission_Retreat() R0;
	virtual int Mission_Return() R0;
	virtual int Mission_Stop() R0;
	virtual int Mission_Unload() R0;
	virtual int Mission_Enter() R0;
	virtual int Mission_Construction() R0;
	virtual int Mission_Selling() R0;
	virtual int Mission_Repair() R0;
	virtual int Mission_Missile() R0;
	virtual int Mission_Open() R0;
	virtual int Mission_Rescue() R0;
	virtual int Mission_Patrol() R0;
	virtual int Mission_ParaDropApproach() R0;
	virtual int Mission_ParaDropOverfly() R0;
	virtual int Mission_Wait() R0;
	virtual int Mission_SpyPlaneApproach() R0;
	virtual int Mission_SpyPlaneOverfly() R0;

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

	using base_type = ObjectClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EDCC0;
			this->IRTTITypeInfo = 0x7EDCA4;
			this->INoticeSink = 0x7EDC9C;
			this->INoticeSource = 0x7EDC94;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7EDCC0;
	static constexpr size_t ClassSize = 0xD4;
public:

	Mission  CurrentMission;
	Mission  SuspendedMission;
	Mission  QueuedMission;
	bool     unknown_bool_B8;
	int      MissionStatus;
	int      CurrentMissionStartTime;	//in frames
	int      MissionAccumulateTime;
	DECLARE_PROPERTY(CDTimerClass, UpdateTimer);
protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline MissionClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}), UpdateTimer(noinit_t{}) {}
	MissionClass(noinit_t) noexcept : MissionClass(fake_noinit_t{}) { vtables.init(this); };
	MissionClass() : MissionClass(fake_noinit_t{}) JMP_THIS(0x5B2DA0);
};
static_assert(sizeof(MissionClass) == MissionClass::ClassSize);
