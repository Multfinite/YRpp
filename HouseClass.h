#pragma once

#include "AircraftTypeClass.h"
#include "BuildingClass.h"
#include "HouseTypeClass.h"
#include "InfantryTypeClass.h"
#include "ScenarioClass.h"
#include "SessionClass.h"
#include "SideClass.h"
#include "UnitClass.h"
#include "UnitTypeClass.h"

#include "Helpers/Cast.h"

class AnimClass;
class BulletClass;
class CellClass;
class FactoryClass;
class ObjectClass;
class SuperClass;
class TagClass;
class WaypointPathClass;
class WaypointClass;

class UnitTrackerClass
{
public:
	int UnitTotals[0x200];
	int UnitCount;
	BOOL InNetworkFormat;
public:
	UnitTrackerClass() JMP_THIS(0x748FD0);
	~UnitTrackerClass() = default; // JMP_THIS(0x749010);
	void IncrementUnitCount(int nUnit) JMP_THIS(0x749020);
	void DecrementUnitCount(int nUnit) JMP_THIS(0x749040);
	void PopulateUnitCount(int nCount) JMP_THIS(0x749060);
	int GetUnitCount() JMP_THIS(0x7490A0);
	const int* GetArray() JMP_THIS(0x7490C0);
	void ClearUnitCount() JMP_THIS(0x7490D0);
	void ToNetworkFormat() JMP_THIS(0x749100);
	void ToPCFormat() JMP_THIS(0x749150);
};

struct ZoneInfoStruct
{
	int Aircraft;
	int Armor;
	int Infantry;
};

struct StartingTechnoStruct
{
	TechnoTypeClass *  Unit;
	CellStruct         Cell;
};

// that's how WW calls it, seems to track levels of how much it hates other houses... typical ww style, with bugs
struct AngerStruct
{
	HouseClass * House;
	int          AngerLevel;

	//need to define a == operator so it can be used in array classes
	bool operator == (const AngerStruct& tAnger) const
	{
		return (House == tAnger.House &&
				AngerLevel == tAnger.AngerLevel);
	}
};

struct ScoutStruct
{
	HouseClass * House;
	bool         IsPreferred;

	//need to define a == operator so it can be used in array classes
	bool operator == (const ScoutStruct& tScout) const
	{
		return (House == tScout.House &&
				IsPreferred == tScout.IsPreferred);
	}
};

//--- BaseNodeClass
class BaseNodeClass
{
public:
	//need to define a == operator so it can be used in array classes
	bool operator == (const BaseNodeClass& tBaseNode) const
	{
		return
			(BuildingTypeIndex == tBaseNode.BuildingTypeIndex) &&
			(MapCoords == tBaseNode.MapCoords) &&
			(Placed == tBaseNode.Placed) &&
			(Attempts == tBaseNode.Attempts);
	}

	int        BuildingTypeIndex;
	CellStruct MapCoords;
	bool       Placed;
	int        Attempts;
};

//--- BaseClass - holds information about a player's base!
class HouseClass;	//forward declaration needed

class BaseClass
{
public:
	BaseClass()
		{ JMP_THIS(0x42E6F0); }
	~BaseClass()
	{
		BaseNodes.~DynamicVectorClass();
		Cells_24.~DynamicVectorClass();
		Cells_38.~DynamicVectorClass();
	}

	//VTable
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm) R0;
	virtual void ComputeCRC(CRCEngine& crc) const RX;

	//virtual ~BaseClass() { /*???*/ }; // gcc demands a virtual since virtual funcs exist

	int FailedToPlaceNode(BaseNodeClass *Node) // called after AI fails to place building, obviously
		{ JMP_THIS(0x42F380); }

	//Properties
	DECLARE_PROPERTY(DynamicVectorClass<BaseNodeClass>, BaseNodes);
	int PercentBuilt;
	DECLARE_PROPERTY(DynamicVectorClass<CellStruct>, Cells_24);
	DECLARE_PROPERTY(DynamicVectorClass<CellStruct>, Cells_38);
	CellStruct Center;

	PROTECTED_PROPERTY(BYTE, unknown_54[0x20]);

	HouseClass* Owner;

#pragma warning(suppress : 4265)
};

// used for each of the 3 drop ships. has more functions that are not reproduced here yet
struct DropshipStruct
{
	DropshipStruct() JMP_THIS(0x4B69B0);
	~DropshipStruct() JMP_THIS(0x4B69D0);

	DECLARE_PROPERTY(CDTimerClass, Timer);
	BYTE             unknown_C;
	PROTECTED_PROPERTY(BYTE, align_D[3]);
	int              Count;
	TechnoTypeClass* Types[5];
	int              TotalCost;
};

/*!
* @brief Players
*/
class __declspec(uuid("D9D4A910-87C6-11D1-B707-00A024DDAFD1"))
NOVTABLE HouseClass : public AbstractClass, public IHouse, public IPublicHouse, public IConnectionPointContainer
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		uintptr_t IHouse;
		uintptr_t IPublicHouse;
		uintptr_t IConnectionPointContainer;

		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EA8A0;
			this->IRTTITypeInfo = 0x7EA884;
			this->INoticeSink = 0x7EA87C;
			this->INoticeSource = 0x7EA874;
			this->IHouse = 0x7EA834;
			this->IPublicHouse = 0x7EA80C;
			this->IConnectionPointContainer = 0x7EA7F4;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7EA8A0;
	static constexpr AbstractType AbsID = AbstractType::House;
	static constexpr size_t ClassSize = 0x160B8;

	// <Player @ A> and friends map to these constants
	enum {PlayerAtA = 4475, PlayerAtB, PlayerAtC, PlayerAtD, PlayerAtE, PlayerAtF, PlayerAtG, PlayerAtH};

	static constexpr constant_ptr<DynamicVectorClass<HouseClass*>, 0xA80228u> const Array{};

	// House of player at this computer.
	static constexpr reference<HouseClass*, 0xA83D4Cu> const CurrentPlayer{};
	// House of player that is observer.
	static constexpr reference<HouseClass*, 0xAC1198u> const Observer{};

