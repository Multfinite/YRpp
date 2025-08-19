/*
	Sides
*/

#pragma once

#include "AbstractTypeClass.h"

class __declspec(uuid("C53DD372-151E-11D2-8175-006008055BB5"))
NOVTABLE SideClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F2EC0;
            this->IRTTITypeInfo = 0x7F2EA4;
            this->INoticeSink = 0x7F2E9C;
            this->INoticeSource = 0x7F2E94;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Side;
    static constexpr uintptr_t AbsVTable = 0x7F2EC0;
    static constexpr size_t ClassSize = 0xB4;

	//Array
	ABSTRACTTYPE_ARRAY(SideClass, 0x8B4120u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~SideClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline SideClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	TypeList<int> HouseTypes;	//indices!

    SideClass(const char* pID) : SideClass(fake_noinit_t{}) JMP_THIS(0x6A4550);
    SideClass(noinit_t) noexcept : SideClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(SideClass) == SideClass::ClassSize);