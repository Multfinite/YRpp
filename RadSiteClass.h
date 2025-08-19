/*
	RadSites
*/

#pragma once

#include "AbstractClass.h"

class LightSourceClass;
class WeaponTypeClass;

class __declspec(uuid("4104D740-D507-11D3-8C38-00A0C933BE44"))
NOVTABLE RadSiteClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F0810;
            this->IRTTITypeInfo = 0x7F07F4;
            this->INoticeSink = 0x7F07EC;
            this->INoticeSource = 0x7F07E4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::RadSite;
    static constexpr uintptr_t AbsVTable = 0x7F0810;
    static constexpr size_t ClassSize = 0x74;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<RadSiteClass*>, Array, 0xB04BD0u)

public:
    virtual ~RadSiteClass() JMP_THIS(0x65B2F0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x65B470);
   
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x65B3D0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x65B450);
   
    RTTIType WhatAmI() const override JMP_THIS(0x65B3C0);
    int Size() const override JMP_THIS(0x65B3A0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x65B3B0);
    void Update() override JMP_THIS(0x65B800);

    void Activate() JMP_THIS(0x65B580);
    void Deactivate() JMP_THIS(0x65BB50);
    void Radiate() JMP_THIS(0x65B9C0);
    void DecreaseRadiation() JMP_THIS(0x65BD00);
    void DecreaseLight() JMP_THIS(0x65BE90);
    void Add(int nRadLevel) JMP_THIS(0x65B530);
    int GetRadLevel() JMP_THIS(0x65B510);
    int GetRadLevelAt(CellStruct* pCell) JMP_THIS(0x65B8F0);
    void SetRadLevel(int nRadLevel) JMP_THIS(0x65B4F0);
    void SetBaseCell(CellStruct* pCell) JMP_THIS(0x65B4C0);
    void GetSpread() JMP_THIS(0x65B4B0);
    void SetSpread(int nCells) JMP_THIS(0x65B4D0);

    // Helper methods
    double GetEffectPercentage() {
        return (this->RadDuration <= 0) ? 0.0 :
            static_cast<double>(this->RadTimeLeft) / static_cast<double>(this->RadDuration);
    }

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline RadSiteClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}

public:

	LightSourceClass* LightSource; // the light source attached to this instance
	DECLARE_PROPERTY(CDTimerClass, RadLevelTimer); // used to count down RadLevelDelay
	DECLARE_PROPERTY(CDTimerClass, RadLightTimer); // used to count down RadLightDelay
	CellStruct        BaseCell; // center cell
	int               Spread; // range in cells
	int               SpreadInLeptons; // range in leptons
	int               RadLevel; // the radiation level,
	int               LevelSteps; // cell's rad level reduced by (RadLevel/LevelSteps) every time RadLevelTimer elapses
	int               Intensity; // the intensity at the beginning
	TintStruct        Tint; // RadColor at the current level
	int               IntensitySteps; // the number of intensity decreases during the duration
	int               IntensityDecrement; // Intensity decremented by this every time RadLightDelay elapses
	int               RadDuration; // as currently set up, the rad site will stay for so many frames
	int               RadTimeLeft; // the remaining frames. divided by RadDuration gives the factor
    RadSiteClass() : RadSiteClass(fake_noinit_t{}) JMP_THIS(0x65B1E0);
    RadSiteClass(CellStruct nBaseCoords, int nSpread, int nRadLevel) : RadSiteClass()
    {
        SetBaseCell(&nBaseCoords);
        SetSpread(nSpread);
        SetRadLevel(nRadLevel);
    }
    RadSiteClass(noinit_t) noexcept : RadSiteClass(fake_noinit_t{}) JMP_THIS(0x65B2A0);
};
static_assert(sizeof(RadSiteClass) == RadSiteClass::ClassSize);