public:
	int                   ArrayIndex;
	HouseTypeClass* Type;
	DECLARE_PROPERTY(DynamicVectorClass<TagClass*>, RelatedTags);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, ConYards);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, Buildings);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, UnitRepairStations);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, Grinders);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, Absorbers);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, Bunkers);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, Occupiables);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, CloningVats);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, SecretLabs);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, PsychicDetectionBuildings);
	DECLARE_PROPERTY(DynamicVectorClass<BuildingClass*>, FactoryPlants);
	int                   CountResourceGatherers;
	int                   CountResourceDestinations;
	int                   CountWarfactories;
	int                   InfantrySelfHeal;
	int                   UnitsSelfHeal;
	DECLARE_PROPERTY(DynamicVectorClass<StartingTechnoStruct*>, StartingUnits);
	AIDifficulty          AIDifficulty;          // be advised that it's reverse, Hard == 0 and Easy == 2. I'm sure Westwood has a good reason for this. Yep.
	double                FirepowerMultiplier;   // used
	double                GroundspeedMultiplier; // unused ...
	double                AirspeedMultiplier;
	double                ArmorMultiplier;
	double                ROFMultiplier;
	double                CostMultiplier;
	double                BuildTimeMultiplier;   // ... unused ends
	double                RepairDelay;
	double                BuildDelay;
	int                   IQLevel;
	int                   TechLevel;
	IndexBitfield<HouseClass*> AltAllies;        // ask question, receive brain damage
	int                   StartingCredits;       // not sure how these are used // actual credits = this * 100
	Edge                  StartingEdge;
	DWORD                 AIState_1E4;
	int                   SideIndex;
	bool                  IsHumanPlayer;         // Is controlled by a human player.
	bool                  IsInPlayerControl;     // Is controlled by current player.
	bool                  Production;            // AI production has begun.
	bool                  AutocreateAllowed;
	bool                  NodeLogic_1F0;
	bool                  ShipYardConst_1F1;
	bool                  AITriggersActive;
	bool                  AutoBaseBuilding;
	bool                  DiscoveredByPlayer;
	bool                  Defeated;
	bool                  IsGameOver;
	bool                  IsWinner;
	bool                  IsLoser;
	bool                  CiviliansEvacuated;    // used by the CivEvac triggers
	bool                  FirestormActive;
	bool                  HasThreatNode;
	bool                  RecheckTechTree;
	int                   IPAddress;
	int                   TournamentTeamID;
	bool                  LostConnection;
	int                   SelectedPathIndex;
	WaypointPathClass* PlanningPaths[12];    // 12 paths for "planning mode"
	char                  Visionary;             //??? exe says so
	bool                  MapIsClear;
	bool                  IsTiberiumShort;
	bool                  HasBeenSpied;
	bool                  HasBeenThieved;        // Something of this house has been entered by a Thief/VehicleThief
	bool                  Repairing;             // BuildingClass::Repair, handholder for hurr durf AI
	bool                  IsBuiltSomething;
	bool                  IsResigner;
	bool                  IsGiverUpper;
	bool                  AllToHunt;
	bool                  IsParanoid;
	bool                  IsToLook;
	int                   IQLevel2;              // no idea why we got this twice
	AIMode                AIMode;
	DECLARE_PROPERTY(DynamicVectorClass<SuperClass*>, Supers);
	int                   LastBuiltBuildingType;
	int                   LastBuiltInfantryType;
	int                   LastBuiltAircraftType;
	int                   LastBuiltVehicleType;
	int                   AllowWinBlocks;        // some ra1 residue map trigger-fu, should die a painful death
	DECLARE_PROPERTY(CDTimerClass, RepairTimer); // for AI
	DECLARE_PROPERTY(CDTimerClass, AlertTimer);
	DECLARE_PROPERTY(CDTimerClass, BorrowedTime);
	DECLARE_PROPERTY(CDTimerClass, PowerBlackoutTimer);
	DECLARE_PROPERTY(CDTimerClass, RadarBlackoutTimer);
	bool                  Side2TechInfiltrated;  // asswards! whether this player has infiltrated stuff
	bool                  Side1TechInfiltrated;  // which is listed in [AI]->BuildTech
	bool                  Side0TechInfiltrated;  // and has the appropriate AIBasePlanningSide
	bool                  BarracksInfiltrated;
	bool                  WarFactoryInfiltrated;

	// these four are unused horrors
	// checking prerequisites:
	/*
	if(1 << this->Country->IndexInArray & item->RequiredHouses
		|| (item->WhatAmI == abs_InfantryType && (item->RequiredHouses & this->InfantryAltOwner))
		|| (item->WhatAmI == abs_UnitType && (item->RequiredHouses & this->UnitAltOwner))
		|| (item->WhatAmI == abs_AircraftType && (item->RequiredHouses & this->AircraftAltOwner))
		|| (item->WhatAmI == abs_BuildingType && (item->RequiredHouses & this->BuildingAltOwner))
	)
		{ can build }
	*/
	DWORD InfantryAltOwner;
	DWORD UnitAltOwner;
	DWORD AircraftAltOwner;
	DWORD BuildingAltOwner;

	int                   AirportDocks;
	int                   PoweredUnitCenters;
	int                   CreditsSpent;
	int                   HarvestedCredits;
	int                   StolenBuildingsCredits;
	int                   OwnedUnits;
	int                   OwnedNavy;
	int                   OwnedBuildings;
	int                   OwnedInfantry;
	int                   OwnedAircraft;
	DECLARE_PROPERTY(StorageClass, OwnedTiberium);
	int                   Balance;
	int                   TotalStorage; // capacity of all building Storage
	DECLARE_PROPERTY(StorageClass, OwnedWeed);
	DWORD unknown_324;
	DECLARE_PROPERTY(UnitTrackerClass, BuiltAircraftTypes);
	DECLARE_PROPERTY(UnitTrackerClass, BuiltInfantryTypes);
	DECLARE_PROPERTY(UnitTrackerClass, BuiltUnitTypes);
	DECLARE_PROPERTY(UnitTrackerClass, BuiltBuildingTypes);
	DECLARE_PROPERTY(UnitTrackerClass, KilledAircraftTypes);
	DECLARE_PROPERTY(UnitTrackerClass, KilledInfantryTypes);
	DECLARE_PROPERTY(UnitTrackerClass, KilledUnitTypes);
	DECLARE_PROPERTY(UnitTrackerClass, KilledBuildingTypes);
	DECLARE_PROPERTY(UnitTrackerClass, CapturedBuildings);
	DECLARE_PROPERTY(UnitTrackerClass, CollectedCrates); // YES, THIS IS HOW WW WASTES TONS OF RAM
	int                   NumAirpads;
	int                   NumBarracks;
	int                   NumWarFactories;
	int                   NumConYards;
	int                   NumShipyards;
	int                   NumOrePurifiers;
	float                 CostInfantryMult;
	float                 CostUnitsMult;
	float                 CostAircraftMult;
	float                 CostBuildingsMult;
	float                 CostDefensesMult;
	int                   PowerOutput;
	int                   PowerDrain;
	FactoryClass* Primary_ForAircraft;
	FactoryClass* Primary_ForInfantry;
	FactoryClass* Primary_ForVehicles;
	FactoryClass* Primary_ForShips;
	FactoryClass* Primary_ForBuildings;
	FactoryClass* Primary_Unused1;
	FactoryClass* Primary_Unused2;
	FactoryClass* Primary_Unused3;
	FactoryClass* Primary_ForDefenses;
	BYTE                  AircraftType_53D0;
	BYTE                  InfantryType_53D1;
	BYTE                  VehicleType_53D2;
	BYTE                  ShipType_53D3;
	BYTE                  BuildingType_53D4;
	BYTE                  unknown_53D5;
	BYTE                  unknown_53D6;
	BYTE                  unknown_53D7;
	BYTE                  DefenseType_53D8;
	BYTE                  unknown_53D9;
	BYTE                  unknown_53DA;
	BYTE                  unknown_53DB;
	UnitClass* OurFlagCarrier;
	CellStruct            OurFlagCoords;
	//for endgame score screen
	int                   KilledUnitsOfHouses[20];     // 20 Houses only!
	int                   TotalKilledUnits;
	int                   KilledBuildingsOfHouses[20]; // 20 Houses only!
	int                   TotalKilledBuildings;
	int                   WhoLastHurtMe;
	CellStruct            BaseSpawnCell;
	CellStruct            BaseCenter; // set by map action 137 and 138
	int                   Radius;
	DECLARE_PROPERTY_ARRAY(ZoneInfoStruct, ZoneInfos, 5);
	int                   LATime;
	int                   LAEnemy;
	int                   ToCapture;
	//	IndexBitfield<HouseTypeClass *> RadarVisibleTo; // these house types(!?!, fuck you WW) can see my radar
	IndexBitfield<HouseClass*> RadarVisibleTo;  // this crap is being rewritten to use house indices instead of house types
	int                   SiloMoney;
	QuarryType            PreferredTargetType; // Set via map action 35. The preferred object type to attack.
	CellStruct            PreferredTargetCell; // Set via map action 135 and 136. Used to override firing location of targettable SWs.
	CellStruct            PreferredDefensiveCell; // Set via map action 140 and 141, or when an AIDefendAgainst SW is launched.
	CellStruct            PreferredDefensiveCell2; // No known function sets this to a real value, but it would take precedence over the other.
	int                   PreferredDefensiveCellStartTime; // The frame the PreferredDefensiveCell was set. Used to fire the Force Shield.

	// Used for: Counting objects ever owned
	// altered on each object's loss or gain
	// BuildLimit > 0 validation uses this
	DECLARE_PROPERTY(CounterClass, OwnedBuildingTypes);
	DECLARE_PROPERTY(CounterClass, OwnedUnitTypes);
	DECLARE_PROPERTY(CounterClass, OwnedInfantryTypes);
	DECLARE_PROPERTY(CounterClass, OwnedAircraftTypes);

	// Used for: Counting objects currently owned and on the map
	// altered on each object's loss or gain
	// AITriggerType condition uses this
	// original PrereqOverride check uses this
	// original Prerequisite check uses this
	// AuxBuilding check uses this
	DECLARE_PROPERTY(CounterClass, ActiveBuildingTypes);
	DECLARE_PROPERTY(CounterClass, ActiveUnitTypes);
	DECLARE_PROPERTY(CounterClass, ActiveInfantryTypes);
	DECLARE_PROPERTY(CounterClass, ActiveAircraftTypes);

	// Used for: Counting objects produced from Factory
	// not altered when things get taken over or removed
	// BuildLimit < 0 validation uses this
	DECLARE_PROPERTY(CounterClass, FactoryProducedBuildingTypes);
	DECLARE_PROPERTY(CounterClass, FactoryProducedUnitTypes);
	DECLARE_PROPERTY(CounterClass, FactoryProducedInfantryTypes);
	DECLARE_PROPERTY(CounterClass, FactoryProducedAircraftTypes);

	DECLARE_PROPERTY(CDTimerClass, AttackTimer);
	int                   InitialAttackDelay; // both unused
	int                   EnemyHouseIndex;
	DECLARE_PROPERTY(DynamicVectorClass<AngerStruct>, AngerNodes); //arghghghgh bugged
	DECLARE_PROPERTY(DynamicVectorClass<ScoutStruct>, ScoutNodes); // filled with data which is never used, jood gob WW
	DECLARE_PROPERTY(CDTimerClass, AITimer);
	DECLARE_PROPERTY(CDTimerClass, Unknown_Timer_5640);
	int                   ProducingBuildingTypeIndex;
	int                   ProducingUnitTypeIndex;
	int                   ProducingInfantryTypeIndex;
	int                   ProducingAircraftTypeIndex;
	int                   RatioAITriggerTeam;
	int                   RatioTeamAircraft;
	int                   RatioTeamInfantry;
	int                   RatioTeamBuildings;
	int                   BaseDefenseTeamCount;
	DECLARE_PROPERTY_ARRAY(DropshipStruct, DropshipData, 3);
	int                   CurrentDropshipIndex;
	byte                  HasCloakingRanges; // don't ask
	ColorStruct           Color;
	ColorStruct           LaserColor; // my idb says so
	BaseClass             Base;
	bool                  RecheckPower;
	bool                  RecheckRadar;
	bool                  SpySatActive;
	bool                  IsBeingDrained;
	Edge                  Edge;
	CellStruct            EMPTarget;
	CellStruct            NukeTarget;
	IndexBitfield<HouseClass*> Allies; // flags, one bit per HouseClass instance
	//                                 //-> 32 players possible here
	DECLARE_PROPERTY(CDTimerClass, DamageDelayTimer);
	DECLARE_PROPERTY(CDTimerClass, TeamDelayTimer); // for AI attacks
	DECLARE_PROPERTY(CDTimerClass, TriggerDelayTimer);
	DECLARE_PROPERTY(CDTimerClass, SpeakAttackDelayTimer);
	DECLARE_PROPERTY(CDTimerClass, SpeakPowerDelayTimer);
	DECLARE_PROPERTY(CDTimerClass, SpeakMoneyDelayTimer);
	DECLARE_PROPERTY(CDTimerClass, SpeakMaxedDelayTimer);
	IAIHouse* AIGeneral;

	unsigned int          ThreatPosedEstimates[130][130]; // BLARGH

	char                  PlainName[21];    // this defaults to the owner country's name in SP or <human player><computer player> in MP. Used as owner for preplaced map objects
	char                  UINameString[33]; // this contains the UIName= text from the INI! or
	wchar_t               UIName[21];      // this contains the CSF string from UIName= above, or a copy of the country's UIName if not defined. Take note that this is shorter than the country's UIName can be...
	int                   ColorSchemeIndex;
	union
	{
		int               StartingPoint;
		CellStruct        StartingCell;     // Could it really be a CellStruct ? - Saved for backwards compatibility
	};
	IndexBitfield<HouseClass*> StartingAllies;
	DWORD                 unknown_16060;
	DECLARE_PROPERTY(DynamicVectorClass<IConnectionPoint*>, WaypointPath);
	DWORD unknown_1607C;
	DWORD unknown_16080;
	DWORD unknown_16084;
	double unused_16088;
	double unused_16090;
	DWORD padding_16098;
	float PredictionEnemyArmor; // defaults to 0.33, AIForcePredictionFudge'd later
	float PredictionEnemyAir;
	float PredictionEnemyInfantry;
	int TotalOwnedInfantryCost;
	int TotalOwnedVehicleCost;
	int TotalOwnedAircraftCost;
	int PowerSurplus;

