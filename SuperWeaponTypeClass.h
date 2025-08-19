#pragma once

#include "FileSystem.h"
#include "AbstractTypeClass.h"

class BuildingTypeClass;
class ObjectClass;
class WeaponTypeClass;

class __declspec(uuid("0CF2BCE7-36E4-11D2-B8D8-006008C809ED"))
NOVTABLE SuperWeaponTypeClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F4090;
            this->IRTTITypeInfo = 0x7F4074;
            this->INoticeSink = 0x7F406C;
            this->INoticeSource = 0x7F4064;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::SuperWeaponType;
    static constexpr uintptr_t AbsVTable = 0x7F4090;
    static constexpr size_t ClassSize = 0x100;

public:
    ABSTRACTTYPE_ARRAY(SuperWeaponTypeClass, 0xA8E330u);

public:
    int ArrayIndex;
    WeaponTypeClass* WeaponType;
    int RechargeVoice;
    int ChargingVoice;
    int ImpatientVoice;
    int SuspendVoice;
    int RechargeTime;
    SuperWeaponType Type;
    SHPStruct* SidebarImage;
    Action Action;
    int SpecialSound;
    int StartSound;
    BuildingTypeClass* AuxBuilding;
    char SidebarImageFile[0x18];
    PROTECTED_PROPERTY(BYTE, zero_E4);
    bool UseChargeDrain;
    bool IsPowered;
    bool DisableableFromShell;
    int FlashSidebarTabFrames;
    bool AIDefendAgainst;
    bool PreClick;
    bool PostClick;
    int PreDependent;
    bool ShowTimer;
    bool ManualControl;
    float Range;
    int LineMultiplier;

public:
    virtual ~SuperWeaponTypeClass() JMP_THIS(0x6CE740);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6CE7C0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6CE800);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6CE8D0);
    
    RTTIType WhatAmI() const override JMP_THIS(0x6CE8F0);
    int Size() const override JMP_THIS(0x6CE900);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6CE910);
    int GetArrayIndex() const override JMP_THIS(0x6CEA10);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6CEA20);
    
    virtual ::Action MouseOverObject(CellStruct const& cell, ObjectClass* pObjBelowMouse) const JMP_THIS(0x6CEF80);
    
    static SuperWeaponTypeClass* __fastcall FindFirstOfAction(::Action action) JMP_STD(0x6CEEB0);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SuperWeaponTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    SuperWeaponTypeClass(const char* pID) : SuperWeaponTypeClass(fake_noinit_t{}) JMP_THIS(0x6CE5B0);
    SuperWeaponTypeClass(noinit_t) noexcept : SuperWeaponTypeClass(fake_noinit_t{}) JMP_THIS(0x6CE700);
};
static_assert(sizeof(SuperWeaponTypeClass) == SuperWeaponTypeClass::ClassSize);
