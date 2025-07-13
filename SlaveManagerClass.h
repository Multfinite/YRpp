#pragma once

#include "AbstractClass.h"

class HouseClass;
class InfantryClass;

enum class SlaveManagerStatus : unsigned int {
    Ready = 0,
    Scanning = 1,
    Travelling = 2,
    Deploying = 3,
    Working = 4,
    ScanningAgain = 5,
    PackingUp = 6
};

enum class SlaveControlStatus : unsigned int {
    Unknown = 0,
    ScanningForTiberium = 1,
    MovingToTiberium = 2,
    Harvesting = 3,
    BringingItBack = 4,
    Respawning = 5,
    Dead = 6
};

class __declspec(uuid("335AAFE4-2DA6-11D5-BE22-00104B62A16C"))
NOVTABLE SlaveManagerClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct SlaveControl {
        InfantryClass* Slave;
        SlaveControlStatus State;
        CDTimerClass RespawnTimer;
    };

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F31C8;
            this->IRTTITypeInfo = 0x7F31AC;
            this->INoticeSink = 0x7F31A4;
            this->INoticeSource = 0x7F319C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::SlaveManager;
    static constexpr uintptr_t AbsVTable = 0x7F31C8;
    static constexpr size_t ClassSize = 0x64;

public:
    static constexpr constant_ptr<DynamicVectorClass<SlaveManagerClass*>, 0xB0B5F0u> const Array{};

public:
    TechnoClass* Owner;
    InfantryTypeClass* SlaveType;
    int SlaveCount;
    int RegenRate;
    int ReloadRate;
    DynamicVectorClass<SlaveControl*> SlaveNodes;
    CDTimerClass RespawnTimer;
    SlaveManagerStatus State;
    int LastScanFrame;

public:
    virtual ~SlaveManagerClass() JMP_THIS(0x6AF4A0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6B1130);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6B1170);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6B1300);
    
    RTTIType KindOf() const override JMP_THIS(0x6B1380);
    int SizeOf() const override JMP_THIS(0x6B1370);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6B10F0);
    void AI() override JMP_THIS(0x6AF5F0);

    void SetOwner(TechnoClass* NewOwner) JMP_THIS(0x6AF580);
    void CreateSlave(SlaveControl* Node) JMP_THIS(0x6AF650);
    void LostSlave(InfantryClass* Slave) JMP_THIS(0x6B0A20);
    void Deploy2() JMP_THIS(0x6B0D60);
    void Killed(TechnoClass* Killer, HouseClass* ForcedOwnerHouse = nullptr) JMP_THIS(0x6B0AE0);
    bool ShouldWakeUpNow() JMP_THIS(0x6B1020);

/*
    Cell* Cell1(Cell* a2) JMP_THIS(0x6B0690);
    Cell* Cell2(Cell* a2) JMP_THIS(0x6B0750);
    bool Cell3(InfantryClass* infantry, CellClass* cell) JMP_THIS(0x6B0880);
    void Create_Slave(SlaveControl* ctrl) JMP_THIS(0x6AF650);
    void Deploy1() JMP_THIS(0x6B0D10);
    uint32_t* Find_More_Ore(uint32_t* a2) JMP_THIS(0x6B02C0);
    int32_t Found_More_Ore() JMP_THIS(0x6B0260);
    void Guard() JMP_THIS(0x6B0CC0);
    void Harvest() JMP_THIS(0x6B0DB0);
    void Idle() JMP_THIS(0x6B0C80);
    void Owner_AI() JMP_THIS(0x6AFD60);
    void Recall_Slaves() JMP_THIS(0x6B0490);
    void Release_A_Slave(int32_t a2) JMP_THIS(0x6B0A90);
    void Send_Slaves() JMP_THIS(0x6B04C0);
    void Set_State(int32_t a2) JMP_THIS(0x6B10D0);
    uint64_t Slave_AI() JMP_THIS(0x6AF6C0);
    int** Where_To_Deploy(int** a2, int32_t a3) JMP_THIS(0x6B0300);
*/

    // Helper methods
    void ZeroOutSlaves();
    void SuspendWork() {
        this->RespawnTimer.StartTime = -1;
        if (!this->RespawnTimer.TimeLeft) {
            this->RespawnTimer.TimeLeft = 1;
        }
    }
    void ResumeWork() {
        this->RespawnTimer.Resume();
    }

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SlaveManagerClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    SlaveManagerClass(TechnoClass* pOwner, InfantryTypeClass* pSlave, int num, int RegenRate, int ReloadRate) noexcept
        : SlaveManagerClass(fake_noinit_t{}) JMP_THIS(0x6AF1A0);
    SlaveManagerClass() : SlaveManagerClass(fake_noinit_t{}) JMP_THIS(0x6AF360);
    SlaveManagerClass(noinit_t) noexcept : SlaveManagerClass(fake_noinit_t{}) JMP_THIS(0x6AF440);
};
static_assert(sizeof(SlaveManagerClass) == SlaveManagerClass::ClassSize);