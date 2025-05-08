#pragma once

#include "AbstractClass.h"

class ObjectClass;
class TechnoClass;
class BuildingClass;
class BuildingTypeClass;
class UnitClass;
class InfantryClass;
class AircraftClass;
class TerrainClass;
class LightConvertClass;
class RadSiteClass;
class FootClass;
class TubeClass;
class FoggedObjectClass;
class TagClass;
class TiberiumClass;
class PixelFXClass;

class NOVTABLE CellClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E4EEC;
			this->IRTTITypeInfo = 0x7E4ED0;
			this->INoticeSink = 0x7E4EC8;
			this->INoticeSource = 0x7E4EC0;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7E4EEC;
	static constexpr AbstractType AbsID = AbstractType::Cell;
	static constexpr size_t ClassSize = 0x148;

public:
	static constexpr int BridgeLevels = 4;

	// the height of a bridge in leptons
	// see ABC5DC, AC13BC
	static constexpr int BridgeHeight = BridgeLevels * Unsorted::LevelHeight;

public:
	CellStruct MapCoords;	//Where on the map does this Cell lie?
	DynamicVectorClass<FoggedObjectClass*>* FoggedObjects;
	CellClass* BridgeOwnerCell;
	DWORD              unknown_30;
	LightConvertClass* LightConvert;
	int                IsoTileTypeIndex;	//What tile is this Cell?
	TagClass* AttachedTag;			// The cell tag
	BuildingTypeClass* Rubble;				// The building type that provides the rubble image
	int                OverlayTypeIndex;	//What Overlay lies on this Cell?
	int                SmudgeTypeIndex;	//What Smudge lies on this Cell?

	PassabilityType    Passability;
	int                WallOwnerIndex; // Which House owns the wall placed in this Cell?
	//                                 // Determined by finding the nearest BuildingType and taking its owner
	int                InfantryOwnerIndex;
	int                AltInfantryOwnerIndex;
	DWORD              unknown_5C;
	DWORD              unknown_60;
	DWORD              RedrawFrame;
	RectangleStruct    InViewportRect;
	//Is this cell in a cloak generator's radius? One bit per House.
	DWORD              CloakedByHouses;	
protected:
	// use Sensors_ funcs above
	// Is this cell in range of some SensorsSight= equipment? One Word(!) per House, ++ and -- per unit.
	// ! 24 houses instead of 32 like cloakgen
	unsigned short               SensorsOfHouses[0x18]; 

	// use DisguiseSensors_ funcs
	// Is this cell in range of some DetectDisguise= equipment? One Word(!) per House, ++ and -- per unit.
	// ! 24 houses instead of 32 like cloakgen
	unsigned short               DisguiseSensorsOfHouses[0x18]; 
public:
	DWORD              BaseSpacerOfHouses; // & (1 << HouseX->ArrayIndex) == base spacing dummy for HouseX
	FootClass* Jumpjet; // a jumpjet occupying this cell atm

	ObjectClass* FirstObject;	//The first Object on this Cell. NextObject functions as a linked list.
	ObjectClass* AltObject;

	LandType           LandType;	//What type of floor is this Cell?
	double             RadLevel;	//The level of radiation on this Cell.
	RadSiteClass* RadSite;	//A pointer to the responsible RadSite.

	PixelFXClass* PixelFX;
	int                OccupyHeightsCoveringMe;
	DWORD              Intensity;
	WORD               Ambient;
	WORD			   Intensity_Normal;
	WORD               Intensity_Terrain;
	WORD               Color1_Blue;
	//ColorStruct      Color2; //110-114
	WORD               Color2_Red;
	WORD               Color2_Green;
	WORD               Color2_Blue;
	signed short       TubeIndex; // !@#% Westwood braindamage, can't use > 127! (movsx eax, al)

	char               unknown_118;
	char               IsIceGrowthAllowed;
	char               Height;
	char               Level;

	BYTE               SlopeIndex;  // this + 2 == cell's slope shape as reflected by PLACE.SHP
	BYTE               unknown_11D;

	unsigned char      OverlayData;	//The crate type on this cell. Also indicates some other weird properties

	BYTE               SmudgeData;
	char               Visibility; // trust me, you don't wanna know... if you do, see 0x7F4194 and cry
	char               Foggedness; // same value as above: -2: Occluded completely, -1: Visible, 0...48: frame in fog.shp or shroud.shp
	BYTE               BlockedNeighbours; // number of somehow occupied cells next to this
	PROTECTED_PROPERTY(BYTE, align_123);

	// SubOccupations - 0x1 Center 0x2 Top(Abandoned) 0x4 Right 0x8 Left 0x10 Down / Terrains
	// 0x20 Units 0x40 Aircrafts 0x80 Buildings
	DWORD              OccupationFlags;
	DWORD              AltOccupationFlags;

	AltCellFlags	   AltFlags;	// related to Flags below
	int                ShroudCounter;
	DWORD              GapsCoveringThisCell; // actual count of gapgens in this cell, no idea why they need a second layer
	bool               VisibilityChanged;
	PROTECTED_PROPERTY(BYTE, align_139[0x3]);
	DWORD              unknown_13C;

	CellFlags          Flags;	//Various settings.
	PROTECTED_PROPERTY(BYTE, padding_144[4]);

