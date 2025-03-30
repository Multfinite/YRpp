#pragma once

#include "TechnoClass.h"
#include "BuildingTypeClass.h"
#include "BuildingLightClass.h"
#include "StageClass.h"

class FactoryClass;
class InfantryClass;
class LightSourceClass;
class FoggedObjectClass;

enum class BStateType : unsigned int
{
	Construction = 0x0,
	Idle = 0x1,
	Active = 0x2,
	Full = 0x3,
	Aux1 = 0x4,
	Aux2 = 0x5,
	Count = 0x6,
	None = 0xFFFFFFFF,
};

enum class BAnimType : unsigned int
{
	Uograde_1 = 0x0,
	Upgrade_2 = 0x1,
	Upgrade_3 = 0x2,
	Active_1 = 0x3,
	Active_2 = 0x4,
	Active_3 = 0x5,
	Active_4 = 0x6,
	PreProduction = 0x7,
	Production = 0x8,
	Turret = 0x9,
	Special_1 = 0xA,
	Special_2 = 0xB,
	Special_3 = 0xC,
	Special_4 = 0xD,
	Super_1 = 0xE,
	Super_2 = 0xF,
	Super_3 = 0x10,
	Super_4 = 0x11,
	Idale = 0x12,
	LowPower = 0x13,
	SuperLowPower = 0x14,
	Count = 0x15,
	M2 = 0xFFFFFFFE // ???
};


/*!
* @brief Buildings
*/
class NOVTABLE BuildingClass : public TechnoClass
{
public:
	using base_type = TechnoClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E3EBC;
			this->IRTTITypeInfo = 0x7E3EA0;
			this->INoticeSink = 0x7E3E98;
			this->INoticeSource = 0x7E3E90;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::Building;
	static constexpr uintptr_t AbsVTable = 0x7E3EBC;
	static constexpr size_t ClassSize = 0x720;

	static constexpr constant_ptr<DynamicVectorClass<BuildingClass*>, 0xA8EB40u> const Array{};
public:
	BuildingTypeClass* Type;
	FactoryClass* Factory;
	CDTimerClass C4Timer;
	BStateType BState;
	BStateType QueueBState;
	DWORD OwnerCountryIndex;
	InfantryClass* C4AppliedBy;
	DWORD LastStrength;
	AnimClass* FirestormAnim;
	AnimClass* PsiWarnAnim;
	CDTimerClass FactoryRetryTimer;

	// see eBuildingAnims above for slot index meanings
	AnimClass* Anims[static_cast<size_t>(BAnimType::Count)];
	// one flag for each of the above anims (whether the anim was enabled when power went offline?)
	bool AnimStates[static_cast<size_t>(BAnimType::Count)];

protected:
	char align_5C5[3];
public:

	AnimClass* DamageFireAnims[0x8];
	// if set, ::Update spawns damage fire anims and zeroes it
	bool RequiresDamageFires; 
	//5E8 - 5F8 ????????
	BuildingTypeClass* Upgrades[0x3];

