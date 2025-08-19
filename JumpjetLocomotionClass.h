#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("92612C46-F71F-11d1-AC9F-006008055BB5"))
NOVTABLE JumpjetLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	using base_type = LocomotionClass;

	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		uintptr_t IPiggyBack;

		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7ECE34;
			this->ILocomotion = 0x7ECD68;
			this->IPiggyBack = 0x7ECD44;
		}

		__forceinline void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7ECD68;
	static constexpr size_t ClassSize = 0x98;
public:
	enum State
	{
		Grounded = 0,
		Ascending = 1,
		Hovering = 2,
		Cruising = 3,
		Descending = 4,
		Crashing = 5,
		Unknown = 6,
	};

	int TurnRate;
	int Speed;
	float Climb;
	float Crash;
	int Height;
	float Accel;
	float Wobbles;
	int Deviation;
	bool NoWobbles;
	BYTE unknown_3D;
	BYTE unknown_3E;
	BYTE unknown_3F;
	Coordinate DestinationCoords;
	bool IsMoving;
	BYTE unknown_4D;
	BYTE unknown_4E;
	BYTE unknown_4F;
	JumpjetLocomotionClass::State State;
	FacingClass LocomotionFacing;
	BYTE unknown_6C;
	BYTE unknown_6D;
	BYTE unknown_6E;
	BYTE unknown_6F;
	double CurrentSpeed;
	double MaxSpeed;
	int CurrentHeight;
	BYTE unknown_84;
	BYTE unknown_85;
	BYTE unknown_86;
	BYTE unknown_87;
	double CurrentWobbles;
	bool DestinationReached;
	BYTE unknown_91;
	BYTE unknown_92;
	BYTE unknown_93;
	ILocomotion* Piggybackee;
public:
	virtual ~JumpjetLocomotionClass() JMP_THIS(0x54AD00);

	HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) override JMP_STD(0x54DC60);
	ULONG __stdcall AddRef() override JMP_STD(0x54DF50);
	ULONG __stdcall Release() override JMP_STD(0x54DF60);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x54B710);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x54B750);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x54B7E0);

	HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x54AD30);
	bool __stdcall Is_Moving() override JMP_STD(0x54AE50);
	Coordinate __stdcall Destination() override JMP_STD(0x54AE60);
	Coordinate __stdcall Head_To_Coord() override JMP_STD(0x54D9B0);
	Move __stdcall Can_Enter_Cell(CellStruct cell) override JMP_STD(0x55ABF0);
	bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x55ABE0);
	Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x54DCC0);
	Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x55A7D0);
	Point2D __stdcall Draw_Point() override JMP_STD(0x55ABD0);
	Point2D __stdcall Shadow_Point() override JMP_STD(0x55A8C0);
	VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x55ABC0);
	int __stdcall Z_Adjust() override JMP_STD(0x55ABA0);
	ZGradient __stdcall Z_Gradient() override JMP_STD(0x55ABB0);
	bool __stdcall Process() override JMP_STD(0x54AEC0);
	void __stdcall Move_To(Coordinate to) override JMP_STD(0x54B1C0);
	void __stdcall Stop_Moving() override JMP_STD(0x54B4D0);
	void __stdcall Do_Turn(DirStruct coord) override JMP_STD(0x54B6E0);
	void __stdcall Unlimbo() override JMP_STD(0x55AC20);
	void __stdcall Tilt_Pitch_Update() override JMP_STD(0x55AB90);
	bool __stdcall Power_On() override JMP_STD(0x55A8F0);
	bool __stdcall Power_Off() override JMP_STD(0x55A910);
	bool __stdcall Is_Powered() override JMP_STD(0x55A930);
	bool __stdcall Is_Ion_Sensitive() override JMP_STD(0x55A940);
	bool __stdcall Push(DirStruct dir) override JMP_STD(0x55AB70);
	bool __stdcall Shove(DirStruct dir) override JMP_STD(0x55AB80);
	void __stdcall Force_Track(int track, Coordinate coord) override JMP_STD(0x55AC10);
	Layer __stdcall In_Which_Layer() override JMP_STD(0x54B8D0);
	void __stdcall Force_Immediate_Destination(Coordinate coord) override JMP_STD(0x55AC00);
	void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x55ACE0);
	bool __stdcall Is_Moving_Now() override JMP_STD(0x54D0D0);
	int __stdcall Apparent_Speed() override JMP_STD(0x55AD10);
	int __stdcall Drawing_Code() override JMP_STD(0x55ACF0);
	FireError __stdcall Can_Fire() override JMP_STD(0x55AD00);
	int __stdcall Get_Status() override JMP_STD(0x4B4C60);
	void __stdcall Acquire_Hunter_Seeker_Target() override JMP_STD(0x4B4C70);
	bool __stdcall Is_Surfacing() override JMP_STD(0x4B4C80);
	void __stdcall Mark_All_Occupation_Bits(MarkType mark) override JMP_STD(0x54D930);
	bool __stdcall Is_Moving_Here(Coordinate to) override JMP_STD(0x4B6630);
	bool __stdcall Will_Jump_Tracks() override JMP_STD(0x4B6640);
	bool __stdcall Is_Really_Moving_Now() override JMP_STD(0x4B4C50);
	void __stdcall Stop_Movement_Animation() override JMP_STD(0x4B4C90);
	void __stdcall Limbo() override JMP_STD(0x4B4CA0);
	void __stdcall Lock() override JMP_STD(0x4B6650);
	void __stdcall Unlock() override JMP_STD(0x4B6660);
	int __stdcall Get_Track_Number() override JMP_STD(0x4B6670);
	int __stdcall Get_Track_Index() override JMP_STD(0x4B6680);
	int __stdcall Get_Speed_Accum() override JMP_STD(0x4B6690);

	HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) override JMP_STD(0x54DA00);
	HRESULT __stdcall End_Piggyback(ILocomotion** pointer) override  JMP_STD(0x54DA50);
	bool __stdcall Is_Ok_To_End() override JMP_STD(0x54DB00);
	HRESULT __stdcall Piggyback_CLSID(GUID* classid) override JMP_STD(0x54DB50);
	bool __stdcall Is_Piggybacking() override JMP_STD(0x54DF70);

	int Size() const override JMP_THIS(0x54DF90);

protected:
	explicit __forceinline JumpjetLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) { }
public:
	JumpjetLocomotionClass() : LocomotionClass(noinit_t{}) JMP_THIS(0x54AC40);
};
static_assert(sizeof(JumpjetLocomotionClass) == JumpjetLocomotionClass::ClassSize);
