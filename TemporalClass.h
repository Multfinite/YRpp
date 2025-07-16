#pragma once

#include "AbstractClass.h"

class SuperClass;
class TechnoClass;

class __declspec(uuid("94112424-E403-11D3-8E6E-005004AAB2FB"))
NOVTABLE TemporalClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F5180;
            this->IRTTITypeInfo = 0x7F5164;
            this->INoticeSink = 0x7F515C;
            this->INoticeSource = 0x7F5154;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Temporal;
    static constexpr uintptr_t AbsVTable = 0x7F5180;
    static constexpr size_t ClassSize = 0x50;

public:
    DEFINE_POINTER(DynamicVectorClass<TemporalClass*>, Array, 0xB0EC60u)

public:
    TechnoClass* Owner;
    TechnoClass* Target;
    CDTimerClass LifeTimer;
    void* unknown_pointer_38;
    SuperClass* SourceSW;
    TemporalClass* NextTemporal;
    TemporalClass* PrevTemporal;
    int WarpRemaining;
    int WarpPerStep;

public:
    virtual ~TemporalClass() JMP_THIS(0x71A5D0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x71A720);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x71A660);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x71A700);
    
    RTTIType KindOf() const override JMP_THIS(0x71B1A0);
    int SizeOf() const override JMP_THIS(0x71B190);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x71A650);
    void AI() override JMP_THIS(0x71A760);

    void Fire(TechnoClass* pTarget) JMP_THIS(0x71AF20);
    bool CanWarpTarget(TechnoClass* pTarget) const JMP_THIS(0x71AE50);
    int GetWarpPerStep(int nHelperCount = 0) const JMP_THIS(0x71AB10);
    void LetGo() JMP_THIS(0x71ABC0);
    void JustLetGo() JMP_THIS(0x71AD40);
    void InvalidatePointer() JMP_THIS(0x71ADE0);

/*
    void Clear_Target() JMP_THIS(0x71ACB0);
    void Clear_Target_Building() JMP_THIS(0x71ACD0);
    BuildingClass* Detach(int32_t a2) JMP_THIS(0x71AB60);
    int32_t Release() JMP_THIS(0x71ADB0);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TemporalClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    TemporalClass() : TemporalClass(fake_noinit_t{}) JMP_THIS(0x71A450);
    TemporalClass(noinit_t) noexcept : TemporalClass(fake_noinit_t{}) JMP_THIS(0x71A5A0);
    TemporalClass(TechnoClass* pOwnerUnit) : TemporalClass(fake_noinit_t{}) JMP_THIS(0x71A4E0);
};
static_assert(sizeof(TemporalClass) == TemporalClass::ClassSize);