	// type # of sw being launched
	int FiringSWType;
	DWORD TurretAnimLetterIndex;
	BuildingLightClass* Spotlight;
	RateTimer GateTimer;
	// tiled light , LightIntensity > 0
	LightSourceClass* LightSource;
	// 0-7 for active directionals, 8/12 for offline ones, check ntfnce.shp or whatever
	DWORD LaserFenceFrame;
	// anim data for firestorm active animations
	DWORD FirestormWallFrame;
	// for hospital, armory, unitrepair etc
	StageClass RepairProgress;
	RectangleStruct unknown_rect_63C;
	CoordStruct unknown_coord_64C;
	Point2D unknown_point_658;
	DWORD unknown_65C;
	bool HasPower;
	bool IsOverpowered;
	// each powered unit controller building gets this set on power activation and unset on power outage
	bool RegisteredAsPoweredUnitSource;
	DWORD SupportingPrisms;
	bool HasExtraPowerBonus;
	bool HasExtraPowerDrain;
	DynamicVectorClass<InfantryClass*> Overpowerers;
	DynamicVectorClass<InfantryClass*> Occupants;
	// which occupant should get XP, which weapon should be fired (see 6FF074)
	int FiringOccupantIndex;
	AudioController ConstructAudio;
	AudioController BuildingAudio;
	// the the last state when Update()ing. if this changed since the last Update(), UpdatePowered is called.
	bool WasOnline;
	// is also NOMINAL under [Structures]
	bool ShowRealName;
	// is also AI_REBUILDABLE under [Structures]
	bool BeingProduced;
	// is also AI_REPAIRABLE under [Structures]
	bool ShouldRebuild;
	// used to pass the NeedsEngineer check
	bool HasEngineer;
	CDTimerClass CashProductionTimer;
	// AI_SELLABLE under [Structures]
	bool IsAIAllowedToSell;
	bool IsReadyToCommence;
	// AI handholder for repair logic,
	bool NeedsRepairs;
	// C4Applied
	bool IsGoingToBlow;
	bool NoCrew;
	bool IsCharging;
	bool IsCharged;
	// has this building changed ownership at least once? affects crew and repair.
	bool HasBeenCaptured;
	bool ActuallyPlacedOnMap;
	bool unknown_bool_6E5;
	// AI handholder for repair logic,
	bool IsDamaged;
	bool IsFogged;
	bool IsBeingRepaired; // show animooted repair wrench
	bool HasBuildUp;
	// status set by EnableStuff() and DisableStuff()
	bool StuffEnabled;
	// some fugly buffers
	char HasCloakingData;
	// from Type->CloakRadiusInCells
	byte CloakRadius; 
	char Translucency;
	// the old "silo needed" logic
	DWORD StorageFilledSlots;
	// randomly assigned secret lab bonus, used if SecretInfantry, SecretUnit, and SecretBuilding are null
	TechnoTypeClass* SecretProduction;
	ColorStruct ColorAdd;
	int unknown_int_6FC;
	short unknown_short_700;
	// as defined by Type->UpgradesToLevel=
	BYTE UpgradeLevel;
	char GateStage;
	PrismChargeState PrismStage;
	Coordinate PrismTargetCoords;
	DWORD DelayBeforeFiring;
	int BunkerState; // used in UpdateBunker and friends
public:
	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	//Destructor
	virtual ~BuildingClass() RX;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	//ObjectClass
	//MissionClass
	//TechnoClass
	virtual void Destroyed(ObjectClass* Killer) RX;
	virtual bool ForceCreate(CoordStruct& coord, DWORD dwUnk = 0) R0;

	//BuildingClass
	virtual CellStruct FindExitCell(DWORD dwUnk, DWORD dwUnk2) const RT(CellStruct);
	virtual int DistanceToDockingCoord(ObjectClass* pObj) const R0;
	virtual void Place(bool captured) RX;
	virtual void UpdateConstructionOptions() RX;
	virtual void Draw(const Point2D& point, const RectangleStruct& rect) RX;
	virtual DirStruct FireAngleTo(ObjectClass* pObject) const RT(DirStruct);
	virtual void Destory(DWORD dwUnused, TechnoClass* pTechno, bool NoSurvivor, CellStruct& cell) RX;
	virtual bool TogglePrimaryFactory() R0;
	virtual void SensorArrayActivate(CellStruct cell=CellStruct::Empty) RX;
	virtual void SensorArrayDeactivate(CellStruct cell=CellStruct::Empty) RX;
	virtual void DisguiseDetectorActivate(CellStruct cell=CellStruct::Empty) RX;
	virtual void DisguiseDetectorDeactivate(CellStruct cell=CellStruct::Empty) RX;
	virtual int AlwaysZero() R0;

	// non-vt

	void UpdateAnimations()
		{ JMP_THIS(0x4509D0); }

	int GetCurrentFrame()
		{ JMP_THIS(0x43EF90); }

	bool IsAllFogged() const
		{ JMP_THIS(0x457A10); }

	void SetRallypoint(CellStruct* pTarget, bool bPlayEVA)
		{ JMP_THIS(0x443860); }

	void FreezeInFog(DynamicVectorClass<FoggedObjectClass*>* pFoggedArray, CellClass* pCell, bool Visible)
		{ JMP_THIS(0x457AA0); }

	// power up
	void GoOnline()
		{ JMP_THIS(0x452260); }
	void GoOffline()
		{ JMP_THIS(0x452360); }

	int GetPowerOutput() const
		{ JMP_THIS(0x44E7B0); }
	int GetPowerDrain() const
		{ JMP_THIS(0x44E880); }

	// Firewall aka FirestormWall
	// depending on what facings of this building
	// are connected to another FWall,
	// returns the index of the image file
	// to draw.
	DWORD GetFWFlags() const
		{ JMP_THIS(0x455B90); }

	void CreateEndPost(bool arg)
		{ JMP_THIS(0x4533A0); }

	// kick out content
	void UnloadBunker()
		{ JMP_THIS(0x4593A0); }

	// content is dead - chronosphered away or died inside
	void ClearBunker()
		{ JMP_THIS(0x459470); }

