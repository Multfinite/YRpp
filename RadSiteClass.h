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

public:
    DEFINE_POINTER(DynamicVectorClass<RadSiteClass*>, Array, 0xB04BD0u)

public:
    LightSourceClass* LightSource;
    DECLARE_PROPERTY(CDTimerClass, RadLevelTimer);
    DECLARE_PROPERTY(CDTimerClass, RadLightTimer);
    CellStruct BaseCell;
    int Spread;
    int SpreadInLeptons;
    int RadLevel;
    int LevelSteps;
    int Intensity;
    TintStruct Tint;
    int IntensitySteps;
    int IntensityDecrement;
    int RadDuration;
    int RadTimeLeft;

public:
    virtual ~RadSiteClass() JMP_THIS(0x65B2F0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x65B470);
   
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x65B3D0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x65B450);
   
    RTTIType KindOf() const override JMP_THIS(0x65B3C0);
    int SizeOf() const override JMP_THIS(0x65B3A0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x65B3B0);
    void AI() override JMP_THIS(0x65B800);

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
    /*! @brief FAKE CTOR */
    explicit __forceinline RadSiteClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}

public:
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