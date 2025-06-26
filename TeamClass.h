#pragma once

#include "TeamTypeClass.h"
#include "AbstractClass.h"

class HouseClass;
class FootClass;
class CellClass;
class ScriptClass;
class TagClass;

/*!
* @brief TeamClass - handles team behaviors and management
*/
class NOVTABLE TeamClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7F4730;
            this->IRTTITypeInfo = 0x7F4714;
            this->INoticeSink = 0x7F470C;
            this->INoticeSource = 0x7F4704;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::Team;
    static constexpr uintptr_t AbsVTable = 0x7F4730;
    static constexpr size_t ClassSize = 0xA0;

public:
    static constexpr constant_ptr<DynamicVectorClass<TeamClass*>, 0x8B40E8u> const Array{};

public:
    TeamTypeClass* Type;
    ScriptClass* CurrentScript;
    HouseClass* Owner;
    HouseClass* Target;
    CellClass* SpawnCell;
    FootClass* ClosestMember;
    AbstractClass* QueuedFocus;
    AbstractClass* Focus;
    int unknown_44;
    int TotalObjects;
    int TotalThreatValue;
    int CreationFrame;
    FootClass* FirstUnit;
    CDTimerClass GuardAreaTimer;
    CDTimerClass SuspendTimer;
    TagClass* Tag;
    bool IsTransient;
    bool NeedsReGrouping;
    bool GuardSlowerIsNotUnderStrength;
    bool IsForcedActive;
    bool IsHasBeen;
    bool IsFullStrength;
    bool IsUnderStrength;
    bool IsReforming;
    bool IsLagging;
    bool NeedsToDisappear;
    bool JustDisappeared;
    bool IsMoving;
    bool StepCompleted;
    bool TargetNotAssigned;
    bool IsLeavingMap;
    bool IsSuspended;
    bool AchievedGreatSuccess;
    int CountObjects[6];

public:
	virtual ~TeamClass() JMP_THIS(0x6E8DE0);

	HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x6EC560);
	
	HRESULT Load(IStream* pStm) override JMP_THIS(0x6EC450);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x6EC540);
	
	void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x6EAE60);
	RTTIType KindOf() const override JMP_THIS(0x6F0440);
	int SizeOf() const override JMP_THIS(0x6F0430);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6EC5A0);
	void AI() override JMP_THIS(0x6E9140);

    void GetTaskForceMissingMemberTypes(DynamicVectorClass<TechnoTypeClass*>& dest) const JMP_THIS(0x6EF4D0);
    void LiberateMember(FootClass* pFoot, int idx = -1, byte count = 0) JMP_THIS(0x6EA870);
    bool AddMember(FootClass* pFoot, bool bForce) JMP_THIS(0x6EA500);
    void AssignMissionTarget(AbstractClass* pTarget) JMP_THIS(0x6E9050);

