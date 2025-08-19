#pragma once

#include "TagTypeClass.h"

//forward declarations
class TriggerClass;

class __declspec(uuid("54F6E432-09ED-11D2-ACA5-006008055BB5"))
NOVTABLE TagClass : public AbstractClass
{
public:
    using base_type = AbstractClass;
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F44E0;
            this->IRTTITypeInfo = 0x7F44C4;
            this->INoticeSink = 0x7F44BC;
            this->INoticeSource = 0x7F44B4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Tag;
    static constexpr uintptr_t AbsVTable = 0x7F44E0;
    static constexpr size_t ClassSize = 0x38;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<TagClass*>, Array, 0xB0E720u)


public:
    virtual ~TagClass() JMP_THIS(0x6E4F60);

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6E56A0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6E5730);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6E57A0);
   
    void PointerExpired(AbstractClass* instance, bool removed = true) override JMP_THIS(0x6E5610);
    RTTIType WhatAmI() const override JMP_THIS(0x6E58A0);
    int Size() const override JMP_THIS(0x6E5890);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6E56E0);

    bool HasCrossesHorizontalLineEvent() const JMP_THIS(0x6E5320);
    bool HasCrossesVerticalLineEvent() const JMP_THIS(0x6E5300);
    bool HasZoneEntryByEvent() const JMP_THIS(0x6E5340);
    bool HasAllowWinAction() const JMP_THIS(0x6E5360);
    void GlobalChanged(int idxGlobal) JMP_THIS(0x6E55A0);
    void LocalChanged(int idxLocal) JMP_THIS(0x6E55B0);
    bool IsOnlyInstanceOfType() const JMP_THIS(0x6E5850);
    bool RaiseEvent(TriggerEvent event, ObjectClass* pTagOwner, CellStruct location, bool forceAllOccured = false, TechnoClass* pSource = nullptr) JMP_THIS(0x6E53A0);
    bool ShouldReplace() const JMP_THIS(0x6E57C0);
    void Destroy() JMP_THIS(0x6E5230);
    void AddTrigger(TriggerClass* pTrigger) JMP_THIS(0x6E55C0);
    bool RemoveTrigger(TriggerClass* pTrigger) JMP_THIS(0x6E55D0);
    bool ContainsTrigger(TriggerClass* pTrigger) const JMP_THIS(0x6E5380);

    constexpr bool HasBeenDestroyed() const { return this->Destroyed; }

    static TagClass* __fastcall GetInstance(TagTypeClass* pType) JMP_STD(0x6E52A0);
    static void __stdcall DeleteAll() JMP_STD(0x6E5570);
    static void __fastcall NotifyGlobalChanged(int idxGlobal) JMP_STD(0x6E57F0);
    static void __fastcall NotifyLocalChanged(int idxLocal) JMP_STD(0x6E5820);

/*
    void Get_Cell(Cell* cell) JMP_THIS(0x6E52F0);
    bool Has_Zone_Entry_By_Event() JMP_THIS(0x6E5340);
    int8_t Is_Destroyed() JMP_THIS(0x6E5290);
    void Set_Cell(int32_t cell) JMP_THIS(0x6E5560);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TagClass(fake_noinit_t) noexcept  : AbstractClass(fake_noinit_t{}) {}
public:
	TagTypeClass* Type;
	TriggerClass* FirstTrigger;
	int InstanceCount;
	CellStruct DefaultCoords;
	bool Destroyed;
	bool IsExecuting;
	PROTECTED_PROPERTY(BYTE, padding_36[2]);
    TagClass(TagTypeClass* pType) : TagClass(fake_noinit_t{}) JMP_THIS(0x6E4DE0);
    TagClass(noinit_t) noexcept : TagClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(TagClass) == TagClass::ClassSize);
