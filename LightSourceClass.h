#pragma once

#include "AbstractClass.h"

/*!
* @brief LightSource - used for light posts and radiation
*/
class NOVTABLE LightSourceClass : public AbstractClass
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

    static const AbstractType AbsID = AbstractType::LightSource;
    static constexpr uintptr_t AbsVTable = 0x7ED028;
    static constexpr size_t ClassSize = 0x4C;

    static constexpr constant_ptr<DynamicVectorClass<LightSourceClass*>, 0xABCA10> Array{};

public:
    int LightIntensity;
    TintStruct LightTint;
    int DetailLevel;
    CoordStruct Location;
    int LightVisibility;
    bool Activated;

public:
    virtual ~LightSourceClass() RX;

    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x555080);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x5550C0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x555110);
    
    RTTIType KindOf() const override JMP_THIS(0x555140);
    int SizeOf() const override JMP_THIS(0x555130);
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
    explicit __forceinline LightSourceClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    LightSourceClass(int X, int Y, int Z, int nVisibility, int nIntensity, int Red, int Green, int Blue) noexcept
        : LightSourceClass(fake_noinit_t()) JMP_THIS(0x554760);

    LightSourceClass(CoordStruct Crd, int nVisibility, int nIntensity, TintStruct Tint) noexcept
        : LightSourceClass(fake_noinit_t()) JMP_THIS(0x554760);

    LightSourceClass() noexcept : LightSourceClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(LightSourceClass) == LightSourceClass::ClassSize);