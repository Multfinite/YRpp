#pragma once

#include "GScreenClass.h"
#include "ArrayClasses.h"
#include "CellClass.h"
#include "AnimTypeClass.h"
#include "Timer.h"

class BulletTypeClass;
class ObjectClass;
class WarheadTypeClass;
class WeaponTypeClass;

// Terrain ground type
class GroundType
{
public:
	DEFINE_ARRAY_REFERENCE(GroundType, [12u], Array, 0x89EA40u)

	static LandType __fastcall GetLandTypeFromName(const char* name)
		{ JMP_STD(0x48DF80); }

	//Properties
	float Cost[8];  // Terrain speed multipliers.
	bool Buildable; // Can build on this terrain?
};

//Powerup crates
class Crate
{
public:
	//Properties
	CDTimerClass CrateTimer;
	::Cell Location;
};

struct CellLevelPassabilityStruct
{
	char CellPassability;
	char CellLevel;
	unsigned short ZoneArrayIndex;
};

struct LevelAndPassabilityStruct2
{
	__int16 word_0[4];
	char CellLevel;
	char field_9;
};

//ZoneConnectionClass - Holding zone connection info from tubes or bridges (probably used for pathfinding)
struct ZoneConnectionClass
{
	::Cell	FromMapCoords;
	::Cell	ToMapCoords;
	bool		unknown_bool_08;
	CellClass*	Cell;

	//need to define a == operator so it can be used in array classes
	bool operator==(const ZoneConnectionClass &other) const {
		return (FromMapCoords == other.FromMapCoords
			&& ToMapCoords == other.ToMapCoords
			&& unknown_bool_08 == other.unknown_bool_08
			&& Cell == other.Cell);
	}
};

struct SubzoneConnectionStruct
{
	DWORD unknown_dword_0;
	BYTE unknown_byte_4;

	//need to define a == operator so it can be used in array classes
	bool operator==(const SubzoneConnectionStruct &other) const {
		return (unknown_dword_0 == other.unknown_dword_0
			&& unknown_byte_4 == other.unknown_byte_4);
	}
};

struct SubzoneTrackingStruct
{
public:
	DynamicVectorClass<SubzoneConnectionStruct> SubzoneConnections;
	WORD unknown_word_18;
	DWORD unknown_dword_1C;
	DWORD unknown_dword_20;

	//need to define a == operator so it can be used in array classes
	bool operator==(const SubzoneTrackingStruct &other) const {
		return (unknown_word_18 != other.unknown_word_18
			&& unknown_dword_1C == other.unknown_dword_1C
			&& unknown_dword_20 == other.unknown_dword_20);
	}
};

// helper class with static methods to detect projectile collisions
class TrajectoryHelper
{
public:
	// whether the bullet hit a cliff when moving from pBefore to pAfter
	static bool __fastcall IsCliffHit(
		CellClass const* pSource, CellClass const* pBefore,
		CellClass const* pAfter)
	{ JMP_STD(0x4CC680); }

	// whether the bullet hit a wall when traversing through pCheck
	static bool __fastcall IsWallHit(
		CellClass const* pSource, CellClass const* pCheck,
		CellClass const* pTarget, HouseClass const* pOwner)
	{ JMP_STD(0x4CC6D0); }

	// returns the cell at crdCur if it contains an obstacle, nullptr otherwise
	static CellClass* __fastcall GetObstacle(
		CellClass const* pCellSource, CellClass const* pCellTarget,
		CellClass const* pCellBullet, Coordinate crdCur,
		BulletTypeClass const* pType, HouseClass const* pOwner)
	{ JMP_STD(0x4CC360); }

	// assumes linear movement, returns the first cell that has a cliff or wall
	// in it, a nullptr otherwise.
	static CellClass* __fastcall FindFirstObstacle(
		Coordinate const& crdSrc, Coordinate const& crdTarget,
		BulletTypeClass const* pType, HouseClass const* pOwner)
	{ JMP_STD(0x4CC100); }

	// if the warhead can destroy walls, walls don't count as obstacle
	static CellClass* __fastcall FindFirstImpenetrableObstacle(
		Coordinate const& crdSrc, Coordinate const& crdTarget,
		WeaponTypeClass const* pWeapon, HouseClass const* pOwner)
	{ JMP_STD(0x4CC310); }
};

class LayerClass : public DynamicVectorClass<ObjectClass*>
{
public:
	virtual bool AddObject(ObjectClass* pObject, bool sorted)
		{ JMP_THIS(0x5519B0); }

