/*
	Smudges
*/

#pragma once

#include "ObjectClass.h"
#include "SmudgeTypeClass.h"

class __declspec(uuid("0E272DC5-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE SmudgeClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F32FC;
            this->IRTTITypeInfo = 0x7F32F4;
            this->INoticeSink = 0x7F32D8;
            this->INoticeSource = 0x7F32D0;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Smudge;
    static constexpr uintptr_t AbsVTable = 0x7F32FC;
    static constexpr size_t ClassSize = 0xB0;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<SmudgeClass*>, Array, 0xA8B1E0u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~SmudgeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline SmudgeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	SmudgeTypeClass* Type;

    SmudgeClass(SmudgeTypeClass const* pType, Coordinate const& pos, int houseId) : SmudgeClass(fake_noinit_t{}) JMP_THIS(0x6B4A50);
    SmudgeClass(noinit_t) noexcept : SmudgeClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(SmudgeClass) == SmudgeClass::ClassSize);