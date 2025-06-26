#pragma once

#include "AbstractClass.h"

class ObjectClass;
class TechnoClass;
class TriggerTypeClass;

/*!
* @brief TriggerClass - handles trigger instances and their runtime behaviors
*/
class NOVTABLE TriggerClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7F5904;
            this->IRTTITypeInfo = 0x7F58E8;
            this->INoticeSink = 0x7F58E0;
            this->INoticeSource = 0x7F58D8;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::Trigger;
    static constexpr uintptr_t AbsVTable = 0x7F5904;
    static constexpr size_t ClassSize = 0x48;

public:
    static constexpr constant_ptr<DynamicVectorClass<TriggerClass*>, 0xA8EAE8u> const Array{};

public:
    TriggerTypeClass* Type;
    TriggerClass* NextTrigger;
    HouseClass* House;
    bool Destroyed;
    PROTECTED_PROPERTY(BYTE, align_31[3]);
    CDTimerClass Timer;
    DWORD OccuredEvents;
    bool Enabled;
    PROTECTED_PROPERTY(BYTE, padding_45[3]);

public:
    virtual ~TriggerClass() JMP_THIS(0x726140);

    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x726820);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x726860);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x7268D0);
    
    void Detach(AbstractClass* target, bool all = true) override JMP_THIS(0x726690);
    RTTIType KindOf() const override JMP_THIS(0x726940);
    int SizeOf() const override JMP_THIS(0x726930);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x726790);

    // TriggerClass specific
    bool HasCrossesHorizontalLineEvent() const JMP_THIS(0x726250);
    bool HasCrossesVerticalLineEvent() const JMP_THIS(0x726290);
    bool HasZoneEntryByEvent() const JMP_THIS(0x7262D0);
    bool HasAllowWinAction() const JMP_THIS(0x726310);
    bool HasGlobalSetOrClearedEvent(int idxGlobal) const JMP_THIS(0x726350);
    void NotifyGlobalChanged(int idxGlobal) JMP_THIS(0x7263A0);
    void NotifyLocalChanged(int idxLocal) JMP_THIS(0x7263D0);
    void ResetTimers() JMP_THIS(0x726400);
    void Destroy() JMP_THIS(0x726720);
    bool RegisterEvent(TriggerEvent event, ObjectClass* pObject, bool forceFire, bool persistent, TechnoClass* pSource) JMP_THIS(0x7264C0);
    bool FireActions(ObjectClass* pObj, CellStruct location) JMP_THIS(0x7265C0);

    static TriggerClass* __fastcall GetInstance(TriggerTypeClass* pType) JMP_STD(0x726630);

    // Helper methods
    constexpr void MarkEventAsOccured(int idx) { this->OccuredEvents |= (1u << idx); }
    constexpr void MarkEventAsNotOccured(int idx) { this->OccuredEvents &= ~(1u << idx); }
    constexpr bool HasEventOccured(int idx) const { return (this->OccuredEvents & (1u << idx)) != 0u; }
    constexpr bool HasBeenDestroyed() const { return this->Destroyed; }
    /*0x726920*/ constexpr void SetHouse(HouseClass* pHouse) { this->House = pHouse; }
    /*0x726910*/ constexpr HouseClass* GetHouse() const { return this->House; }
    /*0x7268F0*/ constexpr void Enable() { this->Enabled = true; this->ResetTimers(); }
    /*0x726900*/ constexpr void Disable() { this->Enabled = false; }

/*
    TriggerClass* Find_Or_Make() JMP_THIS(0x726630);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TriggerClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t()) {}

public:
    TriggerClass(TriggerTypeClass* pType) noexcept  : TriggerClass(fake_noinit_t()) 
        JMP_THIS(0x725FA0);
};
static_assert(sizeof(TriggerClass) == TriggerClass::ClassSize);