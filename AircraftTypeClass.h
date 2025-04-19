#pragma once

#include "TechnoTypeClass.h"

class NOVTABLE AircraftTypeClass : public TechnoTypeClass
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
	static const AbstractType AbsID = AbstractType::AircraftType;
	static constexpr uintptr_t AbsVTable = 0x7E2868;

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
	virtual ~AircraftTypeClass() JMP_THIS(0x41CA20);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	//ObjectTypeClass
	virtual bool InstantiateAt(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* Instantiate(HouseClass* pOwner) R0;

	//TechnoTypeClass

protected:
	explicit __forceinline AircraftTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	AircraftTypeClass(noinit_t) : AircraftTypeClass(fake_noinit_t{}) JMP_THIS(0x41C9F0);
	AircraftTypeClass(const char* pId) : AircraftTypeClass(fake_noinit_t{}) JMP_THIS(0x41C8B0);
};
