#pragma once

#include "FootClass.h"
#include "AircraftTypeClass.h"

/*!
* @brief Aircraft
*/
class NOVTABLE AircraftClass : public FootClass, public IFlyControl
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
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::Aircraft;
	static constexpr uintptr_t AbsVTable = 0x7E22A4;

	static constexpr constant_ptr<DynamicVectorClass<AircraftClass*>, 0xA8E390u> const Array{};
public:
	AircraftTypeClass* Type;
	// Whether or not to deduct ammo after firing run (strafing) is over
	bool ShouldLoseAmmo;
	//parachutes
	bool HasPassengers;
	// when crashing down, duh
	bool IsKamikaze;
	BuildingClass* DockNowHeadingTo;
	bool unknown_bool_6D0;
	bool unknown_bool_6D1;
	// Whether or not aircraft is locked to a firing run (strafing)
	bool IsLocked;
	char NumParadropsLeft;
	bool IsCarryallNotLanding;
	// Aircraft finished attack run and/or went idle and is now returning from it
	bool IsReturningFromAttackRun;

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
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	//Destructor
	virtual ~AircraftClass() RX;

	//Constructor
	AircraftClass(AircraftTypeClass* pType, HouseClass* pOwner) noexcept
		: AircraftClass(noinit_t())
	{ JMP_THIS(0x413D20); }

protected:
	explicit __forceinline AircraftClass(noinit_t) noexcept
		: FootClass(noinit_t())
	{ }
};
