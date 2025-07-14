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

class __declspec(uuid("C1BF99CE-1A8C-11D2-8175-006008055BB5"))
NOVTABLE CellClass : public AbstractClass
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

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x485200);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4839F0);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x483C10);
	
	RTTIType KindOf() const override JMP_THIS(0x487E60);
	int SizeOf() const override JMP_THIS(0x487E70);

	Coordinate Center() const override JMP_THIS(0x486840);
	bool OnGround() const override JMP_THIS(0x4867E0);
	Coordinate TargetingCoord() const override JMP_THIS(0x486890);
public:
	TechnoClass* FindTechnoNearestTo(Point2D const& offsetPixel, bool alt, TechnoClass const* pExcludeThis = nullptr) const JMP_THIS(0x47C3D0);
	ObjectClass* FindObjectOfType(AbstractType abs, bool alt) const JMP_THIS(0x47C4D0);
	BuildingClass* GetBuilding() const JMP_THIS(0x47C520);
	UnitClass* GetUnit(bool alt) const JMP_THIS(0x47EBA0);
	InfantryClass* GetInfantry(bool alt) const JMP_THIS(0x47EC40);
	AircraftClass* GetAircraft(bool alt) const JMP_THIS(0x47EBF0);
	TerrainClass* GetTerrain(bool alt) const JMP_THIS(0x47C550);

	/* craziest thing... first iterates Content looking to Aircraft,
	 * failing that, calls FindTechnoNearestTo,
	 * if that fails too, reiterates Content looking for Terrain
	 */
	ObjectClass* GetSomeObject(const CoordStruct& coords, bool alt) const JMP_THIS(0x47C5A0);
	
	void SetWallOwner() JMP_THIS(0x47D210);

	void IncreaseShroudCounter() JMP_THIS(0x487690);
	void ReduceShroudCounter() JMP_THIS(0x487630);
	bool IsShrouded() const JMP_THIS(0x487950);
	void Unshroud() JMP_THIS(0x4876F0);
	RectangleStruct ShapeRect() JMP_THIS(0x47FDE0);
	// Check Fog maybe? 
	bool IsFogged() JMP_THIS(0x4879B0);
	void FogCell() JMP_THIS(0x486A70);
	void CleanFog() JMP_THIS(0x486BF0);
	void ClearFoggedObjects() JMP_THIS(0x486C50);
	// adjusts LAT
	void SetupLAT()  JMP_THIS(0x47CA80);

	// Recalculates cell attributes.
	// Checks for nearby cliff impassability, calls SetupLAT(), sets up TubeClass if tunnel, cell anim if attached etc.
	// Set cellLevel to -1 if you wish to not change it.
	void RecalcAttributes(int cellLevel) JMP_THIS(0x47D2B0);
	void BlowUpBridge() JMP_THIS(0x47DD70);

	bool CanThisExistHere(SpeedType SpeedType, BuildingTypeClass* pObject, HouseClass* pOwner) const JMP_THIS(0x47C620);
	// those unks are passed to TechnoClass::Scatter in that same order
	void ScatterContent(const CoordStruct &crd, bool ignoreMission, bool ignoreDestination, bool alt) JMP_THIS(0x481670);

	CellClass* GetNeighbourCell(FacingType facing) const JMP_THIS(0x481810);

	// called whenever anything moves, first to remove threat from source cell, second time to add threat to dest cell
	void UpdateThreat(unsigned int SourceHouse, int ThreatLevel) JMP_THIS(0x481870);
	void CollectCrate(FootClass* pCollector) JMP_THIS(0x481A00);

	void ProcessColourComponents(int* arg0, int* pIntensity, int* pAmbient, int* a5, int* a6, int* tintR, int* tintG, int* tintB) JMP_THIS(0x484180);
	TubeClass* GetTunnel() JMP_THIS(0x484F20);

	RectangleStruct* GetContainingRect(RectangleStruct* dest) const JMP_THIS(0x47FB90);

	// don't laugh, it returns the uiname of contained tiberium... which nobody ever sets
	const wchar_t* FullName() const JMP_THIS(0x484FF0);
	// returns whether a cell behaves as if it contained overlay (for gates and wall towers)
	bool ConnectsToOverlay(int idxOverlay = -1, int direction = -1) const JMP_THIS(0x480510);
	// returns the tiberium's index in OverlayTypes
	int GetContainedTiberiumIndex() const JMP_THIS(0x485010);
	int GetContainedTiberiumValue() const JMP_THIS(0x485020);
	bool SpreadTiberium(bool forced) JMP_THIS(0x483780);

	// add or create tiberium of the specified type
	bool IncreaseTiberium(int idxTiberium, int amount) JMP_THIS(0x487190);

	// decreases thze tiberium in the cell
	void ReduceTiberium(int amount) JMP_THIS(0x480A80);
	bool CanTiberiumGerminate(TiberiumClass* tib) JMP_THIS(0x4838E0);

	void SetMapCoords(CoordStruct const& coords) JMP_THIS(0x485240);
	int GetFloorHeight(Point2D const& subcoords) const JMP_THIS(0x47B3A0);

	// Factors in cell height from ramps, level etc.
	CoordStruct GetCellCoords() const JMP_THIS(0x480A30);

	void ActivateVeins() JMP_THIS(0x486920);

	// cloak generators
	bool CloakGen_InclHouse(unsigned int idx) const { return ((1 << idx) & this->CloakedByHouses) != 0; }
	void CloakGen_AddHouse(unsigned int idx) { this->CloakedByHouses |= 1 << idx; }
	void CloakGen_RemHouse(unsigned int idx) { this->CloakedByHouses &= ~(1 << idx); }

	// unused, returns 0 if that house doesn't have cloakgens covering this cell or Player has sensors over this cell
	bool DrawObjectsCloaked(int OwnerHouseIdx) const JMP_THIS(0x486800);

	// sensors
	bool Sensors_InclHouse(unsigned int idx) const { return this->SensorsOfHouses[idx] > 0; }
	void Sensors_AddOfHouse(unsigned int idx) { ++this->SensorsOfHouses[idx]; }
	void Sensors_RemOfHouse(unsigned int idx) { --this->SensorsOfHouses[idx]; }

	// disguise sensors
	bool DisguiseSensors_InclHouse(unsigned int idx) const { return this->DisguiseSensorsOfHouses[idx] > 0; }
	void DisguiseSensors_AddOfHouse(unsigned int idx) { ++this->DisguiseSensorsOfHouses[idx]; }
	void DisguiseSensors_RemOfHouse(unsigned int idx) 	{ --this->DisguiseSensorsOfHouses[idx]; }

	// Rad Sites
	void SetRadSite(RadSiteClass* pRad) { this->RadSite = pRad; }
	RadSiteClass* GetRadSite() const { return this->RadSite; }
	bool IsRadiated() const JMP_THIS(0x487C90);
	int GetRadLevel() const JMP_THIS(0x487CB0);
	void RadLevel_Increase(double amount) JMP_THIS(0x487CE0);
	void RadLevel_Decrease(double amount) JMP_THIS(0x487D00);

	// helper
	bool ContainsBridge() const { return static_cast<bool>(this->Flags & CellFlags::BridgeHead); }
	bool ContainsBridgeEx() const { return static_cast<bool>(this->Flags & CellFlags::Bridge); }

	// helper mimicking game's behaviour
	ObjectClass* GetContent() const { return this->ContainsBridge() ? this->AltObject : this->FirstObject; }
	int GetLevel() const { return this->Level + (this->ContainsBridge() ? BridgeLevels : 0); }

	// tilesets
