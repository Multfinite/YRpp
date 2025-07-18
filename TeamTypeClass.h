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

public:
    ABSTRACTTYPE_ARRAY(TeamTypeClass, 0xA8ECA0u);

public:
    int ArrayIndex;
    int Group;
    int VeteranLevel;
    bool Loadable;
    bool Full;
    bool Annoyance;
    bool GuardSlower;
    bool Recruiter;
    bool Autocreate;
    bool Prebuild;
    bool Reinforce;
    bool Whiner;
    bool Aggressive;
    bool LooseRecruit;
    bool Suicide;
    bool Droppod;
    bool UseTransportOrigin;
    bool DropshipLoadout;
    bool OnTransOnly;
    int Priority;
    int Max;
    int field_BC;
    int MindControlDecision;
    HouseClass* Owner;
    int idxHouse;
    int TechLevel;
    TagClass* Tag;
    int Waypoint;
    int TransportWaypoint;
    int cntInstances;
    ScriptTypeClass* ScriptType;
    TaskForceClass* TaskForce;
    int IsGlobal;
    int field_EC;
    bool field_F0;
    bool field_F1;
    bool AvoidThreats;
    bool IonImmune;
    bool TransportsReturnOnUnload;
    bool AreTeamMembersRecruitable;
    bool IsBaseDefense;
    bool OnlyTargetHouseEnemy;

public:
    virtual ~TeamTypeClass() JMP_THIS(0x6F08F0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6F1C40);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6F1BB0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6F1B90);
    
    void InvalidatePointer(AbstractClass* instance, bool all = true) override JMP_THIS(0x6F1030);
    RTTIType KindOf() const override JMP_THIS(0x6F20A0);
    int SizeOf() const override JMP_THIS(0x6F20B0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6F1C80);
    
    int GetArrayIndex() const override JMP_THIS(0x6F20C0);
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6F1090);
    bool SaveToINI(CCINIClass* pINI) override JMP_THIS(0x6F1550);


    static bool LoadFromINIList(CCINIClass* pINI, bool IsGlobal) { PUSH_VAR8(IsGlobal); SET_REG32(ECX, pINI); CALL(0x6F19B0); }
    TeamClass* CreateTeam(HouseClass* pHouse) JMP_THIS(0x6F09C0);
    void DestroyAllInstances() JMP_THIS(0x6F0A70);
    int GetGroup() const JMP_THIS(0x6F1870);
    CellStruct* GetWaypoint(CellStruct* retstr) const JMP_THIS(0x6F18A0);
    CellStruct* GetTransportWaypoint(CellStruct* retstr) const JMP_THIS(0x6F18E0);
    bool CanRecruitUnit(FootClass* pUnit, HouseClass* pOwner) const JMP_THIS(0x6F1320);
    void FlashAllInstances(int Duration) JMP_THIS(0x6F1F30);
    TeamClass* FindFirstInstance() const JMP_THIS(0x6F1F70);
    void ProcessTaskForce() JMP_THIS(0x6F1FA0);
    static void ProcessAllTaskforces() JMP_STD(0x6F2040);
    HouseClass* GetHouse() const JMP_THIS(0x6F2070);

/*
    bool Can_Recruit(FootClass * obj, HouseClass * house) JMP_THIS(0x6F1E20);
    TeamTypeClass * Find_Or_Make() JMP_THIS(0x6F1920);
    TeamTypeClass * From_Name() JMP_THIS(0x6F0FC0);
    TeamTypeClass * Suggested_New_Team(HouseClass * house, bool alerted) JMP_THIS(0x6F0AB0);
    void Write_Scenario_INI(int32_t a2) JMP_THIS(0x6F1AB0);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TeamTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}

public:
    TeamTypeClass(const char* pID) : TeamTypeClass(fake_noinit_t{}) JMP_THIS(0x6F06E0);
};
static_assert(sizeof(TeamTypeClass) == TeamTypeClass::ClassSize);