public:
	virtual ~HouseClass() JMP_THIS(0x4F7140);
	
	HRESULT STDMETHODCALLTYPE EnumConnectionPoints(__RPC__deref_out_opt IEnumConnectionPoints** ppEnum) override JMP_STD(0x5024F0);
	HRESULT STDMETHODCALLTYPE FindConnectionPoint(__RPC__in REFIID riid, __RPC__deref_out_opt IConnectionPoint** ppCP) override JMP_STD(0x502550);

	long __stdcall Apparent_Category_Quantity(Category category) const override JMP_STD(0x4F6A80);
	long __stdcall Apparent_Category_Power(Category category) const override JMP_STD(0x4F6B50);
	CellStruct __stdcall Apparent_Base_Center() const override JMP_STD(0x4F6D10);
	bool __stdcall Is_Powered() const override JMP_STD(0x4F6910);

	long __stdcall ID_Number() const override JMP_STD(0x4F6E60);
	BSTR __stdcall Name() const override JMP_STD(0x4F6950);
	IApplication* __stdcall Get_Application() override JMP_STD(0x4F6930);
	long __stdcall Available_Money() const override JMP_STD(0x4F6990);
	long __stdcall Available_Storage() const override JMP_STD(0x4F69D0);
	long __stdcall Power_Output() const override JMP_STD(0x4F6A00);
	long __stdcall Power_Drain() const override JMP_STD(0x4F6A10);
	long __stdcall Category_Quantity(Category category) const override JMP_STD(0x4F6A20);
	long __stdcall Category_Power(Category category) const override JMP_STD(0x4F6AE0);
	CellStruct __stdcall Base_Center() const override JMP_STD(0x4F6BC0);
	HRESULT __stdcall Fire_Sale() const override JMP_STD(0x5013A0);
	HRESULT __stdcall All_To_Hunt() override JMP_STD(0x501400);
	
	HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x5046F0);
	
	HRESULT Load(IStream* pStm) override JMP_STD(0x503040);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x504080);
	
	void InvalidatePointer(AbstractClass* target, bool all = true) override JMP_THIS(0x4FB9B0);
	RTTIType KindOf() const override JMP_THIS(0x50E360);
	int SizeOf() const override JMP_THIS(0x504730);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x502D60);
	int ArrayIndex() const override JMP_THIS(0x50E370);
	void AI() override JMP_THIS(0x4F8440);

