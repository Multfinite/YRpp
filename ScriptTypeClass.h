/*
	[ScriptTypes]
*/

#pragma once

#include "AbstractTypeClass.h"

struct ScriptActionNode
{
	int Action;
	int Argument;
};

class TechnoTypeClass;

class __declspec(uuid("42F3A647-0789-11D2-ACA5-006008055BB5"))
NOVTABLE ScriptTypeClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F1008;
            this->IRTTITypeInfo = 0x7F0FEC;
            this->INoticeSink = 0x7F0FE4;
            this->INoticeSource = 0x7F0FDC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::ScriptType;
    static constexpr uintptr_t AbsVTable = 0x7F1008;
    static constexpr size_t ClassSize = 0x234;

	//Array
	ABSTRACTTYPE_ARRAY(ScriptTypeClass, 0x8B41C8u);
	static ScriptTypeClass* __fastcall FindOrAllocate(const char* id)
	{ JMP_STD(0x691C00); }

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ScriptTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//AbstractTypeClass
	static bool LoadFromINIList(CCINIClass *pINI, bool IsGlobal)
		{ JMP_STD(0x691970); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline ScriptTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	int      ArrayIndex;
	bool     IsGlobal;
	int      ActionsCount;
	ScriptActionNode ScriptActions [50];
    ScriptTypeClass(const char* pID) noexcept : ScriptTypeClass(fake_noinit_t{}) JMP_THIS(0x6916B0);
};
static_assert(sizeof(ScriptTypeClass) == ScriptTypeClass::ClassSize);
