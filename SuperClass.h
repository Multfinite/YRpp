#pragma once

#include "SuperWeaponTypeClass.h"

class AnimClass;
class HouseClass;

/*!
* @brief SuperClass - handles super weapon behaviors and effects
*/
class NOVTABLE SuperClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F3FE8;
            this->IRTTITypeInfo = 0x7F3FCC;
            this->INoticeSink = 0x7F3FC4;
            this->INoticeSource = 0x7F3FBC;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::Super;
    static constexpr uintptr_t AbsVTable = 0x7F3FE8;
    static constexpr size_t ClassSize = 0x80;

public:
    static constexpr constant_ptr<DynamicVectorClass<SuperClass*>, 0xA83CB8u> const Array{};
    static constexpr reference<DynamicVectorClass<SuperClass*>, 0xA83D50u> const ShowTimers{};

public:
    int CustomChargeTime;
    SuperWeaponTypeClass* Type;
    HouseClass* Owner;
    CDTimerClass RechargeTimer;
    PROTECTED_PROPERTY(DWORD, unused_3C);
    bool BlinkState;
    PROTECTED_PROPERTY(BYTE, unused_41[7]);
    LARGE_INTEGER BlinkTimer;
    int SpecialSoundDuration;
    CoordStruct SpecialSoundLocation;
    bool CanHold;
    PROTECTED_PROPERTY(BYTE, unused_61);
    CellStruct ChronoMapCoords;
    PROTECTED_PROPERTY(BYTE, unused_66[2]);
    AnimClass* Animation;
    bool AnimationGotInvalid;
    bool IsPresent;
    bool IsOneTime;
    bool IsReady;
    bool IsSuspended;
    PROTECTED_PROPERTY(BYTE, unused_71[3]);
    int ReadyFrame;
    int CameoChargeState;
    ChargeDrainState ChargeDrainState;

public:
    virtual ~SuperClass() noexcept JMP_THIS(0x6CB120);
    
    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x6CDEB0);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x6CDEF0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x6CDFD0);
    
    void Detach(AbstractClass* target, bool all = true) override JMP_THIS(0x6CDFF0);
    RTTIType KindOf() const override JMP_THIS(0x6CE200);
    int SizeOf() const override JMP_THIS(0x6CE210);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6CE020);

    // Super weapon operations
    void CreateChronoAnim(CoordStruct coords) JMP_THIS(0x6CB3A0);
    void Reset() JMP_THIS(0x6CE0B0);
    bool SetOnHold(bool onHold) JMP_THIS(0x6CB4D0);
    bool Grant(bool oneTime, bool announce, bool onHold) JMP_THIS(0x6CB560);
    bool Lose() JMP_THIS(0x6CB7B0);
    bool IsPowered() const { return this->Type->IsPowered; }
    void Launch(const CellStruct& cell, bool isPlayer) JMP_THIS(0x6CC390);
    char CanFire() const JMP_THIS(0x6CC360);
    void SetReadiness(bool ready) JMP_THIS(0x6CB820);
    char StopPreclickAnim(bool isPlayer) JMP_THIS(0x6CB830);
    char ClickFire(bool isPlayer, const CellStruct& cell) JMP_THIS(0x6CB920);
    bool HasChargeProgressed(bool isPlayer) JMP_THIS(0x6CBCA0);
    signed int AnimStage() const JMP_THIS(0x6CBEE0);
    void SetCharge(int percentage) JMP_THIS(0x6CC1E0);
    int GetRechargeTime() const JMP_THIS(0x6CC260);
    void SetRechargeTime(int time) JMP_THIS(0x6CC280);
    void ResetRechargeTime() JMP_THIS(0x6CC290);
    const wchar_t* NameReadiness() const JMP_THIS(0x6CC2B0);
    bool ShouldDrawProgress() const JMP_THIS(0x6CDE90);
    bool ShouldFlashTab() const JMP_THIS(0x6CE1A0);

