#pragma once

#include "ObjectTypeClass.h"

class __declspec(uuid("5AF2CE7B-0634-11D2-ACA4-006008055BB5"))
NOVTABLE TerrainTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F5458;
            this->IRTTITypeInfo = 0x7F543C;
            this->INoticeSink = 0x7F5434;
            this->INoticeSource = 0x7F542C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::TerrainType;
    static constexpr uintptr_t AbsVTable = 0x7F5458;
    static constexpr size_t ClassSize = 0x2BC;

public:
    ABSTRACTTYPE_ARRAY(TerrainTypeClass, 0xA8E318u);

public:
    int ArrayIndex;
    int Foundation;
    ColorStruct RadarColor;
    int AnimationRate;
    float AnimationProbability;
    int TemperateOccupationBits;
    int SnowOccupationBits;
    bool WaterBound;
    bool SpawnsTiberium;
    bool IsFlammable;
    bool IsAnimated;
    bool IsVeinhole;
    CellStruct* FoundationData;

public:
    virtual ~TerrainTypeClass() JMP_THIS(0x71DC00);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x71E260);

    HRESULT Load(IStream* pStm) override JMP_STD(0x71E1D0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x71E240);

    RTTIType KindOf() const override JMP_THIS(0x71E330);
    int SizeOf() const override JMP_THIS(0x71E340);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x71E140);
    
    int ArrayIndex() const override JMP_THIS(0x71E350);
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x71DEA0);
    CoordStruct FixupCoord(CoordStruct& coord) const override JMP_THIS(0x71E0D0);
    bool InstantiateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x71DDD0);
    ObjectClass* Instantiate(HouseClass* pOwner) override JMP_THIS(0x71DE10);
    CellStruct* OccupiedCells(bool includeBib = false) const override JMP_THIS(0x71DE40); cupy_List(bool placement) const override JMP_THIS(0x71DE40);

    static TerrainTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x71E2A0);
/*
    int32_t From_Name() JMP_THIS(0x71DD80);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TerrainTypeClass(fake_noinit_t) noexcept
        : ObjectTypeClass(fake_noinit_t{})
    {}

public:
    TerrainTypeClass(const char* pID) : TerrainTypeClass(fake_noinit_t{})
        JMP_THIS(0x71DA80);
    TerrainTypeClass(noinit_t) noexcept : TerrainTypeClass(fake_noinit_t{})
        JMP_THIS(0x71DBD0);
};
static_assert(sizeof(TerrainTypeClass) == TerrainTypeClass::ClassSize);