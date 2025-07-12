#pragma once

#include "GeneralDefinitions.h"
#include "GeneralStructures.h"
#include "AbstractClass.h"
#include "ColorScheme.h"
#include "Helpers/CompileTime.h"

struct TacticalSelectableStruct
{
    TechnoClass* Techno;
    int X;
    int Y;
};

class DSurface;
class CellClass;

/*!
* @brief TacticalClass - handles tactical map rendering and display
*/
class __declspec(uuid("CF56B38A-240D-11D2-817C-006008055BB5"))
NOVTABLE TacticalClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F4348;
            this->IRTTITypeInfo = 0x7F432C;
            this->INoticeSink = 0x7F4324;
            this->INoticeSource = 0x7F431C;
        }
    };
    static inline vtables_t vtables{};
public:
    static constexpr AbstractType AbsID = AbstractType::TacticalMap;
    static constexpr uintptr_t AbsVTable = 0x7F4348;
    static constexpr size_t ClassSize = 0xE18;

    static constexpr reference<TacticalClass*, 0x887324u> const Instance{};

    // Properties
    wchar_t ScreenText[64];
    int EndGameGraphicsFrame;
    int LastAIFrame;
    bool field_AC;
    bool field_AD;
    PROTECTED_PROPERTY(char, gap_AE[2]);
    Point2D TacticalPos;
    Point2D LastTacticalPos;
    double ZoomInFactor;
    Point2D Point_C8;
    Point2D Point_D0;
    float field_D8;
    float field_DC;
    int VisibleCellCount;
    CellClass* VisibleCells[800];
    Point2D TacticalCoord1;
    DWORD field_D6C;
    DWORD field_D70;
    Point2D TacticalCoord2;
    bool field_D7C;
    bool Redrawing;
    PROTECTED_PROPERTY(char, gap_D7E[2]);
    RectangleStruct ContainingMapCoords;
    LTRBStruct Band;
    DWORD MouseFrameIndex;
    CDTimerClass StartTime;
    int SelectableCount;
    Matrix3D Unused_Matrix3D;
    Matrix3D IsoTransformMatrix;
    DWORD field_E14;

public:
    virtual ~TacticalClass() JMP_THIS(0x6D1C20);

    virtual bool DrawLine_6DBB60(RectangleStruct const& a2, RectangleStruct const& a3, COLORREF a4, bool bool1) JMP_THIS(0x6DBB60);

    void SetTacticalPosition(CoordStruct* pCoord) JMP_THIS(0x6D6070);
    CellStruct* CoordsToCell(CellStruct* pDest, CoordStruct* pSource) JMP_THIS(0x6D6590);
    [[deprecated]] bool CoordsToClient(CoordStruct const* coords, Point2D* pOutClient) const JMP_THIS(0x6D2140);
    [[deprecated]] Point2D* CoordsToScreen(Point2D* pDest, const CoordStruct* pSource) JMP_THIS(0x6D1F10);
    CoordStruct* ClientToCoords(CoordStruct* pOutBuffer, Point2D const& client) const JMP_THIS(0x6D2280);
    char GetOcclusion(const CellStruct& cell, bool fog) const JMP_THIS(0x6D8700);

    // Helper methods
    std::pair<Point2D, bool> CoordsToClient(const CoordStruct& coords) const
    {
        constexpr reference<RectangleStruct, 0xB0CE28> view_bound{};
        Point2D point = CoordsToScreen(coords) - this->TacticalPos;
        bool visible = point.X >= -360 && point.X <= view_bound->Width + 360
            && point.Y >= -180 && point.Y <= view_bound->Height + 180;
        return std::make_pair(point, visible);
    }

    static Point2D CoordsToScreen(const CoordStruct& coord)
    {
        auto [x, y] = AdjustForZShapeMove(coord.X, coord.Y);
        return Point2D{ x, y - AdjustForZ(coord.Z) };
    }

    CoordStruct ClientToCoords(Point2D const& client) const
    {
        CoordStruct buffer;
        this->ClientToCoords(&buffer, client);
        return buffer;
    }

    static Point2D AdjustForZShapeMove(int x, int y)
    {
        return Point2D{
            (-Unsorted::CellWidthInPixels * y / 2 + Unsorted::CellWidthInPixels * x / 2) / Unsorted::LeptonsPerCell,
            (Unsorted::CellHeightInPixels * y / 2 + Unsorted::CellHeightInPixels * x / 2) / Unsorted::LeptonsPerCell
        };
    }

    static int __fastcall AdjustForZ(int Height)
    {
        return static_cast<int>(Height * (*reinterpret_cast<double*>(0xB0CD48)) + int(Height >= 728) + 0.5);
    }

    // View operations
    void FocusOn(CoordStruct* pDest, int Velocity) JMP_THIS(0x6D2420);
    void RegisterDirtyArea(RectangleStruct Area, bool bUnk) JMP_THIS(0x6D2790);
    void RegisterCellAsVisible(CellClass* pCell) JMP_THIS(0x6DA7D0);
    static int DrawTimer(int index, ColorScheme* Scheme, int Time, wchar_t* Text, Point2D* someXY1, Point2D* someXY2) JMP_STD(0x6D4B50);
    void AddSelectable(TechnoClass* pTechno, int x, int y) JMP_THIS(0x6D9EF0);

    // Rendering
    void Render(DSurface* pSurface, bool flag, int eMode) JMP_THIS(0x6D3D10);
    [[deprecated]] Point2D* ApplyMatrix_Pixel(Point2D* coords, Point2D* offset) JMP_THIS(0x6D2070);

    Point2D ApplyMatrix_Pixel(const Point2D& offset)
    {
        auto&& temp = this->IsoTransformMatrix * Vector3D<float>{(float)offset.X, (float)offset.Y, 0};
        return { (int)temp.X,(int)temp.Y };
    }

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TacticalClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    TacticalClass() : TacticalClass(fake_noinit_t{}) JMP_THIS(0x6D1C20);
    TacticalClass(noinit_t) noexcept : TacticalClass(fake_noinit_t{}) JMP_THIS(0x6D1E30);
};
static_assert(sizeof(TacticalClass) == TacticalClass::ClassSize);