public:
	virtual ~CellClass() JMP_THIS(0x47BB60);

	HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x485200);
	HRESULT Load(IStream* pStm) override JMP_THIS(0x4839F0);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x483C10);
	
	RTTIType KindOf() const override JMP_THIS(0x487E60);
	int SizeOf() const override JMP_THIS(0x487E70);

	Coordinate Center() const override JMP_THIS(0x486840);
	bool OnGround() const override JMP_THIS(0x4867E0);
	Coordinate TargetingCoord() const override JMP_THIS(0x486890);
public:
	constexpr TechnoClass* FindTechnoNearestTo(Point2D const& offsetPixel, bool alt, TechnoClass const* pExcludeThis = nullptr) const JMP_THIS(0x47C3D0);
	constexpr ObjectClass* FindObjectOfType(AbstractType abs, bool alt) const JMP_THIS(0x47C4D0);
	constexpr BuildingClass* GetBuilding() const JMP_THIS(0x47C520);
	constexpr UnitClass* GetUnit(bool alt) const JMP_THIS(0x47EBA0);
	constexpr InfantryClass* GetInfantry(bool alt) const JMP_THIS(0x47EC40);
	constexpr AircraftClass* GetAircraft(bool alt) const JMP_THIS(0x47EBF0);
	constexpr TerrainClass* GetTerrain(bool alt) const JMP_THIS(0x47C550);

	/* craziest thing... first iterates Content looking to Aircraft,
	 * failing that, calls FindTechnoNearestTo,
	 * if that fails too, reiterates Content looking for Terrain
	 */
	constexpr ObjectClass* GetSomeObject(const CoordStruct& coords, bool alt) const JMP_THIS(0x47C5A0);
	
	constexpr void SetWallOwner() JMP_THIS(0x47D210);

	constexpr void IncreaseShroudCounter() JMP_THIS(0x487690);
	constexpr void ReduceShroudCounter() JMP_THIS(0x487630);
	constexpr bool IsShrouded() const JMP_THIS(0x487950);
	constexpr void Unshroud() JMP_THIS(0x4876F0);
	constexpr RectangleStruct ShapeRect() JMP_THIS(0x47FDE0);
	// Check Fog maybe? 
	constexpr bool IsFogged() JMP_THIS(0x4879B0);
	constexpr void FogCell() JMP_THIS(0x486A70);
	constexpr void CleanFog() JMP_THIS(0x486BF0);
	constexpr void ClearFoggedObjects() JMP_THIS(0x486C50);
	// adjusts LAT
	constexpr void SetupLAT()  JMP_THIS(0x47CA80);

	// Recalculates cell attributes.
	// Checks for nearby cliff impassability, calls SetupLAT(), sets up TubeClass if tunnel, cell anim if attached etc.
	// Set cellLevel to -1 if you wish to not change it.
	constexpr void RecalcAttributes(int cellLevel) JMP_THIS(0x47D2B0);
	constexpr void BlowUpBridge() JMP_THIS(0x47DD70);

	constexpr bool CanThisExistHere(SpeedType SpeedType, BuildingTypeClass* pObject, HouseClass* pOwner) const JMP_THIS(0x47C620);
	// those unks are passed to TechnoClass::Scatter in that same order
	constexpr void ScatterContent(const CoordStruct &crd, bool ignoreMission, bool ignoreDestination, bool alt) JMP_THIS(0x481670);

	constexpr CellClass* GetNeighbourCell(FacingType facing) const JMP_THIS(0x481810);

	// called whenever anything moves, first to remove threat from source cell, second time to add threat to dest cell
	constexpr void UpdateThreat(unsigned int SourceHouse, int ThreatLevel) JMP_THIS(0x481870);
	constexpr void CollectCrate(FootClass* pCollector) JMP_THIS(0x481A00);

	constexpr void ProcessColourComponents(int* arg0, int* pIntensity, int* pAmbient, int* a5, int* a6, int* tintR, int* tintG, int* tintB) JMP_THIS(0x484180);
	constexpr TubeClass* GetTunnel() JMP_THIS(0x484F20);

	constexpr RectangleStruct* GetContainingRect(RectangleStruct* dest) const JMP_THIS(0x47FB90);

	// don't laugh, it returns the uiname of contained tiberium... which nobody ever sets
	constexpr const wchar_t* FullName() const JMP_THIS(0x484FF0);
	// returns whether a cell behaves as if it contained overlay (for gates and wall towers)
	constexpr bool ConnectsToOverlay(int idxOverlay = -1, int direction = -1) const JMP_THIS(0x480510);
	// returns the tiberium's index in OverlayTypes
	constexpr int GetContainedTiberiumIndex() const JMP_THIS(0x485010);
	constexpr int GetContainedTiberiumValue() const JMP_THIS(0x485020);
	constexpr bool SpreadTiberium(bool forced) JMP_THIS(0x483780);

	// add or create tiberium of the specified type
	constexpr bool IncreaseTiberium(int idxTiberium, int amount) JMP_THIS(0x487190);

	// decreases thze tiberium in the cell
	constexpr void ReduceTiberium(int amount) JMP_THIS(0x480A80);
	constexpr bool CanTiberiumGerminate(TiberiumClass* tib) JMP_THIS(0x4838E0);

	constexpr void SetMapCoords(CoordStruct const& coords) JMP_THIS(0x485240);
	constexpr int GetFloorHeight(Point2D const& subcoords) const JMP_THIS(0x47B3A0);

	// Factors in cell height from ramps, level etc.
	constexpr CoordStruct GetCellCoords() const JMP_THIS(0x480A30);

	constexpr void ActivateVeins() JMP_THIS(0x486920);

	// cloak generators
	constexpr bool CloakGen_InclHouse(unsigned int idx) const { return ((1 << idx) & this->CloakedByHouses) != 0; }
	constexpr void CloakGen_AddHouse(unsigned int idx) { this->CloakedByHouses |= 1 << idx; }
	constexpr void CloakGen_RemHouse(unsigned int idx) { this->CloakedByHouses &= ~(1 << idx); }

	// unused, returns 0 if that house doesn't have cloakgens covering this cell or Player has sensors over this cell
	bool DrawObjectsCloaked(int OwnerHouseIdx) const JMP_THIS(0x486800);

	// sensors
	constexpr bool Sensors_InclHouse(unsigned int idx) const { return this->SensorsOfHouses[idx] > 0; }
	constexpr void Sensors_AddOfHouse(unsigned int idx) { ++this->SensorsOfHouses[idx]; }
	constexpr void Sensors_RemOfHouse(unsigned int idx) { --this->SensorsOfHouses[idx]; }

	// disguise sensors
	constexpr bool DisguiseSensors_InclHouse(unsigned int idx) const { return this->DisguiseSensorsOfHouses[idx] > 0; }
	constexpr void DisguiseSensors_AddOfHouse(unsigned int idx) { ++this->DisguiseSensorsOfHouses[idx]; }
	constexpr void DisguiseSensors_RemOfHouse(unsigned int idx) 	{ --this->DisguiseSensorsOfHouses[idx]; }

	// Rad Sites
	constexpr void SetRadSite(RadSiteClass* pRad) { this->RadSite = pRad; }
	constexpr RadSiteClass* GetRadSite() const { return this->RadSite; }
	constexpr bool IsRadiated() const JMP_THIS(0x487C90);
	constexpr int GetRadLevel() const JMP_THIS(0x487CB0);
	constexpr void RadLevel_Increase(double amount) JMP_THIS(0x487CE0);
	constexpr void RadLevel_Decrease(double amount) JMP_THIS(0x487D00);

	// helper
	constexpr bool ContainsBridge() const { return static_cast<bool>(this->Flags & CellFlags::BridgeHead); }
	constexpr bool ContainsBridgeEx() const { return static_cast<bool>(this->Flags & CellFlags::Bridge); }

	// helper mimicking game's behaviour
	constexpr ObjectClass* GetContent() const { return this->ContainsBridge() ? this->AltObject : this->FirstObject; }
	constexpr int GetLevel() const { return this->Level + (this->ContainsBridge() ? BridgeLevels : 0); }

	// tilesets
