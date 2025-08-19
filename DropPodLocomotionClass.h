#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582745-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE DropPodLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	using base_type = LocomotionClass;

	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		uintptr_t IPiggyBack;

		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E8344;
			this->ILocomotion = 0x7E8278;
			this->IPiggyBack = 0x7E8254;
		}

		__forceinline void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7E8278;
	static constexpr size_t ClassSize = 0x30;
public:
	bool OutOfMap;
	CoordStruct DestinationCoords;
	ILocomotionPtr Piggybackee;
public:
	virtual ~DropPodLocomotionClass() JMP_THIS(0x4B5B00);

	HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) override JMP_STD(0x4AF720);
	ULONG __stdcall AddRef() override JMP_STD(0x4B66A0);
	ULONG __stdcall Release() override JMP_STD(0x4B66B0);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x4B6200);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4B6240);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4B62C0);

	HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x55A710);
	bool __stdcall Is_Moving() override JMP_STD(0x4B5B30);
	CoordStruct __stdcall Destination() override JMP_STD(0x4B5B40);
	Move __stdcall Can_Enter_Cell(CellStruct cell) override JMP_STD(0x55ABF0);
	bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x55ABE0);
	Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x55A7D0);
	Point2D __stdcall Draw_Point() override JMP_STD(0x55ABD0);
	Point2D __stdcall Shadow_Point() override JMP_STD(0x55A8C0);
	VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x55ABC0);
	int __stdcall Z_Adjust() override JMP_STD(0x55ABA0);
	ZGradient __stdcall Z_Gradient() override JMP_STD(0x55ABB0);
	bool __stdcall Process() override JMP_STD(0x4B5B70);
	void __stdcall Move_To(CoordStruct to) override JMP_STD(0x4B6040);
	void __stdcall Stop_Moving() override JMP_STD(0x4B63A0);
	void __stdcall Do_Turn(DirStruct coord) override JMP_STD(0x55AC30);
	void __stdcall Unlimbo() override JMP_STD(0x55AC20);
	void __stdcall Tilt_Pitch_Update() override JMP_STD(0x55AB90);
	bool __stdcall Power_On() override JMP_STD(0x55A8F0);
	bool __stdcall Power_Off() override JMP_STD(0x55A910);
	bool __stdcall Is_Powered() override JMP_STD(0x55A930);
	bool __stdcall Is_Ion_Sensitive() override JMP_STD(0x55A940);
	bool __stdcall Push(DirStruct dir) override JMP_STD(0x55AB70);
	bool __stdcall Shove(DirStruct dir) override JMP_STD(0x55AB80);
	void __stdcall Force_Track(int track, CoordStruct coord) override JMP_STD(0x55AC10);
	Layer __stdcall In_Which_Layer() override JMP_STD(0x4B64D0);
	void __stdcall Force_Immediate_Destination(CoordStruct coord) override JMP_STD(0x55AC00);
	void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x55ACE0);
	bool __stdcall Is_Moving_Now() override JMP_STD(0x4B6610);
	int __stdcall Apparent_Speed() override JMP_STD(0x55AD10);
	int __stdcall Drawing_Code() override JMP_STD(0x4B65F0);
	FireError __stdcall Can_Fire() override JMP_STD(0x55AD00);
	int __stdcall Get_Status() override JMP_STD(0x4B4C60);
	void __stdcall Acquire_Hunter_Seeker_Target() override JMP_STD(0x4B4C70);
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

	HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) override JMP_STD(0x4B63B0);
	HRESULT __stdcall End_Piggyback(ILocomotion** pointer) override JMP_STD(0x4B6400);
	bool __stdcall Is_Ok_To_End() override JMP_STD(0x4B6440)
	HRESULT __stdcall Piggyback_CLSID(GUID* classid) override JMP_STD(0x4B64E0);
	bool __stdcall Is_Piggybacking() override JMP_STD(0x4B66C0);

	int Size() const override JMP_THIS(0x4B66E0);

protected:
	explicit __forceinline DropPodLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) {}
public:
	DropPodLocomotionClass() : DropPodLocomotionClass(noinit_t{}) JMP_THIS(0x4B5AB0);

};
static_assert(sizeof(DropPodLocomotionClass) == DropPodLocomotionClass::ClassSize);
