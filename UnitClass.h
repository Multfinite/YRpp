/*
	Ground & Naval Vehicles
*/

#pragma once

#include "FootClass.h"
#include "UnitTypeClass.h"

//forward declarations
class EBolt;

class NOVTABLE UnitClass : public FootClass
{
public:
	static constexpr AbstractType AbsID = AbstractType::Unit;
	static constexpr uintptr_t AbsVTable = 0x7F5C70;
	static constexpr size_t ClassSize = 0x8E8;

	//Static
	static constexpr constant_ptr<DynamicVectorClass<UnitClass*>, 0x8B4108u> const Array{};
public:
	int counter_6C0;
	UnitTypeClass* Type;
	// groovy - link defined in the map's [Units] section, looked up on startup
	UnitClass* FollowerCar;
	// Carrying the flag of this House
	int FlagHouseIndex;
	// This vehicle is another vehicle's FollowerCar (such as a train car following train).
	bool IsFollowerCar;
	bool Unloading;
	bool IsHarvesting;
	bool TerrainPalette;
	int Visceroid_direction;
	int DeathFrameCounter;
	//Unit is the owner of this
	EBolt* ElectricBolt;
	bool Deployed;
	bool Deploying;
	bool Undeploying;
	// // Set when unloading passengers. Units with TurretCount>0 will not unload the gunner.
	int NonPassengerCount;

	wchar_t ToolTipText[0x100];
public:
	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_THIS(0x746DE0);
	HRESULT __stdcall Load(IStream* pStm)  override JMP_THIS(0x744470);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x744600);

	virtual ~UnitClass() JMP_THIS(0x735780);

	/*0:0x0*/virtual void UnitClass_sink_746100() JMP_THIS(0x746100);

	void Init() override JMP_THIS(0x746810);
	void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x7446E0);
	RTTIType KindOf() const override JMP_THIS(0x746E20);
	int SizeOf() const override JMP_THIS(0x746DD0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x744640);
	void AI() override JMP_THIS(0x7360C0);

	Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x7404B0);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x73FD50);
	bool IsStrange() const override JMP_THIS(0x746400);
	ObjectTypeClass* Type() const override JMP_THIS(0x741490);
	const wchar_t* FullName() const override JMP_THIS(0x746B20);
	bool IsDisguisedAs(HouseClass* target) const override JMP_THIS(0x746750);
	ObjectTypeClass* Disguise(bool disguisedAgainstAllies) const override JMP_THIS(0x7465B0);
	HouseClass* DisguiseHouse(bool disguisedAgainstAllies) const override JMP_THIS(0x7465F0);
	bool Limbo() override JMP_THIS(0x7440B0);
	bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x737BA0);
	void RegisterKillByObject(ObjectClass const* destroyedBy) override JMP_THIS(0x744720);
	void MarkAllOccupationBits(const Coordinate& coords) override JMP_THIS(0x7441B0);
	void UnmarkAllOccupationBits(const Coordinate& coords) override JMP_THIS(0x744210);
	bool DrawIfVisible(RectangleStruct* pBounds, bool EvenIfCloaked, DWORD dwUnk3) const override JMP_THIS(0x73B0B0);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x73CEC0);
	bool ObjectClickedAction(Action action, ObjectClass* pTarget, bool bUnk) override JMP_THIS(0x738910);
	bool CellClickedAction(Action action, ::Cell* pCell, ::Cell* pCell1, bool bUnk) override JMP_THIS(0x738890);
	DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x737C90);
	void Destroy() override JMP_THIS(0x746D60);
	void Scatter(const Coordinate& crd, bool ignoreMission, bool ignoreDestination) override JMP_THIS(0x743A50);
	void UpdatePosition(PCPType how) override JMP_THIS(0x739EC0);
	RadioCommand ReceiveCommand(TechnoClass* pSender, RadioCommand command, AbstractClass*& pInOut) override JMP_THIS(0x737430);
	Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const override JMP_THIS(0x73F0A0);
	
	bool IsReadyToCommence() override JMP_THIS(0x744270);
	int MissionAttack() override JMP_THIS(0x7447A0);
	int MissionGuard() override JMP_THIS(0x740810);
	int MissionGuardArea() override JMP_THIS(0x744100);
	int MissionHarvest() override JMP_THIS(0x73E5E0);
	int MissionMove() override JMP_THIS(0x740A90);
	int MissionPatrol() override JMP_THIS(0x740B10);
	int MissionRepair() override JMP_THIS(0x740EF0);
	int MissionUnload() override JMP_THIS(0x73D630);

	// ...and so on
	// FIXME other virtual function explicit addresses

	virtual FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const override JMP_THIS(0x740FD0);

	//UnitClass
	// main drawing functions - Draw() calles one of these, they call parent's Draw_A_smth
	virtual void DrawAsVXL(Point2D Coords, RectangleStruct BoundingRect, int Brightness, int Tint)
		{ JMP_THIS(0x73B470); }

	virtual void DrawAsSHP(Point2D Coords, RectangleStruct BoundingRect, int Brightness, int Tint)
		{ JMP_THIS(0x73C5F0); }

	virtual void DrawObject(Surface* pSurface, Point2D Coords, RectangleStruct CacheRect, int Brightness, int Tint)
		{ JMP_THIS(0x73B140); }

	// non-virtual

	bool IsDeactivated() const
		{ JMP_THIS(0x70FBD0); }

	void UpdateTube() JMP_THIS(0x7359F0);
	void UpdateRotation() JMP_THIS(0x736990);
	void UpdateEdgeOfWorld() JMP_THIS(0x736C10); // inlined in game
	void UpdateFiring() JMP_THIS(0x736DF0);
	void UpdateVisceroid() JMP_THIS(0x737180);
	void UpdateDisguise() JMP_THIS(0x7468C0);

	void Explode() JMP_THIS(0x738680);

	bool GotoClearSpot() JMP_THIS(0x738D30);
	bool TryToDeploy() JMP_THIS(0x7393C0);
	void Deploy() JMP_THIS(0x739AC0);
	void Undeploy() JMP_THIS(0x739CD0);

	bool Harvesting() JMP_THIS(0x73D450);

	bool FlagAttach(int nHouseIdx) JMP_THIS(0x740DF0);
	bool FlagRemove() JMP_THIS(0x740E20);

	void APCCloseDoor() JMP_THIS(0x740E60); // inlined in game
	void APCOpenDoor() JMP_THIS(0x740E80); // inlined in game

	static void __fastcall ReadINI(CCINIClass* pINI) JMP_STD(0x743270);
	static void __fastcall WriteINI(CCINIClass* pINI) JMP_STD(0x7436E0);

	bool ShouldCrashIt(TechnoClass* pTarget) JMP_THIS(0x7438F0);

	AbstractClass* AssignDestination_7447B0(AbstractClass* pTarget) JMP_THIS(0x7447B0);
	bool AStarAttempt(const CellStruct& cell1, const CellStruct& cell2) JMP_THIS(0x746000);

protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline UnitClass(fake_noinit_t) noexcept : FootClass(fake_noinit_t{}) {}
public:
	UnitClass(noinit_t) : FootClass(fake_noinit_t{}) {};
	UnitClass(UnitTypeClass* type, HouseClass* house) : UnitClass(fake_noinit_t{}) JMP_THIS(0x7353C0);
};
static_assert(sizeof(UnitClass) == UnitClass::ClassSize);
