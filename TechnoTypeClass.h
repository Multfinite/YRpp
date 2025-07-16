#pragma once

#include "ObjectTypeClass.h"
#include "RulesClass.h"
#include "WeaponTypeClass.h"

//forward declarations
class AircraftTypeClass;
class AnimTypeClass;
class BuildingTypeClass;
class InfantryTypeClass;
class ParticleSystemTypeClass;
class VoxelAnimTypeClass;
class UnitTypeClass;

struct AbilitiesStruct
{
	bool FASTER; //0x00
	bool STRONGER; //0x01
	bool FIREPOWER; //0x02
	bool SCATTER; //0x03
	bool ROF; //0x04
	bool SIGHT; //0x05
	bool CLOAK; //0x06
	bool TIBERIUM_PROOF; //0x07
	bool VEIN_PROOF; //0x08
	bool SELF_HEAL; //0x09
	bool EXPLODES; //0x0A
	bool RADAR_INVISIBLE; //0x0B
	bool SENSORS; //0x0C
	bool FEARLESS; //0x0D
	bool C4; //0x0E
	bool TIBERIUM_HEAL; //0x0F
	bool GUARD_AREA; //0x10
	bool CRUSHER; //0x11

	bool& operator[](Ability i)
	{
		return reinterpret_cast<bool*>(this)[static_cast<int>(i)];
	}
};

struct TurretControl
{
	int Travel;
	int CompressFrames;
	int RecoverFrames;
	int HoldFrames;
};

struct WeaponStruct
{
	WeaponTypeClass*  WeaponType;
	CoordStruct       FLH;
	int               BarrelLength;
	int               BarrelThickness;
	bool              TurretLocked;

	WeaponStruct() : WeaponType(nullptr),
		FLH(CoordStruct::Empty),
		BarrelLength(0),
		BarrelThickness(0),
		TurretLocked(false)
	{ }

	bool operator == (const WeaponStruct& pWeap) const
		{ return false; }
};

/*!
* @brief TechnoTypes are initialized by INI files.
*/
class NOVTABLE TechnoTypeClass : public ObjectTypeClass
{
public:
	using base_type = ObjectTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F4ED8;
			this->IRTTITypeInfo = 0x7F4EBC;
			this->INoticeSink = 0x7F4EB4;
			this->INoticeSource = 0x7F4EAC;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7F4ED8;
	static constexpr size_t ClassSize = 0xDF8;

	DEFINE_REFERENCE(DynamicVectorClass<TechnoTypeClass*>, Array, 0xA8EB00u)
	static constexpr auto MaxWeapons = 18;
public:

	int             WalkRate;
	int             IdleRate;
	AbilitiesStruct VeteranAbilities;
	AbilitiesStruct EliteAbilities;
	double          SpecialThreatValue;
	double          MyEffectivenessCoefficient;
	double          TargetEffectivenessCoefficient;
	double          TargetSpecialThreatCoefficient;
	double          TargetStrengthCoefficient;
	double          TargetDistanceCoefficient;
	double          ThreatAvoidanceCoefficient;
	int             SlowdownDistance;
	DWORD align_2FC;
	double          unknown_double_300;
	double          AccelerationFactor;
	int             CloakingSpeed;
	TypeList<VoxelAnimTypeClass*> DebrisTypes;
	TypeList<int> DebrisMaximums;
	_GUID           Locomotor;
	DWORD align_35C;
	double          VoxelScaleX;
	double          VoxelScaleY;
	double          Weight;
	double          PhysicalSize;
	double          Size;
	double          SizeLimit;
	bool            HoverAttack;
	int             VHPScan;
	int             unknown_int_398;
	DWORD align_39C;
	double          RollAngle;
	double          PitchSpeed;
	double          PitchAngle;
	int             BuildLimit;
	Category        Category;
	DWORD           unknown_3C0;
	DWORD align_3C4;
	double          DeployTime;
	int             FireAngle;
	PipScale        PipScale;
	bool            PipsDrawForAll;
	int             LeptonMindControlOffset;
	int             PixelSelectionBracketDelta;
	int             PipWrap;
	TypeList<BuildingTypeClass*> Dock;
	BuildingTypeClass* DeploysInto;
	UnitTypeClass* UndeploysInto;
	UnitTypeClass* PowersUnit;
	bool            PoweredUnit;
	TypeList<int> VoiceSelect;
	TypeList<int> VoiceSelectEnslaved;
	TypeList<int> VoiceSelectDeactivated;
	TypeList<int> VoiceMove;
	TypeList<int> VoiceAttack;
	TypeList<int> VoiceSpecialAttack;
	TypeList<int> VoiceDie;
	TypeList<int> VoiceFeedback;
	TypeList<int> MoveSound;
	TypeList<int> DieSound;
	int             AuxSound1;
	int             AuxSound2;
	int             CreateSound;
	int             DamageSound;
	int             ImpactWaterSound;
	int             ImpactLandSound;
	int             CrashingSound;
	int             SinkingSound;
	int             VoiceFalling;
	int             VoiceCrashing;
	int             VoiceSinking;
	int             VoiceEnter;
	int             VoiceCapture;
	int             TurretRotateSound;
	int             EnterTransportSound;
	int             LeaveTransportSound;
	int             DeploySound;
	int             UndeploySound;
	int             ChronoInSound;
	int             ChronoOutSound;
	int             VoiceHarvest;
	int             VoicePrimaryWeaponAttack;
	int             VoicePrimaryEliteWeaponAttack;
	int             VoiceSecondaryWeaponAttack;
	int             VoiceSecondaryEliteWeaponAttack;
	int             VoiceDeploy;
	int             VoiceUndeploy;
	int             EnterGrinderSound;
	int             LeaveGrinderSound;
	int             EnterBioReactorSound;
	int             LeaveBioReactorSound;
	int             ActivateSound;
	int             DeactivateSound;
	int             MindClearedSound;
	MovementZone    MovementZone;
	int             GuardRange;
	int             MinDebris;
	int             MaxDebris;
	TypeList<AnimTypeClass*> DebrisAnims;
	int             Passengers;
	bool            OpenTopped;
	int             Sight;
	bool            ResourceGatherer;
	bool            ResourceDestination;
	bool            RevealToAll;
	bool            Drainable;
	int             SensorsSight;
	int             DetectDisguiseRange;
	int             BombSight;
	int             LeadershipRating;
	NavalTargetingType NavalTargeting;
	LandTargetingType LandTargeting;
	float           BuildTimeMultiplier;
	int             MindControlRingOffset;
	int             Cost;
	int             Soylent;
	int             FlightLevel;
	int             AirstrikeTeam;
	int             EliteAirstrikeTeam;
	AircraftTypeClass* AirstrikeTeamType;
	AircraftTypeClass* EliteAirstrikeTeamType;
	int             AirstrikeRechargeTime;
	int             EliteAirstrikeRechargeTime;
	int             TechLevel;
	TypeList<int> Prerequisite;
	TypeList<int> PrerequisiteOverride;
	int             ThreatPosed;
	int             Points;
	int             Speed;
	SpeedType       SpeedType;
	int             InitialAmmo;
	int             Ammo;
	int             IFVMode;
	int             AirRangeBonus;
	bool            BerserkFriendly;
	bool            SprayAttack;
	bool            Pushy;
	bool            Natural;
	bool            Unnatural;
	bool            CloseRange;
	int             Reload;
	int             EmptyReload;
	int             ReloadIncrement;
	int             RadialFireSegments;
	int             DeployFireWeapon;
	bool            DeployFire;
	bool            DeployToLand;
	bool            MobileFire;
	bool            OpportunityFire;
	bool            DistributedFire;
	bool            DamageReducesReadiness;
	int             ReadinessReductionMultiplier;
	UnitTypeClass* UnloadingClass;
	AnimTypeClass* DeployingAnim;
	bool            AttackFriendlies;
	bool            AttackCursorOnFriendlies;
	int             UndeployDelay;
	bool            PreventAttackMove;
	DWORD           OwnerFlags;
	int             AIBasePlanningSide;
	bool            StupidHunt;
	bool            AllowedToStartInMultiplayer;
	char            CameoFile[0x19];
	PROTECTED_PROPERTY(BYTE, align_6EF);
	SHPStruct* Cameo;
	bool            CameoAllocated;
	char            AltCameoFile[0x19];
	PROTECTED_PROPERTY(BYTE, align_70E[2]);
	SHPStruct* AltCameo;
	bool            AltCameoAllocated;
	int             RotCount;
	int             ROT;
	int             TurretOffset;
	bool            CanBeHidden;
	int             Points2; //twice
	TypeList<AnimTypeClass*> Explosion;
	TypeList<AnimTypeClass*> DestroyAnim;
	ParticleSystemTypeClass* NaturalParticleSystem;
	CoordStruct NaturalParticleSystemLocation;
	ParticleSystemTypeClass* RefinerySmokeParticleSystem;
	TypeList<ParticleSystemTypeClass*> DamageParticleSystems;
	TypeList<ParticleSystemTypeClass*> DestroyParticleSystems;
	CoordStruct DamageSmokeOffset;
	bool            DamSmkOffScrnRel;
	CoordStruct DestroySmokeOffset;
	CoordStruct RefinerySmokeOffsetOne;
	CoordStruct RefinerySmokeOffsetTwo;
	CoordStruct RefinerySmokeOffsetThree;
	CoordStruct RefinerySmokeOffsetFour;
	int             ShadowIndex;
	int             Storage;
	bool            TurretNotExportedOnGround;
	bool            Gunner;
	bool            HasTurretTooltips;
	int             TurretCount;
	int             WeaponCount;
	bool            IsChargeTurret;
	int             TurretWeapon[MaxWeapons];
	CoordStruct     AlternativeFLH[5];
	WeaponStruct	Weapon[MaxWeapons];
	bool            ClearAllWeapons;
	WeaponStruct	EliteWeapon[MaxWeapons];
	bool            TypeImmune;
	bool            MoveToShroud;
	bool            Trainable;
	bool            DamageSparks; //enabled for Cyborg InfantryTypes
	bool            TargetLaser;
	bool            ImmuneToVeins;
	bool            TiberiumHeal;
	bool            CloakStop;
	bool            IsTrain;
	bool            IsDropship;
	bool            ToProtect;
	bool            Disableable;
	bool            Unbuildable; //always false, if true it cannot be built from sidebar
	bool            DoubleOwned;
	bool            Invisible;
	bool            RadarVisible;
	bool            HasPrimary; //not loaded from the INIs
	bool            Sensors;
	bool            Nominal;
	bool            DontScore;
	bool            DamageSelf;
	bool            Turret;
	bool            TurretRecoil;
	TurretControl   TurretAnimData;
	bool            unknown_bool_CB4; //always false?
	TurretControl   BarrelAnimData;
	bool            unknown_bool_CC8; //always false?

protected:
	BYTE align_CC9, align_CCA, align_CCB;

public:
	bool            Repairable;
	bool            Crewed;
	bool            Naval;
	bool            Remapable;
	bool            Cloakable;
	bool            GapGenerator;
	char            GapRadiusInCells;
	char            SuperGapRadiusInCells;
	bool            Teleporter;
	bool            IsGattling;
	int             WeaponStages;
	int WeaponStage[6];
	int EliteStage[6];
	int             RateUp;
	int             RateDown;
	bool            SelfHealing;
	bool            Explodes;
	WeaponTypeClass* DeathWeapon;
	float           DeathWeaponDamageModifier;
	bool            NoAutoFire;
	bool            TurretSpins;
	bool            TiltCrashJumpjet;
	bool            Normalized;
	bool            ManualReload;
	bool            VisibleLoad;
	bool            LightningRod;
	bool            HunterSeeker;
	bool            Crusher;
	bool            OmniCrusher;
	bool            OmniCrushResistant;
	bool            TiltsWhenCrushes;
	bool            IsSubterranean;
	bool            AutoCrush;
	bool            Bunkerable;
	bool            CanDisguise;
	bool            PermaDisguise;
	bool            DetectDisguise;
	bool            DisguiseWhenStill;
	bool            CanApproachTarget;
	bool            CanRecalcApproachTarget;
	bool            ImmuneToPsionics;
	bool            ImmuneToPsionicWeapons;
	bool            ImmuneToRadiation;
	bool            Parasiteable;
	bool            DefaultToGuardArea;
	bool            Warpable;
	bool            ImmuneToPoison;
	bool            ReselectIfLimboed;
	bool            RejoinTeamIfLimboed;
	bool            Slaved;
	InfantryTypeClass* Enslaves;
	int             SlavesNumber;
	int             SlaveRegenRate;
	int             SlaveReloadRate;
	int             OpenTransportWeapon;
	bool            Spawned;
	AircraftTypeClass* Spawns;
	int             SpawnsNumber;
	int             SpawnRegenRate;
	int             SpawnReloadRate;
	bool            MissileSpawn;
	bool            Underwater;
	bool            BalloonHover;
	int             SuppressionThreshold;
	int             JumpjetTurnRate;
	int             JumpjetSpeed;
	float           JumpjetClimb;
	float           JumpjetCrash;
	int             JumpjetHeight;
	float           JumpjetAccel;
	float           JumpjetWobbles;
	bool            JumpjetNoWobbles;
	int             JumpjetDeviation;
	bool            JumpJet;
	bool            Crashable;
	bool            ConsideredAircraft;
	bool            Organic;
	bool            NoShadow;
	bool            CanPassiveAquire;
	bool            CanRetaliate;
	bool            RequiresStolenThirdTech;
	bool            RequiresStolenSovietTech;
	bool            RequiresStolenAlliedTech;
	DWORD           RequiredHouses;
	DWORD           ForbiddenHouses;
	DWORD           SecretHouses;
	bool            UseBuffer;
	CoordStruct SecondSpawnOffset;
	bool            IsSelectableCombatant;
	bool            Accelerates;
	bool            DisableVoxelCache;
	bool            DisableShadowCache;
	int             ZFudgeCliff;
	int             ZFudgeColumn;
	int             ZFudgeTunnel;
	int             ZFudgeBridge;
	char            PaletteFile[0x20];
	DynamicVectorClass<ColorScheme*>* Palette; //no... idea....
	DWORD           align_DF4;
public:
	virtual ~TechnoTypeClass() JMP_THIS(0x711AE0);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x7162F0);

	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x716DC0);
	HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) override JMP_STD(0x7170A0);

	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x7171A0);
	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x712170);
	DWORD Ownable() const override JMP_THIS(0x711EC0);
	int MaxPips() const override JMP_THIS(0x716290);
	int CostOf(HouseClass* pHouse) const override JMP_THIS(0x711F00);
	int TimeToBuild() const override JMP_THIS(0x711EE0);
	SHPStruct* GetCameo() const override JMP_THIS(0x712040);

	/*!
	* @brief
	* @note original_name new_theater_A0_5247B0
	* @note vtable_index 40:0xA0
	* @note address 0x711E80
	*/
	virtual bool CanUseWaypoint() const JMP_THIS(0x711E80);

	/*!
	* @brief
	* @note original_name Can_Attack_Move
	* @note vtable_index 41:0xA4
	* @note address 0x711E90
	*/
	virtual bool CanAttackMove() const JMP_THIS(0x711E90);

	/*!
	* @brief
	* @note original_name Legal_Placement
	* @note vtable_index 42:0xA8
	* @note address 0x716150
	*/
	virtual bool CanCreateHere(const CellStruct& mapCoords, HouseClass* pOwner) const JMP_THIS(0x716150);

	/*!
	* @brief
	* @note original_name Raw_Cost
	* @note vtable_index 43:0xAC
	* @note address 0x711EB0
	*/
	virtual int GetCost() const JMP_THIS(0x711EB0);

	/*!
	* @brief
	* @note original_name Repair_Cost
	* @note vtable_index 44:0xB0
	* @note address 0x7120D0
	*/
	virtual int GetRepairStepCost() const JMP_THIS(0x7120D0);

	/*!
	* @brief
	* @note original_name Repair_Step
	* @note vtable_index 45:0xB4
	* @note address 0x712120
	*/
	virtual int GetRepairStep() const JMP_THIS(0x712120);

	/*!
	* @brief
	* @note original_name Refund_Amount
	* @note vtable_index 46:0xB8
	* @note address 0x711F60
	*/
	virtual int GetRefund(HouseClass* pHouse, bool bUnk) const JMP_THIS(0x711F60);

	/*!
	* @brief
	* @note original_name Flight_Level
	* @note vtable_index 47:0xBC
	* @note address 0x717800
	*/
	virtual int GetFlightLevel() const JMP_THIS(0x717800);

	WeaponStruct* GetWeapon(int index) JMP_THIS(0x7177C0);
	WeaponStruct* GetEliteWeapon(int index) JMP_THIS(0x7177E0);
	int GetTurretWeapon(int index) JMP_THIS(0x7178B0);
	bool HasTurret() const JMP_THIS(0x717880);
	// looks like this function return true if weapon burst more than 1
	bool IsTwoShooter() JMP_THIS(0x712130);
	void SetPalette() JMP_THIS(0x717820);
	int SetPalettes() JMP_THIS(0x717840);
	void SetTurretWeapon(int index, int weapon) JMP_THIS(0x717890);

	static TechnoTypeClass* __fastcall GetByTypeAndIndex(AbstractType abs, int index) JMP_THIS(0x48DCD0);

	constexpr bool HasMultipleTurrets() const { return this->TurretCount > 0; }
	CoordStruct GetParticleSysOffset() const JMP_THIS(0x7178C0);

	bool InOwners(DWORD const bitHouseType) const { return 0u != (Ownable() & bitHouseType); }

	constexpr bool InRequiredHouses(DWORD const bitHouseType) const {
		auto const test = this->RequiredHouses;
		if(static_cast<int>(test) == -1) {
			return true;
		}
		return 0u != (test & bitHouseType);
	}
	constexpr bool InForbiddenHouses(DWORD const bitHouseType) const {
		auto const test = this->ForbiddenHouses;
		if(static_cast<int>(test) == -1) {
			return false;
		}
		return 0u != (test & bitHouseType);
	}

	static __declspec(noinline) TechnoTypeClass* __fastcall Find(const char* pID)
	{
		for (auto pItem : Array) {
			if (!_strcmpi(pItem->ID, pID)) {
				return pItem;
			}
		}
		return nullptr;
	}

	static __declspec(noinline) int __fastcall FindIndex(const char* pID)
	{
		for (int i = 0; i < Array.Count; ++i) {
			if (!_strcmpi(Array.Items[i]->get_ID(), pID)) {
				return i;
			}
		}
		return -1;
	}

	constexpr WeaponStruct& GetWeapon(size_t const index, bool const elite) { return elite ? this->EliteWeapon[index] : this->Weapon[index]; }
	constexpr WeaponStruct const& GetWeapon(size_t const index, bool const elite) const { return elite ? this->EliteWeapon[index] : this->Weapon[index]; }

protected:
	explicit __forceinline TechnoTypeClass(fake_noinit_t) noexcept : ObjectTypeClass(fake_noinit_t{}) {}
	TechnoTypeClass(noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) JMP_THIS(0x711840);
	TechnoTypeClass(const char* pId, ::SpeedType speed) : TechnoTypeClass(fake_noinit_t{}) JMP_THIS(0x710AF0);
};
static_assert(sizeof(TechnoTypeClass) == TechnoTypeClass::ClassSize);
