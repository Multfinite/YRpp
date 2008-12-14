/*
	[AITriggerTypes]
*/

#ifndef AITRIGTYPE_H
#define AITRIGTYPE_H

#include <YRPP.h>
#include <HouseTypeClass.h>
#include <TeamTypeClass.h>
#include <AbstractTypeClass.h>

//forward declarations
class TechnoTypeClass;
class TeamTypeClass;

struct AITriggerConditionComparator
{
	int ComparatorType;
	int ComparatorOperand;
};

class AITriggerTypeClass : public AbstractTypeClass
{
public:
	//Array
	ABSTRACTTYPE_ARRAY(AITriggerTypeClass);

	//IPersist
	virtual HRESULT _stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT _stdcall Load(IStream* pStm) R0;
	virtual HRESULT _stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~AITriggerTypeClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() R0;
	virtual int Size() R0;

	static bool LoadFromINIList(CCINIClass *pINI)
		{ SET_REG32(ECX, pINI); CALL(0x41F2E0); }

	// Global == saving into AI.ini as opposed to map?
	// if !Global, [AITriggerTypesEnable] gets saved as well
	static bool SaveToINIList(CCINIClass *pINI, bool Global)
		{ SET_REG32(ECX, pINI); SET_REG8(DL, Global); CALL(0x41F490); }

	// non-virtual

	// teams finished script, and 
	void RegisterSuccess()
		{ THISCALL(0x41FD60); }

	void RegisterFailure()
		{ THISCALL(0x41FE20); }

	// the main condition
	bool ConditionMet(HouseClass *CallingHouse, HouseClass *TargetHouse, bool EnoughBaseDefense)
		{ PUSH_VAR8(EnoughBaseDefense); PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41E720); }

	// slaves
	bool OwnerHouseOwns(HouseClass *CallingHouse, HouseClass *TargetHouse)
		{ PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41EAF0); }

	bool CivilianHouseOwns(HouseClass *CallingHouse, HouseClass *TargetHouse)
		{ PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41EC90); }

	bool EnemyHouseOwns(HouseClass *CallingHouse, HouseClass *TargetHouse)
		{ PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41EE90); }

	bool IronCurtainCharged(HouseClass *CallingHouse, HouseClass *TargetHouse)
		{ PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41F0D0); }

	bool ChronoSphereCharged(HouseClass *CallingHouse, HouseClass *TargetHouse)
		{ PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41F180); }

	bool HouseCredits(HouseClass *CallingHouse, HouseClass *TargetHouse)
		{ PUSH_VAR32(TargetHouse); PUSH_VAR32(CallingHouse); THISCALL(0x41F230); }

	void FormatForSaving(char * buffer) {
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

		if(this->OwnerHouseType == th_Single) {
			int HouseIndex = this->HouseIndex;
			if(HouseIndex != -1) {
				HouseName = HouseTypeClass::Array->GetItem(HouseIndex)->get_ID();
			}
		} else if(this->OwnerHouseType == th_Any) {
			HouseName = "<all>";
		}

		TechnoTypeClass *O = this->ConditionObject;
		if(O) {
			ConditionName = O->get_ID();
		}

		char ConditionString[68];
		int idx = 0;
		char * condStr = ConditionString;
		byte *buf = (byte *)&this->Conditions;
		do {
			sprintf(condStr, "%02x", *buf);
			++buf;
			++idx;
			condStr += 2;
		} while(idx < 0x20 );
		*condStr = '\0';

		sprintf(buffer, "%X = %s,%s,%s,%d,%d,%s,%s,%lf,%lf,%lf,%d,%d,%d,%d,%s,%d,%d,%d\n", 
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
			this->IsForSkirmish != 0,
			0,
			this->SideIndex,
			this->IsForBaseDefense != 0,
			Team2Name,
			this->Enabled_Easy != 0,
			this->Enabled_Normal != 0,
			this->Enabled_Hard != 0
		);

	}

	//Constructor
	AITriggerTypeClass(const char* pID) : AbstractTypeClass(false)
		JMP_THIS(0x41E350);

protected:
	AITriggerTypeClass() : AbstractTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

	PROPERTY(eAITrigCondition, ConditionType);
	PROPERTY(int,              IsGlobal);
	PROPERTY(eAITrigHouseType, OwnerHouseType);
	PROPERTY(bool,             IsEnabled);
	PROPERTY(int,              HouseIndex);
	PROPERTY(int,              SideIndex);
	PROPERTY(int,              TechLevel);
	PROPERTY(int,              unknown_B4);
	PROPERTY(double,           Weight_Current);
	PROPERTY(double,           Weight_Minimum);
	PROPERTY(double,           Weight_Maximum);
	PROPERTY(bool,             IsForSkirmish);
	PROPERTY(bool,             IsForBaseDefense);
	PROPERTY(bool,             Enabled_Easy);
	PROPERTY(bool,             Enabled_Normal);
	PROPERTY(bool,             Enabled_Hard);
	PROPERTY(TechnoTypeClass*, ConditionObject);
	PROPERTY(TeamTypeClass*,   Team1);
	PROPERTY(TeamTypeClass*,   Team2);
	PROPERTY_STRUCT_ARRAY(
		AITriggerConditionComparator, Conditions, 4); // don't ask
	PROPERTY(int,              TimesExecuted);
	PROPERTY(int,              TimesCompleted);
	PROPERTY(int,              unknown_10C);

};

#endif