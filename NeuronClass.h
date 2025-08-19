/*
	I have not the slightest idea what this is good for...
*/

#pragma once

#include "AbstractClass.h"

class __declspec(uuid("241AB316-4CF5-11D2-BC26-00104B8FB04D"))
NOVTABLE NeuronClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E3DF0;
            this->IRTTITypeInfo = 0x7E3DD4;
            this->INoticeSink = 0x7E3DCC;
            this->INoticeSource = 0x7E3DC4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Neuron;
    static constexpr uintptr_t AbsVTable = 0x7E3DF0;
    static constexpr size_t ClassSize = 0x38;



public:
    virtual ~NeuronClass() JMP_THIS(0x43A440);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x43A500);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x43A540);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x43A5B0);
    
    RTTIType WhatAmI() const override JMP_THIS(0x43A9A0);
    int Size() const override JMP_THIS(0x43A9B0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x43A5D0);

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline NeuronClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	void* unknown_ptr_24;
	void* unknown_ptr_28;
	void* unknown_ptr_2C;
	CDTimerClass unknown_timer_30;
    NeuronClass() : NeuronClass(fake_noinit_t{}) JMP_THIS(0x43A350);
};
static_assert(sizeof(NeuronClass) == NeuronClass::ClassSize);

//Even more questions marks on the use of this... >.<
class BrainClass
{
public:
	virtual ~BrainClass() JMP_THIS(0x43AA90);

	BrainClass() { THISCALL(0x43A600); }

	//Properties
	VectorClass<NeuronClass*> Neurons;	//???
};
