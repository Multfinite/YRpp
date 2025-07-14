#pragma once

#include "AbstractTypeClass.h"
#include "Helpers\String.h"

class AircraftTypeClass;
class InfantryTypeClass;
class UnitTypeClass;

class __declspec(uuid("1DD43928-046B-11D2-ACA4-006008055BB5"))
NOVTABLE HouseTypeClass : public AbstractTypeClass
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
	static constexpr AbstractType AbsID = AbstractType::HouseType;
	static constexpr uintptr_t AbsVTable = 0x7EAB58;
	static constexpr size_t ClassSize = 0x1B0;

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
	virtual ~HouseTypeClass() JMP_THIS(0x5116A0);

	HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override JMP_STD(0x5125A0);
	ULONG __stdcall AddRef() override JMP_STD(0x512740);
	ULONG __stdcall Release() override JMP_STD(0x512750);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x512640);

	HRESULT __stdcall IsDirty() override JMP_STD(0x512280);
	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x512290);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x512480);
	HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) override JMP_STD(0x512570);
	RTTIType KindOf() const override JMP_THIS(0x512710);
	int SizeOf() const override JMP_THIS(0x512720);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x512170);
	int GetArrayIndex() const override JMP_THIS(0x512730);
	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x511850);

	HouseTypeClass* FindParentCountry() const { return HouseTypeClass::Find(this->ParentCountry); }
	int FindParentCountryIndex() const { return HouseTypeClass::FindIndexOfName(this->ParentCountry); }
	static signed int __fastcall FindIndexOfName(const char* name) JMP_STD(0x5117D0);
	static HouseTypeClass* __fastcall FindOrMake(const char* name) JMP_STD(0x512680);

protected:
	explicit __forceinline HouseTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}
public:
	HouseTypeClass(noinit_t) noexcept : HouseTypeClass(fake_noinit_t{}) JMP_THIS(0x511650);
	HouseTypeClass(const char* pId) : HouseTypeClass(fake_noinit_t{}) JMP_THIS(0x5113F0);
};
static_assert(sizeof(HouseTypeClass) == HouseTypeClass::ClassSize);
