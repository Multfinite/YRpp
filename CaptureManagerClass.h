#pragma once

#include "AbstractClass.h"

class HouseClass;
class TechnoClass;

struct ControlNode
{
    explicit ControlNode() noexcept {}

    TechnoClass* Unit;
    HouseClass* OriginalOwner;
    DECLARE_PROPERTY(CDTimerClass, LinkDrawTimer);
};

/*!
* @brief CaptureManager - used for mind control.
*/
class __declspec(uuid("0679E982-AD9D-11D3-BE16-00104B62A16C"))
NOVTABLE CaptureManagerClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7E4B40;
            this->IRTTITypeInfo = 0x7E4B24;
            this->INoticeSink = 0x7E4B1C;
            this->INoticeSource = 0x7E4B14;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::CaptureManager;
    static constexpr uintptr_t AbsVTable = 0x7E4B40;
    static constexpr size_t ClassSize = 0x50;

public:
    static constexpr constant_ptr<DynamicVectorClass<CaptureManagerClass*>, 0x89E0F0u> const Array{};

public:
    DynamicVectorClass<ControlNode*> ControlNodes;
    int MaxControlNodes;
    bool InfiniteMindControl;
    bool OverloadDeathSoundPlayed;
    int OverloadPipState;
    TechnoClass* Owner;
    int OverloadDamageDelay;

public:
    virtual ~CaptureManagerClass() JMP_THIS(0x4719A0);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x472960);

    HRESULT Load(IStream* pStm) override JMP_STD(0x472720);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4728E0);
    
    RTTIType KindOf() const override JMP_THIS(0x4729B0);
    int SizeOf() const override JMP_THIS(0x4729A0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x4726F0);

    bool CaptureUnit(TechnoClass* pUnit) JMP_THIS(0x471D40);
    bool FreeUnit(TechnoClass* pUnit) JMP_THIS(0x471FF0);
    void FreeAll() JMP_THIS(0x472140);
    int NumControlNodes() const JMP_THIS(0x4722D0);
    bool CanCapture(TechnoClass* Target) const JMP_THIS(0x471C90);
    bool CannotControlAnyMore() const JMP_THIS(0x4722A0);
    bool IsControllingSomething() const JMP_THIS(0x4722C0);
    bool IsOverloading(bool* wasDamageApplied) const JMP_THIS(0x4726C0);
    void HandleOverload() JMP_THIS(0x471A50);
    bool NeedsToDrawLinks() const JMP_THIS(0x472640);
    bool DrawLinks() JMP_THIS(0x472160);
    /*! @brief AI_Capture */
    void DecideUnitFate(TechnoClass* Unit) JMP_THIS(0x4723B0);
    HouseClass* GetOriginalOwner(TechnoClass* Unit) const JMP_THIS(0x4722F0);
/*
    int32_t Can_Control_Only_One() JMP_THIS(0x4722E0);
    int8_t Detach(int32_t a2) JMP_THIS(0x471F90);
    HouseClass* GetOriginalOwner(int32_t a2) JMP_THIS(0x4722F0);
    bool Set_Owner_To_Civilian(TechnoClass* techno) JMP_THIS(0x472330);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline CaptureManagerClass(fake_noinit_t) noexcept
        : AbstractClass(fake_noinit_t{})
    { }

public:
    CaptureManagerClass(noinit_t) noexcept : CaptureManagerClass(fake_noinit_t{}) JMP_THIS(00471950);
    CaptureManagerClass() : CaptureManagerClass(fake_noinit_t{}) JMP_THIS(0x471890);
    CaptureManagerClass(TechnoClass* pOwner, int nMaxControlNodes, bool bInfiniteControl) noexcept
        : CaptureManagerClass(fake_noinit_t{})
    JMP_THIS(0x4717D0);
};
static_assert(sizeof(CaptureManagerClass) == CaptureManagerClass::ClassSize);