#pragma once

#include "YRPP.h"
#include "HouseTypeClass.h"
#include "TeamTypeClass.h"
#include "AbstractTypeClass.h"
#include "TechnoTypeClass.h"

//forward declarations
class TechnoTypeClass;
class TeamTypeClass;

struct AITriggerConditionComparator
{
	int ComparatorType;
	int ComparatorOperand;
};

/*!
* @brief[AITriggerTypes]
*/
class NOVTABLE AITriggerTypeClass : public AbstractTypeClass
{
public:
	using base_type = AbstractTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E2A50;
			this->IRTTITypeInfo = 0x7E2A34;
			this->INoticeSink = 0x7E2A2C;
			this->INoticeSource = 0x7E2A24;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::AITriggerType;
	static constexpr uintptr_t AbsVTable = 0x7E2A50;

	ABSTRACTTYPE_ARRAY(AITriggerTypeClass, 0xA8B200u);
public:
	AITriggerCondition ConditionType;
	int              IsGlobal;
	AITriggerHouseType OwnerHouseType;
	bool             IsEnabled;
	int              HouseIndex;
	int              SideIndex;
	int              TechLevel;
	int              unknown_B4;
	double           Weight_Current;
	double           Weight_Minimum;
	double           Weight_Maximum;
	bool             IsForSkirmish;
	bool             IsForBaseDefense;
	bool             Enabled_Easy;
	bool             Enabled_Normal;
	bool             Enabled_Hard;
	TechnoTypeClass* ConditionObject;
	TeamTypeClass* Team1;
	TeamTypeClass* Team2;
	AITriggerConditionComparator Conditions[4]; // don't ask
	int              TimesExecuted;
	int              TimesCompleted;
	int              unknown_10C;

public:
	virtual ~AITriggerTypeClass() JMP_THIS(0x41E480);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int SizeOf() const R0;

	constexpr static bool LoadFromINIList(CCINIClass *pINI) JMP_STD(0x41F2E0);

	// Global == saving into AI.ini as opposed to map?
	// if !Global, [AITriggerTypesEnable] gets saved as well
	constexpr static bool SaveToINIList(CCINIClass *pINI, bool Global) JMP_STD(0x41F490);

	// non-virtual

	// teams finished script, and
	constexpr void RegisterSuccess() JMP_THIS(0x41FD60);
	constexpr void RegisterFailure() JMP_THIS(0x41FE20);
	
	// the main condition
	constexpr bool ConditionMet(HouseClass *CallingHouse, HouseClass *TargetHouse, bool EnoughBaseDefense) const JMP_THIS(0x41E720);

	// slaves
	constexpr bool OwnerHouseOwns(HouseClass *CallingHouse, HouseClass *TargetHouse) const JMP_THIS(0x41EE90);
	constexpr bool CivilianHouseOwns(HouseClass *CallingHouse, HouseClass *TargetHouse) const JMP_THIS(0x41EC90); 
	constexpr bool EnemyHouseOwns(HouseClass *CallingHouse, HouseClass *TargetHouse) const JMP_THIS(0x41EAF0);
	constexpr bool IronCurtainCharged(HouseClass *CallingHouse, HouseClass *TargetHouse) const JMP_THIS(0x41F0D0);
	constexpr bool ChronoSphereCharged(HouseClass *CallingHouse, HouseClass *TargetHouse) const JMP_THIS(0x41F180); 
	constexpr bool HouseCredits(HouseClass *CallingHouse, HouseClass *TargetHouse) const JMP_THIS(0x41F230);

	constexpr void FormatForSaving(char * buffer, size_t size) const {
		const char *Team1Name = "<none>";
		const char *Team2Name = "<none>";
		const char *HouseName = "<none>";
		const char *ConditionName = "<none>";

		TeamTypeClass *T = this->Team1;
		if(T) {
			Team1Name = T->get_ID();
		}
		T = this->Team2;
		if(T) {
			Team2Name = T->get_ID();
		}

		if(this->OwnerHouseType == AITriggerHouseType::Single) {
			auto const idxHouse = this->HouseIndex;
			if(idxHouse != -1) {
				HouseName = HouseTypeClass::Array->GetItem(idxHouse)->get_ID();
			}
		} else if(this->OwnerHouseType == AITriggerHouseType::Any) {
			HouseName = "<all>";
		}

		TechnoTypeClass *O = this->ConditionObject;
		if(O) {
			ConditionName = O->get_ID();
		}

		char ConditionString[68];
		int idx = 0;
		char * condStr = ConditionString;
		auto buf = reinterpret_cast<const byte*>(&this->Conditions);
		do {
			sprintf_s(condStr, 4, "%02x", *buf);
			++buf;
			++idx;
			condStr += 2;
		} while(idx < 0x20 );
		*condStr = '\0';

		sprintf_s(buffer, size, "%s = %s,%s,%s,%d,%d,%s,%s,%lf,%lf,%lf,%u,%d,%d,%u,%s,%u,%u,%u\n",
			this->ID,
			this->Name,
			Team1Name,
			HouseName,
			this->TechLevel,
			this->ConditionType,
			ConditionName,
			ConditionString,
			this->Weight_Current,
			this->Weight_Minimum,
			this->Weight_Maximum,
			this->IsForSkirmish,
			0,
			this->SideIndex,
			this->IsForBaseDefense,
			Team2Name,
			this->Enabled_Easy,
			this->Enabled_Normal,
			this->Enabled_Hard
		);
	}

protected:
	explicit __forceinline AITriggerTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}
public:
	AITriggerTypeClass(noinit_t) : AITriggerTypeClass(fake_noinit_t{}) { vtables.init(this); };
	AITriggerTypeClass(const char* pId) : AITriggerTypeClass(fake_noinit_t{}) JMP_THIS(0x41E350);
};
