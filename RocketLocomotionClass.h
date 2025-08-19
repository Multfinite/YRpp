//Locomotor = {B7B49766-E576-11d3-9BD9-00104B972FE8}

#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("B7B49766-E576-11d3-9BD9-00104B972FE8"))
NOVTABLE RocketLocomotionClass : public LocomotionClass
{
public:
	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	virtual ULONG __stdcall AddRef() R0;
	virtual ULONG __stdcall Release() R0;

	//ILocomotion
	virtual bool __stdcall Is_Moving() R0;
	virtual CoordStruct* __stdcall Destination(CoordStruct* pcoord) R0;
	virtual bool __stdcall Process() R0;
	virtual void __stdcall Move_To(CoordStruct to) RX;
	virtual void __stdcall Stop_Moving() RX;
	virtual void __stdcall Do_Turn(DirStruct coord) RX;
	virtual Layer __stdcall In_Which_Layer() RT(Layer);
	virtual void __stdcall Mark_All_Occupation_Bits(MarkType mark) RX;
	virtual void __stdcall Limbo() RX;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~RocketLocomotionClass() RX;

	//LocomotionClass
	virtual	int Size() R0;

	//RocketLocomotionClass

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
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

	CoordStruct MovingDestination;
	static constexpr uintptr_t ILocoVTable = 0x7F0B1C;
	static constexpr size_t ClassSize = 0x60;
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
protected:
	explicit __forceinline RocketLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) { }
public:
	RocketLocomotionClass() : RocketLocomotionClass(noinit_t{}) JMP_THIS(0x661EC0);
};
static_assert(sizeof(RocketLocomotionClass) == RocketLocomotionClass::ClassSize);
