#pragma once

#include "GeneralDefinitions.h"
#include "ObjectClass.h"

class TechnoClass;

class __declspec(uuid("0E272DCD-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE WaveClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F6BF4;
            this->IRTTITypeInfo = 0x7F6BD8;
            this->INoticeSink = 0x7F6BD0;
            this->INoticeSource = 0x7F6BC8;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Wave;
    static constexpr uintptr_t AbsVTable = 0x7F6BF4;
    static constexpr size_t ClassSize = 0x240;

public:
    static constexpr constant_ptr<DynamicVectorClass<WaveClass*>, 0xA8EC38u> const Array{};

public:
    AbstractClass* Target;
    WaveType Type;
    CoordStruct LimboCoords;
    CoordStruct Pos0;
    Point2D WaveStartMiddle;
    Point2D WaveEndMiddle;
    Point2D WaveEndSide1;
    Point2D WaveEndSide2;
    Point2D WaveStartSide1;
    Point2D WaveStartSide2;
    CoordStruct WaveEndSide1Coord;
    CoordStruct WaveEndSide2Coord;
    CoordStruct WaveStartSide1Coord;
    CoordStruct WaveStartSide2Coord;
    bool IsTraveling;
    bool ShouldEnd;
    BYTE field_12E;
    BYTE field_12F;
    int WaveEC;
    int WaveCount;
    double MatrixScale1;
    double MatrixScale2;
    int PointData_Counter;
    DWORD PointData_Pointer;
    Point2D SonicPoints[6];
    Point2D MagPoints[4];
    int PointData2_X;
    int PointData2_Y;
    DWORD PointData2_Pointer;
    int PitchData[8];
    int FacingIndex;
    int LaserEC;
    TechnoClass* Owner;
    FacingClass Facing;
    DynamicVectorClass<CellClass*> Cells;
    int ColorData[14];

public:
    virtual ~WaveClass() JMP_THIS(0x75ED30);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x75F840);

    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x75F650);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x75F7D0);
    
    void InvalidatePointer(AbstractClass* instance, bool all = true) override JMP_THIS(0x75F610);
    RTTIType KindOf() const override JMP_THIS(0x7631F0);
    int SizeOf() const override JMP_THIS(0x75F880);    
    void AI() override JMP_THIS(0x760F50);

    Layer InWhichLayer() const override JMP_THIS(0x75F890);
    ObjectTypeClass* Type() const override JMP_THIS(0x75F8A0);
    bool Limbo() override JMP_THIS(0x75F980);
    bool Unlimbo(const Coordinate& position, Dir256 direction) override JMP_THIS(0x75F8B0);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x75F9F0);

    void DrawMagnetic(CoordStruct const& xyzFrom, CoordStruct const& xyzTo) JMP_THIS(0x762070);
    void DrawNonMagnetic(CoordStruct const& xyzFrom, CoordStruct const& xyzTo) JMP_THIS(0x761640);
    void UpdateWave() JMP_THIS(0x762AF0);
    void DamageArea(CoordStruct const& location) const JMP_THIS(0x75F330);

/*
        void Add_Cell(Cell * cell) JMP_THIS(0x75F4C0);
        void AI_Old() JMP_THIS(0x7610A0);
        void AI_Old_0() JMP_THIS(0x761030);
        void Calculate_Magnetic_Beam(int32_t arg_0, int32_t arg_4, int32_t a4, uint16_t * color) JMP_THIS(0x760190);
        void Calculate_Sonic_Beam(int32_t a2, int32_t a3, int32_t a4, uint16_t * color) JMP_THIS(0x75EDF0);
        int16_t * Draw_Laser(uint32_t * , int32_t * ) JMP_THIS(0x7609E0);
        void Draw_Magnetic_Beam(uint32_t * , int32_t * ) JMP_THIS(0x7602E0);
        int32_t Draw_Sonic_Beam(Point2D * arg0, int32_t a3) JMP_THIS(0x75FA90);
        void Laser_AI() JMP_THIS(0x7610D0);
        void Update_Cells() JMP_THIS(0x7610F0);
        void Wave_AI() JMP_THIS(0x762AF0);
        void wavecolor_75EF30(uint16_t * a1, int32_t a2) JMP_THIS(0x75EF30);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline WaveClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}

public:
    WaveClass(CoordStruct const& From, CoordStruct const& To, TechnoClass* Owner, WaveType mode, AbstractClass* Target)
        : WaveClass(fake_noinit_t{})
    JMP_THIS(0x75E950);
    WaveClass() : WaveClass(fake_noinit_t{}) JMP_THIS(0x75EBE0);
};
static_assert(sizeof(WaveClass) == WaveClass::ClassSize);