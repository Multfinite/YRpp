#pragma once

#include "TechnoTypeClass.h"

class NOVTABLE AircraftTypeClass : public TechnoTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::AircraftType;
	static constexpr uintptr_t AbsVTable = 0x7E2868;

	//Array
	ABSTRACTTYPE_ARRAY(AircraftTypeClass, 0xA8B218u);
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
public:
	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//Destructor
	virtual ~AircraftTypeClass() RX;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	//ObjectTypeClass
	virtual bool InstantiateAt(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* Instantiate(HouseClass* pOwner) R0;

	//TechnoTypeClass

	//Constructor
	AircraftTypeClass(const char* pID) noexcept
		: AircraftTypeClass(noinit_t())
	{ JMP_THIS(0x41C8B0); }

protected:
	explicit __forceinline AircraftTypeClass(noinit_t) noexcept
		: TechnoTypeClass(noinit_t())
	{ }
};