	virtual void RemoveAll()
		{ this->Clear(); }

	virtual void vt_entry_24()
		{ }

	void Load(IStream* pStm)
		{ JMP_THIS(0x551B90); }

	void Save(IStream* pStm)
		{ JMP_THIS(0x551B20); }

	void Sort()
		{ JMP_THIS(0x551A30); }
};

class LogicClass : public LayerClass
{
public:
	DEFINE_REFERENCE(LogicClass, Instance, 0x87F778u)

	virtual bool AddObject(ObjectClass* pObject, bool sorted) override
		{ JMP_THIS(0x55BAA0); }

	virtual void PointerGotInvalid(AbstractClass* pInvalid, bool removed)
		{ JMP_THIS(0x55B880); }

	void RemoveObject(ObjectClass* pObject)
		{ JMP_THIS(0x55BAE0); }

	void Update()
		{ JMP_THIS(0x55AFB0); }
};

class NOVTABLE MapClass : public GScreenClass
{
public:
	DEFINE_REFERENCE(MapClass, Instance, 0x87F7E8u)

	DEFINE_REFERENCE(CellClass, InvalidCell, 0xABDC50u)

	static const int MaxCells = 0x40000;

	// this actually points to 5 vectors, one for each layer
	DEFINE_ARRAY_REFERENCE(LayerClass, [5u], ObjectsInLayers, 0x8A0360u)

	/// <summary>
	/// Some sort of hardcoded constant lookup matrix with rows (0-8) representing CellClass Passability(Type) and columns are MovementZones, used to determine pathfinding behaviour.
	/// </summary>
	DEFINE_ARRAY_REFERENCE(int, [static_cast<size_t>(MovementZone::Count)][static_cast<size_t>(PassabilityType::Count)], MovementAdjustArray, 0x82A594u)

	static LayerClass* GetLayer(Layer lyr)
	{
		return (lyr >= Layer::Underground && lyr <= Layer::Top)
			? &ObjectsInLayers[static_cast<int>(lyr)]
			: nullptr;
	}

	//IGameMap
	virtual long __stdcall Is_Visible(::Cell cell) override R0;

	//Destructor
	virtual ~MapClass() RX;

	//MapClass
	virtual void AllocateCells() RX;
	virtual void DestructCells() RX;
	virtual void ConstructCells() RX;
	virtual void PointerGotInvalid(AbstractClass* ptr, bool bUnk) RX;
	virtual bool DraggingInProgress() R0;
	virtual void UpdateCrates() RX;
	virtual void CreateEmptyMap(const RectangleStruct& mapRect, bool reuse, char nLevel, bool bUnk2) RX;
	virtual void SetVisibleRect(const RectangleStruct& mapRect) RX;

	//Non-virtual
	CellClass* TryGetCellAt(const ::Cell& MapCoords) const {
		int idx = GetCellIndex(MapCoords);
		return (idx >= 0 && idx < MaxCells) ? Cells[idx] : nullptr;
	}

	CellClass* TryGetCellAt(const Coordinate& Crd) const {
		::Cell cell = CellClass::Coord2Cell(Crd);
		return TryGetCellAt(cell);
	}

	CellClass* GetCellAt(const ::Cell &MapCoords) const {
		auto pCell = TryGetCellAt(MapCoords);

		if(!pCell) {
			pCell = &InvalidCell;
			pCell->MapCoords = MapCoords;
		}

		return pCell;
	}

	CellClass* GetCellAt(const Coordinate &Crd) const {
		::Cell cell = CellClass::Coord2Cell(Crd);
		return GetCellAt(cell);
	}

	CellClass* GetTargetCell(Point2D& location)
		{ JMP_THIS(0x565730); }

	bool CellExists(const ::Cell &MapCoords) const {
		return TryGetCellAt(MapCoords) != nullptr;
	}

	int GetThreatPosed(const ::Cell& cell, HouseClass* pHouse) const
		{ JMP_THIS(0x56BCD0); }

	bool IsLocationShrouded(const Coordinate &crd) const
		{ JMP_THIS(0x586360); }

	static int GetCellIndex(const ::Cell &MapCoords) {
		return (MapCoords.Y << 9) + MapCoords.X;
	}

	// gets a coordinate in a random direction a fixed distance in leptons away from coords
	static Coordinate* __fastcall __GetRandomCoordsNear(Coordinate* retstr, const Coordinate &coords, int distance, bool center) {
		JMP_STD(0x49F420);
	}

