#pragma once

#include "AbstractTypeClass.h"
#include "Helpers\String.h"

class AircraftTypeClass;
class InfantryTypeClass;
class UnitTypeClass;

class NOVTABLE HouseTypeClass : public AbstractTypeClass
{
public:
	using base_type = AbstractTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EAB58;
			this->IRTTITypeInfo = 0x7EAB3C;
			this->INoticeSink = 0x7EAB34;
			this->INoticeSource = 0x7EAB2C;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::HouseType;

	//Array
	ABSTRACTTYPE_ARRAY(HouseTypeClass, 0xA83C98u);
public:
	FixedString<25> ParentCountry;
	PROTECTED_PROPERTY(BYTE, align_B1[3]);
	int            ArrayIndex;
	int            ArrayIndex2; //dunno why
	int            SideIndex;
	int            ColorSchemeIndex;
	PROTECTED_PROPERTY(DWORD, align_C4);

	//are these unused TS leftovers?
	double         FirepowerMult;
	double         GroundspeedMult;
	double         AirspeedMult;
	double         ArmorMult;
	double         ROFMult;
	double         CostMult;
	double         BuildtimeMult;
	//---

	float          ArmorInfantryMult;
	float          ArmorUnitsMult;
	float          ArmorAircraftMult;
	float          ArmorBuildingsMult;
	float          ArmorDefensesMult;

	float          CostInfantryMult;
	float          CostUnitsMult;
	float          CostAircraftMult;
	float          CostBuildingsMult;
	float          CostDefensesMult;

	float          SpeedInfantryMult;
	float          SpeedUnitsMult;
	float          SpeedAircraftMult;

	float          BuildtimeInfantryMult;
	float          BuildtimeUnitsMult;
	float          BuildtimeAircraftMult;
	float          BuildtimeBuildingsMult;
	float          BuildtimeDefensesMult;

	float          IncomeMult;

	TypeList<InfantryTypeClass*> VeteranInfantry;
	TypeList<UnitTypeClass*> VeteranUnits;
	TypeList<AircraftTypeClass*> VeteranAircraft;

	char Suffix[4];

	char           Prefix;
	bool           Multiplay;
	bool           MultiplayPassive;
	bool           WallOwner;
	bool           SmartAI; //"smart"?
	PROTECTED_PROPERTY(BYTE, padding_1A9[7]);
public:
	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~HouseTypeClass() JMP_THIS(0x5116A0);

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	//helpers
	HouseTypeClass* FindParentCountry() const {
		return HouseTypeClass::Find(this->ParentCountry);
	}

	int FindParentCountryIndex() const {
		return HouseTypeClass::FindIndexOfName(this->ParentCountry);
	}

	static signed int __fastcall FindIndexOfName(const char *name)
		{ JMP_STD(0x5117D0); }

protected:
	explicit __forceinline HouseTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}
public:
	HouseTypeClass(noinit_t) : HouseTypeClass(fake_noinit_t{}) JMP_THIS(0x511650);
	HouseTypeClass(const char* pId) : HouseTypeClass(fake_noinit_t{}) JMP_THIS(0x5113F0);
};
