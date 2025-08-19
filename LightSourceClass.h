#pragma once

#include "AbstractClass.h"

/*!
* @brief LightSource - used for light posts and radiation
*/
class __declspec(uuid("6F9C48F0-1207-11D2-8174-006008055BB5"))
NOVTABLE LightSourceClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7ED028;
            this->IRTTITypeInfo = 0x7ED00C;
            this->INoticeSink = 0x7ED004;
            this->INoticeSource = 0x7ECFFC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::LightSource;
    static constexpr uintptr_t AbsVTable = 0x7ED028;
    static constexpr size_t ClassSize = 0x4C;

    DEFINE_REFERENCE(DynamicVectorClass<LightSourceClass*>, Array, 0xABCA10)

public:
    int LightIntensity;
    TintStruct LightTint;
    int DetailLevel;
    Coordinate Location;
    int LightVisibility;
    bool Activated;

public:
    virtual ~LightSourceClass() JMP_THIS(0x554910);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x555080);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x5550C0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x555110);
    
    RTTIType WhatAmI() const override JMP_THIS(0x555140);
    int Size() const override JMP_THIS(0x555130);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x555070);

    void Activate(DWORD dwZero = 0) JMP_THIS(0x554A60);
    void Deactivate(DWORD dwZero = 0) JMP_THIS(0x554A80);
    void ChangeLevels(int nIntensity, TintStruct Tint, char mode) JMP_THIS(0x554AA0);
    static void __fastcall UpdateLightConverts(int value) JMP_STD(0x554D50);

/*
    void Cear_Pending() JMP_THIS(0x5549A0);
    void Draw(bool update_drawers) JMP_THIS(0x554AF0);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline LightSourceClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    LightSourceClass(int X, int Y, int Z, int nVisibility, int nIntensity, int Red, int Green, int Blue)
        : LightSourceClass(fake_noinit_t{}) JMP_THIS(0x554760);

    LightSourceClass(Coordinate Crd, int nVisibility, int nIntensity, TintStruct Tint)
        : LightSourceClass(fake_noinit_t{}) JMP_THIS(0x554760);

    LightSourceClass() : LightSourceClass(fake_noinit_t{}) JMP_THIS(0x554830);
    LightSourceClass(noinit_t) noexcept : LightSourceClass(fake_noinit_t{}) JMP_THIS(0x5548E0);
};
static_assert(sizeof(LightSourceClass) == LightSourceClass::ClassSize);