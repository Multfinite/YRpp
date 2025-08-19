#pragma once

#include "TechnoTypeClass.h"

class __declspec(uuid("AE8B33D9-061C-11D2-ACA4-006008055BB5"))
NOVTABLE AircraftTypeClass : public TechnoTypeClass
{
public:
	using base_type = TechnoTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E2868;
			this->IRTTITypeInfo = 0x7E284C;
			this->INoticeSink = 0x7E2844;
			this->INoticeSource = 0x7E283C;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::AircraftType;
	static constexpr uintptr_t AbsVTable = 0x7E2868;
	static constexpr size_t ClassSize = 0xE10;

	//Array
	ABSTRACTTYPE_ARRAY(AircraftTypeClass, 0xA8B218u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//Destructor
	virtual ~AircraftTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//TechnoTypeClass

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	bool Carryall;
	AnimTypeClass* Trailer;
	int SpawnDelay;
	bool Rotors;
	bool CustomRotor;
	bool Landable;
	bool FlyBy;
	bool FlyBack;
	bool AirportBound;
	bool Fighter;
protected:
	explicit __forceinline AircraftTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	AircraftTypeClass(noinit_t) : AircraftTypeClass(fake_noinit_t{}) JMP_THIS(0x41C9F0);
	AircraftTypeClass(const char* pId) : AircraftTypeClass(fake_noinit_t{}) JMP_THIS(0x41C8B0);
};
static_assert(sizeof(AircraftTypeClass) == AircraftTypeClass::ClassSize);
