//Locomotor = {2BEA74E1-7CCA-11d3-BE14-00104B62A16C}

#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("2BEA74E1-7CCA-11d3-BE14-00104B62A16C"))
NOVTABLE ShipLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    using base_type = LocomotionClass;

	// TODO stub virtuals implementations
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        uintptr_t IPiggyBack;

	//Destructor
	virtual ~ShipLocomotionClass() RX;
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


	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

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
};


protected:
    explicit __forceinline ShipLocomotionClass(noinit_t) noexcept : LocomotionClass(noinit_t{}) {}
public:
    ShipLocomotionClass() noexcept: ShipLocomotionClass(noinit_t{}) JMP_THIS(0x69EC50);
};
static_assert(sizeof(ShipLocomotionClass) == ShipLocomotionClass::ClassSize);