	// kick out content, remove anims, etc... don't ask me what's different from kick out
	void EmptyBunker()
		{ JMP_THIS(0x4595C0); }

	// called after destruction - CrateBeneath, resetting foundation'ed cells
	void AfterDestruction()
		{ JMP_THIS(0x441F60); }

	// destroys the specific animation (active, turret, special, etc)
	void DestroyNthAnim(BuildingAnimSlot Slot)
		{ JMP_THIS(0x451E40); }

	void PlayNthAnim(BuildingAnimSlot Slot, int effectDelay = 0) {
		bool Damaged = !this->IsGreenHP();
		bool Garrisoned = this->GetOccupantCount() > 0;

		auto& AnimData = this->Type->GetBuildingAnim(Slot);
		const char *AnimName = nullptr;
		if(Damaged) {
			AnimName = AnimData.Damaged;
		} else if(Garrisoned) {
			AnimName = AnimData.Garrisoned;
		} else {
			AnimName = AnimData.Anim;
		}
		if(AnimName && *AnimName) {
			this->PlayAnim(AnimName, Slot, Damaged, Garrisoned, effectDelay);
		}
	}

	void PlayAnim(const char* animName, BuildingAnimSlot Slot, bool Damaged, bool Garrisoned, int effectDelay = 0)
		{ JMP_THIS(0x451890); }

	// changes between building's damaged and undamaged animations.
	void ToggleDamagedAnims(bool isDamaged)
		{ JMP_THIS(0x451EE0); }

	// when the building is switched off
	void DisableStuff()
		{ JMP_THIS(0x452480); }

	// when the building is switched on
	void EnableStuff()
		{ JMP_THIS(0x452410); }

	// when the building is warped
	void DisableTemporal()
		{ JMP_THIS(0x4521C0); }

	// when the building warped back in
	void EnableTemporal()
		{ JMP_THIS(0x452210); }

	// returns Type->SuperWeapon, if its AuxBuilding is satisfied
	int FirstActiveSWIdx() const
		{ JMP_THIS(0x457630); }

	int GetShapeNumber() const
		{ JMP_THIS(0x43EF90); }

	void BeginMode(BStateType bType)
		{ JMP_THIS(0x447780); }

	// returns Type->SuperWeapon2, if its AuxBuilding is satisfied
	int SecondActiveSWIdx() const
		{ JMP_THIS(0x457690); }

	void FireLaser(CoordStruct Coords)
		{ JMP_THIS(0x44ABD0); }

	bool IsBeingDrained() const
		{ JMP_THIS(0x70FEC0); }

	bool UpdateBunker()
		{ JMP_THIS(0x458E50); }

	void KillOccupants(TechnoClass* pAssaulter)
		{ JMP_THIS(0x4585C0); }

	// returns false if this is a gate that needs time to open, true otherwise
	bool MakeTraversable()
		{ JMP_THIS(0x452540); }

	bool CheckFog()
		{ JMP_THIS(0x457A10); }

	Matrix3D* GetVoxelBarrelOffsetMatrix(Matrix3D& ret)
		{ JMP_THIS(0x458810); }

	// returns false if this is a gate that is closed, true otherwise
	bool IsTraversable() const
		{ JMP_THIS(0x4525F0); }

	int DrawInfoTipAndSpiedSelection(Point2D* pLocation, RectangleStruct* pRect) const
		{ JMP_THIS(0x43E7B0); }

	// helpers
	bool HasSuperWeapon(int index) const {
		if(this->Type->HasSuperWeapon(index)) {
			return true;
		}
		for(auto pType : this->Upgrades) {
			if(pType && pType->HasSuperWeapon(index)) {
				return true;
			}
		}
		return false;
	}

	TechnoTypeClass* GetSecretProduction() const;

	AnimClass*& GetAnim(BuildingAnimSlot slot) {
		return this->Anims[static_cast<int>(slot)];
	}

	AnimClass* const& GetAnim(BuildingAnimSlot slot) const {
		return this->Anims[static_cast<int>(slot)];
	}

	bool& GetAnimState(BuildingAnimSlot slot) {
		return this->AnimStates[static_cast<int>(slot)];
	}

	bool const& GetAnimState(BuildingAnimSlot slot) const {
		return this->AnimStates[static_cast<int>(slot)];
	}

	//Constructor
	BuildingClass(BuildingTypeClass* pType, HouseClass* pOwner) noexcept
		: BuildingClass(noinit_t())
	{ JMP_THIS(0x43B740); }

protected:
	explicit __forceinline BuildingClass(noinit_t) noexcept
		: TechnoClass(noinit_t())
	{ }
};