/*
    void Firestorm(int32_t a1, int32_t a2) JMP_THIS(0x6CDE80);
    void Forced_Charge(bool player) JMP_THIS(0x6CC080);
    void Impatient_Click() JMP_THIS(0x6CC070);
    bool Is_Powered() JMP_THIS(0x6CC2A0);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SuperClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    SuperClass(SuperWeaponTypeClass* pSWType, HouseClass* pOwner) noexcept : SuperClass(fake_noinit_t()) JMP_THIS(0x6CAF90);
    SuperClass() noexcept : SuperClass(fake_noinit_t{}) JMP_THIS(0x6CAEC0);
};
static_assert(sizeof(SuperClass) == SuperClass::ClassSize);

class LightningStorm
{
public:
    static constexpr reference<double, 0xB0CDD8u> const CloudHeightFactor{};
    static constexpr reference<CellStruct, 0xA9F9CCu> const Coords{};
    static constexpr reference<HouseClass*, 0xA9FACCu> const Owner{};
    static constexpr reference<int, 0xA9FAB8u> const Deferment{};
    static constexpr reference<int, 0x827FC4u> const Duration{};
    static constexpr reference<int, 0x827FC0u> const StartTime{};
    static constexpr reference<bool, 0xA9FAB4u> const Active{};
    static constexpr reference<bool, 0xA9FAD0u> const TimeToEnd{};

    static constexpr reference<DynamicVectorClass<AnimClass*>, 0xA9F9D0u> const CloudsPresent{};
    static constexpr reference<DynamicVectorClass<AnimClass*>, 0xA9FA60u> const CloudsManifesting{};
    static constexpr reference<DynamicVectorClass<AnimClass*>, 0xA9FA18u> const BoltsPresent{};

    static void Start(int duration, int deferment, CellStruct cell, HouseClass* pOwner)
    {
        PUSH_VAR32(pOwner); PUSH_VAR32(cell); SET_REG32(EDX, deferment); SET_REG32(ECX, duration); CALL(0x539EB0);
    }
    static void RequestStop() { CALL(0x53A090); }
    static bool HasDeferment() { CALL(0x53A0E0); }
    static void Strike(CellStruct cell) { PUSH_VAR32(cell); CALL(0x53A140); }
    static void Strike2(CoordStruct coords) JMP_STD(0x53A300);
    static void PrintMessage() { CALL(0x53AE00); }
    static void AI() JMP_STD(0x53A6C0);
    static void Init() JMP_STD(0x53AB50);
};

class PsyDom
{
public:
    static constexpr reference<PsychicDominatorStatus, 0xA9FAC0u> const Status{};
    static constexpr reference<CellStruct, 0xA9FA48u> const Coords{};
    static constexpr reference<HouseClass*, 0xA9FAC8u> const Owner{};
    static constexpr reference<AnimClass*, 0xA9FAC4u> const Anim{};

    static void Start(HouseClass* pOwner, CellStruct coords)
    { PUSH_VAR32(coords); SET_REG32(ECX, pOwner); CALL(0x53AE50); }
    static void AI() { CALL(0x53AF40); }
    static void Fire() { CALL(0x53B080); }
    static void PrintMessage() { CALL(0x53B410); }
    static bool Active() { CALL(0x53B400); }
};

class ChronoScreenEffect
{
public:
    static constexpr reference<int, 0xA9FAB0u> const Status{};
    static constexpr reference<int, 0xA9FA98u> const Duration{};

    static void Start(int duration) { SET_REG32(ECX, duration); CALL(0x53B460); }
    static void AI() { CALL(0x53B560); }
    static bool Active() { CALL(0x53BAD0); }
};

class NukeFlash
{
public:
    static constexpr reference<NukeFlashStatus, 0xA9FABCu> const Status{};
    static constexpr reference<int, 0x827FC8u> const StartTime{};
    static constexpr reference<int, 0x827FCCu> const Duration{};

    static void FadeIn() { CALL(0x53AB70); }
    static void FadeOut() { CALL(0x53AC50); }
    static bool IsFadingIn() { CALL(0x53A110); }
    static bool IsFadingOut() { CALL(0x53A120); }
};