#define ISTILE(tileset, addr) \
	bool Tile_Is_ ## tileset() const JMP_THIS(addr);

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

	inline static CoordStruct Cell2Coord(CellStruct const& cell, int z = 0)
	{
		CoordStruct ret;
		ret.X = cell.X * 256 + 128;
		ret.Y = cell.Y * 256 + 128;
		ret.Z = z;
		return ret;
	}

	inline static CellStruct Coord2Cell(CoordStruct const& crd)
	{
		CellStruct ret;
		ret.X = static_cast<short>(crd.X / 256);
		ret.Y = static_cast<short>(crd.Y / 256);
		return ret;
	}

	inline CoordStruct FixHeight(CoordStruct crd) const
	{
		if (this->ContainsBridge())
			crd.Z += BridgeHeight;

		return crd;
	}

	// helper - gets coords and fixes height for bridge
	CoordStruct GetCoordsWithBridge() const
	{
		CoordStruct buffer = this->Center();
		return FixHeight(buffer);
	}

	void MarkForRedraw() JMP_THIS(0x486E70);

	void ChainReaction()
	{
		CellStruct* cell = &this->MapCoords;
		SET_REG32(ecx, cell);
		CALL(0x489270);
	}

	CoordStruct* FindInfantrySubposition(const CoordStruct& coords, bool ignoreContents, bool alt, bool useCellCoords) JMP_THIS(0x481180);

	bool TryAssignJumpjet(FootClass* pObject) JMP_THIS(0x487D70);
	void AddContent(ObjectClass* Content, bool onBridge) JMP_THIS(0x47E8A0);
	void RemoveContent(ObjectClass* pContent, bool onBridge) JMP_THIS(0x47EA90);
	void ReplaceTag(TagClass* pTag) JMP_THIS(0x485250)
	void UpdateCellLighting() JMP_THIS(0x484680); 
	void CalculateLightSourceLighting(int& nIntensity, int& nAmbient, int& Red1, int& Green1, int& Blue1, int& Red2, int& Green2, int& Blue2) JMP_THIS(0x484180);

	void InitLightConvert(LightConvertClass* pDrawer = nullptr, int nIntensity = 0x10000,
		int nAmbient = 0, int Red1 = 1000, int Green1 = 1000, int Blue1 = 1000) JMP_THIS(0x483E30);

	void DrawOverlay(const Point2D& Location, const RectangleStruct& Bound) JMP_THIS(0x47F6A0);
	void DrawOverlayShadow(const Point2D& Location, const RectangleStruct& Bound) JMP_THIS(0x47F510);
	bool IsClearToMove(SpeedType speedType, bool ignoreInfantry, bool ignoreVehicles, int zone, MovementZone movementZone, int level, bool isBridge) JMP_THIS(0x4834A0);

protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline CellClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	CellClass(noinit_t) noexcept : AbstractClass(fake_noinit_t{}) JMP_THIS(0x47B360);
	CellClass() : CellClass(fake_noinit_t{}) JMP_THIS(0x47BBF0);

/*
	CellClass * Adjacent_Cell(int32_t dir) JMP_THIS(0x481810);
	void Adjust_Threat(int32_t house, int32_t threat_value) JMP_THIS(0x481870);
	int32_t Attach_Tag(TagClass * celltag) JMP_THIS(0x485250);
	int8_t Can_Tiberium_Germinate(TiberiumClass * a2) JMP_THIS(0x4838E0);
	bool Can_Tiberium_Grow() JMP_THIS(0x483620);
	bool Can_Tiberium_Spread() JMP_THIS(0x483690);
	FootClass * Cell_Aircraft(bool check_alt) JMP_THIS(0x47EBF0);
	BuildingClass * Cell_Building() JMP_THIS(0x47C520);
	void Cell_Color(RGBClass * arg0, RGBClass * arg4) JMP_THIS(0x47C060);
	uint32_t Cell_Color_For_Minimap(uint8_t * a2, int8_t a3) JMP_THIS(0x47BDB0);
	Coordinate * Cell_Coord() JMP_THIS(0x480A30);
	FootClass * Cell_Find_Object(RTTIType rtti, int32_t check_alt) JMP_THIS(0x47C4D0);
	BuildingClass * Cell_Gate() JMP_THIS(0x4814A0);
	FootClass * Cell_Infantry(bool check_alt) JMP_THIS(0x47EC40);
	ObjectClass * Cell_Object(Point2D * a2, bool check_alt) JMP_THIS(0x47C5A0);
	int8_t Cell_Shadow_Update(int32_t a2, int32_t a3) JMP_THIS(0x4801F0);
	TechnoClass * Cell_Techno(Point2D * a2, bool check_alt, TechnoClass * techno) JMP_THIS(0x47C3D0);
	TerrainClass * Cell_Terrain(bool check_alt) JMP_THIS(0x47C550);
	FootClass * Cell_Unit(bool check_alt) JMP_THIS(0x47EBA0);
	CellClass * CellClass() JMP_THIS(0x47BBF0);
	void CellClass() JMP_THIS(0x47BB60);
	CellClass * CellClass(NoInitClass * x) JMP_THIS(0x47B360);
	void Check_Passability() JMP_THIS(0x483C80);
	Coordinate Closest_Free_Spot(Coordinate * a1, int8_t any, int8_t use_alt, int8_t substract_coord) JMP_THIS(0x481180);
	void Decrease_Rad_Level(double a2) JMP_THIS(0x487D00);
	void Destroy_Bridge_At() JMP_THIS(0x47DD70);
	void Detach(TechnoClass * a2) JMP_THIS(0x485130);
	void Draw_Fog(int32_t a1, int32_t a2, int32_t a4) JMP_THIS(0x47F250);
	int8_t Draw_It(Coordinate * coord, Rect * rect, bool blitbool) JMP_THIS(0x47EC90);
	void Draw_Overlay(int32_t a2, int32_t a6) JMP_THIS(0x47F6A0);
	void Draw_Overlay_Shadow(int32_t a3, int32_t a6) JMP_THIS(0x47F510);
	void Draw_Shadow_Cast(Point2D * a2, Rect * a3) JMP_THIS(0x4802A0);
	void Draw_Shroud(int32_t a1, int32_t a2, int32_t a4) JMP_THIS(0x47EFE0);
	void Draw_Tile(Point2D * a2, Rect * a3, int8_t a4) JMP_THIS(0x480350);
	void Draw_Tile_0(Point2D * a2, Rect * a3) JMP_THIS(0x480180);
	bool Flag_Place(int32_t house) JMP_THIS(0x483410);
	bool Flag_Remove() JMP_THIS(0x483460);
	int32_t Get_Rad_Level() JMP_THIS(0x487CB0);
	uint32_t Get_RadSite() JMP_THIS(0x487C80);
	int32_t Get_Tiberium_Type() JMP_THIS(0x485010);
	int32_t Get_Tiberium_Value() JMP_THIS(0x485020);
	Rect Get_Tile_Rect() JMP_THIS(0x47FF80);
	int32_t Get_Z_Offset(Point2D * a2) JMP_THIS(0x47B3A0);
	int32_t Get_Z_Pos_Adj() JMP_THIS(0x485080);
	int8_t Goodie_Check(FootClass * object) JMP_THIS(0x481A00);
	bool Grow_Tiberium() JMP_THIS(0x483710);
	bool Has_Tiberium() JMP_THIS(0x487DF0);
	void Incoming(Coordinate * threat, bool forced, bool nokidding, bool alt) JMP_THIS(0x481670);
	void Increase_Rad_Level(double a2) JMP_THIS(0x487CE0);
	void Init_Drawer(int32_t color2red, int32_t intensity, int32_t ambient, int32_t color1red, int32_t color1green, int32_t color1blue) JMP_THIS(0x483E30);
	int32_t Is_Bridge_Here() JMP_THIS(0x483610);
	bool Is_Buildable() JMP_THIS(0x487C10);
	bool Is_Clear_To_Build(SpeedType loco, BuildingTypeClass * a3, HouseClass * house) JMP_THIS(0x47C620);
	bool Is_Clear_To_Move(SpeedType loco, bool ignoreinfantry, bool ignorevehicles, int32_t zone, MZoneType check, int32_t level, bool bool1) JMP_THIS(0x4834A0);
	int8_t Is_Cliff() JMP_THIS(0x4863D0);
	bool Is_Desguise_Sensed(int32_t houseid) JMP_THIS(0x4870F0);
	int32_t Is_Irradiated() JMP_THIS(0x487C90);
	bool Is_Mapped() JMP_THIS(0x487950);
	bool Is_Median() JMP_THIS(0x486730);
	bool Is_Morphable() JMP_THIS(0x6B25C0);
	bool Is_PavedRoadSlope() JMP_THIS(0x486710);
	bool Is_ShorePieces() JMP_THIS(0x578D60);
	bool Is_Spot_Free(int32_t bit, int8_t check_alt) JMP_THIS(0x481130);
	void Overlap_Down(TerrainClass * a2, bool onbridge) JMP_THIS(0x47E8A0);
	void Overlap_Up(BuildingClass * object, bool use_alt) JMP_THIS(0x47EA90);
	bool Place_Tiberium_At_Cell(int32_t type, int32_t image) JMP_THIS(0x487190);
	void Recalc_Attributes(int32_t level) JMP_THIS(0x47D2B0);
	void redraw_cells1() JMP_THIS(0x485590);
	void redraw_cells2_veins() JMP_THIS(0x485AF0);
	int32_t Reduce_Tiberium(int32_t levels_reducer) JMP_THIS(0x480A80);
	int32_t Reduce_Wall(int32_t damage) JMP_THIS(0x480CB0);
	void SensedByHouses_deincriment(int32_t a2) JMP_THIS(0x487160);
	void SensedByHouses_incriment(int32_t a2) JMP_THIS(0x487150);
	void Set_Position(Cell * a2) JMP_THIS(0x485240);
	void Set_RadSite(RadSiteClass * a2) JMP_THIS(0x487C70);
	void Set_Wall_Owner() JMP_THIS(0x47D210);
	void Shimmer() JMP_THIS(0x483480);
	int32_t Spot_Index() JMP_THIS(0x4810A0);
	bool Spread_Tiberium(bool forced) JMP_THIS(0x483780);
	int32_t Tiberium_Adjust(bool pregame) JMP_THIS(0x4818E0);
	int32_t Tiberium_Name() JMP_THIS(0x484FF0);
	int32_t Tile_Variation(int32_t tiletype, int32_t a3) JMP_THIS(0x4814F0);
	void Trigger_Veins() JMP_THIS(0x486920);
	void Update_Lighting() JMP_THIS(0x484680);
	void UpdateVeins() JMP_THIS(0x486E30);
	bool Valid_Tube_Cell() JMP_THIS(0x484AB0);
	bool Wall_Check(int32_t overlay_type, int32_t a3) JMP_THIS(0x480510);
	void Wall_Update(bool a2) JMP_THIS(0x480630);
*/
};
static_assert(sizeof(CellClass) == CellClass::ClassSize);