	// gets a coordinate in a random direction a fixed distance in leptons away from coords
	static Coordinate GetRandomCoordsNear(const Coordinate &coords, int distance, bool center) {
		Coordinate ret;
		__GetRandomCoordsNear(&ret, coords, distance, center);
		return ret;
	}

	static Coordinate* __stdcall __PickInfantrySublocation(Coordinate* retstr, const Coordinate &coords, bool ignoreContents = false)
		{ JMP_STD(0x4ACA10); }

	static Coordinate PickInfantrySublocation(const Coordinate &coords, bool ignoreContents = false) {
		Coordinate retstr;
		__PickInfantrySublocation(&retstr, coords, ignoreContents);
		return retstr;
	}

	static void __fastcall UnselectAll()
		{ JMP_STD(0x48DC90); }

	void CenterMap()
		{ JMP_THIS(0x4AE290); }

	void CellIteratorReset()
		{ CALL(0x578350); }

	CellClass* CellIteratorNext()
		{ CALL(0x578290); }

	int GetMovementZoneType(const ::Cell& MapCoords, MovementZone movementZone, bool isBridge)
		{ JMP_THIS(0x56D230); }

// the key damage delivery
/*! The key damage delivery function.
	\param Coords Location of the impact/center of damage.
	\param Damage Amount of damage to deal.
	\param SourceObject The object which caused the damage to be delivered (iow, the shooter).
	\param WH The warhead to use to apply the damage.
	\param AffectsTiberium If this is false, Tiberium=yes is ignored.
	\param SourceHouse The house to which SourceObject belongs, the owner/bringer of damage.
*/
	static DamageAreaResult __fastcall DamageArea(
		const Coordinate& Coords,
		int Damage,
		TechnoClass* SourceObject,
		WarheadTypeClass *WH,
		bool AffectsTiberium,
		HouseClass* SourceHouse)
			{ JMP_STD(0x489280); }

	/*
	 * Picks the appropriate anim from WH's AnimList= based on damage dealt and land type (Conventional= )
	 * so after DamageArea:
	 * if(AnimTypeClass *damageAnimType = SelectDamageAnimation(...)) {
	 * 	GameCreate<AnimClass>(damageAnimType, location);
	 * }
	 */
	static AnimTypeClass * __fastcall SelectDamageAnimation
		(int Damage, WarheadTypeClass *WH, LandType LandType, const Coordinate& coords)
			{ JMP_STD(0x48A4F0); }

	static void __fastcall FlashbangWarheadAt
		(int Damage, WarheadTypeClass *WH, Coordinate coords, bool Force = 0, SpotlightFlags CLDisableFlags = SpotlightFlags::None)
			{JMP_STD(0x48A620); }

	// get the damage a warhead causes to specific armor
	static int __fastcall GetTotalDamage(int damage, const WarheadTypeClass* pWarhead, Armor armor, int distance)
		{ JMP_STD(0x489180); }

	int GetCellFloorHeight(const Coordinate& crd) const
		{ JMP_THIS(0x578080); }

	::Cell * __PickCellOnEdge(::Cell* retstr, Edge Edge, const ::Cell &CurrentLocation, const ::Cell &Fallback,
		SpeedType SpeedType, bool ValidateReachability, MovementZone MovZone) const
			{ JMP_THIS(0x4AA440); }

	::Cell PickCellOnEdge(Edge Edge, const ::Cell &CurrentLocation, const ::Cell &Fallback,
		SpeedType SpeedType, bool ValidateReachability, MovementZone MovZone) const
	{
		::Cell ret;
		__PickCellOnEdge(&ret, Edge, CurrentLocation, Fallback, SpeedType, ValidateReachability, MovZone);
		return ret;
	}

// Pathfinding voodoo
// do not touch them, mmkay, they trigger ZoneConnection recalc which is a MUST for firestorm to work

	void Update_Pathfinding_1()
		{ JMP_THIS(0x56C510); }

	void Update_Pathfinding_2(const DynamicVectorClass<::Cell> &where)
		{ JMP_THIS(0x586990); }

	// Find nearest spot
	::Cell* __NearByLocation(::Cell& retstr, const ::Cell &position, SpeedType SpeedType, int a5, MovementZone MovementZone, bool alt, int SpaceSizeX, int SpaceSizeY, bool disallowOverlay, bool a11, bool requireBurrowable, bool allowBridge, const ::Cell &closeTo, bool a15, bool buildable)
		{ JMP_THIS(0x56DC20); }

