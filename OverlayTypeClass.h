#pragma once

#include "ObjectTypeClass.h"

class AnimTypeClass;

/*!
* @brief OverlayTypes are initialized by INI files.
*/
class __declspec(uuid("5AF2CE79-0634-11D2-ACA4-006008055BB5"))
NOVTABLE OverlayTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EF600;
            this->IRTTITypeInfo = 0x7EF5E4;
            this->INoticeSink = 0x7EF5DC;
            this->INoticeSource = 0x7EF5D4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::OverlayType;
    static constexpr uintptr_t AbsVTable = 0x7EF600;
    static constexpr size_t ClassSize = 0x2BC;

public:
    ABSTRACTTYPE_ARRAY(OverlayTypeClass, 0xA83D80u);

public:
    int ArrayIndex;
    LandType LandType;
    AnimTypeClass* CellAnim;
    int DamageLevels;
    int Strength;
    bool Wall;
    bool Tiberium;
    bool Crate;
    bool CrateTrigger;
    bool NoUseTileLandType;
    bool IsVeinholeMonster;
    bool IsVeins;
    bool ImageLoaded;
    bool Explodes;
    bool ChainReaction;
    bool Overrides;
    bool DrawFlat;
    bool IsRubble;
    bool IsARock;
    ColorStruct RadarColor;

public:
    virtual ~OverlayTypeClass() JMP_THIS(0x5FE3F0);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x5FEC30);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x5FEAF0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x5FEC10);
    
    RTTIType KindOf() const override JMP_THIS(0x5FEF00);
    int SizeOf() const override JMP_THIS(0x5FEF10);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x5FEA50);
    int ArrayIndex() const override JMP_THIS(0x5FEF20);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x5FE770);
    CoordStruct FixupCoord(CoordStruct& coord) const override JMP_THIS(0x5FEA30);
    bool InstantiateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x5FE530);
    ObjectClass* Instantiate(HouseClass* pOwner) override JMP_THIS(0x5FE570);
    CellStruct* OccupiedCells(bool includeBib = false) const override JMP_THIS(0x5FE4C0);
    SHPStruct* GetImage() const override JMP_THIS(0x5FEDE0);

    virtual void Draw(Point2D* pClientCoords, RectangleStruct* pClipRect, int nFrame) JMP_THIS(0x5FE5A0);

/*
    OverlayTypeClass* Find_Or_Make() JMP_THIS(0x5FEC70);
    int32_t From_Name() JMP_THIS(0x5FE470);
    RGBClass Get_Radar_Color(int32_t a3) JMP_THIS(0x5FED00);
    void Init() JMP_THIS(0x5FE620);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline OverlayTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    OverlayTypeClass(const char* pID) : OverlayTypeClass(fake_noinit_t{}) JMP_THIS(0x5FE250);
    OverlayTypeClass(noinit_t) noexcept : OverlayTypeClass(fake_noinit_t{}) JMP_THIS(0x5FE3C0);
};
static_assert(sizeof(OverlayTypeClass) == OverlayTypeClass::ClassSize);