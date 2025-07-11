#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582741-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE DriveLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    using base_type = LocomotionClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        uintptr_t IPiggyBack;

        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E7F7C;
            this->ILocomotion = 0x7E7EB0;
            this->IPiggyBack = 0x7E7E8C;
        }
    
        constexpr void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
    };
    static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7E7EB0;
    static constexpr size_t ClassSize = 0x70;
public:
	DWORD PreviousRamp;
	DWORD CurrentRamp;
	RateTimer SlopeTimer;
	CoordStruct Destination;
	CoordStruct HeadToCoord;
	int SpeedAccum;
	double movementspeed_50;
	DWORD TrackNumber;
	int TrackIndex;
	bool IsOnShortTrack;
	BYTE IsTurretLockedDown;
	bool IsRotating;
	bool IsDriving;
	bool IsRocking;
	bool IsLocked;
	ILocomotion* Piggybackee;
	int field_6C;
public:
	virtual ~DriveLocomotionClass() JMP_THIS(0x4AF5E0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x4B4830);

    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4AF780);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4AF800);

    HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x55A710);
    bool __stdcall Is_Moving() override JMP_STD(0x4AFB80);
    CoordStruct __stdcall Destination() override JMP_STD(0x4AFC90);
    CoordStruct __stdcall Head_To_Coord() override JMP_STD(0x4AFCC0);
    Move __stdcall Can_Enter_Cell(CellStruct cell) override JMP_STD(0x55ABF0);
    bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x55ABE0);
    Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x4AFF60);
    Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x4B0410);
    Point2D __stdcall Draw_Point() override JMP_STD(0x55ABD0);
    Point2D __stdcall Shadow_Point() override JMP_STD(0x55A8C0);
    VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x55ABC0);
    int __stdcall Z_Adjust() override JMP_STD(0x4B4870);
    ZGradient __stdcall Z_Gradient() override JMP_STD(0x4B4880);
    bool __stdcall Process() override JMP_STD(0x4B0500);
    void __stdcall Move_To(CoordStruct to) override JMP_STD(0x4AFD40);
    void __stdcall Stop_Moving() override JMP_STD(0x4AFE00);
    void __stdcall Do_Turn(DirStruct coord) override JMP_STD(0x4B0EF0);
    void __stdcall Unlimbo() override JMP_STD(0x4B04D0);
    void __stdcall Tilt_Pitch_AI() override JMP_STD(0x55AB90);
    bool __stdcall Power_On() override JMP_STD(0x55A8F0);
    bool __stdcall Power_Off() override JMP_STD(0x55A910);
    bool __stdcall Is_Powered() override JMP_STD(0x55A930);
    bool __stdcall Is_Ion_Sensitive() override JMP_STD(0x55A940);
    bool __stdcall Push(DirStruct dir) override JMP_STD(0x55AB70);
    bool __stdcall Shove(DirStruct dir) override JMP_STD(0x55AB80);
    void __stdcall Force_Track(int track, CoordStruct coord) override JMP_STD(0x4B0C40);
    Layer __stdcall In_Which_Layer() override JMP_STD(0x4B4820);
    void __stdcall Force_Immediate_Destination(CoordStruct coord) override JMP_STD(0x55AC00);
    void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x4AFB40);
    bool __stdcall Is_Moving_Now() override JMP_STD(0x4AFC20);
    int __stdcall Apparent_Speed() override JMP_STD(0x55AD10);
    int __stdcall Drawing_Code() override JMP_STD(0x55ACF0);
    FireError __stdcall Can_Fire() override JMP_STD(0x55AD00);
    int __stdcall Get_Status() override JMP_STD(0x4B4C60);
    void __stdcall Acquire_Hunter_Seeker_Target() override JMP_STD(0x4B4C70);
    bool __stdcall Is_Surfacing() override JMP_STD(0x4B4C80);
    void __stdcall Mark_All_Occupation_Bits(MarkType mark) override JMP_STD(0x4B48D0);
    bool __stdcall Is_Moving_Here(CoordStruct to) override JMP_STD(0x4B4920);
    bool __stdcall Will_Jump_Tracks() override JMP_STD(0x4B4B00);
    bool __stdcall Is_Really_Moving_Now() override JMP_STD(0x4B4C50);
    void __stdcall Stop_Movement_Animation() override JMP_STD(0x4B4C90);
    void __stdcall Limbo() override JMP_STD(0x4B4CA0);
    void __stdcall Unlock() override JMP_STD(0x4B4BE0);
    void __stdcall Lock() override JMP_STD(0x4B4BF0);
    int __stdcall Get_Track_Number() override JMP_STD(0x4B4C00);
    int __stdcall Get_Track_Index() override JMP_STD(0x4B4C10);
    int __stdcall Get_Speed_Accum() override JMP_STD(0x4B4C20);

    HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) override JMP_STD(0x4AF8E0);
    HRESULT __stdcall End_Piggyback(ILocomotion** pointer) override JMP_STD(0x4AF930);
    bool __stdcall Is_Ok_To_End() override JMP_STD(0x4AF970);
    HRESULT __stdcall Piggyback_CLSID(GUID* classid) override JMP_STD(0x4AF610);
    bool __stdcall Is_Piggybacking() override JMP_STD(0x4B4CD0);

    int SizeOf() const override JMP_THIS(0x4B4CF0);

/*
    void Mark_Track(Coordinate* headto, MarkType type) JMP_THIS(0x4B0AD0);
    int32_t SetSloped(int32_t a2) JMP_THIS(0x4AFB00);
    bool Sloped() JMP_THIS(0x4AFED0);
    double Sloped_0() JMP_THIS(0x4AFAA0);
    Matrix3D_Union* Sloped_Matrix(Matrix3D_Union* a2) JMP_THIS(0x4AF9B0);
    Coordinate* Smooth_Turn(Coordinate* arg_0, Coordinate* adj, int32_t* dir) JMP_THIS(0x4B4780);
    void Start_Of_Move(uint8_t* a5, Cell navcell, int32_t a2) JMP_THIS(0x4B2630);
    int8_t Stop_Driver_maybe() JMP_THIS(0x4B0DA0);
    int8_t While_Moving(int8_t arg0) JMP_THIS(0x4B0F20);
*/

protected:
	explicit __forceinline DriveLocomotionClass(noinit_t) : LocomotionClass(noinit_t()) { }
public:
    DriveLocomotionClass() : DriveLocomotionClass(noinit_t()) JMP_THIS(0x4AF540);
};
static_assert(sizeof(DriveLocomotionClass) == DriveLocomotionClass::ClassSize);
