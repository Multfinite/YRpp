#pragma once

#include "TechnoTypeClass.h"

class OverlayTypeClass;
class IsometricTileTypeClass;

struct BuildingAnimStruct
{
	char Anim[0x10];
	char Damaged[0x10];
	char Garrisoned[0x10];
	Point2D Position;
	int ZAdjust;
	int YSort;
	bool Powered;
	bool PoweredLight;
	bool PoweredEffect;
	bool PoweredSpecial;
};

struct BuildingAnimFrameStruct
{
	DWORD dwUnknown;
	int FrameCount;
	int FrameDuration;
};

class __declspec(uuid("AE8B33DB-061C-11D2-ACA4-006008055BB5"))
NOVTABLE BuildingTypeClass : public TechnoTypeClass
{
public:
	using base_type = TechnoTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E4570;
			this->IRTTITypeInfo = 0x7E4554;
			this->INoticeSink = 0x7E454C;
			this->INoticeSource = 0x7E4544;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::BuildingType;
	static constexpr uintptr_t AbsVTable = 0x7E4570;
	static constexpr size_t ClassSize = 0x1798;

	ABSTRACTTYPE_ARRAY(BuildingTypeClass, 0xA83C68u);
public:
	int ArrayIndex;
	CellStruct* FoundationData;
	SHPStruct* Buildup;
	bool BuildupLoaded;
	BuildCat BuildCat;
	CoordStruct HalfDamageSmokeLocation1;
	CoordStruct HalfDamageSmokeLocation2;
	DWORD align_E24;
	double GateCloseDelay;
	int LightVisibility;
	int LightIntensity;
	int LightRedTint;
	int LightGreenTint;
	int LightBlueTint;
	Point2D PrimaryFirePixelOffset;
	Point2D SecondaryFirePixelOffset;
	OverlayTypeClass* ToOverlay;
	IsometricTileTypeClass* ToTile;
	char BuildupFile[0x10];
	int BuildupSound;
	int PackupSound;
	int CreateUnitSound;
	int UnitEnterSound;
	int UnitExitSound;
	int WorkingSound;
	int NotWorkingSound;
	char PowersUpBuilding[0x18];
	UnitTypeClass* FreeUnit;
	InfantryTypeClass* SecretInfantry;
	UnitTypeClass* SecretUnit;
	BuildingTypeClass* SecretBuilding;
	int field_EB0;
	int Adjacent;
	AbstractType Factory;
	CoordStruct TargetCoordOffset;
	CoordStruct ExitCoord;
	CellStruct* FoundationOutside;
	int field_ED8;
	int DeployFacing;
	int PowerBonus;
	int PowerDrain;
	int ExtraPowerBonus;
	int ExtraPowerDrain;
	Foundation Foundation;
	int Height;
	int OccupyHeight;
	int MidPoint;
	int DoorStages;

	BuildingAnimFrameStruct BuildingAnimFrame[6];

	BuildingAnimStruct BuildingAnim[0x15];

	int Upgrades;
	SHPStruct* DeployingAnim;
	bool DeployingAnimLoaded;
	SHPStruct* UnderDoorAnim;
	bool UnderDoorAnimLoaded;
	SHPStruct* Rubble;
	bool RubbleLoaded;
	SHPStruct* RoofDeployingAnim;
	bool RoofDeployingAnimLoaded;
	SHPStruct* UnderRoofDoorAnim;
	bool UnderRoofDoorAnimLoaded;
	SHPStruct* DoorAnim;
	SHPStruct* SpecialZOverlay;
	int SpecialZOverlayZAdjust;
	SHPStruct* BibShape;
	bool BibShapeLoaded;
	int NormalZAdjust;
	int AntiAirValue;
	int AntiArmorValue;
	int AntiInfantryValue;
	Point2D ZShapePointMove;
	RectangleStruct unknown_1538;
	WORD ExtraLight;
	bool TogglePower;
	bool HasSpotlight;
	bool IsTemple;
	bool IsPlug;
	bool HoverPad;
	bool BaseNormal;
	bool EligibileForAllyBuilding;
	bool EligibleForDelayKill;
	bool NeedsEngineer;
	int CaptureEvaEvent;
	int ProduceCashStartup;
	int ProduceCashAmount;
	int ProduceCashDelay;
	int InfantryGainSelfHeal;
	int UnitsGainSelfHeal;
	int RefinerySmokeFrames;
	bool Bib;
	bool Wall;
	bool Capturable;
	bool Powered;
	bool PoweredSpecial;
	bool Overpowerable;
	bool Spyable;
	bool CanC4;
	bool WantsExtraSpace;
	bool Unsellable;
	bool ClickRepairable;
	bool CanBeOccupied;
	bool CanOccupyFire;
	int MaxNumberOccupants;
	bool ShowOccupantPips;

	Point2D MuzzleFlash[0xA];

	Point2D DamageFireOffset[8];

	Point2D QueueingCell;
	int NumberImpassableRows;

	Point2D RemoveOccupy[8];

	Point2D AddOccupy[8];

	bool Radar;
	bool SpySat;
	bool ChargeAnim;
	bool IsAnimDelayedFire;
	bool SiloDamage;
	bool UnitRepair;
	bool UnitReload;
	bool Bunker;
	bool Cloning;
	bool Grinding;
	bool UnitAbsorb;
	bool InfantryAbsorb;
	bool SecretLab;
	bool DoubleThick;
	bool Flat;
	bool DockUnload;
	bool Recoilless;
	bool HasStupidGuardMode;
	bool BridgeRepairHut;
	bool Gate;
	bool SAM;
	bool ConstructionYard;
	bool NukeSilo;
	bool Refinery;
	bool Weeder;
	bool WeaponsFactory;
	bool LaserFencePost;
	bool LaserFence;
	bool FirestormWall;
	bool Hospital;
	bool Armory;
	bool EMPulseCannon;
	bool TickTank;
	bool TurretAnimIsVoxel;
	bool BarrelAnimIsVoxel;
	bool CloakGenerator;
	bool SensorArray;
	bool ICBMLauncher;
	bool Artillary;
	bool Helipad;
	bool OrePurifier;
	bool FactoryPlant;
	float InfantryCostBonus;
	float UnitsCostBonus;
	float AircraftCostBonus;
	float BuildingsCostBonus;
	float DefensesCostBonus;
	bool GDIBarracks;
	bool NODBarracks;
	bool YuriBarracks;
	float ChargedAnimTime;
	int DelayedFireDelay;
	int SuperWeapon;
	int SuperWeapon2;
	int GateStages;
	int PowersUpToLevel;
	bool DamagedDoor;
	bool InvisibleInGame;
	bool TerrainPalette;
	bool PlaceAnywhere;
	bool ExtraDamageStage;
	bool AIBuildThis;
	bool IsBaseDefense;
	BYTE CloakRadiusInCells;
	bool ConcentricRadialIndicator;
	int PsychicDetectionRadius;
	int BarrelStartPitch;
	char VoxelBarrelFile[0x1C];
	CoordStruct VoxelBarrelOffsetToPitchPivotPoint;
	CoordStruct VoxelBarrelOffsetToRotatePivotPoint;
	CoordStruct VoxelBarrelOffsetToBuildingPivotPoint;
	CoordStruct VoxelBarrelOffsetToBarrelEnd;
	bool DemandLoad;
	bool DemandLoadBuildup;
	bool FreeBuildup;
	bool IsThreatRatingNode;
	bool PrimaryFireDualOffset;
	bool ProtectWithWall;
	bool CanHideThings;
	bool CrateBeneath;
	bool LeaveRubble;
	bool CrateBeneathIsMoney;
	char TheaterSpecificID[0x13];
	int NumberOfDocks;
	VectorClass<CoordStruct> DockingOffsets;
protected: DWORD align_1794;
public:
	virtual ~BuildingTypeClass() JMP_THIS(0x45E580);

	HRESULT __stdcall GetClassID(CLSID* pClassID) JMP_STD(0x465380);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x465010);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x465300);

	RTTIType KindOf() const override JMP_THIS(0x465D90);
	int SizeOf() const override JMP_THIS(0x465DA0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x464B30);
	int GetArrayIndex() const override JMP_THIS(0x465DB0);
	
	bool LoadFromINI(CCINIClass* ini) override JMP_THIS(0x45FE50);

	Coordinate* __FixupCoord(Coordinate* retstr, Coordinate& coord) const override JMP_THIS(0x464A70);
	int MaxPips() const override JMP_THIS(0x45ECE0);
	Point3D* __PixelDimensions(Point3D* retstr) const override JMP_THIS(0x45EBD0);
	Point3D* __LeptonDimensions(Point3D* retstr) const override JMP_THIS(0x464AF0);
	bool CreateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x45E800);
	int CostOf(HouseClass* pHouse) const override JMP_THIS(0x45EDD0);
	ObjectClass* Create(HouseClass* pOwner) override JMP_THIS(0x45E880);
	CellStruct* OccupiedCells(bool placement) const override JMP_THIS(0x45EC20);
	SHPStruct* GetImage() const override JMP_THIS(0x45F040);

	bool CanUseWaypoint() const override JMP_THIS(0x465910);
	bool CanAttackMove() const override JMP_THIS(0x465920);
	bool CanCreateHere(const CellStruct& mapCoords, HouseClass* pOwner) const override JMP_THIS(0x464AC0);
	int GetCost() const override JMP_THIS(0x45ED50);

	virtual SHPStruct* LoadBuildup() JMP_THIS(0x465960);

	void ClearBuildUp() JMP_THIS(0x465AF0);
	bool IsVehicle() const JMP_THIS(0x465D40);

	short GetFoundationWidth() const JMP_THIS(0x45EC90);
	short GetFoundationHeight(bool bIncludeBib) const JMP_THIS(0x45ECA0);

	bool HasSuperWeapon(int index) const { return (this->SuperWeapon == index || this->SuperWeapon2 == index); }
	bool HasSuperWeapon() const { return (this->SuperWeapon != -1 || this->SuperWeapon2 != -1); }
	bool CanTogglePower() const { return this->TogglePower && (this->PowerDrain > 0 || this->Powered); }
	BuildingAnimStruct& GetBuildingAnim(BuildingAnimSlot slot) { return this->BuildingAnim[static_cast<int>(slot)]; }
	const BuildingAnimStruct& GetBuildingAnim(BuildingAnimSlot slot) const { return this->BuildingAnim[static_cast<int>(slot)]; }

protected:
	explicit __forceinline BuildingTypeClass(fake_noinit_t) noexcept : TechnoTypeClass(fake_noinit_t{}) {}
public:
	BuildingTypeClass(noinit_t) noexcept : BuildingTypeClass(fake_noinit_t{}) JMP_THIS(0x45E520);
	BuildingTypeClass(const char* pId) : BuildingTypeClass(fake_noinit_t{}) JMP_THIS(0x45DD90);
};
static_assert(sizeof(BuildingTypeClass) == BuildingTypeClass::ClassSize);