/*
		bool Add(FootClass * a2) JMP_THIS(0x6EA4F0);
		bool Add(FootClass * obj, int8_t arg_4) JMP_THIS(0x6EA500);
		void Assign_Mission_Target(TechnoClass * new_target) JMP_THIS(0x6E9050);
		void Calc_Center(FootClass * * a2, FootClass * * a3) JMP_THIS(0x6EAEE0);
		bool Can_Add(UnitClass * a2, int32_t * entry, int8_t somebool) JMP_THIS(0x6EA610);
		void Coordinate_Attack() JMP_THIS(0x6EB490);
		bool Coordinate_Conscript(FootClass * a2) JMP_THIS(0x6EC130);
		bool Coordinate_Do(int32_t , int32_t ) JMP_THIS(0x6ED7E0);
		void Coordinate_Move() JMP_THIS(0x6EBAD0);
		bool Coordinate_Regroup() JMP_THIS(0x6EB870);
		int8_t Does_Any_Member_Have_Ammo() JMP_THIS(0x6F03F0);
		FootClass * Fetch_A_Leader() JMP_THIS(0x6EC3D0);
		void Flash_For(int32_t a2) JMP_THIS(0x6EF5F0);
		int32_t Get_Stray() JMP_THIS(0x6F03B0);
		int8_t has_aircraft() JMP_THIS(0x6EF470);
		bool Has_Entered_Map() JMP_THIS(0x6EC370);
		bool Is_A_Member(FootClass * member) JMP_THIS(0x6EC220);
		bool Is_Leaving_Map() JMP_THIS(0x6EC300);
		bool Lagging_Units() JMP_THIS(0x6EBF50);
		bool Recalculate() JMP_THIS(0x6EA3E0);
		bool Recruit(uint64_t ) JMP_THIS(0x6EAA90);
		void Regroup() JMP_THIS(0x6EA0D0);
		bool Remove(FootClass * obj, int32_t typeindex, int32_t somebool) JMP_THIS(0x6EA870);
		void Scan_Limit() JMP_THIS(0x6EC3A0);
		void Suspend_Teams(HouseClass * house) JMP_THIS(0x6EC250);
		TeamClass * TeamClass(TeamTypeClass * teamtype, HouseClass * owner, int32_t investigate_me) JMP_THIS(0x6E8A90);
		void TeamClass() JMP_THIS(0x6E8DE0);
		bool TMission_Attack(int32_t , int32_t ) JMP_THIS(0x6ED090);
		bool TMission_Attack_Building_At_Waypoint(int32_t arg_0, int8_t a3) JMP_THIS(0x6ECA70);
		bool TMission_Attack_Enemy_Building(int32_t a2, int8_t a3) JMP_THIS(0x6EE310);
		bool TMission_Attack_Waypoint(int32_t arg0, int8_t a3) JMP_THIS(0x6EC9A0);
		void TMission_Begin_Production(int32_t a2, int32_t a3) JMP_THIS(0x6EDF90);
		void TMission_Center_View_On_Team(int32_t a2, int32_t a3) JMP_THIS(0x6EE100);
		void TMission_Change_House(int32_t a2) JMP_THIS(0x6ECF50);
		int8_t TMission_Change_Script(int32_t a2) JMP_THIS(0x6ED030);
		void TMission_Change_Team(TeamMissionClass * a2, bool ) JMP_THIS(0x6ECFB0);
		bool TMission_Clear_Global(int32_t a2, int32_t a3) JMP_THIS(0x6EDAC0);
		bool TMission_Clear_Local(int32_t a2, int32_t a3) JMP_THIS(0x6EDB20);
		void TMission_Delete_Members(int32_t a2, int32_t a3) JMP_THIS(0x6EE050);
		bool TMission_Deploy(int32_t , int32_t ) JMP_THIS(0x6ED4D0);
		void TMission_Enter_Bio_Reactor(int32_t a2, int32_t a3) JMP_THIS(0x6ECBF0);
		void TMission_Enter_Grinder(int32_t a2, int32_t a3) JMP_THIS(0x6ECB50);
		void TMission_Fire_Sale(int32_t a2, int32_t a3) JMP_THIS(0x6EDFB0);
		void TMission_Flash(uint64_t a2, int8_t a3) JMP_THIS(0x6EF5C0);
		void TMission_Follow(int32_t a2, int32_t a3) JMP_THIS(0x6EDB50);
		void TMission_Force_Facing(int32_t arg0, int32_t a3) JMP_THIS(0x6EDCA0);
		void TMission_Garrison_Building(int32_t a2, int32_t a3) JMP_THIS(0x6ECC90);
		void TMission_Gather_At_Base(int32_t a2, int32_t a3) JMP_THIS(0x6EFA10);
		void TMission_Gather_At_Enemy(TeamMissionClass * , bool ) JMP_THIS(0x6EF700);
		void TMission_Go_Berzerk(int32_t a2, int32_t a3) JMP_THIS(0x6EDD90);
		void TMission_Go_to_Shroud(TeamMissionClass * a2, int8_t a3) JMP_THIS(0x6EC730);
		void TMission_Guard(int32_t a2, int8_t a3) JMP_THIS(0x6ED770);
		int32_t TMission_Idle_Anim(int32_t a2, int32_t a3) JMP_THIS(0x6EDDC0);
		void TMission_Ion_Storm_End(int32_t a2, int32_t a3) JMP_THIS(0x6EE0E0);
		void TMission_Ion_Storm_Start(int32_t a2, int32_t a3) JMP_THIS(0x6EE0A0);
		void TMission_Iron_Curtain_Me(ScriptMissionClass * a2, bool ) JMP_THIS(0x6EFC70);
		bool TMission_Load(int32_t , int32_t ) JMP_THIS(0x6ED200);
		void TMission_Load_Truck(int32_t a2, int32_t a3) JMP_THIS(0x6EE2A0);
		void TMission_Loop(int32_t a2, int32_t a3) JMP_THIS(0x6EDE10);
		void TMission_Move_To_Cell(TeamMissionClass * , Cell a2) JMP_THIS(0x6EC770);
		bool TMission_Move_To_Enemy_Building(int32_t arg0, int32_t arg1) JMP_THIS(0x6EE3F0);
		void TMission_Move_To_Own_Building(int32_t a2, int32_t a3) JMP_THIS(0x6EE5C0);
		bool TMission_Move_To_Waypoint(int32_t a2, Cell arg4) JMP_THIS(0x6EC7D0);
		void TMission_Occupy_Battle_Bunker(int32_t a2, int32_t a3) JMP_THIS(0x6ECC40);
		void TMission_Occupy_Tank_Bunker(int32_t a2, int32_t a3) JMP_THIS(0x6ECBA0);
		void TMission_Panic(int32_t a2, int32_t a3) JMP_THIS(0x6EDD60);
		bool TMission_Patrol(int32_t , int32_t ) JMP_THIS(0x6ECCE0);
		void TMission_Play_Animation(ScriptMissionClass * , bool ) JMP_THIS(0x6EF610);
		void TMission_Play_Movie(int32_t a2, int32_t a3) JMP_THIS(0x6EDEC0);
		void TMission_Play_Music(int32_t a2, int32_t a3) JMP_THIS(0x6EDEF0);
		void TMission_Play_Sound(int32_t a2, int32_t a3) JMP_THIS(0x6EDE90);
		void TMission_Play_Speech(int32_t a2, int32_t a3) JMP_THIS(0x6EDE80);
		int8_t TMission_Player_Loses(int32_t a2, int32_t a3) JMP_THIS(0x6EDE60);
		int8_t TMission_Player_Wins(int32_t a2, int32_t a3) JMP_THIS(0x6EDE40);
		void TMission_Reduce_Tiberium(int32_t a2, int32_t a3) JMP_THIS(0x6EDF10);
		void TMission_Reshroud_Map(int32_t a2, int32_t a3) JMP_THIS(0x6EE1B0);
		void TMission_Reveal_Map(int32_t a2, int32_t a3) JMP_THIS(0x6EE1D0);
		bool TMission_Scatter(int32_t , int32_t ) JMP_THIS(0x6ECF10);
		void TMission_Scout(int32_t a2_1, int32_t a3) JMP_THIS(0x6EE800);
		void TMission_Self_Destruct(int32_t a2, int32_t a3) JMP_THIS(0x6EDFD0);
		bool TMission_Set_Global(int32_t , int32_t ) JMP_THIS(0x6EDA90);
		bool TMission_Set_Local(int32_t a2, int32_t a3) JMP_THIS(0x6EDAF0);
		bool TMission_Spy(int32_t , int32_t ) JMP_THIS(0x6ECE60);
		void TMission_Success(int32_t a2, int32_t a3) JMP_THIS(0x6EF450);
		void TMission_Talk_Bubble(ScriptMissionClass * , bool ) JMP_THIS(0x6EF6D0);
		bool TMission_Unload(int32_t arg0, int32_t a3) JMP_THIS(0x6EF110);
		void TMission_Unload_Truck(int32_t a2, int32_t a3) JMP_THIS(0x6EE230);
		int32_t TMission_Unpanic(int32_t a2, int32_t a3) JMP_THIS(0x6EDC70);
		void TMission_Wait_Until_Loaded(int32_t a2, int32_t a3) JMP_THIS(0x6EE1F0);
		void Took_Damage(FootClass * a2, ResultType result, ObjectClass * source) JMP_THIS(0x6EB380);

*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TeamClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}

public:
    TeamClass(TeamTypeClass* pType, HouseClass* pOwner, int _unknown_44) noexcept : TeamClass(fake_noinit_t())
        JMP_THIS(0x6E8A90);
	TeamClass(noinit_t) : TeamClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(TeamClass) == TeamClass::ClassSize);