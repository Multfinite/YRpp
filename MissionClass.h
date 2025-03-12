/*
	Base class for all game objects with missions (yeah... not many).
*/

#pragma once

#include "ObjectClass.h"

class CCINIClass;

class MissionControlClass
{
	public:
		static constexpr reference<MissionControlClass, 0xA8E3A8, 0x20> const Array {};
		static constexpr reference<const char*, 0xA8E3A8, 0x20> const Names {};

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
	static constexpr uintptr_t AbsVTable = 0x7EDCC0;
	static constexpr size_t ClassSize = 0xD4;
public:
	Mission  CurrentMission;
	Mission  SuspendedMission;
	Mission  QueuedMission;
	bool     AssignmentState;
	int      MissionStatus;
	//in frames
	int      CurrentMissionStartTime;	
	int      MissionAccumulateTime;
	DECLARE_PROPERTY(CDTimerClass, UpdateTimer);
public:
	//Destructor (inlined)
	//virtual ~MissionClass() { ~ObjectClass(); }

	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x5B3970);
	void AI() override JMP_THIS(0x5B3060);
	Mission CurrentMission() const override JMP_THIS(0x5B3040);

	/*!
	* @note original_name Assign_Mission
	* @note vtable_index 122:0x1E8
	* @note address 0x5B35E0
	*/
	virtual void AssignMission(Mission mission, bool commence) JMP_THIS(0x5B35E0);

	/*!
	* @note original_name Commence
	* @note vtable_index 123:0x1EC
	* @note address 0x5B3570
	*/
	virtual bool Commence() JMP_THIS(0x5B3570);

	/*!
	* @note original_name Set_Mission
	* @note vtable_index 124:0x1F0
	* @note address 0x5B2FD0
	*/
	virtual void SetMission(Mission mission) JMP_THIS(0x5B2FD0);

	/*!
	* @note original_name Override_Mission
	* @note vtable_index 125:0x1F4
	* @note address 0x5B3650
	*/
	virtual void OverrideMission(Mission mission, AbstractClass* target, AbstractClass* destination) JMP_THIS(0x5B3650);

	/*!
	* @note original_name Restore_Mission
	* @note vtable_index 126:0x1F8
	* @note address 0x5B36B0
	*/
	virtual bool RestoreMission() JMP_THIS(0x5B36B0);

	/*!
	* @note original_name Has_A_Suspended_Mission
	* @note vtable_index 127:0x1FC
	* @note address 0x5B3A10
	*/
	virtual bool HasSuspendedMission() JMP_THIS(0x5B3A10);

	/*!
	* @note original_name Ready_To_Commence
	* @note vtable_index 128:0x200
	* @note address 0x4E0140
	*/
	virtual bool IsReadyToCommence() JMP_THIS(0x4E0140);

	/*!
	* @note original_name Mission_Sleep
	* @note vtable_index 129:0x204
	* @note address 0x5B2E10
	*/
	virtual int MissionSleep() JMP_THIS(0x5B2E10);

	/*!
	* @note original_name Mission_Harmless
	* @note vtable_index 130:0x208
	* @note address 0x5B2E20
	*/
	virtual int MissionHarmless() JMP_THIS(0x5B2E20);

	/*!
	* @note original_name Mission_Ambush
	* @note vtable_index 131:0x20C
	* @note address 0x5B2E30
	*/
	virtual int MissionAmbush() JMP_THIS(0x5B2E30);

	/*!
	* @note original_name Mission_Attack
	* @note vtable_index 132:0x210
	* @note address 0x5B2E40
	*/
	virtual int MissionAttack() JMP_THIS(0x5B2E40);

	/*!
	* @note original_name Mission_Capture
	* @note vtable_index 133:0x214
	* @note address 0x5B2E50
	*/
	virtual int MissionCapture() JMP_THIS(0x5B2E50);

	/*!
	* @note original_name Mission_Eaten
	* @note vtable_index 134:0x218
	* @note address 0x5B2E60
	*/
	virtual int MissionEaten() JMP_THIS(0x5B2E60);

	/*!
	* @note original_name Mission_Guard
	* @note vtable_index 135:0x21C
	* @note address 0x5B2E70
	*/
	virtual int MissionGuard() JMP_THIS(0x5B2E70);

	/*!
	* @note original_name Mission_Guard_Area
	* @note vtable_index 136:0x220
	* @note address 0x5B2E80
	*/
	virtual int MissionGuardArea() JMP_THIS(0x5B2E80);

	/*!
	* @note original_name Mission_Harvest
	* @note vtable_index 137:0x224
	* @note address 0x5B2E90
	*/
	virtual int MissionHarvest() JMP_THIS(0x5B2E90);

	/*!
	* @note original_name Mission_Hunt
	* @note vtable_index 138:0x228
	* @note address 0x5B2EA0
	*/
	virtual int MissionHunt() JMP_THIS(0x5B2EA0);

	/*!
	* @note original_name Mission_Move
	* @note vtable_index 139:0x22C
	* @note address 0x5B2EB0
	*/
	virtual int MissionMove() JMP_THIS(0x5B2EB0);

	/*!
	* @note original_name Mission_Retreat
	* @note vtable_index 140:0x230
	* @note address 0x5B2EC0
	*/
	virtual int MissionRetreat() JMP_THIS(0x5B2EC0);

	/*!
	* @note original_name Mission_Return
	* @note vtable_index 141:0x234
	* @note address 0x5B2ED0
	*/
	virtual int MissionReturn() JMP_THIS(0x5B2ED0);

	/*!
	* @note original_name Mission_Stop
	* @note vtable_index 142:0x238
	* @note address 0x5B2EE0
	*/
	virtual int MissionStop() JMP_THIS(0x5B2EE0);

	/*!
	* @note original_name Mission_Unload
	* @note vtable_index 143:0x23C
	* @note address 0x5B2EF0
	*/
	virtual int MissionUnload() JMP_THIS(0x5B2EF0);

	/*!
	* @note original_name Mission_Enter
	* @note vtable_index 144:0x240
	* @note address 0x5B2F00
	*/
	virtual int MissionEnter() JMP_THIS(0x5B2F00);

	/*!
	* @note original_name Mission_Construction
	* @note vtable_index 145:0x244
	* @note address 0x5B2F10
	*/
	virtual int MissionConstruction() JMP_THIS(0x5B2F10);

	/*!
	* @note original_name Mission_Deconstruction
	* @note vtable_index 146:0x248
	* @note address 0x5B2F20
	*/
	virtual int MissionDeconstruction() JMP_THIS(0x5B2F20);

	/*!
	* @note original_name Mission_Repair
	* @note vtable_index 147:0x24C
	* @note address 0x5B2F30
	*/
	virtual int MissionRepair() JMP_THIS(0x5B2F30);

	/*!
	* @note original_name Mission_Missile
	* @note vtable_index 148:0x250
	* @note address 0x5B2F40
	*/
	virtual int MissionMissile() JMP_THIS(0x5B2F40);

	/*!
	* @note original_name Mission_Open
	* @note vtable_index 149:0x254
	* @note address 0x5B2F50
	*/
	virtual bool MissionOpen() JMP_THIS(0x5B2F50);

	/*!
	* @note original_name Mission_Rescue
	* @note vtable_index 150:0x258
	* @note address 0x5B2F60
	*/
	virtual int MissionRescue() JMP_THIS(0x5B2F60);

	/*!
	* @note original_name Mission_Patrol
	* @note vtable_index 151:0x25C
	* @note address 0x5B2F70
	*/
	virtual int MissionPatrol() JMP_THIS(0x5B2F70);

	/*!
	* @note original_name Mission_Paradrop_Approach
	* @note vtable_index 152:0x260
	* @note address 0x5B2F80
	*/
	virtual int MissionParadropApproach() JMP_THIS(0x5B2F80);

	/*!
	* @note original_name Mission_Paradrop_Overfly
	* @note vtable_index 153:0x264
	* @note address 0x5B2F90
	*/
	virtual int MissionParadropOverfly() JMP_THIS(0x5B2F90);

	/*!
	* @note original_name Mission_Wait
	* @note vtable_index 154:0x268
	* @note address 0x5B2FA0
	*/
	virtual int MissionWait() JMP_THIS(0x5B2FA0);

	/*!
	* @note original_name Mission_Spyplane_Approach
	* @note vtable_index 155:0x26C
	* @note address 0x5B2FB0
	*/
	virtual int MissionSpyplaneApproach() JMP_THIS(0x5B2FB0);

	/*!
	* @note original_name Mission_Spyplane_Overfly
	* @note vtable_index 156:0x270
	* @note address 0x5B2FC0
	*/
	virtual int MissionSpyplaneOverfly() JMP_THIS(0x5B2FC0);

	constexpr MissionControlClass* CurrentMissionControl() JMP_THIS(0x5B3A00);
	constexpr static bool __fastcall IsRecruitableMission(const char* pName) JMP(0x5B36E0);
	constexpr static Mission MissionByName() JMP_THIS(0x5B3910);
	constexpr static const char* MissionNameOf(Mission mission) JMP_THIS(0x5B3950);
	constexpr int MissionTime() JMP_THIS(0x5B3A20);

protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline MissionClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}), UpdateTimer(noinit_t{}) {}
	MissionClass(noinit_t) : MissionClass(fake_noinit_t{}) {};
	MissionClass() : MissionClass(fake_noinit_t{}) JMP_THIS(0x5B2DA0);
};
static_assert(sizeof(MissionClass) == MissionClass::ClassSize);
