#pragma once

#include "AbstractClass.h"

class SuperClass;
class TechnoClass;
class TeamTypeClass;

class __declspec(uuid("4F0EC393-0A55-11D2-ACA7-006008055BB5"))
NOVTABLE TEventClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F5578;
            this->IRTTITypeInfo = 0x7F555C;
            this->INoticeSink = 0x7F5554;
            this->INoticeSource = 0x7F554C; 
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Event;
    static constexpr uintptr_t AbsVTable = 0x7F5578;
    static constexpr size_t ClassSize = 0x58;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<TEventClass*>, Array, 0xB0F1A0u)
public:
    virtual ~TEventClass() JMP_THIS(0x71E830);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x71F880);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x71F8C0);    
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x71F930);

    void PointerExpired(AbstractClass* instance, bool removed = true) override JMP_THIS(0x71F800);
    RTTIType WhatAmI() const override JMP_THIS(0x71FA60);
    int Size() const override JMP_THIS(0x71FA50);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x71F820);
    int GetArrayIndex() const override JMP_THIS(0x71FA70);

    // Event handling
    void LoadFromINI() JMP_THIS(0x71F4E0);
    void PrepareSaveToINI(char* buffer) const JMP_THIS(0x71F390);
    static TriggerAttachType __fastcall GetAttachType(int eventKind) JMP_STD(0x71F680);
    bool GetStateA() const JMP_THIS(0x71F950);
    bool GetStateB() const JMP_THIS(0x71F9C0);
    bool HasOccured(int eventKind, HouseClass* pHouse, ObjectClass* Object,
        CDTimerClass* ActivationFrame, bool* isRepeating) const JMP_THIS(0x71E940);

/*
    int32_t Get_House() JMP_THIS(0x71FA30);
    NeedType Needs() JMP_THIS(0x71F5B0);
    void Set_House(HouseClass* a2) JMP_THIS(0x71FA40);
    int32_t Static_CTOR() JMP_THIS(0x71E620);
    void Static_DTOR() JMP_THIS(0x71E660);
*/

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline TEventClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}

public:
	int ArrayIndex;
	TEventClass* NextEvent;
	TriggerEvent EventKind;
	TeamTypeClass* TeamType; // If this event needs to reference a team type, then this is the pointer to the team type object.
	int Value;
	char String[0x1C];
	HouseClass* House;
    TEventClass() : TEventClass(fake_noinit_t{}) JMP_THIS(0x71E6A0);
    TEventClass(noinit_t) noexcept : TEventClass(fake_noinit_t{}) JMP_THIS(0x71E800);
};
static_assert(sizeof(TEventClass) == TEventClass::ClassSize);
