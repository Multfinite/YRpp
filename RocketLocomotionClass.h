#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("B7B49766-E576-11d3-9BD9-00104B972FE8"))
NOVTABLE RocketLocomotionClass : public LocomotionClass
{
public:
	using base_type = LocomotionClass;

	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F0BE8;
			this->ILocomotion = 0x7F0B1C;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7F0B1C;
	static constexpr size_t ClassSize = 0x60;
public:
	CoordStruct DestinationCoords;
	RateTimer MissionTimer;
	CDTimerClass TrailerTimer;
	int MissionState;
	DWORD unknown_44;
	double CurrentSpeed;
	bool unknown_bool_4C;
	bool SpawnerIsElite;
	float CurrentPitch;
	DWORD unknown_58;
	DWORD unknown_5C;
public:
	virtual ~RocketLocomotionClass() JMP_THIS(0x661F30);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6633D0);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x663410);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override R0;

    HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x55A710);
    bool __stdcall Is_Moving() override JMP_STD(0x661F50);
    CoordStruct __stdcall Destination() override JMP_STD(0x661FB0);
    //CoordStruct __stdcall Head_To_Coord() override;
    Move __stdcall Can_Enter_Cell(CellStruct cell) override JMP_STD(0x55ABF0);
    bool __stdcall Is_To_Have_Shadow() override JMP_STD(0x55ABE0);
    Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x663470);
    Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) override JMP_STD(0x55A7D0);
    Point2D __stdcall Draw_Point() override JMP_STD(0x55ABD0);
    Point2D __stdcall Shadow_Point() override JMP_STD(0x55A8C0);
    VisualType __stdcall Visual_Character(bool raw) override JMP_STD(0x55ABC0);
    int __stdcall Z_Adjust() override JMP_STD(0x55ABA0);
    ZGradient __stdcall Z_Gradient() override JMP_STD(0x55ABB0);
    bool __stdcall Process() override JMP_STD(0x6622C0);
    void __stdcall Move_To(CoordStruct to) override JMP_STD(0x6632E0);
    void __stdcall Stop_Moving() override JMP_STD(0x6633C0);
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
    Layer __stdcall In_Which_Layer() override JMP_STD(0x663460);
    void __stdcall Force_Immediate_Destination(CoordStruct coord) override JMP_STD(0x55AC00);
    void __stdcall Force_New_Slope(int ramp) override JMP_STD(0x55ACE0);
    bool __stdcall Is_Moving_Now() override JMP_STD(0x661F90);
    int __stdcall Apparent_Speed() override JMP_STD(0x55AD10);
    int __stdcall Drawing_Code() override JMP_STD(0x55ACF0);
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

	int Size() const JMP_THIS(0x6635B0);

/*
	double Calculate_Pitch() JMP_THIS(0x662240);
	void Explode() JMP_THIS(0x663030);
	Coordinate Get_Next_Position(int32_t speed) JMP_THIS(0x661FE0);
	bool Time_To_Explode(RocketStruct* rocket) JMP_THIS(0x6620F0);
*/

protected:
	explicit __forceinline RocketLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) { }
public:
	RocketLocomotionClass() : RocketLocomotionClass(noinit_t{}) JMP_THIS(0x661EC0);
};
static_assert(sizeof(RocketLocomotionClass) == RocketLocomotionClass::ClassSize);
