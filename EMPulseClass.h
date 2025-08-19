/*
	EMP - no, you're NOT seeing things :P
*/

#pragma once

#include "AbstractClass.h"

class __declspec(uuid("B825CB22-200E-11D2-9FA9-0060089AD458"))
NOVTABLE EMPulseClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {            
            this->IPersistStream = 0x7E87A8;
            this->IRTTITypeInfo = 0x7E878C;
            this->INoticeSink = 0x7E8784;
            this->INoticeSource = 0x7E877C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::EMPulse;
    static constexpr uintptr_t AbsVTable = 0x7E87A8;
    static constexpr size_t ClassSize = 0x34;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<EMPulseClass*>, Array, 0x8A3870u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~EMPulseClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

    /*! @brief FAKE CTOR */
    explicit __forceinline EMPulseClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}
public:

	CellStruct BaseCoords;
	int Spread;
	int CreationTime;	//frame in which this EMP got created
	int Duration;
    EMPulseClass(CellStruct dwCrd, int nSpread, int nDuration, TechnoClass* pGenerator) noexcept : EMPulseClass(fake_noinit_t{}) JMP_THIS(0x4C52B0);
    EMPulseClass() : EMPulseClass(fake_noinit_t{}) JMP_THIS(0x4C5370);
    EMPulseClass(noinit_t) noexcept : EMPulseClass(fake_noinit_t{}) JMP_THIS(0x4C53B0);
};
static_assert(sizeof(EMPulseClass) == EMPulseClass::ClassSize);
