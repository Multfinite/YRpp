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

public:
    DEFINE_REFERENCE(DynamicVectorClass<EMPulseClass*>, Array, 0x8A3870u)

public:
    CellStruct BaseCoords;
    int Spread;
    int CreationTime;
    int Duration;

public:
    virtual ~EMPulseClass() JMP_THIS(0x4C53E0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x4C59F0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4C5A30);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4C5A80);
    
    RTTIType WhatAmI() const override JMP_THIS(0x4C5AB0);
    int Size() const override JMP_THIS(0x4C5AA0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x4C59A0);

/*
    int32_t Update() JMP_THIS(0x4C54A0);
    void Create(int32_t arg0) JMP_THIS(0x4C54E0);
    int32_t Init_Clear() JMP_THIS(0x4C5470);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline EMPulseClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}
public:
    EMPulseClass(CellStruct dwCrd, int nSpread, int nDuration, TechnoClass* pGenerator) noexcept : EMPulseClass(fake_noinit_t{}) JMP_THIS(0x4C52B0);
    EMPulseClass() : EMPulseClass(fake_noinit_t{}) JMP_THIS(0x4C5370);
    EMPulseClass(noinit_t) noexcept : EMPulseClass(fake_noinit_t{}) JMP_THIS(0x4C53B0);
};
static_assert(sizeof(EMPulseClass) == EMPulseClass::ClassSize);
