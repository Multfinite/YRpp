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

/*!
* @brief Buildings
*/
class __declspec(uuid("0E272DC6-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE BuildingClass : public TechnoClass
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
	static constexpr AbstractType AbsID = AbstractType::Building;
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
	AnimClass* Anims[static_cast<size_t>(BuildingAnimSlot::Count)];
	// one flag for each of the above anims (whether the anim was enabled when power went offline?)
	bool AnimStates[static_cast<size_t>(BuildingAnimSlot::Count)];

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
	virtual ~BuildingClass() JMP_THIS(0x43BCF0);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x459E80);

	HRESULT STDMETHODCALLTYPE Load(__RPC__in_opt IStream* pStm) override JMP_STD(0x453E20);
	HRESULT STDMETHODCALLTYPE Save(__RPC__in_opt IStream* pStm, int32_t fClearDirty) override JMP_STD(0x454190);

	void Init() override JMP_THIS(0x442C40);
	void InvalidatePointer(AbstractClass* target, bool all) override JMP_THIS(0x44E8F0);
	RTTIType KindOf() const override JMP_THIS(0x459EC0);
	int SizeOf() const override JMP_THIS(0x459E70);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x454260);
	Coordinate Center() const override JMP_THIS(0x447AC0);
	Coordinate Destination(TechnoClass* pDocker = nullptr) const override JMP_THIS(0x447E90);
	void AI() override JMP_THIS(0x43FB20);

	VisualType VisualCharacter(VARIANT_BOOL specificOwner, HouseClass* whoIsAsking) const override JMP_THIS(0x4544A0);
	SHPStruct* GetImage() const override JMP_THIS(0x4513D0);
	Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x447540);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x447210);
	bool IsStrange() const override JMP_THIS(0x457620);
	ObjectTypeClass* Type() const override JMP_THIS(0x459EE0);
	const wchar_t* FullName() const override JMP_THIS(0x459ED0);
	bool Repairable() const override JMP_THIS(0x452630);
	bool Soldable() const override JMP_THIS(0x4494C0);
	bool CanPlayerFire() const override JMP_THIS(0x44F5C0);
	Coordinate TargetCoord() const override JMP_THIS(0x4500A0);
	Coordinate DockingCoord(TechnoClass* docker) const override JMP_THIS(0x447B20);
	Coordinate RenderCoord() const override JMP_THIS(0x459EF0);
	Coordinate FLH(int idxWeapon, Coordinate BaseCoords) const override JMP_THIS(0x453840);
	Coordinate ExitCoord() const override JMP_THIS(0x44F640);
	int YSort() const override JMP_THIS(0x449410);
	bool Limbo() override JMP_THIS(0x445880);
	bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x440580);
	void DetachAll(bool permanently) override JMP_THIS(0x44EBF0);
	void MarkAllOccupationBits(Coordinate const& coords) override JMP_THIS(0x453D60);
	void UnmarkAllOccupationBits(Coordinate const& coords) override JMP_THIS(0x453DC0);
	KickOutResult KickOutUnit(TechnoClass* pTechno, ::Cell Cell) override JMP_THIS(0x443C60);
	bool DrawIfVisible(RectangleStruct* pBounds, bool EvenIfCloaked, DWORD dwUnk3) const override JMP_THIS(0x43CEA0);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x43D290);
	void DrawAgain(const Point2D& location, const RectangleStruct& bounds) const override JMP_THIS(0x43D030);
	bool Mark(MarkType value) override JMP_THIS(0x43F180);
	RectangleStruct* GetRenderDimensions(RectangleStruct* pRect) override JMP_THIS(0x455C20);
	void DrawRadialIndicator(DWORD dwUnk) override JMP_THIS(0x456750);
	bool CanBeSelectedNow() const override JMP_THIS(0x459C00);
	bool ObjectClickedAction(Action action, ObjectClass* pTarget, bool bUnk) override JMP_THIS(0x4436F0);
	bool CellClickedAction(Action action, ::Cell* pCell, ::Cell* pCell1, bool bUnk) override JMP_THIS(0x443410);
	void ClickedAsTarget(int duration) override JMP_THIS(0x456E00);
	DamageState IronCurtain(int nDuration, HouseClass* pSource, bool ForceShield) override JMP_THIS(0x457C90);
	DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x442230);
	RadioCommand ReceiveCommand(TechnoClass* pSender, RadioCommand command, AbstractClass*& pInOut) override JMP_THIS(0x43C2D0);
	bool DiscoveredBy(HouseClass* pHouse) override JMP_THIS(0x44D5D0);
	void SetRepairState(int state) override JMP_THIS(0x446FF0);
	void Sell(DWORD control) override JMP_THIS(0x447110);
	Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const override JMP_THIS(0x449440);
	
	bool IsReadyToCommence() override JMP_THIS(0x454250);
	int MissionAttack() override JMP_THIS(0x44ACF0);
	int MissionCapture() override JMP_THIS(0x44B760);
	int MissionGuard() override JMP_THIS(0x4496B0);
	int MissionGuardArea() override JMP_THIS(0x449A40);
	int MissionHarvest() override JMP_THIS(0x44B770);
	int MissionUnload() override JMP_THIS(0x44D880);
	int MissionConstruction() override JMP_THIS(0x449A50);
	int MissionDeconstruction() override JMP_THIS(0x449C30);
	int MissionRepair() override JMP_THIS(0x44B780);
	int MissionMissile() override JMP_THIS(0x44C980);
	bool MissionOpen() override JMP_THIS(0x44E440);
	
	bool IsUnitFactory() const override JMP_THIS(0x455DA0);
	bool IsReadyToCloak() const override JMP_THIS(0x457770);
	bool ShouldNotBeCloaked() const override JMP_THIS(0x4578C0);
	DirStruct TurretFacing() const override JMP_THIS(0x445E50);
	bool IsArmed() const override JMP_THIS(0x458DB0);
	int GetPipFillLevel() const override JMP_THIS(0x44D700);
	DirStruct UnknownFireangle(TechnoClass* techno) override JMP_THIS(0x43E940);
	int GetCrewCount() const override JMP_THIS(0x451330);
	int GetAntiAirValue() const override JMP_THIS(0x459870);
	int GetAntiArmorValue() const override JMP_THIS(0x459880);
	int GetAntiInfantryValue() const override JMP_THIS(0x459890);
	void GotHijacked() override JMP_THIS(0x4576F0);
	int GetZAdjustment() const override JMP_THIS(0x43E900);
	Coordinate FiringOffset() const override JMP_THIS(0x453A70);
	DirStruct GetRealFacing() const override JMP_THIS(0x44D7D0);
	InfantryTypeClass* GetCrew() const override JMP_THIS(0x44EB10);
	bool IsRadarVisible(int* pOutDetection) const override JMP_THIS(0x457020);
	bool IsPowerOnline() const override JMP_THIS(0x4555D0);
	int VoiceDeploy()  override JMP_THIS(0x459C20);
	void Destroyed(ObjectClass * killer) override JMP_THIS(0x44D760);
	FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const override JMP_THIS(0x447F10);
	AbstractClass* GreatestThreat(ThreatType threat, Coordinate* pCoord, bool onlyTargetHouseEnemy) override JMP_THIS(0x445F00);
	void SetTarget(AbstractClass* pTarget) override JMP_THIS(0x443B90);
	bool SetOwningHouse(HouseClass* pHouse, bool announce = true) override JMP_THIS(0x448260);
	WeaponStruct* GetWeapon(int nWeaponIndex) const override JMP_THIS(0x4526F0);
	bool HasTurret() const override JMP_THIS(0x4527D0);
	bool CanOccupyFire() const override JMP_THIS(0x458DD0);
	int GetOccupyRangeBonus() const override JMP_THIS(0x458E00);
	int GetOccupantCount() const override JMP_THIS(0x4581F0);
	void UpdateCloak(bool bUnk = 1) override JMP_THIS(0x454DB0);
	int32_t FlashTintStage(int32_t tintStage) const override JMP_THIS(0x456F80);
	void UpdateRefinerySmokeSystems() override JMP_THIS(0x459900);
	void SetDestination(AbstractClass* target, bool a2) override JMP_THIS(0x455D50);
	bool EnterIdleMode(bool initial, bool a2) override JMP_THIS(0x44D6A0);
	bool ForceCreate(Coordinate& coord, DWORD dwUnk = 0) override JMP_THIS(0x458A80);
	int RadarTrackingStart() override JMP_THIS(0x456580);
	int RadarTrackingStop() override JMP_THIS(0x4565E0);
	void RadarTrackingFlash() override JMP_THIS(0x456640);

	/*!
	* @brief
	* @note original_name Find_Exit_Cell
	* @note vtable_index 309:0x4D4
	* @note address 0x44EFB0
	*/
	virtual ::Cell FindExitCell(TechnoClass* techno, ::Cell unkCell) const JMP_THIS(0x44EFB0);

	/*!
	* @brief
	* @note original_name Docking_Distance
	* @note vtable_index 310:0x4D8
	* @note address 0x447E00
	*/
	virtual int DistanceToDockingCoord(TechnoClass* docker) const JMP_THIS(0x447E00);

	/*!
	* @brief
	* @note original_name Grand_Opening
	* @note vtable_index 311:0x4DC
	* @note address 0x445F80
	*/
	virtual void Place(bool captured) JMP_THIS(0x445F80);

	/*!
	* @brief
	* @note original_name Update_Buildables
	* @note vtable_index 312:0x4E0
	* @note address 0x4456D0
	*/
	virtual void UpdateConstructionOptions() JMP_THIS(0x4456D0);

	/*!
	* @brief
	* @note original_name Draw_Door_And_Turret
	* @note vtable_index 313:0x4E4
	* @note address 0x43DA80
	*/
	virtual void Draw(Point2D const& point, const RectangleStruct& rect) JMP_THIS(0x43DA80);

	/*!
	* @brief
	* @note original_name Turret_Facing_Towards
	* @note vtable_index 314:0x4E8
	* @note address 0x43ED40
	*/
	virtual DirStruct FireAngleTo(ObjectClass* pObject) const JMP_THIS(0x43ED40);

	/*!
	* @brief
	* @note original_name On_Destruction
	* @note vtable_index 315:0x4EC
	* @note address 0x4415F0
	*/
	virtual void Destroy(TechnoClass* lastContact, TechnoClass* source, bool noSurvivor, ::Cell* occupyList) JMP_THIS(0x4415F0);

	/*!
	* @brief
	* @note original_name Toggle_Primary
	* @note vtable_index 316:0x4F0
	* @note address 0x448160
	*/
	virtual bool TogglePrimaryFactory() JMP_THIS(0x448160);

	/*!
	* @brief
	* @note original_name Sensor_Array_Activate
	* @note vtable_index 317:0x4F4
	* @note address 0x455820
	*/
	virtual void SensorArrayActivate(::Cell cell = ::Cell::Empty) JMP_THIS(0x455820);

	/*!
	* @brief
	* @note original_name Sensor_Array_Deactivate
	* @note vtable_index 318:0x4F8
	* @note address 0x4556D0
	*/
	virtual void SensorArrayDeactivate(::Cell cell = ::Cell::Empty) JMP_THIS(0x4556D0);

	/*!
	* @brief
	* @note original_name Disguise_Detector_Activate
	* @note vtable_index 319:0x4FC
	* @note address 0x455A80
	*/
	virtual void DisguiseDetectorActivate(::Cell cell = ::Cell::Empty) JMP_THIS(0x455A80);

	/*!
	* @brief
	* @note original_name Disguise_Detector_Deactivate
	* @note vtable_index 320:0x500
	* @note address 0x455980
	*/
	virtual void DisguiseDetectorDeactivate(::Cell cell = ::Cell::Empty) JMP_THIS(0x455980);

	/*!
	* @brief
	* @note original_name vthk_0x504_BuildingClass
	* @note vtable_index 321:0x504
	* @note address 0x452250
	*/
	virtual int vthk_0x504_AlwaysZero() JMP_THIS(0x452250);

	// non-vt

	constexpr void UpdateFactory() JMP_THIS(0x4500F0);
	constexpr void UpdateCharging() JMP_THIS(0x4503F0);
	constexpr void UpdateOnFire() JMP_THIS(0x43C0D0);
	constexpr void UpdateRepair() JMP_THIS(0x450630);
	constexpr BuildingTypeClass* UpdateGarrison() JMP_THIS(0x458200);
	constexpr void UpdateGarrisonAnim() JMP_THIS(0x458330);
	constexpr void UpdateRadarSpied() JMP_THIS(0x44F7A0);

	//  return Class->UnitAbsorb || Class->InfantryAbsorb;
	constexpr int32_t IsAbsorber() JMP_THIS(0x4598A0);
	constexpr int8_t AddOverpowerer(int32_t a2) JMP_THIS(0x452820);
	// called in Unlimbo
	constexpr int8_t Anim_Logic_1(int32_t a2) JMP_THIS(0x451400);
	constexpr bool CanOccupy(InfantryClass* inf) JMP_THIS(0x457CE0);
	constexpr bool CanUpgrade(BuildingTypeClass* a2, HouseClass* house) JMP_THIS(0x452670);
	
	constexpr ::Cell CheckPoint(CheckPointType cp) JMP_THIS(0x44F6E0);
	constexpr void ClearFactoryBib() JMP_THIS(0x449540);
	constexpr void DoAnim(BAnimType anim, int32_t is_damaged, int32_t is_garrsioned, int32_t delay) JMP_THIS(0x451750);
	constexpr void DropDebris(int32_t) JMP_THIS(0x442D90);
	
	constexpr int32_t FlushForPlacement(TechnoClass* techno, int32_t a3) JMP_THIS(0x44EF80);
	
	constexpr TechnoTypeClass* GetSecretObject() JMP_THIS(0x459840);
	constexpr bool IsImpassable(CellClass* a2) JMP_THIS(0x458A00);
	constexpr int8_t occupier_lists() JMP_THIS(0x44E3A0);
	
	constexpr void Produce_Cash() JMP_THIS(0x458750);	
	constexpr void Remove_Damage_Fires() JMP_THIS(0x43C2A0);
	
	constexpr void turret_stage_43EE50() JMP_THIS(0x43EE50);

	constexpr void UpdateAnimations() JMP_THIS(0x4509D0);
	constexpr int GetCurrentFrame() JMP_THIS(0x43EF90);
	constexpr bool IsAllFogged() const JMP_THIS(0x457A10);
	constexpr void SetRallypoint(::Cell* pTarget, bool bPlayEVA) JMP_THIS(0x443860);
	constexpr void FreezeInFog(DynamicVectorClass<FoggedObjectClass*>* pFoggedArray, CellClass* pCell, bool Visible) JMP_THIS(0x457AA0);
	constexpr void GoOnline() JMP_THIS(0x452260);
	constexpr void GoOffline() JMP_THIS(0x452360);
	constexpr int GetPowerOutput() const JMP_THIS(0x44E7B0); 
	constexpr int GetPowerDrain() const JMP_THIS(0x44E880);
	// Firewall aka FirestormWall
	// depending on what facings of this building
	// are connected to another FWall,
	// returns the index of the image file
	// to draw.
	constexpr DWORD GetFWFlags() const JMP_THIS(0x455B90);
	constexpr void CreateEndPost(bool arg) JMP_THIS(0x4533A0);
	// kick out content
	constexpr void UnloadBunker() JMP_THIS(0x4593A0);
	// content is dead - chronosphered away or died inside
	constexpr void ClearBunker() JMP_THIS(0x459470);
	// kick out content, remove anims, etc... don't ask me what's different from kick out
	constexpr void EmptyBunker() JMP_THIS(0x4595C0);
	// called after destruction - CrateBeneath, resetting foundation'ed cells
	// Leave_Rubble
	constexpr void AfterDestruction() JMP_THIS(0x441F60);
	// destroys the specific animation (active, turret, special, etc)
	constexpr void DestroyNthAnim(BuildingAnimSlot Slot) JMP_THIS(0x451E40);
	constexpr void PlayAnim(const char* animName, BuildingAnimSlot Slot, bool Damaged, bool Garrisoned, int effectDelay = 0) JMP_THIS(0x451890);
	// changes between building's damaged and undamaged animations.
	constexpr void ToggleDamagedAnims(bool isDamaged) JMP_THIS(0x451EE0);
	// when the building is switched off
	constexpr void DisableStuff() JMP_THIS(0x452480);
	// when the building is switched on
	constexpr void EnableStuff() JMP_THIS(0x452410);
	// when the building is warped
	constexpr void DisableTemporal() JMP_THIS(0x4521C0);
	// when the building warped back in
	constexpr void EnableTemporal() JMP_THIS(0x452210);
	// returns Type->SuperWeapon, if its AuxBuilding is satisfied
	constexpr int FirstActiveSWIdx() const JMP_THIS(0x457630);
	constexpr int GetShapeNumber() const JMP_THIS(0x43EF90);
	constexpr void BeginMode(BStateType bType) JMP_THIS(0x447780);
	// returns Type->SuperWeapon2, if its AuxBuilding is satisfied
	constexpr int SecondActiveSWIdx() const JMP_THIS(0x457690);
	constexpr void FireLaser(CoordStruct Coords) JMP_THIS(0x44ABD0);
	constexpr bool IsBeingDrained() const JMP_THIS(0x70FEC0);
	constexpr bool UpdateBunker() JMP_THIS(0x458E50);
	constexpr void KillOccupants(TechnoClass* pAssaulter) JMP_THIS(0x4585C0);
	// returns false if this is a gate that needs time to open, true otherwise
	constexpr bool MakeTraversable() JMP_THIS(0x452540);
	constexpr Matrix3D* GetVoxelBarrelOffsetMatrix(Matrix3D& ret) JMP_THIS(0x458810);
	// returns false if this is a gate that is closed, true otherwise
	constexpr bool IsTraversable() const JMP_THIS(0x4525F0);
	constexpr int DrawInfoTipAndSpiedSelection(Point2D* pLocation, RectangleStruct* pRect) const JMP_THIS(0x43E7B0);
	
	constexpr int8_t BuildINIEntry(CCINIClass* pINI) JMP_THIS(0x44FEC0);
	constexpr static void __fastcall ReadINI(CCINIClass* pINI) JMP_STD(0x44F820);
	constexpr static void __fastcall WriteINI(CCINIClass* pINI) JMP_STD(0x44FE60);

	// helpers

	void PlayNthAnim(BuildingAnimSlot Slot, int effectDelay = 0) {
		bool Damaged = !this->IsGreenHP();
		bool Garrisoned = this->GetOccupantCount() > 0;

		auto& AnimData = this->Type->GetBuildingAnim(Slot);
		const char* AnimName = nullptr;
		if (Damaged) {
			AnimName = AnimData.Damaged;
		}
		else if (Garrisoned) {
			AnimName = AnimData.Garrisoned;
		}
		else {
			AnimName = AnimData.Anim;
		}
		if (AnimName && *AnimName) {
			this->PlayAnim(AnimName, Slot, Damaged, Garrisoned, effectDelay);
		}
	}

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
		return this->Anims[static_cast<std::underlying_type_t<BuildingAnimSlot>>(slot)];
	}

	AnimClass* const& GetAnim(BuildingAnimSlot slot) const {
		return this->Anims[static_cast<std::underlying_type_t<BuildingAnimSlot>>(slot)];
	}

	bool& GetAnimState(BuildingAnimSlot slot) {
		return this->AnimStates[static_cast<std::underlying_type_t<BuildingAnimSlot>>(slot)];
	}

	bool const& GetAnimState(BuildingAnimSlot slot) const {
		return this->AnimStates[static_cast<std::underlying_type_t<BuildingAnimSlot>>(slot)];
	}

protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline BuildingClass(fake_noinit_t) noexcept : TechnoClass(fake_noinit_t{}) {}

public:
	BuildingClass(noinit_t) noexcept : TechnoClass(fake_noinit_t{}) { vtables.init(this); };
	BuildingClass(InfantryTypeClass* pType, HouseClass* pOwner) noexcept : BuildingClass(fake_noinit_t{}) JMP_THIS(0x43B740);
};
static_assert(sizeof(BuildingClass) == BuildingClass::ClassSize);