	::Cell NearByLocation(const ::Cell &position, SpeedType SpeedType, int a5, MovementZone MovementZone, bool alt, int SpaceSizeX, int SpaceSizeY, bool disallowOverlay, bool a11, bool requireBurrowable, bool allowBridge, const ::Cell &closeTo, bool a15, bool buildable) {
		::Cell ret;
		__NearByLocation(ret, position, SpeedType, a5, MovementZone, alt, SpaceSizeX, SpaceSizeY, disallowOverlay, a11, requireBurrowable, allowBridge, closeTo, a15, buildable);
		return ret;
	}

	void  AddContentAt(::Cell *coords, TechnoClass *Content)
		{ JMP_THIS(0x5683C0); }

	void  RemoveContentAt(::Cell *coords, TechnoClass *Content)
		{ JMP_THIS(0x5687F0); }


	bool IsWithinUsableArea(const ::Cell& cell, bool checkLevel) const
		{ JMP_THIS(0x578460); }

	bool IsWithinUsableArea(CellClass* pCell, bool checkLevel) const
		{ JMP_THIS(0x578540); }

	bool IsWithinUsableArea(const Coordinate& coords) const
		{ JMP_THIS(0x5785F0); }

	bool CoordinatesLegal(const ::Cell& cell) const
		{ JMP_THIS(0x568300); }

	bool IsLinkedBridgeDestroyed(const ::Cell& cell) const
		{ JMP_THIS(0x587410); }

	bool PlacePowerupCrate(::Cell cell, Powerup type)
		{ JMP_THIS(0x56BEC0); }

// ====================================
//         FIRESTORM RELATED
// ====================================

	Coordinate* __FindFirstFirestorm(
		Coordinate* retstr, const Coordinate& start,
		const Coordinate& end, HouseClass const* pHouse = nullptr) const
	{ JMP_THIS(0x5880A0); }

	Coordinate FindFirstFirestorm(
		const Coordinate& start, const Coordinate& end,
		HouseClass const* pHouse = nullptr) const
	{
		Coordinate ret;
		__FindFirstFirestorm(&ret, start, end, pHouse);
		return ret;
	}

// ====================================
//        MAP REVEAL BRAINDAMAGE
// ====================================

/*
 * TechnoClass::Fire uses this for RevealOnFire on player's own units (radius = 3)
 * TechnoClass::See uses this on all (singleCampaign || !MultiplayPassive) units
 * TalkBubble uses this to display the unit to the player
 */
	void RevealArea1(
		Coordinate* Coords,
		int Radius,
		HouseClass* OwnerHouse,
		::Cell arg4,
		BYTE RevealByHeight,
		BYTE arg6,
		BYTE arg7,
		BYTE arg8)
			{ JMP_THIS(0x5673A0); }

/*
 * these come in pairs - first the last argument is 0 and then 1

 * AircraftClass::Fire - reveal the target area to the owner (0,0,0,1,x)
 * AircraftClass::See - reveal shroud when on the ground (arg,arg,0,1,x), and fog always (0,0,1,(height < flightlevel/2),x)
 * AnimClass::AnimClass - reveal area to player if anim->Type = [General]DropZoneAnim= (radius = Rules->DropZoneRadius /256) (0,0,0,1,x)
 * BuildingClass::Place - reveal (r = 1) to player if this is ToTile and owned by player (0,0,0,1,x)
 * BuildingClass::Unlimbo - reveal (radius = this->Type->Sight ) to owner (0,0,0,1,x)
 * PsychicReveal launch - reveal to user (0,0,0,0,x)
 * ActionClass::RevealWaypoint - reveal RevealTriggerRadius= to player (0,0,0,1,x)
 * ActionClass::RevealZoneOfWaypoint - reveal (r = 2) to player (0,0,0,1,x)
 */
	void RevealArea2(
		Coordinate* Coords,
		int Radius,
		HouseClass* OwnerHouse,
		DWORD /*::Cell*/ arg4,
		BYTE RevealByHeight,
		BYTE arg6,
		BYTE arg7,
		BYTE arg8)
			{ JMP_THIS(0x5678E0); }

/*
 * AircraftClass::SpyPlaneApproach
 * AircraftClass::SpyPlaneOverfly
 * AircraftClass::Carryall_Unload
 * BuildingClass::Place - RevealToAll
 * Foot/Infantry Class::Update/UpdatePosition
 * MapClass::RevealArea0 calls this to do the work
 * ParasiteClass::Infect/PointerGotInvalid
 * TechnoClass::Unlimbo
 * TechnoClass::Fire uses this (r = 4) right after using RevealArea0, wtfcock
 */
	void RevealArea3(Coordinate *Coords, int Height, int Radius, bool SkipReveal)
		{ JMP_THIS(0x567DA0); }

