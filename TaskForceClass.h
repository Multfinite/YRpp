/*
	TaskForces as in the AI inis
*/

#pragma once

#include "AbstractTypeClass.h"

class TechnoTypeClass;

struct TaskForceEntryStruct
{
	int Amount;
	TechnoTypeClass* Type;
};

class __declspec(uuid("61DE341E-0774-11D2-ACA5-006008055BB5"))
NOVTABLE TaskForceClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

	//Array
	ABSTRACTTYPE_ARRAY(TaskForceClass, 0xA8E8D0u);
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F4680;
            this->IRTTITypeInfo = 0x7F4664;
            this->INoticeSink = 0x7F465C;
            this->INoticeSource = 0x7F4654;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::TaskForce;
    static constexpr uintptr_t AbsVTable = 0x7F4680;
    static constexpr size_t ClassSize = 0xD4;



public:
    virtual ~TaskForceClass() JMP_THIS(0x6E7F80);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6E8710);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6E86A0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) JMP_STD(0x6E8680);
    
    RTTIType WhatAmI() const override JMP_THIS(0x6E87D0);
    int Size() const override JMP_THIS(0x6E87E0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6E8750);
   
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6E8420);
    bool SaveToINI(CCINIClass* pINI) override JMP_THIS(0x6E8510);

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline TaskForceClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	int     Group;
	int     CountEntries;
	bool    IsGlobal;
	TaskForceEntryStruct Entries [0x6];
    TaskForceClass(const char* pID) : TaskForceClass(fake_noinit_t{}) JMP_THIS(0x6E7E80);
    TaskForceClass(noinit_t) noexcept : TaskForceClass(fake_noinit_t{}) JMP_THIS(0x6E7F50);
};
static_assert(sizeof(TaskForceClass) == TaskForceClass::ClassSize);