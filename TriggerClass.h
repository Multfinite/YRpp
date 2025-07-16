#pragma once

#include "AbstractClass.h"

class ObjectClass;
class TechnoClass;
class TriggerTypeClass;

class __declspec(uuid("C02D1590-0A2A-11D2-ACA7-006008055BB5"))
NOVTABLE TriggerClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F5904;
            this->IRTTITypeInfo = 0x7F58E8;
            this->INoticeSink = 0x7F58E0;
            this->INoticeSource = 0x7F58D8;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Trigger;
    static constexpr uintptr_t AbsVTable = 0x7F5904;
    static constexpr size_t ClassSize = 0x48;

public:
    DEFINE_POINTER(DynamicVectorClass<TriggerClass*>, Array, 0xA8EAE8u)

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

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x726820);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x726860);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x7268D0);
    
    void InvalidatePointer(AbstractClass* target, bool all = true) override JMP_THIS(0x726690);
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
    void MarkEventAsOccured(int idx) { this->OccuredEvents |= (1u << idx); }
    void MarkEventAsNotOccured(int idx) { this->OccuredEvents &= ~(1u << idx); }
    bool HasEventOccured(int idx) const { return (this->OccuredEvents & (1u << idx)) != 0u; }
    bool HasBeenDestroyed() const { return this->Destroyed; }
    /*0x726920*/ void SetHouse(HouseClass* pHouse) { this->House = pHouse; }
    /*0x726910*/ HouseClass* GetHouse() const { return this->House; }
    /*0x7268F0*/ void Enable() { this->Enabled = true; this->ResetTimers(); }
    /*0x726900*/ void Disable() { this->Enabled = false; }

/*
    TriggerClass* Find_Or_Make() JMP_THIS(0x726630);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TriggerClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}

public:
    TriggerClass(TriggerTypeClass* pType) : TriggerClass(fake_noinit_t{}) JMP_THIS(0x725FA0);
};
static_assert(sizeof(TriggerClass) == TriggerClass::ClassSize);