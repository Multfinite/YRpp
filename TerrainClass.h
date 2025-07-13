#pragma once

#include "ObjectClass.h"
#include "TerrainTypeClass.h"
#include "StageClass.h"

class __declspec(uuid("0E272DCE-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE TerrainClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F522C;
            this->IRTTITypeInfo = 0x7F5224;
            this->INoticeSink = 0x7F521C;
            this->INoticeSource = 0x7F5200;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Terrain;
    static constexpr uintptr_t AbsVTable = 0x7F522C;
    static constexpr size_t ClassSize = 0xE0;

public:
    static constexpr constant_ptr<DynamicVectorClass<TerrainClass*>, 0xA8E988u> const Array{};

public:
    StageClass Animation;
    TerrainTypeClass* Type;
    bool IsBurning;
    bool IsCrumbling;
    RectangleStruct unknown_rect_D0;

public:
    virtual ~TerrainClass() JMP_THIS(0x71B7B0);

public:
    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x71D310);

    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x71CDA0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x71CF30);
    
    void InvalidatePointer(AbstractClass* target, bool all = true) override JMP_THIS(0x71CFD0);
    RTTIType KindOf() const override JMP_THIS(0x71D300);
    int SizeOf() const override JMP_THIS(0x71D2F0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x71CF50);
    void AI() override JMP_THIS(0x71C730);
   
    ObjectTypeClass* Type() const override JMP_THIS(0x71D150);
    bool Limbo() override JMP_THIS(0x71C930);
    bool Unlimbo(const Coordinate& coords, Dir256 dir) override JMP_THIS(0x71D000);
    void MarkAllOccupationBits(const Coordinate& coord) override JMP_THIS(0x71C110);
    void UnmarkAllOccupationBits(const Coordinate& coord) override JMP_THIS(0x71C070);
    bool DrawIfVisible(RectangleStruct* pBounds, bool EvenIfCloaked, DWORD dwUnk3) const override JMP_THIS(0x71CC50);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x71C1B0);
    void DrawAgain(const Point2D& location, const RectangleStruct& bounds) const override JMP_THIS(0x71C360);
    bool Mark(MarkType mark) override JMP_THIS(0x71BFB0);
    RectangleStruct* GetRenderDimensions(RectangleStruct* pRect) override JMP_THIS(0x71D160);
    DamageState ReceiveDamage(int* damage, int distance, WarheadTypeClass* warhead, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x71B920);
    bool Ignite() override JMP_THIS(0x71C5B0);
    void Extinguish() override JMP_THIS(0x71C6B0);
    Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const override JMP_THIS(0x71C4D0);
/*
    void Read_INI() JMP_THIS(0x71CA70);
    void Start_To_Crumble() JMP_THIS(0x71C8E0);
    void Write_INI() JMP_THIS(0x71CB90);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TerrainClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}

public:
    TerrainClass(TerrainTypeClass* tt, CellStruct coords) : TerrainClass(fake_noinit_t{})
        JMP_THIS(0x71BB90);
    TerrainClass() : TerrainClass(fake_noinit_t{})
        JMP_THIS(0x71BDF0);
};
static_assert(sizeof(TerrainClass) == TerrainClass::ClassSize);