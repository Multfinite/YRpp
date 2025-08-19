#pragma once

#include "AbstractClass.h"

//forward declarations
class AircraftTypeClass;
class ObjectClass;
class TechnoClass;
class FootClass;

//The AirstrikeClass handles the airstrikes Boris calls in.
class __declspec(uuid("70DE3921-1E26-11D5-8F95-00A02483489C"))
NOVTABLE AirstrikeClass : public AbstractClass
{
public:

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~AirstrikeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//non-virtual
	void StartMission(ObjectClass* pTarget)
		{ JMP_THIS(0x41D830); }

	void InvalidatePointer(void* ptr)
	{ JMP_THIS(0x41D540); }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E29A8;
			this->IRTTITypeInfo = 0x7E298C;
			this->INoticeSink = 0x7E2984;
			this->INoticeSource = 0x7E297C;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7E29A8;
	static constexpr AbstractType AbsID = AbstractType::Airstrike;
	static constexpr size_t ClassSize = 0x60;
public:

	int AirstrikeTeam;			//As in the INI files.
	int EliteAirstrikeTeam;	//As in the INI files.
	int AirstrikeTeamTypeIndex;	//As in the INI files.
	int EliteAirstrikeTeamTypeIndex;	//As in the INI files.
	DWORD unknown_34;
	DWORD unknown_38;	//unused?
	bool IsOnMission;	//Is the Aircraft on its way?
	bool unknown_bool_3D;
	DWORD TeamDissolveFrame;	//when was the last time this team was invoked and subsequently dissolved
	int AirstrikeRechargeTime;	//As in the INI files.
	int EliteAirstrikeRechargeTime;	//As in the INI files.
	TechnoClass* Owner;		//The unit that called the Airstrike (usually Boris).
	ObjectClass* Target;	//The Airstrike's target.
	AircraftTypeClass* AirstrikeTeamType;	//As in the INI files.
	AircraftTypeClass* EliteAirstrikeTeamType;	//As in the INI files.
	FootClass* FirstObject;
protected:
	explicit __forceinline AirstrikeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	AirstrikeClass(noinit_t) noexcept : AirstrikeClass(fake_noinit_t{}) JMP_THIS(0x41D300);
	AirstrikeClass(TechnoClass* pOwner) : AirstrikeClass(fake_noinit_t{}) JMP_THIS(0x41D380);
	AirstrikeClass() : AirstrikeClass(fake_noinit_t{}) JMP_THIS(0x41D300);
};
static_assert(sizeof(AirstrikeClass) == AirstrikeClass::ClassSize);
