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

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TEventClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	// you are responsible for doing INI::ReadString and strtok'ing it before calling
	// this func only calls strtok again, doesn't know anything about buffers
	void LoadFromINI()
		JMP_THIS(0x71F4E0);

	// you allocate the buffer for this, and save it to ini yourself after this returns
	// this func only sprintf's the stuff it needs into buffer
	void PrepareSaveToINI(char* buffer) const
		JMP_THIS(0x71F390);

	static TriggerAttachType __fastcall GetAttachType(int eventKind)
		JMP_STD(0x71F680);

	// used in TriggerClass::HaveEventsOccured , when trigger is repeating
	// both need to be true to check this event as done
	bool GetStateA() const
		JMP_THIS(0x71F950);

	bool GetStateB() const
		JMP_THIS(0x71F9C0);

	// main brain
	bool HasOccured(
		int eventKind,
		HouseClass* pHouse,
		ObjectClass* Object,
		CDTimerClass* ActivationFrame,
		bool* isRepeating
	) const
		JMP_THIS(0x71E940);


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
