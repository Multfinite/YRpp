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

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x41CEB0);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x41CE20);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x41CE90);

	RTTIType KindOf() const override JMP_THIS(0x41CFB0);
	int SizeOf() const override JMP_THIS(0x41CFC0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x41CDB0);
	int ArrayIndex() const override JMP_THIS(0x41CFD0);

	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x41CC20);

	Point3D LeptonDimensions() const override JMP_THIS(0x41CBF0);
	bool InstantiateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x41CBE0);
	ObjectClass* Instantiate(HouseClass* pOwner) override JMP_THIS(0x41CB20);
	CellStruct* OccupiedCells(bool placement) const override JMP_THIS(0x41CB70);

	bool CanUseWaypoint() const override JMP_THIS(0x41CB50);
	bool CanAttackMove() const override JMP_THIS(0x41CB60);

protected:
	explicit __forceinline AircraftTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	AircraftTypeClass(noinit_t) : AircraftTypeClass(fake_noinit_t{}) JMP_THIS(0x41C9F0);
	AircraftTypeClass(const char* pId) : AircraftTypeClass(fake_noinit_t{}) JMP_THIS(0x41C8B0);
};
static_assert(sizeof(AircraftTypeClass) == AircraftTypeClass::ClassSize);