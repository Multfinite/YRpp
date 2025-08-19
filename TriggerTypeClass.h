#pragma once

#include "AbstractTypeClass.h"

class CCINIClass;
class HouseTypeClass;
class TActionClass;
class TEventClass;
class TagTypeClass;

class __declspec(uuid("4104D740-D507-11D3-8C38-00A0C933BE44"))
NOVTABLE TriggerTypeClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

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

    static constexpr AbstractType AbsID = AbstractType::TriggerType;
    static constexpr uintptr_t AbsVTable = 0x7F5904;
    static constexpr size_t ClassSize = 0xB4;

	//Array
	ABSTRACTTYPE_ARRAY(TriggerTypeClass, 0x8B4178u);


public:
    virtual ~TriggerTypeClass() JMP_THIS(0x726E00);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x727BB0);

    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x727BF0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x727CD0);

    void PointerExpired(AbstractClass* instance, bool all = true) override JMP_THIS(0x727090);
    RTTIType WhatAmI() const override JMP_THIS(0x727CA0);
    int Size() const override JMP_THIS(0x727CB0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x727B30);

    int ArrayIndex() const override JMP_THIS(0x727CC0);
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x727240);
    bool SaveToINI(CCINIClass* pINI) override JMP_THIS(0x7276A0);

public:
    static void __fastcall LoadFromINIList(CCINIClass* pINI) JMP_STD(0x7275D0);
    static void __fastcall SaveToINIList(CCINIClass* pINI) JMP_STD(0x727880);
    TagTypeClass* __fastcall FindByNameOrID(char const* pName) JMP_STD(0x727120);

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    using Flags = BYTE;
    Flags GetFlags() const JMP_THIS(0x7271E0);
    bool HasAllowWinAction() const JMP_THIS(0x726FE0);
    bool HasGlobalSetOrClearedEvent(int idxGlobal) const JMP_THIS(0x727010);
    bool HasLocalSetOrClearedEvent(int idxLocal) const JMP_THIS(0x727050);
    bool HasCrossesHorizontalLineEvent() const JMP_THIS(0x726F80);
    bool HasCrossesVerticalLineEvent() const JMP_THIS(0x726F50);
    bool HasZoneEntryByEvent() const JMP_THIS(0x726FB0);
    bool RemoveAction(TActionClass* pAction) JMP_THIS(0x7279E0);
    bool RemoveEvent(TEventClass* pEvent) JMP_THIS(0x727A40);

/*
    AttachType Attaches_To() JMP_THIS(0x7271E0);
    int32_t Clear_INI_Entries() JMP_THIS(0x727880);
    TriggerTypeClass * Find_Or_Make() JMP_THIS(0x727AA0);
    int8_t * Name_From_Persistance() JMP_THIS(0x7271D0);
    int32_t Persistance_From_Name() JMP_THIS(0x727190);
    void Read_INI() JMP_THIS(0x7275D0);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TriggerTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}
public:
	int ArrayIndex;
	bool Difficulty[3]; // easy = 0, normal = 1, hard = 2
	bool Enabled;
	bool MustTransfer; // vehicle thieves must take Tag with it when hijacking
	PROTECTED_PROPERTY(BYTE, align_A1[3]);
	HouseTypeClass* House;
	TriggerTypeClass* NextTrigger;
	TEventClass* FirstEvent;
	TActionClass* FirstAction;
    TriggerTypeClass(char const* pName) : TriggerTypeClass(fake_noinit_t{}) JMP_THIS(0x726C80);
};
static_assert(sizeof(TriggerTypeClass) == TriggerTypeClass::ClassSize);