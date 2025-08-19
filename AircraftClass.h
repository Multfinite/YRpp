/*
	Aircraft
*/

#pragma once

#include "FootClass.h"
#include "AircraftTypeClass.h"

//AircraftClass
class __declspec(uuid("0E272DC2-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE AircraftClass : public FootClass, public IFlyControl
{
public:
	using base_type = TechnoClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		uintptr_t IFlyControl;

		constexpr vtables_t() noexcept : base_type::vtables_t(), IFlyControl(0x7E2250)
		{
			this->IPersistStream = 0x7E22A4;
			this->IRTTITypeInfo = 0x7E2288;
			this->INoticeSink = 0x7E2280;
			this->INoticeSource = 0x7E2278;
		}

		__forceinline void init(AircraftClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::Aircraft;
	static constexpr uintptr_t AbsVTable = 0x7E22A4;
	static constexpr size_t ClassSize = 0x6D8;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<AircraftClass*>, Array, 0xA8E390u)

	//IFlyControl
	virtual int __stdcall Landing_Altitude() R0;
	virtual int __stdcall Landing_Direction() R0;
	virtual long __stdcall Is_Loaded() R0;
	virtual long __stdcall Is_Strafe() R0;
	virtual long __stdcall Is_Fighter() R0;
	virtual long __stdcall Is_Locked() R0;

	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	virtual ULONG __stdcall AddRef() R0;
	virtual ULONG __stdcall Release() R0;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//Destructor
	virtual ~AircraftClass() RX;

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	AircraftTypeClass* Type;
	bool ShouldLoseAmmo; // Whether or not to deduct ammo after firing run (strafing) is over
	bool HasPassengers;	//parachutes
	bool IsKamikaze; // when crashing down, duh
	BuildingClass* DockNowHeadingTo;
	bool unknown_bool_6D0;
	bool unknown_bool_6D1;
	bool IsLocked; // Whether or not aircraft is locked to a firing run (strafing)
	char NumParadropsLeft;
	bool IsCarryallNotLanding;
	bool IsReturningFromAttackRun; // Aircraft finished attack run and/or went idle and is now returning from it
protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline AircraftClass(fake_noinit_t) noexcept : FootClass(fake_noinit_t{}) {}
	
public:
	//AircraftClass() {}
	AircraftClass(noinit_t) noexcept : FootClass(fake_noinit_t{}) { vtables.init(this); }
	AircraftClass(AircraftTypeClass* type, HouseClass* owner) : AircraftClass(fake_noinit_t{}) JMP_THIS(0x413D20);
};
static_assert(sizeof(AircraftClass) == AircraftClass::ClassSize);
