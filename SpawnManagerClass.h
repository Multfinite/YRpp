#pragma once

#include "AircraftClass.h"

enum class SpawnManagerStatus : unsigned int {
    Idle = 0,       // no target or out of range
    Launching = 1,  // one launch in progress
    CoolDown = 2    // waiting for launch to complete
};

enum class SpawnNodeStatus : unsigned int {
    Idle = 0,       // docked, waiting for target
    TakeOff = 1,    // missile tilting and launch
    Preparing = 2,  // gathering, waiting
    Attacking = 3,  // attacking until no ammo
    Returning = 4,  // return to carrier
    // 5 unused
    Reloading = 6,  // docked, reloading ammo and health
    Dead = 7        // respawning
};

struct SpawnControl {
    AircraftClass* Unit;
    SpawnNodeStatus Status;
    CDTimerClass SpawnTimer;
    BOOL IsSpawnMissile;
};

class __declspec(uuid("0679E981-AD9D-11D3-BE16-00104B62A16C"))
NOVTABLE SpawnManagerClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F3650;
            this->IRTTITypeInfo = 0x7F3634;
            this->INoticeSink = 0x7F362C;
            this->INoticeSource = 0x7F3624;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::SpawnManager;
    static constexpr uintptr_t AbsVTable = 0x7F3650;
    static constexpr size_t ClassSize = 0x74;

public:
    DEFINE_REFERENCE(DynamicVectorClass<SpawnManagerClass*>, Array, 0xB0B880u)

public:
    TechnoClass* Owner;
    AircraftTypeClass* SpawnType;
    int SpawnCount;
    int RegenRate;
    int ReloadRate;
    DynamicVectorClass<SpawnControl*> SpawnedNodes;
    CDTimerClass UpdateTimer;
    CDTimerClass SpawnTimer;
    AbstractClass* Target;
    AbstractClass* NewTarget;
    SpawnManagerStatus Status;

public:
    virtual ~SpawnManagerClass() JMP_THIS(0x6B7010);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6B7ED0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6B7F10);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6B80B0);
    
    RTTIType KindOf() const override JMP_THIS(0x6B8130);
    int SizeOf() const override JMP_THIS(0x6B8120);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6B7DE0);
    void AI() override JMP_THIS(0x6B7230); 

    void KillNodes() JMP_THIS(0x6B7100);
    void SetTarget(AbstractClass* pTarget) JMP_THIS(0x6B7B90);
    bool UpdateTarget() JMP_THIS(0x6B7C40);
    void ResetTarget() JMP_THIS(0x6B7BB0);
    int CountAliveSpawns() const JMP_THIS(0x6B7D30);
    int CountDockedSpawns() const JMP_THIS(0x6B7D50);
    int CountLaunchingSpawns() const JMP_THIS(0x6B7D80);
    void UnlinkPointer() JMP_THIS(0x6B7C60);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SpawnManagerClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    SpawnManagerClass(TechnoClass* pOwner, AircraftTypeClass* pSpawnType, int nMaxNodes,
        int RegenRate, int ReloadRate) : SpawnManagerClass(fake_noinit_t{}) JMP_THIS(0x6B6C90);
    SpawnManagerClass() : SpawnManagerClass(fake_noinit_t{}) JMP_THIS(0x6B6EA0);
    SpawnManagerClass(noinit_t) noexcept : SpawnManagerClass(fake_noinit_t{}) JMP_THIS(0x6B6FA0);
};

static_assert(sizeof(SpawnManagerClass) == SpawnManagerClass::ClassSize);