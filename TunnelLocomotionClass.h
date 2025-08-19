#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582743-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE TunnelLocomotionClass : public LocomotionClass
{
public:
	using base_type = LocomotionClass;

	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F5AF0;
			this->ILocomotion = 0x7F5A24;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7F5A24;
	static constexpr size_t ClassSize = 0x3C;
	DEFINE_REFERENCE(double, TunnelMovementSpeed, 0x7F5B20u)
public:
	enum State : int
	{
		Idle = 0,
		PreDigIn = 1,
		DiggingIn = 2,
		DugIn = 3,
		Digging = 4,
		PreDigOut = 5,
		DiggingOut = 6,
		DugOut = 7
	};

	TunnelLocomotionClass::State State;
	Coordinate Coords;
	RateTimer DigTimer;
	bool IsMoving;
public:
	/* SDTOR: 0x72A210 */
	virtual ~TunnelLocomotionClass() RX;

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x72A110);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x72A150);

	//HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x55A710);
	bool __stdcall Is_Moving() override JMP_STD(0x728A50);
	Coordinate __stdcall Destination() override JMP_STD(0x728A90);
	Move __stdcall Can_Enter_Cell(::Cell cell) override JMP_STD(0x72A090);
	bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x72A060);
	Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x729B40);
	//Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x55A7D0);
	//Point2D __stdcall Draw_Point() override JMP_STD(0x55ABD0);
	//Point2D __stdcall Shadow_Point() override JMP_STD(0x55A8C0);
	VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x7291D0);
	int __stdcall Z_Adjust() override JMP_STD(0x729E50);
	ZGradient __stdcall Z_Gradient() override JMP_STD(0x72A020);
	bool __stdcall Process() override JMP_STD(0x728E30);
	void __stdcall Move_To(Coordinate to) override JMP_STD(0x728AF0);
	void __stdcall Stop_Moving() override JMP_STD(0x728C00);
	void __stdcall Do_Turn(DirStruct coord) override JMP_STD(0x72A0E0);
	//void __stdcall Unlimbo() override JMP_STD(0x55AC20);
	//void __stdcall Tilt_Pitch_Update() override JMP_STD(0x55AB90);
	//bool __stdcall Power_On() override JMP_STD(0x55A8F0);
	//bool __stdcall Power_Off() override JMP_STD(0x55A910);
	//bool __stdcall Is_Powered() override JMP_STD(0x55A930);
	//bool __stdcall Is_Ion_Sensitive() override JMP_STD(0x55A940);
	//bool __stdcall Push(DirStruct dir) override JMP_STD(0x55AB70);
	//bool __stdcall Shove(DirStruct dir) override JMP_STD(0x55AB80);
	//void __stdcall Force_Track(int track, Coordinate coord) override JMP_STD(0x55AC10);
	Layer __stdcall In_Which_Layer() override JMP_STD(0x72A1A0);
	//void __stdcall Force_Immediate_Destination(Coordinate coord) override JMP_STD(0x55AC00);
	//void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x55ACE0);
	bool __stdcall Is_Moving_Now() override JMP_STD(0x728A60);
	//int __stdcall Apparent_Speed() override JMP_STD(0x55AD10);
	//int __stdcall Drawing_Code() override JMP_STD(0x55ACF0);
	FireError __stdcall Can_Fire() override JMP_STD(0x72A1C0);
	//int __stdcall Get_Status() override JMP_STD(0x4B4C60);
	//void __stdcall Acquire_Hunter_Seeker_Target() override JMP_STD(0x4B4C70);
	bool __stdcall Is_Surfacing() override JMP_STD(0x72A1E0);
	//void __stdcall Mark_All_Occupation_Bits(MarkType mark) override JMP_STD(0x4B6620);
	//bool __stdcall Is_Moving_Here(Coordinate to) override JMP_STD(0x4B6630);
	//bool __stdcall Will_Jump_Tracks() override JMP_STD(0x4B6640);
	//bool __stdcall Is_Really_Moving_Now() override JMP_STD(0x4B4C50);
	//void __stdcall Stop_Movement_Animation() override JMP_STD(0x4B4C90);
	//void __stdcall Limbo() override JMP_STD(0x4B4CA0);
	//void __stdcall Lock() override JMP_STD(0x4B6650);
	//void __stdcall Unlock() override JMP_STD(0x4B6660);
	//int __stdcall Get_Track_Number() override JMP_STD(0x4B6670);
	//int __stdcall Get_Track_Index() override JMP_STD(0x4B6680);
	//int __stdcall Get_Speed_Accum() override JMP_STD(0x4B6690);

	int Size() const override JMP_THIS(0x72A200);

	bool ProcessPreDigIn() JMP_THIS(0x7291F0); 
	bool ProcessDiggingIn() JMP_THIS(0x729370); 
	bool ProcessDugIn() JMP_THIS(0x7294E0); 
	bool ProcessDigging() JMP_THIS(0x729580); 
	bool ProcessPreDigOut() JMP_THIS(0x7298F0);
	bool ProcessDiggingOut() JMP_THIS(0x729AA0);
	bool ProcessDugOut() JMP_THIS(0x729480);

protected:
	explicit __forceinline TunnelLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) { }
public:
	TunnelLocomotionClass()	: TunnelLocomotionClass(noinit_t{}) JMP_THIS(0x728A00);
};
static_assert(sizeof(TunnelLocomotionClass) == TunnelLocomotionClass::ClassSize);