	void Reveal(HouseClass* pHouse)
		{ JMP_THIS(0x577D90); }

	void Reshroud(HouseClass* pHouse)
		{ JMP_THIS(0x577AB0); }

	int GetZPos(Coordinate *Coords)
		{ JMP_THIS(0x578080); }

	// these two VERY slowly reprocess the map after gapgen state changes
	void sub_657CE0()
		{ JMP_THIS(0x657CE0); }

	void RedrawSidebar(int mode)
		{ JMP_THIS(0x4F42F0); }

	ObjectClass* NextObject(ObjectClass* pCurrentObject)
		{ JMP_THIS(0x4AA2B0); }

	void SetTogglePowerMode(int mode)
		{ JMP_THIS(0x4AC820); }

	void SetPlaceBeaconMode(int mode)
		{ JMP_THIS(0x4AC960); }

	void SetSellMode(int mode)
		{ JMP_THIS(0x4AC660); }

	void SetWaypointMode(int mode, bool somebool)
		{ JMP_THIS(0x4AC700); }

	void SetRepairMode(int mode)
		{ JMP_THIS(0x4AC8C0); }

	void DestroyCliff(CellClass *Cell)
		{ JMP_THIS(0x581140); }

	bool IsLocationFogged(const Coordinate& coord)
		{ JMP_THIS(0x5865E0); }
	bool IsLocationFogged(Coordinate&& coord)
		{ return IsLocationFogged(coord); }

	void RevealCheck(CellClass* pCell, HouseClass* pHouse, bool bUnk)
		{ JMP_THIS(0x5865F0); }

	// returns false if visitor should wait for a gate to open, true otherwise
	bool MakeTraversable(ObjectClass const* pVisitor, ::Cell const& cell) const
		{ JMP_THIS(0x578AD0); }

	void BuildingToFirestormWall(::Cell const& cell,HouseClass* pHouse,BuildingTypeClass* pBldType)
		{ JMP_THIS(0x588570); }

	void BuildingToWall(::Cell const& cell, HouseClass* pHouse, BuildingTypeClass* pBldType)
		{ JMP_THIS(0x588750); }

	// Called on wall state updates etc. when the wall hasn't been removed.
	void RecalculateZones(::Cell const& cell)
		{ JMP_THIS(0x56D5A0);}

	// Called on wall state updates etc. when the wall HAS been removed.
	void ResetZones(::Cell const& cell)
	{ JMP_THIS(0x56D460); }

	// Called on wall state updates etc
	void RecalculateSubZones(::Cell const& cell)
	{ JMP_THIS(0x584550); }


protected:
	//Constructor
	MapClass() {}	//don't need this

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:
	DWORD unknown_10;
	void* unknown_pointer_14;
	void* MovementZones [13];
	DWORD somecount_4C;
	DynamicVectorClass<ZoneConnectionClass> ZoneConnections;
	CellLevelPassabilityStruct* LevelAndPassability;
	int ValidMapCellCount;
	LevelAndPassabilityStruct2* LevelAndPassabilityStruct2pointer_70;
	DWORD unknown_74;
	DWORD unknown_78;
	DWORD unknown_7C;
	DWORD unknown_80[3]; // somehow connected to the 3 vectors below
	DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking1;
	DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking2;
	DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking3;
	DynamicVectorClass<::Cell> CellStructs1;
	RectangleStruct MapRect;
	RectangleStruct VisibleRect;
	int CellIterator_NextX;
	int CellIterator_NextY;
	int CellIterator_CurrentY;
	CellClass* CellIterator_NextCell;
	int ZoneIterator_X;
	int ZoneIterator_Y;
	LTRBStruct MapCoordBounds; // the minimum and maximum cell struct values
	int TotalValue;
	VectorClass<CellClass*> Cells;
	int MaxLevel;
	int MaxWidth;
	int MaxHeight;
	int MaxNumCells;
	Crate Crates [0x100];
	BOOL Redraws;
	DynamicVectorClass<::Cell> TaggedCells;
};