public:

	bool IsAlliedWith(int idxHouse) const
		//{ JMP_THIS(0x4F9A10); }
	{
		if (idxHouse == this->ArrayIndex) return true;
		if (idxHouse == -1)return false;
		return this->Allies.Contains(idxHouse);
	}

	bool IsAlliedWith(HouseClass const* pHouse) const
		//{ JMP_THIS(0x4F9A50); }
	{
		if (!this || !pHouse || pHouse->ArrayIndex == -1) return false;
		if (this == pHouse || this->ArrayIndex == pHouse->ArrayIndex) return true;

		return this->Allies.Contains(pHouse->ArrayIndex);
	}

	bool IsAlliedWith(ObjectClass const* pObject) const
		//	{ JMP_THIS(0x4F9A90); }
	{
		return pObject && this->IsAlliedWith(pObject->OwningHouse());
	}

	bool IsAlliedWith(AbstractClass const* pAbstract) const
		//	{ JMP_THIS(0x4F9AF0); }
	{
		return this->IsAlliedWith(generic_cast<ObjectClass const*>(pAbstract));
	}

	void MakeAlly(int iHouse, bool bAnnounce)
		{ JMP_THIS(0x4F9B50); }
	void MakeAlly(HouseClass* pWho, bool bAnnounce)
		{ JMP_THIS(0x4F9B70); }
	void MakeEnemy(HouseClass* pWho, bool bAnnounce)
		{ JMP_THIS(0x4F9F90); }

	void AdjustThreats()
		{ JMP_THIS(0x509400); }
	void UpdateAngerNodes(int nScoreAdd, HouseClass* pHouse)
		{ JMP_THIS(0x504790); }


	void AllyAIHouses()
		{ JMP_THIS(0x501640); }

	// no explosions, just poooof
	void SDDTORAllAndTriggers()
		{ JMP_THIS(0x4FB920); }

	void AcceptDefeat()
		{ JMP_THIS(0x4FC0B0); }

	// every matching object takes damage and explodes
	void DestroyAll()
		{ JMP_THIS(0x4FC6D0); }
	void DestroyAllBuildings()
		{ JMP_THIS(0x4FC790); }
	void DestroyAllNonBuildingsNonNaval()
		{ JMP_THIS(0x4FC820); }
	void DestroyAllNonBuildingsNaval()
		{ JMP_THIS(0x4FC8D0); }

	void RespawnStartingBuildings()
		{ JMP_THIS(0x50D320); }
	void RespawnStartingForces()
		{ JMP_THIS(0x50D440); }

	BYTE Win(bool bSavourSomething)
		{ JMP_THIS(0x4FC9E0); }
	BYTE Lose(bool bSavourSomething)
		{ JMP_THIS(0x4FCBD0); }

	void RegisterJustBuilt(TechnoClass* pTechno)
		{ JMP_THIS(0x4FB6B0); }

	bool CanAlly(HouseClass* pOther) const
		{ JMP_THIS(0x501540); }

	bool CanOverpower(TechnoClass *pTarget) const
		{ JMP_THIS(0x4F9AF0); }

	// warning: logic pretty much broken
	void LostPoweredCenter(TechnoTypeClass *pTechnoType)
		{ JMP_THIS(0x50E0E0); }
	void GainedPoweredCenter(TechnoTypeClass *pTechnoType)
		{ JMP_THIS(0x50E1B0); }

	bool DoInfantrySelfHeal() const
		{ return this->InfantrySelfHeal > 0; }
	int GetInfSelfHealStep() const
		{ JMP_THIS(0x50D9E0); }

	bool DoUnitsSelfHeal() const
		{ return this->UnitsSelfHeal > 0; }
	int GetUnitSelfHealStep() const
		{ JMP_THIS(0x50D9F0); }

	void UpdatePower()
		{ JMP_THIS(0x508C30); }
	void CreatePowerOutage(int duration)
		{ JMP_THIS(0x50BC90); }
	double GetPowerPercentage() const
		{ JMP_THIS(0x4FCE30); }

	bool HasFullPower() const {
		return this->PowerOutput >= this->PowerDrain || !this->PowerDrain;
	}

	bool HasLowPower() const {
		return this->PowerOutput < this->PowerDrain && this->PowerDrain;
	}

	void CreateRadarOutage(int duration)
		{ JMP_THIS(0x50BCD0); }

	// won't work if has spysat
	void ReshroudMap()
		{ JMP_THIS(0x50BD10); }

	void Cheer()
		{ JMP_THIS(0x50C8C0); }

	void BuildingUnderAttack(BuildingClass *pBld)
		{ JMP_THIS(0x4F93E0); }

	void TakeMoney(int amount)
		{ JMP_THIS(0x4F9790); }
	void GiveMoney(int amount)
		{ JMP_THIS(0x4F9950); }

	inline bool CanTransactMoney(int amount) const {
		return amount > 0 || this->Available_Money() >= -amount;
	}

	inline void TransactMoney(int amount) {
		if(amount > 0) {
			this->GiveMoney(amount);
		} else {
			this->TakeMoney(-amount);
		}
	}

	void GiveTiberium(float amount, int type)
		{ JMP_THIS(0x4F9610); }
	void UpdateAllSilos(int prevStorage, int prevTotalStorage)
		{ JMP_THIS(0x4F9970); }
	double GetStoragePercentage()
		{ JMP_THIS(0x4F6E70); }

	// no LostThreatNode() , this gets called also when node building dies! BUG
	void AcquiredThreatNode()
		{ JMP_THIS(0x509130); }

	// these are for mostly for map actions - HouseClass* foo = IsMP() ? Find_YesMP() : Find_NoMP();
	static bool __fastcall Index_IsMP(int idx)
	{
		// JMP_STD(0x510F60);
		return idx >= PlayerAtA && idx <= PlayerAtH;
	}
	static HouseClass * __fastcall FindByCountryIndex(int HouseType) // find first house of this houseType
		{ JMP_STD(0x502D30); }
	static HouseClass * __fastcall FindByIndex(int idxHouse) // find house at given index
		{ JMP_STD(0x510ED0); }                    // 0..15 map to ScenarioClass::HouseIndices, also supports PlayerAtA and up
	static signed int __fastcall FindIndexByName(const char *name)
		{ JMP_STD(0x50C170); }

	static int __fastcall GetPlayerAtFromString(const char* name)
		{ JMP_STD(0x510FB0); }
	static HouseClass* __fastcall FindByPlayerAt(int at)
		{ JMP_STD(0x510ED0); }

	// gets the first house of a type with this name
	static HouseClass* FindByCountryName(const char* name) {
		auto idx = HouseTypeClass::FindIndexOfName(name);
		return FindByCountryIndex(idx);
	}

	// gets the first house of a type with name Neutral
	static HouseClass* FindNeutral() {
		return FindByCountryName(GameStrings::Neutral);
	}

	// gets the first house of a type with name Special
	static HouseClass* FindSpecial() {
		return FindByCountryName(GameStrings::Special);
	}

	// gets the first house of a side with this name
	static HouseClass* FindBySideIndex(int index) {
		for(auto pHouse : *Array) {
			if(pHouse->Type->SideIndex == index) {
				return pHouse;
			}
		}
		return nullptr;
	}

	// gets the first house of a type with this name
	static HouseClass* FindBySideName(const char* name) {
		auto idx = SideClass::FindIndex(name);
		return FindBySideIndex(idx);
	}

	// gets the first house of a type from the Civilian side
	static HouseClass* FindCivilianSide() {
		return FindBySideName(GameStrings::Civilian);
	}

	static void __fastcall LoadFromINIList(CCINIClass *pINI)
		{ JMP_STD(0x5009B0); }

	int GetSpawnPosition() {
		ScenarioClass* pScenario = ScenarioClass::Instance;
		for (int i = 0; i < 8; i++)
		{
			if (HouseClass::Array->GetItemOrDefault(pScenario->HouseIndices[i], nullptr) == this)
				return i;
		}
		return -1;
	}

	WaypointClass * GetPlanningWaypointAt(CellStruct *coords)
		{ JMP_THIS(0x5023B0); }
	bool GetPlanningWaypointProperties(WaypointClass *wpt, int &idxPath, BYTE &idxWP)
		{ JMP_THIS(0x502460); }

	// calls WaypointPathClass::WaypointPathClass() if needed
	void EnsurePlanningPathExists(int idx)
		{ JMP_THIS(0x504740); }

	// call after the availability of a factory has changed.
	void Update_FactoriesQueues(AbstractType factoryOf, bool isNaval, BuildCat buildCat) const
		{ JMP_THIS(0x509140); }

	// returns the factory owned by this house, having pItem in production right now, not queued
	FactoryClass* GetFactoryProducing(TechnoTypeClass const* pItem) const
		{ JMP_THIS(0x4F83C0); }

	// finds a buildingtype from the given array that this house can build
	// this checks whether the Owner=, Required/ForbiddenHouses= , AIBasePlanningSide= match and if SuperWeapon= (not SW2=) is not forbidden
	BuildingTypeClass* FirstBuildableFromArray(DynamicVectorClass<BuildingTypeClass*> const& items)
		{ JMP_THIS(0x5051E0); }

	// are all prereqs for Techno listed in vectorBuildings[0..vectorLength]. Yes, the length is needed (the vector is used for breadth-first search)
	bool AllPrerequisitesAvailable(TechnoTypeClass const* pItem, DynamicVectorClass<BuildingTypeClass*> const& vectorBuildings, int vectorLength)
		{ JMP_THIS(0x505360); }

	// Whether any human player controls this house.
	bool IsControlledByHuman() const { // { JMP_THIS(0x50B730); }
		bool result = this->IsHumanPlayer;
		if(SessionClass::Instance->GameMode == GameMode::Campaign) {
			result = result || this->IsInPlayerControl;
		}
		return result;
	}

	// Whether the human player on this computer can control this house.
	bool IsControlledByCurrentPlayer() const { // { JMP_THIS(0x50B6F0); }
		if(SessionClass::Instance->GameMode != GameMode::Campaign) {
			return this->IsCurrentPlayer();
		}
		return this->IsHumanPlayer || this->IsInPlayerControl;
	}

	// Target ought to be Object, I imagine, but cell doesn't work then
	void __fastcall SendSpyPlanes(int AircraftTypeIdx, int AircraftAmount, Mission SetMission, AbstractClass *Target, ObjectClass *Destination)
		{ JMP_STD(0x65EAB0); }

	// registering in prereq counters (all technoes get logged, but only buildings get checked on validation... wtf)
	void RegisterGain(TechnoClass* pTechno, bool ownerChange)
		{ JMP_THIS(0x502A80); }

	void RegisterLoss(TechnoClass* pTechno, bool keepTiberium)
		{ JMP_THIS(0x5025F0); }

	BuildingClass* FindBuildingOfType(int idx, int sector = -1) const
		{ JMP_THIS(0x4FD060); }

	AnimClass * __fastcall PsiWarn(CellClass *pTarget, BulletClass *Bullet, char *AnimName)
		JMP_THIS(0x43B5E0);

	bool Fire_LightningStorm(SuperClass* pSuper)
		{ JMP_THIS(0x509E00); }

	bool Fire_ParaDrop(SuperClass* pSuper)
		{ JMP_THIS(0x509CD0); }

	bool Fire_PsyDom(SuperClass* pSuper)
		{ JMP_THIS(0x50A150); }

	bool Fire_GenMutator(SuperClass* pSuper)
		{ JMP_THIS(0x509F60); }

	bool IonSensitivesShouldBeOffline() const
		{ JMP_THIS(0x53A130); }

	const char *get_ID() const {
		return this->Type->get_ID();
	}

	int FindSuperWeaponIndex(SuperWeaponType type) const;

	SuperClass* FindSuperWeapon(SuperWeaponType type) const;

	// I don't want to talk about these
	// read the code <_<

	//  Count owned now
	int CountOwnedNow(TechnoTypeClass const* pItem) const;

	int CountOwnedNow(BuildingTypeClass const* const pItem) const {
		return this->OwnedBuildingTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedNow(AircraftTypeClass const* const pItem) const {
		return this->OwnedAircraftTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedNow(InfantryTypeClass const* const pItem) const {
		return this->OwnedInfantryTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedNow(UnitTypeClass const* const pItem) const {
		return this->OwnedUnitTypes.GetItemCount(pItem->ArrayIndex);
	}

	// Count owned and present
	int CountOwnedAndPresent(TechnoTypeClass const* pItem) const;

	int CountOwnedAndPresent(BuildingTypeClass const* const pItem) const {
		return this->ActiveBuildingTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedAndPresent(AircraftTypeClass const* const pItem) const {
		return this->ActiveAircraftTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedAndPresent(InfantryTypeClass const* const pItem) const {
		return this->ActiveInfantryTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedAndPresent(UnitTypeClass const* const pItem) const {
		return this->ActiveUnitTypes.GetItemCount(pItem->ArrayIndex);
	}

	// Count owned ever
	int CountOwnedEver(TechnoTypeClass const* pItem) const;

	int CountOwnedEver(BuildingTypeClass const* const pItem) const {
		return this->FactoryProducedBuildingTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedEver(AircraftTypeClass const* const pItem) const {
		return this->FactoryProducedAircraftTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedEver(InfantryTypeClass const* const pItem) const {
		return this->FactoryProducedInfantryTypes.GetItemCount(pItem->ArrayIndex);
	}

	int CountOwnedEver(UnitTypeClass const* const pItem) const {
		return this->FactoryProducedUnitTypes.GetItemCount(pItem->ArrayIndex);
	}


	bool HasFromSecretLab(const TechnoTypeClass* const pItem) const {
		for(const auto& pLab : this->SecretLabs) {
			if(pLab->GetSecretProduction() == pItem) {
				return true;
			}
		}
		return false;
	}

	bool HasAllStolenTech(const TechnoTypeClass* const pItem) const {
		if(pItem->RequiresStolenAlliedTech && !this->Side0TechInfiltrated) { return false; }
		if(pItem->RequiresStolenSovietTech && !this->Side1TechInfiltrated) { return false; }
		if(pItem->RequiresStolenThirdTech && !this->Side2TechInfiltrated) { return false; }
		return true;
	}

	bool HasFactoryForObject(const TechnoTypeClass* const pItem) const {
		auto const abs = pItem->KindOf();
		auto const naval = pItem->Naval;
		for(auto const& pBld : this->Buildings) {
			auto pType = pBld->Type;
			if(pType->Factory == abs && pType->Naval == naval) {
				return true;
			}
		}
		return false;
	}

	bool CanExpectToBuild(const TechnoTypeClass* pItem) const;

	bool CanExpectToBuild(const TechnoTypeClass* pItem, int idxParent) const;

	bool InOwners(const TechnoTypeClass* const pItem) const {
		auto const idxParentCountry = this->Type->FindParentCountryIndex();
		return pItem->InOwners(1u << idxParentCountry);
	}

	bool InRequiredHouses(const TechnoTypeClass* const pItem) const {
		return pItem->InRequiredHouses(1u << this->Type->ArrayIndex2);
	}

	bool InForbiddenHouses(const TechnoTypeClass* const pItem) const {
		return pItem->InForbiddenHouses(1u << this->Type->ArrayIndex2);
	}

	CanBuildResult CanBuild(TechnoTypeClass const* pItem, bool buildLimitOnly, bool allowIfInProduction) const
		{ JMP_THIS(0x4F7870); }

	int AI_BaseConstructionUpdate()
		{ JMP_THIS(0x4FE3E0); }

	int AI_VehicleConstructionUpdate()
		{ JMP_THIS(0x4FEA60); }

	void AI_TryFireSW()
		{ JMP_THIS(0x5098F0); }

	bool Fire_SW(int idx, const CellStruct &coords)
		{ JMP_THIS(0x4FAE50); }

	CellStruct* PickTargetByType(CellStruct &outBuffer, QuarryType targetType) const
		{ JMP_THIS(0x50D170); }

	CellStruct PickTargetByType(QuarryType targetType) const {
		CellStruct outBuffer;
		this->PickTargetByType(outBuffer, targetType);
		return outBuffer;
	}

	CellStruct* PickIonCannonTarget(CellStruct &outBuffer) const
		{ JMP_THIS(0x50CBF0); }

	CellStruct PickIonCannonTarget() const {
		CellStruct outBuffer;
		this->PickIonCannonTarget(outBuffer);
		return outBuffer;
	}

	bool IsIonCannonEligibleTarget(const TechnoClass* pTechno) const;

	void UpdateFlagCoords(UnitClass *NewCarrier, DWORD dwUnk)
		{ JMP_THIS(0x4FBE40); }

	void DroppedFlag(CellStruct *Where, UnitClass *Who)
		{ JMP_THIS(0x4FBF60); }

	char PickedUpFlag(UnitClass *Who, DWORD dwUnk)
		{ JMP_THIS(0x4FC060); }

	FactoryClass* GetPrimaryFactory(AbstractType absID, bool naval, BuildCat buildCat) const
		{ JMP_THIS(0x500510); }

	void SetPrimaryFactory(FactoryClass* pFactory, AbstractType absID, bool naval, BuildCat buildCat)
		{ JMP_THIS(0x500850); }

	const CellStruct& GetBaseCenter() const {
		if(this->BaseCenter != CellStruct::Empty) {
			return this->BaseCenter;
		} else {
			return this->BaseSpawnCell;
		}
	}

	unsigned int GetAIDifficultyIndex() const {
		return static_cast<unsigned int>(this->AIDifficulty);
	}

	/*!
		At the moment, this function is really just a more intuitively named mask for
		this->Type->MultiplayPassive, but it might be expanded into something more
		complicated later.

		Primarily used to check if something is owned by the neutral house.
		\return true if house is passive in multiplayer, false if not.
		\author Renegade
		\date 01.03.10
	*/
	bool IsNeutral() const {
		return this->Type->MultiplayPassive;
	}

	// Whether this house is equal to CurrentPlayer
	bool IsCurrentPlayer() const {
		return this == CurrentPlayer;
	}

	// Whether this house is equal to Observer
	bool IsObserver() const {
		return this == Observer;
	}

	// Whether CurrentPlayer is equal to Observer
	static bool IsCurrentPlayerObserver() {
		return CurrentPlayer && CurrentPlayer->IsObserver();
	}

	int CalculateCostMultipliers()
		{ JMP_THIS(0x50BF60); }

	void ForceEnd()
		{ JMP_THIS(0x4FCDC0); }

	void RemoveTracking(TechnoClass* pTechno)
		{ JMP_THIS(0x4FF550); }

	void AddTracking(TechnoClass* pTechno)
		{ JMP_THIS(0x4FF700); }

	double GetWeedStoragePercentage()
		{ JMP_THIS(0x4F9750); }

	bool AISupers()
		{ JMP_THIS(0x50B1D0); }

/*
	ProdFailType Abandon_Production(int32_t rtti, int32_t heapid, bool naval, bool abandon_all) JMP_THIS(0x4FAA10);
	void Activate_Powered_Units1(TechnoTypeClass*) JMP_THIS(0x50E010);
	void Activate_Powered_Units2(TechnoTypeClass*) JMP_THIS(0x50E1C0);
	void Active_Add(BuildingClass* a2) JMP_THIS(0x4FFA50);
	void Active_Remove(BuildingClass* a2) JMP_THIS(0x4FF980);
	void Adjust_Threat(int32_t region, int32_t risk) JMP_THIS(0x4FA2E0);
	void Adjust_Threats() JMP_THIS(0x509400);
	int32_t AI_Aircraft() JMP_THIS(0x4FF210);
	UrgencyType AI_Build_Income() JMP_THIS(0x4FD9A0);
	int32_t AI_Building() JMP_THIS(0x4FE3E0);
	bool AI_Fire_Sale(UrgencyType urgency) JMP_THIS(0x4FDCE0);
	uint64_t AI_Infantry() JMP_THIS(0x4FEEE0);
	bool AI_Raise_Money(UrgencyType urgency) JMP_THIS(0x4FDD10);
	bool AI_Supers() JMP_THIS(0x50B1D0);
	int8_t AI_Takeover() JMP_THIS(0x50A5C0);
	int32_t AI_Unit() JMP_THIS(0x4FEA60);
	int32_t allocate_planning_paths() JMP_THIS(0x5090A0);
	HouseClass* As_Pointer() JMP_THIS(0x502D30);
	int32_t Assign_Handicap(int32_t a2) JMP_THIS(0x4F6EC0);
	void Attacked(BuildingClass* source) JMP_THIS(0x4F93E0);
	void AUTO_BASE_BUILDING_50C210() JMP_THIS(0x50C210);
	Coordinate* Base_Center(Coordinate* a2) JMP_THIS(0x50DF30);
	int8_t Base_Spacer(BuildingTypeClass* buildtype, Cell* cell) JMP_THIS(0x50B760);
	ProdFailType Begin_Production(RTTIType rtti, int32_t id, bool naval, bool forcemaybe) JMP_THIS(0x4FA350);
	void Blackout_Radar(int32_t duration) JMP_THIS(0x50BCD0);
	void Blowup_All() JMP_THIS(0x4FC6D0);
	int8_t Blowup_Buildings() JMP_THIS(0x4FC790);
	int8_t Blowup_Land_Units() JMP_THIS(0x4FC820);
	int8_t Blowup_Naval_Units() JMP_THIS(0x4FC8D0);
	char** Build_Node_AI() JMP_THIS(0x5082C0);
	int32_t Calc_Cost_Mult() JMP_THIS(0x50BF60);
	void Calc_Predictions() JMP_THIS(0x508150);
	int32_t Can_Build(BuildingTypeClass* type, int8_t more_checks, int8_t even_more_checks) JMP_THIS(0x4F7870);
	int32_t Check_Fire_Sale() JMP_THIS(0x4FD940);
	void Clear_Defensive_Target_Cell() JMP_THIS(0x50DA50);
	void Clear_Prefered_Target_Cell() JMP_THIS(0x50DA10);
	void Clobber_All() JMP_THIS(0x4FB920);
	void Computer_Paranoid() JMP_THIS(0x501640);
	void Deactivate_Powered_Units1(TechnoTypeClass*) JMP_THIS(0x50E0E0);
	void Deactivate_Powered_Units2(TechnoTypeClass*) JMP_THIS(0x50E280);
	int8_t Does_Enemy_Building_Exist(int32_t building) JMP_THIS(0x4FBD00);
	int32_t edgestuff_50DB00(BuildingClass* bld) JMP_THIS(0x50DB00);
	uint64_t Expert_AI() JMP_THIS(0x4FD500);
	int32_t Factory_Count(int32_t rtti, int8_t ship) JMP_THIS(0x500910);
	int32_t* Factory_Counter(int32_t rtti, bool naval) JMP_THIS(0x4FF8F0);
	FactoryClass* Fetch_Factory(int32_t rtti, int8_t naval, int32_t defensebuilding) JMP_THIS(0x500510);
	int32_t Find_Best_Storage_Building() JMP_THIS(0x4F9670);
	int32_t Find_Build_Location(int32_t a2) JMP_THIS(0x4FD120);
	Cell* Find_Build_Location(Cell* cell, BuildingTypeClass* buildtype, _DWORD(*)(int, int)* somefunc, int32_t a5) JMP_THIS(0x5060B0);
	BuildingClass* Find_Building(int32_t building, ZoneType zone) JMP_THIS(0x4FD060);
	int32_t Find_Juicy_Target(Coordinate* coord) JMP_THIS(0x500300);
	bool Flag_Attach(Cell* cell, int32_t newloc) JMP_THIS(0x4FBF60);
	bool Flag_Attach(UnitClass* a2, int32_t a3) JMP_THIS(0x4FC060);
	bool Flag_Remove(UnitClass* unit, int32_t newloc) JMP_THIS(0x4FBE40);
	void Flag_To_Chear() JMP_THIS(0x50C8C0);
	int8_t Force_End() JMP_THIS(0x4FCDC0);
	void* Get_Base_Center(uint32_t* a2) JMP_THIS(0x50DEF0);
	DynamicVectorClass Get_Buildable_AntiAir(DynamicVectorClass* ownedNonDefenseBuildings) JMP_THIS(0x507B80);
	int32_t Get_Buildable_AntiArmor(DynamicVectorClass* arg0, int32_t a2) JMP_THIS(0x507D70);
	int32_t Get_Buildable_AntiInf(DynamicVectorClass* arg0, TechnoTypeClass* a2) JMP_THIS(0x507F60);
	double Get_BuildTimeMult(BuildingTypeClass* a2) JMP_THIS(0x50C0A0);
	double Get_CostMult(BuildingTypeClass* a2) JMP_THIS(0x50BEB0);
	int8_t* Get_Factory(int32_t a2) JMP_THIS(0x4F83C0);
	UnitTypeClass* Get_First_Ownable(TypeList* typelist) JMP_THIS(0x505310);
	double Get_IncomeMult() JMP_THIS(0x50C160);
	double Get_SpeedMult(BuildingTypeClass* a2) JMP_THIS(0x50C050);
	double Get_Type_Armor_Mult(BuildingTypeClass* a2) JMP_THIS(0x50BD30);
	double Get_Type_CostMult(BuildingTypeClass* a2) JMP_THIS(0x50BDF0);
	float Harvested_Ore(float number) JMP_THIS(0x4F9610);
	void Harvested_Weeds(int32_t a2, int32_t a3) JMP_THIS(0x4F9700);
	int32_t Has_Powered_Unit_Centers(int32_t) JMP_THIS(0x50E1B0);
	bool Infantry_Self_Heal() JMP_THIS(0x50D9C0);
	int32_t Infantry_SelfHealAmount() JMP_THIS(0x50D9E0);
	void Init_Data(int32_t color, int32_t a3, int32_t credits) JMP_THIS(0x4FCE00);
	void init_laser_color() JMP_THIS(0x50BA00);
	void Init_PlanningPaths(int32_t a2) JMP_THIS(0x504740);
	bool Is_Allowed_To_Ally(HouseClass* a2) JMP_THIS(0x501540);
	bool Is_Ally(int32_t a2) JMP_THIS(0x4F9A10);
	bool Is_Ally(TechnoClass* a2) JMP_THIS(0x4F9A90);
	bool Is_Ally(HouseClass* a2) JMP_THIS(0x4F9A50);
	bool Is_Player_Control() JMP_THIS(0x50B730);
	bool Is_Target_Ally(TechnoClass*) JMP_THIS(0x4F9AF0);
	void Make_Ally(int8_t a3, int32_t a3a) JMP_THIS(0x4F9B50);
	void Make_Ally(HouseClass*, int8_t) JMP_THIS(0x4F9B70);
	void Make_Enemy(HouseClass* house, bool dont_speak) JMP_THIS(0x4F9F90);
	void Make_Enemy(int32_t, bool) JMP_THIS(0x4F9F70);
	bool Manual_Place(BuildingClass* builder, BuildingClass* object) JMP_THIS(0x4FB840);
	void mindcontrolbuildings(HouseClass* a2) JMP_THIS(0x50D290);
	char** mindcontrolbuildings_0(int32_t a2) JMP_THIS(0x50D2D0);
	void One_Time() JMP_THIS(0x4F6EB0);
	Cell* Pick_Any_Target_For_SW(Cell* arg0) JMP_THIS(0x50CBF0);
	int32_t* Pick_Prefered_Target_For_SW(int32_t*, QuarryType quarry) JMP_THIS(0x50D170);
	bool Place_Object(RTTIType rtti, int32_t heapid, int32_t is_ship, Cell* cellnum) JMP_THIS(0x4FB0E0);
	bool Place_Special_Blast(int32_t id, Cell* cell) JMP_THIS(0x4FAE50);
	bool Player_Has_Control() JMP_THIS(0x50B6F0);
	double Power_Fraction() JMP_THIS(0x4FCE30);
	void Radar_Spied(HouseClass* arg0) JMP_THIS(0x5092F0);
	uint32_t* Random_Cell_In_Zone(uint32_t* random_cell, ZoneType zone) JMP_THIS(0x501AC0);
	int32_t Read_HouseTypes() JMP_THIS(0x5009B0);
	void Read_INI(CCINIClass* ini) JMP_THIS(0x500B40);
	void Recalc_Center() JMP_THIS(0x4FD150);
	void Refund_Money(int32_t a2) JMP_THIS(0x4F9950);
	void Register_Just_Built(TechnoClass* arg0) JMP_THIS(0x4FB6B0);
	Cell Reset_Base_Center() JMP_THIS(0x50DFF0);
	void Sell_Wall(Cell* cell, int8_t skip_sound) JMP_THIS(0x4FCE80);
	Cell Set_Base_Center(Cell) JMP_THIS(0x50DFE0);
	Cell Set_Base_Spawn_Cell(Cell) JMP_THIS(0x50E000);
	void Set_Defensive_Target_Cell(int32_t a2) JMP_THIS(0x50DA20);
	void Set_Factory(int32_t primary, RTTIType rtti, int8_t isship, int32_t defensebuilding) JMP_THIS(0x500850);
	void Set_Force_Shield_Blackout(int32_t a2) JMP_THIS(0x50BC90);
	void Set_HasThreatNode() JMP_THIS(0x509130);
	void Set_Prefered_Target_Cell(int32_t a2) JMP_THIS(0x50DA00);
	void shroudmap() JMP_THIS(0x50BD10);
	void Silo_Redraw_Check(int32_t oldtib, int32_t oldcap) JMP_THIS(0x4F9970);
	int32_t Special_Weapon_AI(int32_t super, int32_t a3) JMP_THIS(0x4FAD20);
	void Spend_Money(int32_t money) JMP_THIS(0x4F9790);
	void SpySat_AI() JMP_THIS(0x508F60);
	void startingunitclearvector() JMP_THIS(0x50D5D0);
	int32_t startingunitfillvector(int32_t a2, int32_t a3) JMP_THIS(0x50D560);
	void startingunitstuff() JMP_THIS(0x50D610);
	void startingunitstuff_buildings() JMP_THIS(0x50D320);
	void startingunitstuff_infantry_units() JMP_THIS(0x50D440);
	int32_t Suggest_New_Building() JMP_THIS(0x4FD040);
	int8_t* Suggest_New_Object(int32_t rtti, int32_t kennel) JMP_THIS(0x4FBD80);
	TypeList* Suggested_New_Team(TypeList* possible_teams_1, bool alerted) JMP_THIS(0x4FA210);
	void Super_Weapon_Handler() JMP_THIS(0x50AF10);
	int32_t Super_Weapon_Handler_Old() JMP_THIS(0x4F9370);
	int8_t SuperWeapon_AI() JMP_THIS(0x5098F0);
	int32_t Suspend_Production(int32_t rtti, int32_t heap_id, bool naval) JMP_THIS(0x4FA910);
	uint64_t Target_Dominator(int8_t) JMP_THIS(0x50A150);
	uint64_t Target_Lighting_Storm(int8_t) JMP_THIS(0x509E00);
	int32_t Team_Type_Count(int32_t teamtype) JMP_THIS(0x5095D0);
	void Tracking_Add(BuildingClass* techno) JMP_THIS(0x4FF700);
	void Tracking_Remove(BuildingClass* a2) JMP_THIS(0x4FF550);
	int32_t Unit_SelfHealAmount() JMP_THIS(0x50D9F0);
	bool Units_Self_Heal() JMP_THIS(0x50D9D0);
	uint64_t Update_Anger_Nodes(int32_t score_add, HouseClass* house) JMP_THIS(0x504790);
	void Update_Base_Nodes(int32_t a2) JMP_THIS(0x5048A0);
	void Update_Counts_0(BuildingClass* a2, int32_t arg4) JMP_THIS(0x5025F0);
	void Update_Counts_1(BuildingClass* a2, int32_t a3_1) JMP_THIS(0x502A80);
	BuildingClass* Update_Factories(int32_t rtti, bool is_ship, int32_t buildcat) JMP_THIS(0x509140);
	void Update_Scout_Nodes(HouseClass* house) JMP_THIS(0x504860);
	double Weed_Fraction() JMP_THIS(0x4F9750);
	int32_t Where_To_Go(int32_t a1, BuildingClass* a2) JMP_THIS(0x500200);
	ZoneType Which_Zone(Coordinate* a2) JMP_THIS(0x4FFB20);
	ZoneType Which_Zone(Cell* a2) JMP_THIS(0x4FFD90);
	ZoneType Which_Zone(ObjectClass* a2) JMP_THIS(0x4FFD50);
	void Write_HouseTypes() JMP_THIS(0x501160);
	void Write_INI(int8_t* a1) JMP_THIS(0x501210);
	Cell* Zone_Cell(Cell* retval_1, ZoneType zone) JMP_THIS(0x4FFDD0);
*/

protected:
	explicit __forceinline HouseClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	HouseClass(HouseTypeClass* pCountry) : HouseClass(fake_noinit_t{}) JMP_THIS(0x4F54A0);
	HouseClass(noinit_t) noexcept : HouseClass(fake_noinit_t{}) JMP_THIS(0x4F5190);
};
static_assert(sizeof(HouseClass) == HouseClass::ClassSize);