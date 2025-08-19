//Locomotor = {2BEA74E1-7CCA-11d3-BE14-00104B62A16C}

#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("2BEA74E1-7CCA-11d3-BE14-00104B62A16C"))
NOVTABLE ShipLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    using base_type = LocomotionClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        uintptr_t IPiggyBack;

        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F2E58;
            this->ILocomotion = 0x7F2D8C;
            this->IPiggyBack = 0x7F2D68;
        }

        __forceinline void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
    };
    static inline vtables_t vtables{};
public:
    static constexpr uintptr_t ILocoVTable = 0x7F2D8C;
    static constexpr size_t ClassSize = 0x70;
public:
    DWORD PreviousRamp;
    DWORD CurrentRamp;
    RateTimer SlopeTimer;
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

public:
    virtual ~ShipLocomotionClass() RX;

    HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) override JMP_STD(0x69EE30);
    ULONG __stdcall AddRef() override JMP_STD(0x6A4260);
    ULONG __stdcall Release() override JMP_STD(0x6A4270);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6A3E60);

	CoordStruct Destination;
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x69EE90);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x69EF10);

	HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x55A710);
	bool __stdcall Is_Moving() override JMP_STD(0x69F290);
	CoordStruct __stdcall Destination() override JMP_STD(0x69F3A0);
	CoordStruct __stdcall Head_To_Coord() override JMP_STD(0x69F3D0);
	Move __stdcall Can_Enter_Cell(CellStruct cell) override JMP_STD(0x55ABF0);
	bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x55ABE0);
	Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x69F670);
	Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x69FB20);
	Point2D __stdcall Draw_Point() override JMP_STD(0x55ABD0);
	Point2D __stdcall Shadow_Point() override JMP_STD(0x55A8C0);
	VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x55ABC0);
	int __stdcall Z_Adjust() override JMP_STD(0x6A3EA0);
	ZGradient __stdcall Z_Gradient() override JMP_STD(0x6A3EB0);
	bool __stdcall Process() override JMP_STD(0x69FC10);
	void __stdcall Move_To(CoordStruct to) override JMP_STD(0x69F450);
	void __stdcall Stop_Moving() override JMP_STD(0x69F510);
	void __stdcall Do_Turn(DirStruct coord) override JMP_STD(0x6A05C0);
	void __stdcall Unlimbo() override JMP_STD(0x69FBE0);
	void __stdcall Tilt_Pitch_Update() override JMP_STD(0x55AB90);
	bool __stdcall Power_On() override JMP_STD(0x55A8F0);
	bool __stdcall Power_Off() override JMP_STD(0x55A910);
	bool __stdcall Is_Powered() override JMP_STD(0x55A930);
	bool __stdcall Is_Ion_Sensitive() override JMP_STD(0x55A940);
	bool __stdcall Push(DirStruct dir) override JMP_STD(0x55AB70);
	bool __stdcall Shove(DirStruct dir) override JMP_STD(0x55AB80);
	void __stdcall Force_Track(int track, CoordStruct coord) override JMP_STD(0x6A0310);
	Layer __stdcall In_Which_Layer() override JMP_STD(0x6A3E50);
	void __stdcall Force_Immediate_Destination(CoordStruct coord) override JMP_STD(0x55AC00);
	void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x69F250);
	bool __stdcall Is_Moving_Now() override JMP_STD(0x69F330);
	int __stdcall Apparent_Speed() override JMP_STD(0x55AD10);
	int __stdcall Drawing_Code() override JMP_STD(0x55ACF0);
	FireError __stdcall Can_Fire() override JMP_STD(0x55AD00);
	int __stdcall Get_Status() override JMP_STD(0x4B4C60);
	void __stdcall Acquire_Hunter_Seeker_Target() override JMP_STD(0x4B4C70);
	bool __stdcall Is_Surfacing() override JMP_STD(0x4B4C80);
	void __stdcall Mark_All_Occupation_Bits(MarkType mark) override JMP_STD(0x6A3F00);
	bool __stdcall Is_Moving_Here(CoordStruct to) override JMP_STD(0x6A3F50);
	bool __stdcall Will_Jump_Tracks() override JMP_STD(0x6A4130);
	bool __stdcall Is_Really_Moving_Now() override JMP_STD(0x4B4C50);
	void __stdcall Stop_Movement_Animation() override JMP_STD(0x4B4C90);
	void __stdcall Limbo() override JMP_STD(0x4B4CA0);
	void __stdcall Unlock() override JMP_STD(0x6A4210);
	void __stdcall Lock() override JMP_STD(0x6A4220);
	int __stdcall Get_Track_Number() override JMP_STD(0x6A4230);
	int __stdcall Get_Track_Index() override JMP_STD(0x6A4240);
	int __stdcall Get_Speed_Accum() override JMP_STD(0x6A4250);

	HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) override JMP_STD(0x69EFF0);
	HRESULT __stdcall End_Piggyback(ILocomotion** pointer) override  JMP_STD(0x69F040);
	bool __stdcall Is_Ok_To_End() override JMP_STD(0x69F080);
	HRESULT __stdcall Piggyback_CLSID(GUID* classid) override JMP_STD(0x69ED20);
	bool __stdcall Is_Piggybacking() override JMP_STD(0x6A4280);

    int Size() const override JMP_THIS(0x6A42A0);

protected:
    explicit __forceinline ShipLocomotionClass(noinit_t) noexcept : LocomotionClass(noinit_t{}) {}
public:
    ShipLocomotionClass() noexcept: ShipLocomotionClass(noinit_t{}) JMP_THIS(0x69EC50);
};
static_assert(sizeof(ShipLocomotionClass) == ShipLocomotionClass::ClassSize);
