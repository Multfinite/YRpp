//Locomotor = {4A582741-9839-11d1-B709-00A024DDAFD1}

#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582741-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE DriveLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	static constexpr uintptr_t ILocoVTable = 0x7E7EB0;

	DEFINE_ARRAY_REFERENCE(const TurnTrackType, [72], TurnTrack, 0x7E7B28)
	DEFINE_ARRAY_REFERENCE(const RawTrackType, [16], RawTrack, 0x7E7A28)

	// TODO stub virtuals implementations

	//Destructor
	virtual ~DriveLocomotionClass() RX;

    using base_type = LocomotionClass;

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        uintptr_t IPiggyBack;

        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E7F7C;
            this->ILocomotion = 0x7E7EB0;
            this->IPiggyBack = 0x7E7E8C;
        }
    
		__forceinline void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
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
};

protected:
	explicit __forceinline DriveLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) { }
public:
    DriveLocomotionClass() : DriveLocomotionClass(noinit_t{}) JMP_THIS(0x4AF540);
};
static_assert(sizeof(DriveLocomotionClass) == DriveLocomotionClass::ClassSize);