#define ISTILE(tileset, addr) \
	constexpr bool Tile_Is_ ## tileset() const JMP_THIS(addr);

	ISTILE(Tunnel, 0x484AB0);
	ISTILE(Water, 0x485060);
	ISTILE(Blank, 0x486380);
	ISTILE(Ramp, 0x4863A0);
	ISTILE(Cliff, 0x4863D0);
	ISTILE(Shore, 0x4865B0);
	ISTILE(Wet, 0x4865D0);
	ISTILE(MiscPave, 0x486650);
	ISTILE(Pave, 0x486670);
	ISTILE(DirtRoad, 0x486690);
	ISTILE(PavedRoad, 0x4866D0);
	ISTILE(PavedRoadEnd, 0x4866F0);
	ISTILE(PavedRoadSlope, 0x486710);
	ISTILE(Median, 0x486730);
	ISTILE(Bridge, 0x486750);
	ISTILE(WoodBridge, 0x486770);
	ISTILE(ClearToSandLAT, 0x486790);
	ISTILE(Green, 0x4867B0);
	ISTILE(NotWater, 0x4867E0);
	ISTILE(DestroyableCliff, 0x486900);

	constexpr static CoordStruct Cell2Coord(CellStruct const& cell, int z = 0)
	{
		CoordStruct ret;
		ret.X = cell.X * 256 + 128;
		ret.Y = cell.Y * 256 + 128;
		ret.Z = z;
		return ret;
	}

	constexpr  static CellStruct Coord2Cell(CoordStruct const& crd)
	{
		CellStruct ret;
		ret.X = static_cast<short>(crd.X / 256);
		ret.Y = static_cast<short>(crd.Y / 256);
		return ret;
	}

	constexpr CoordStruct FixHeight(CoordStruct crd) const
	{
		if (this->ContainsBridge())
			crd.Z += BridgeHeight;

		return crd;
	}

	// helper - gets coords and fixes height for bridge
	constexpr  CoordStruct GetCoordsWithBridge() const
	{
		CoordStruct buffer = this->Center();
		return FixHeight(buffer);
	}

	constexpr  void MarkForRedraw() JMP_THIS(0x486E70);

	constexpr  void ChainReaction()
	{
		CellStruct* cell = &this->MapCoords;
		SET_REG32(ecx, cell);
		CALL(0x489270);
	}

	CoordStruct* FindInfantrySubposition(const CoordStruct& coords, bool ignoreContents, bool alt, bool useCellCoords) JMP_THIS(0x481180);

	constexpr bool TryAssignJumpjet(FootClass* pObject) JMP_THIS(0x487D70);
	constexpr void AddContent(ObjectClass* Content, bool onBridge) JMP_THIS(0x47E8A0);
	constexpr void RemoveContent(ObjectClass* pContent, bool onBridge) JMP_THIS(0x47EA90);
	constexpr void ReplaceTag(TagClass* pTag) JMP_THIS(0x485250)
	constexpr void UpdateCellLighting() JMP_THIS(0x484680); 
	constexpr void CalculateLightSourceLighting(int& nIntensity, int& nAmbient, int& Red1, int& Green1, int& Blue1, int& Red2, int& Green2, int& Blue2) JMP_THIS(0x484180);

	constexpr void InitLightConvert(LightConvertClass* pDrawer = nullptr, int nIntensity = 0x10000,
		int nAmbient = 0, int Red1 = 1000, int Green1 = 1000, int Blue1 = 1000) JMP_THIS(0x483E30);

	constexpr void DrawOverlay(const Point2D& Location, const RectangleStruct& Bound) JMP_THIS(0x47F6A0);
	constexpr void DrawOverlayShadow(const Point2D& Location, const RectangleStruct& Bound) JMP_THIS(0x47F510);
	constexpr bool IsClearToMove(SpeedType speedType, bool ignoreInfantry, bool ignoreVehicles, int zone, MovementZone movementZone, int level, bool isBridge) JMP_THIS(0x4834A0);

protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline CellClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	CellClass(noinit_t) : AbstractClass(fake_noinit_t{}) JMP_THIS(0x47B360);
	CellClass() : CellClass(fake_noinit_t{}) JMP_THIS(0x47BBF0);
};
static_assert(sizeof(CellClass) == CellClass::ClassSize);