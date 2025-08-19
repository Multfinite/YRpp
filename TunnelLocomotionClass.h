//Locomotor = {4A582743-9839-11d1-B709-00A024DDAFD1}

#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582743-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE TunnelLocomotionClass : public LocomotionClass
{
public:
	DEFINE_REFERENCE(double const, TunnelMovementSpeed, 0x7F5B20u)
	using base_type = LocomotionClass;

	enum State
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

	// TODO stub virtuals implementations

	bool ProcessPreDigIn()
		{ JMP_THIS(0x7291F0); }

	bool ProcessDiggingIn()
		{ JMP_THIS(0x729370); }

	bool ProcessDugIn()
		{ JMP_THIS(0x7294E0); }

	bool ProcessDigging()
		{ JMP_THIS(0x729580); }

	bool ProcessPreDigOut()
		{ JMP_THIS(0x7298F0); }

	bool ProcessDiggingOut()
		{ JMP_THIS(0x729AA0); }

	bool ProcessDugOut()
		{ JMP_THIS(0x729480); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
	explicit __forceinline TunnelLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) { }
public:

	TunnelLocomotionClass::State State;
	CoordStruct Coords;
	RateTimer DigTimer;
	bool bool38;
	TunnelLocomotionClass()	: TunnelLocomotionClass(noinit_t{}) JMP_THIS(0x728A00);
};
static_assert(sizeof(TunnelLocomotionClass) == TunnelLocomotionClass::ClassSize);
