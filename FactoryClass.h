#pragma once

#include "AbstractClass.h"
#include "StageClass.h"

class HouseClass;
class TechnoClass;
class TechnoTypeClass;

/*!
* @brief Factories are responsible for producing units and buildings. 
*/
class __declspec(uuid("34ECD9A8-0AB0-11D2-ACA7-006008055BB5"))
NOVTABLE FactoryClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E88D0;
            this->IRTTITypeInfo = 0x7E88B4;
            this->INoticeSink = 0x7E88AC;
            this->INoticeSource = 0x7E88A4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Factory;
    static constexpr uintptr_t AbsVTable = 0x7E88D0;
    static constexpr size_t ClassSize = 0x74;

public:
    static constexpr constant_ptr<DynamicVectorClass<FactoryClass*>, 0xA83E30u> const Array{};

public:
    StageClass Production;
    DynamicVectorClass<TechnoTypeClass*> QueuedObjects;
    TechnoClass* Object;
    bool OnHold;
    bool IsDifferent;
    PROTECTED_PROPERTY(BYTE, align_5E[2]);
    int Balance;
    int OriginalBalance;
    int SpecialItem;
    HouseClass* Owner;
    bool IsSuspended;
    bool IsManual;
    PROTECTED_PROPERTY(BYTE, padding_72[2]);

public:
    virtual ~FactoryClass() JMP_THIS(0x4C9A10);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x4CA230);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x4CA270);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4CA3C0);
    
    void InvalidatePointer(AbstractClass* target, bool all = true) override JMP_THIS(0x4CA580);
    RTTIType KindOf() const override JMP_THIS(0x4CA750);
    int SizeOf() const override JMP_THIS(0x4CA760);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x4CA430);
    void AI() override JMP_THIS(0x4C9B20);

    bool HasProgressChanged() JMP_THIS(0x4C9C60);
    bool DemandProduction(TechnoTypeClass const* pType, HouseClass* pOwner, bool shouldQueue) JMP_THIS(0x4C9C70);
    void SetObject(TechnoClass* pObject) JMP_THIS(0x4C9E10);
    bool Suspend(bool manual) JMP_THIS(0x4C9E60);
    bool Unsuspend(bool manual) JMP_THIS(0x4C9EA0);
    int GetBuildTimeFrames() const JMP_THIS(0x4C9FB0);
    bool AbandonProduction() JMP_THIS(0x4C9FF0);
    int GetProgress() const JMP_THIS(0x4CA120);
    bool IsDone() const JMP_THIS(0x4CA130);
    int GetCostPerStep() const JMP_THIS(0x4CA180);
    bool CompletedProduction() JMP_THIS(0x4CA1A0);
    void StartProduction() JMP_THIS(0x4CA5A0);
    bool RemoveOneFromQueue(TechnoTypeClass const* pItem) JMP_THIS(0x4CA620);
    int CountTotal(TechnoTypeClass const* pType) const JMP_THIS(0x4CA670);
    bool IsQueued(TechnoTypeClass const* pType) const JMP_THIS(0x4CA6B0);

/*
    FootClass* Get_Object() JMP_THIS(0x4CA160);
    int32_t Get_Special_Item() JMP_THIS(0x4CA170);
    bool On_Hold() JMP_THIS(0x4C9C50);
    int32_t Total_Techno_Queued(TechnoTypeClass* techno) JMP_THIS(0x4CA670);
*/

    // Static helper
    static FactoryClass* FindByOwnerAndProduct(HouseClass const* const pHouse, TechnoTypeClass const* const pItem)
    {
        for (auto const& pFact : *FactoryClass::Array) {
            if (pFact->Owner == pHouse) {
                if (pFact->CountTotal(pItem) > 0) {
                    return pFact;
                }
            }
        }
        return nullptr;
    }

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline FactoryClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}
public:
    FactoryClass() : FactoryClass(fake_noinit_t{}) JMP_THIS(0x4C98B0);
    FactoryClass(noinit_t) noexcept : FactoryClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(FactoryClass) == FactoryClass::ClassSize);