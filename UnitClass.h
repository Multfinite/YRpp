#pragma once

#include "FootClass.h"
#include "UnitTypeClass.h"

class EBolt;

/*!
* @brief Ground & Naval Vehicles
*/
class __declspec(uuid("0E272DCA-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE UnitClass : public FootClass
{
public:
	using base_type = FootClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F5C70;
			this->IRTTITypeInfo = 0x7F5C54;
			this->INoticeSink = 0x7F5C4C;
			this->INoticeSource = 0x7F5C44;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::Unit;
	static constexpr uintptr_t AbsVTable = 0x7F5C70;
	static constexpr size_t ClassSize = 0x8E8;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<UnitClass*>, Array, 0x8B4108u)
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
	virtual ~UnitClass() JMP_THIS(0x735780);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x746DE0);

	HRESULT __stdcall Load(IStream* pStm)  override JMP_STD(0x744470);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x744600);

	/*0:0x0*/virtual void UnitClass_sink_746100() JMP_THIS(0x746100);

	void Init() override JMP_THIS(0x746810);
	void InvalidatePointer(AbstractClass* instance, bool all = true) override JMP_THIS(0x7446E0);
	RTTIType KindOf() const override JMP_THIS(0x746E20);
	int SizeOf() const override JMP_THIS(0x746DD0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x744640);
	void AI() override JMP_THIS(0x7360C0);

	Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x7404B0);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x73FD50);
	bool IsStrange() const override JMP_THIS(0x746400);
	ObjectTypeClass* ClassOf() const override JMP_THIS(0x741490);
	const wchar_t* FullName() const override JMP_THIS(0x746B20);
	bool IsDisguisedAs(HouseClass* target) const override JMP_THIS(0x746750);
	ObjectTypeClass* DisguisedAs(bool disguisedAgainstAllies) const override JMP_THIS(0x7465B0);
	HouseClass* DisguisedAsHouse(bool disguisedAgainstAllies) const override JMP_THIS(0x7465F0);
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

	void SetDestination(AbstractClass* target, bool a2) override JMP_THIS(0x741970);
	FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const override JMP_THIS(0x740FD0);
	void Stun() override JMP_THIS(0x746C90);
	bool SetOwningHouse(HouseClass* pHouse, bool announce = true) override JMP_THIS(0x7463A0);
	InfantryTypeClass* ClearDisguise() override JMP_THIS(0x746720);
	InfantryTypeClass* GetCrew() const override JMP_THIS(0x740EE0);
	FacingType DesiredLoadDir(ObjectClass const* object, ::Cell* cell) const JMP_THIS(0x740B60);
	bool EnterIdleMode(bool initial, bool a2) override JMP_THIS(0x738970);
	BulletClass* Fire(AbstractClass* pTarget, int nWeaponIndex) override JMP_THIS(0x741340);
	DirStruct GetRealFacing() const override JMP_THIS(0x740F80);
	bool CanAttackOnTheMove() const override JMP_THIS(0x746CC0);
	AbstractClass* GreatestThreat(ThreatType threat, Coordinate* pCoord, bool onlyTargetHouseEnemy) override JMP_THIS(0x743190);
	bool IsDoorClosed() override JMP_THIS(0x744180);
	int GetPipFillLevel() const override JMP_THIS(0x740E50);
	void Reload() override JMP_THIS(0x736CA0);
	void DisguiseAs(AbstractClass* target) override JMP_THIS(0x746670);
	double GetStoragePercentage() const override JMP_THIS(0x7414A0);
	DirStruct TurretFacing() const override JMP_THIS(0x746E30);
	int SelectWeapon(AbstractClass* pTarget) const override JMP_THIS(0x746CD0);

	AbstractClass* ApproachTarget(bool assign) override JMP_THIS(0x7414E0);
	void OverrunSquare(volatile ::Cell* a2, ::Cell a3) override JMP_THIS(0x7416A0);

	/*!
	* @brief main drawing functions - Draw() calles one of these, they call parent's Draw_A_smth
	* @note original_name UnitClass__Draw_Voxel
	* @note vtable_index 341:x554
	* @note address 0x73B470
	*/
	virtual void DrawAsVXL(Point2D coords, RectangleStruct boundingRect, int brightness, int tint) JMP_THIS(0x73B470);
	
	/*!
	* @brief main drawing functions - Draw() calles one of these, they call parent's Draw_A_smth
	* @note original_name UnitClass__drawcode
	* @note vtable_index 342x558
	* @note address 0x73C5F0
	*/
	virtual void DrawAsSHP(Point2D coords, RectangleStruct boundingRect, int brightness, int tint) JMP_THIS(0x73C5F0);

	/*!
	* @brief main drawing functions - Draw() calles one of these, they call parent's Draw_A_smth
	* @note original_name UnitClass__Draw_Object343
	* @note vtable_index 343x55C
	* @note address 0x73B140
	*/
	virtual void DrawObject(Surface* surface, Point2D coords, RectangleStruct cacheRect, int brightness, int tint) JMP_THIS(0x73B140);

	bool IsDeactivated() const JMP_THIS(0x70FBD0);

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

	/*!
	* @brief Object deployed.
	* @note original_name HasDeployed
	* @note address 0x746D80
	*/
	bool HasDeployed() JMP_THIS(0x746D80);

	/*!
	* @brief Object deployed already or deploying now
	* @note original_name IsDeploying
	* @note address 0x746D90
	*/
	bool IsDeployed() JMP_THIS(0x746D90);

	/*!
	* @brief Object changes it's state: being deploying or undeploying
	* @note original_name IsDeploying
	* @note address 0x746DB0
	*/
	bool InDeployTansition() JMP_THIS(0x746DB0);

	bool IsSimpleDeployerDeployToLand() JMP_THIS(0x746D10);

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

	int32_t DisguiseStuff(ObjectTypeClass* type) JMP_THIS(0x746630);
	int64_t CreditLoad() JMP_THIS(0x7438B0);
	bool DeployFire() const JMP_THIS(0x746D00);
protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline UnitClass(fake_noinit_t) noexcept : FootClass(fake_noinit_t{}) {}
public:
	UnitClass(noinit_t) noexcept : FootClass(fake_noinit_t{}) { vtables.init(this); };
	UnitClass(UnitTypeClass* type, HouseClass* house) : UnitClass(fake_noinit_t{}) JMP_THIS(0x7353C0);
};
static_assert(sizeof(UnitClass) == UnitClass::ClassSize);