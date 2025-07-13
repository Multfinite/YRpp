#pragma once

#include "AbstractTypeClass.h"

class CCINIClass;
class TriggerTypeClass;

class __declspec(uuid("54F6E433-09ED-11D2-ACA5-006008055BB5"))
NOVTABLE TagTypeClass : public AbstractTypeClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractTypeClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractTypeClass::vtables_t()
        {
            this->IPersistStream = 0x7F45C4;
            this->IRTTITypeInfo = 0x7F45A8;
            this->INoticeSink = 0x7F45A0;
            this->INoticeSource = 0x7F4598;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::TagType;
    static constexpr uintptr_t AbsVTable = 0x7F45C4;
    static constexpr size_t ClassSize = 0xA4;

public:
    ABSTRACTTYPE_ARRAY(TagTypeClass, 0xB0E780u);

public:
    int ArrayIndex;
    TriggerPersistence Persistence;
    TriggerTypeClass* FirstTrigger;

public:
    virtual ~TagTypeClass() JMP_THIS(0x6E5CA0);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x6E63A0);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x6E6410);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6E6470);
    
    void InvalidatePointer(AbstractClass* instance, bool all = true) override JMP_THIS(0x6E5E50);
    RTTIType KindOf() const override JMP_THIS(0x6E6490);
    int SizeOf() const override JMP_THIS(0x6E64A0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6E63E0);
    int ArrayIndex() const override JMP_THIS(0x6E64B0);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6E6080);
    bool SaveToINI(CCINIClass* pINI) override JMP_THIS(0x6E6160);

public:
    static void __fastcall LoadFromINIList(CCINIClass* pINI) JMP_STD(0x6E5ED0);
    static void __fastcall SaveToINIList(CCINIClass* pINI) JMP_STD(0x6E5FE0);
    static TagTypeClass* __fastcall FindByNameOrID(char const* pName) JMP_STD(0x6E5E70);

    using Flags = BYTE;
    Flags GetFlags() const JMP_THIS(0x6E61F0);
    bool HasAllowWinAction() const JMP_THIS(0x6E6220);
    bool HasCrossesHorizontalLineEvent() const JMP_THIS(0x6E6250);
    bool HasCrossesVerticalLineEvent() const JMP_THIS(0x6E6280);
    bool HasZoneEntryByEvent() const JMP_THIS(0x6E62B0);
    bool AddTrigger(TriggerTypeClass* pTrigger) JMP_THIS(0x6E5DD0);
    bool RemoveTrigger(TriggerTypeClass* pTrigger) JMP_THIS(0x6E5E00);
    bool ContainsTrigger(TriggerTypeClass* pTrigger) const JMP_THIS(0x6E62E0);

/*
    TagTypeClass * Find_Or_Make_0() JMP_THIS(0x6E6310);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TagTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) { }

public:
    TagTypeClass(char const* pName) : TagTypeClass(fake_noinit_t{}) JMP_THIS(0x5447C0);
    TagTypeClass(noinit_t) noexcept : TagTypeClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(TagTypeClass) == TagTypeClass::ClassSize);