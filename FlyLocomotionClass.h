#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582746-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE FlyLocomotionClass : public LocomotionClass
{
public:
	using base_type = LocomotionClass;

	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E8AC0;
			this->ILocomotion = 0x7E89F4;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7E89F4;
	static constexpr size_t ClassSize = 0x60;
public:
	bool AirportBound;
	CoordStruct DestinationCoords;
	CoordStruct XYZ2;
	bool HasMoveOrder;
	int FlightLevel;
	double TargetSpeed;
	double CurrentSpeed;
	char IsTakingOff;
	bool IsLanding;
	bool WasLanding;
	bool unknown_bool_53;
	DWORD unknown_54;
	DWORD unknown_58;
	bool IsElevating;
	bool unknown_bool_5D;
	bool unknown_bool_5E;
	bool unknown_bool_5F;
public:
	virtual ~FlyLocomotionClass() JMP_THIS(0x4CCA70);

	HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) override R0;
	ULONG __stdcall AddRef() override R0;
	ULONG __stdcall Release() override R0;

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x4CFC80);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4CFCC0);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override R0;

	HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x4CCA20);
	bool __stdcall Is_Moving() override JMP_STD(0x4CCA90);
	CoordStruct __stdcall Destination() override JMP_STD(0x4CCAE0);
	Move __stdcall Can_Enter_Cell(CellStruct cell) override JMP_STD(0x55ABF0);
	bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x55ABE0);
	Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x4CF610);
	Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x4CFB00);
	Point2D __stdcall Draw_Point() override JMP_STD(0x4CF830);
	Point2D __stdcall Shadow_Point() override JMP_STD(0x4CF940);
	VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x55ABC0);
	int __stdcall Z_Adjust() override JMP_STD(0x55ABA0);
	ZGradient __stdcall Z_Gradient() override JMP_STD(0x55ABB0);
	bool __stdcall Process() override JMP_STD(0x4CCB40);
	void __stdcall Move_To(CoordStruct to) override JMP_STD(0x4CCC80);
	void __stdcall Stop_Moving() override JMP_STD(0x4CCFD0);
	void __stdcall Do_Turn(DirStruct coord) override JMP_STD(0x4CFC10);
	void __stdcall Unlimbo() override JMP_STD(0x55AC20);
	void __stdcall Tilt_Pitch_AI() override JMP_STD(0x55AB90);
	bool __stdcall Power_On() override JMP_STD(0x55A8F0);
	bool __stdcall Power_Off() override JMP_STD(0x4CFD20);
	bool __stdcall Is_Powered() override JMP_STD(0x4CFD90);
	bool __stdcall Is_Ion_Sensitive() override JMP_STD(0x4CFDA0);
	bool __stdcall Push(DirStruct dir) override JMP_STD(0x55AB70);
	bool __stdcall Shove(DirStruct dir) override JMP_STD(0x55AB80);
	void __stdcall Force_Track(int track, CoordStruct coord) override JMP_STD(0x55AC10);
	Layer __stdcall In_Which_Layer() override JMP_STD(0x4CFCF0);
	void __stdcall Force_Immediate_Destination(CoordStruct coord) override JMP_STD(0x55AC00);
	void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x55ACE0);
	bool __stdcall Is_Moving_Now() override JMP_STD(0x4CCAC0);
	int __stdcall Apparent_Speed() override JMP_STD(0x4CFE20);
	int __stdcall Drawing_Code() override JMP_STD(0x55ACF0);
	FireError __stdcall Can_Fire() override JMP_STD(0x55AD00);
	int __stdcall Get_Status() override JMP_STD(0x4CFE50);
	void __stdcall Acquire_Hunter_Seeker_Target() override JMP_STD(0x4CFE80);
	bool __stdcall Is_Surfacing() override JMP_STD(0x4B4C80);
	void __stdcall Mark_All_Occupation_Bits(MarkType mark) override JMP_STD(0x4B6620);
	bool __stdcall Is_Moving_Here(CoordStruct to) override JMP_STD(0x4B6630);
	bool __stdcall Will_Jump_Tracks() override JMP_STD(0x4B6640);
	bool __stdcall Is_Really_Moving_Now() override JMP_STD(0x4B4C50);
	void __stdcall Stop_Movement_Animation() override JMP_STD(0x4B4C90);
	void __stdcall Limbo() override JMP_STD(0x4B4CA0);
	void __stdcall Lock() override JMP_STD(0x4B6650);
	void __stdcall Unlock() override JMP_STD(0x4B6660);
	int __stdcall Get_Track_Number() override JMP_STD(0x4B6670);
	int __stdcall Get_Track_Index() override JMP_STD(0x4B6680);
	int __stdcall Get_Speed_Accum() override JMP_STD(0x4B6690);

	int SizeOf() const override JMP_THIS(0x4D0390);

protected:
	explicit __forceinline FlyLocomotionClass(noinit_t) : LocomotionClass(noinit_t()) { }
public:
	FlyLocomotionClass() : LocomotionClass(noinit_t()) JMP_THIS(0x4CC9A0);
};
static_assert(sizeof(FlyLocomotionClass) == FlyLocomotionClass::ClassSize);
