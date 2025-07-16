#pragma once

#include "FootClass.h"
#include "AircraftTypeClass.h"

/*!
* @brief Aircraft
*/
class __declspec(uuid("0E272DC2-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE AircraftClass : public FootClass, public IFlyControl
{
public:
	using base_type = TechnoClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		uintptr_t IFlyControl;

		constexpr vtables_t() noexcept : base_type::vtables_t(), IFlyControl(0x7E2250)
		{
			this->IPersistStream = 0x7E22A4;
			this->IRTTITypeInfo = 0x7E2288;
			this->INoticeSink = 0x7E2280;
			this->INoticeSource = 0x7E2278;
		}

		__forceinline void init(AircraftClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::Aircraft;
	static constexpr uintptr_t AbsVTable = 0x7E22A4;
	static constexpr size_t ClassSize = 0x6D8;

	DEFINE_POINTER(DynamicVectorClass<AircraftClass*>, Array, 0xA8E390u)
public:
	AircraftTypeClass* Type;
	// Whether or not to deduct ammo after firing run (strafing) is over
	bool ShouldLoseAmmo;
	//parachutes
	bool HasPassengers;
	// when crashing down, duh
	bool IsKamikaze;
	BuildingClass* DockNowHeadingTo;
	bool unknown_bool_6D0;
	bool unknown_bool_6D1;
	// Whether or not aircraft is locked to a firing run (strafing)
	bool IsLocked;
	char NumParadropsLeft;
	bool IsCarryallNotLanding;
	// Aircraft finished attack run and/or went idle and is now returning from it
	bool IsReturningFromAttackRun;
public:
	virtual ~AircraftClass() JMP_THIS(0x414080);

	int __stdcall Landing_Altitude() override JMP_STD(0x41B6A0);
	int __stdcall Landing_Direction() override JMP_STD(0x41B760);
	long __stdcall Is_Loaded() override JMP_STD(0x41B7D0);
	long __stdcall Is_Strafe() override JMP_STD(0x41B7F0);
	long __stdcall Is_Fighter() override JMP_STD(0x41B840);
	long __stdcall Is_Locked() override JMP_STD(0x41B860);

	// Death weapon logic here
	bool __stdcall Respond(DWORD command) override JMP_STD(0x41BC30);
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) override JMP_STD(0x414290);
	ULONG __stdcall AddRef() override JMP_STD(0x4142F0);
	ULONG __stdcall Release() override JMP_STD(0x414300);
	HRESULT __stdcall GetClassID(CLSID* pClassID)  override JMP_STD(0x41C190);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x41B430);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x41B5C0);

	void Init() override JMP_THIS(0x413F80);
	void InvalidatePointer(AbstractClass* target, bool all) override JMP_THIS(0x41B660);
	RTTIType KindOf() const override JMP_THIS(0x41C180);
	int SizeOf() const override JMP_THIS(0x41C170);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x41B610);
	bool IsOnGround() const override JMP_THIS(0x41B980);
	bool InAir() const override JMP_THIS(0x41B920);
	void AI() override JMP_THIS(0x414BB0);

	Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x417F80);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x417CC0);
	Layer InWhichLayer() const override JMP_THIS(0x41ADC0);
	bool IsStrange() const override JMP_THIS(0x41B910);
	ObjectTypeClass* ClassOf() const override JMP_THIS(0x41C200);
	const wchar_t* FullName() const override JMP_THIS(0x41C1D0);
	bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x414310);
	KickOutResult KickOutUnit(TechnoClass* pTechno, ::Cell Cell) override JMP_THIS(0x415B10);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x4144B0);
	void See(bool incremental, int32_t arg_4) override JMP_THIS(0x41ADF0);
	bool ObjectClickedAction(Action action, ObjectClass* pTarget, bool bUnk) override JMP_THIS(0x417C80);
	bool CellClickedAction(Action action, ::Cell* pCell, ::Cell* pCell1, bool bUnk) override JMP_THIS(0x417BD0);
	DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x4165C0);
	void Scatter(const Coordinate& crd, bool ignoreMission, bool ignoreDestination) override JMP_THIS(0x41A590);
	RadioCommand ReceiveCommand(TechnoClass* pSender, RadioCommand command, AbstractClass*& pInOut) override JMP_THIS(0x4190B0);
	Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const override JMP_THIS(0x4196B0);
	
	void AssignMission(Mission mission, bool commence) override JMP_THIS(0x41BA90);
	bool Commence() override JMP_THIS(0x41B870);
	void SetMission(Mission mission) override JMP_THIS(0x41B9F0);
	void OverrideMission(Mission mission, AbstractClass* target, AbstractClass* destination) override JMP_THIS(0x41BB30);
	bool IsReadyToCommence() override JMP_THIS(0x41B5E0);
	int MissionAttack() override JMP_THIS(0x417FE0);
	int MissionGuard() override JMP_THIS(0x41A5C0);
	int MissionGuardArea() override JMP_THIS(0x41A940);
	int MissionHunt() override JMP_THIS(0x414A80);
	int MissionMove() override JMP_THIS(0x4166C0);
	int MissionRetreat() override JMP_THIS(0x415A50);
	int MissionUnload() override JMP_THIS(0x4151E0);
	int MissionEnter() override JMP_THIS(0x419C80);
	int MissionPatrol() override JMP_THIS(0x417300);
	int MissionParadropApproach() override JMP_THIS(0x4158E0);
	int MissionParadropOverfly() override JMP_THIS(0x415960);
	int MissionSpyplaneApproach() override JMP_THIS(0x4155F0);
	int MissionSpyplaneOverfly() override JMP_THIS(0x4157C0);

	DirStruct TurretFacing() const override JMP_THIS(0x41C1E0);
	FacingType DesiredLoadDir(ObjectClass const* object, ::Cell* cell) const override JMP_THIS(0x4195A0);
	DirStruct GetRealFacing() const override JMP_THIS(0x41A570);
	bool ClickedMission(Mission Mission, ObjectClass* pTarget, CellClass* TargetCell, CellClass* NearestTargetCellICanEnter) override JMP_THIS(0x417CA0);
	void DecreaseAmmo() override JMP_THIS(0x41B900);
	FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const override JMP_THIS(0x41A9E0);
	BulletClass* Fire(AbstractClass* pTarget, int nWeaponIndex) override JMP_THIS(0x415EE0);
	bool IsNotWarpingIn() const override JMP_THIS(0x41B9E0);
	void SetDestination(AbstractClass* target, bool a2) override JMP_THIS(0x41AA80);
	bool EnterIdleMode(bool initial, bool a2) override JMP_THIS(0x4176F0);

	bool IsLeavingMap() const override JMP_THIS(0x41B890);
	BuildingClass* TryNearestDockBuilding(TypeList<BuildingTypeClass*>* bList, DWORD dwUnk2, DWORD dwUnk3) const override JMP_THIS(0x41BBD0);
protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline AircraftClass(fake_noinit_t) noexcept : FootClass(fake_noinit_t{}) {}
	
public:
	//AircraftClass() {}
	AircraftClass(noinit_t) noexcept : FootClass(fake_noinit_t{}) { vtables.init(this); }
	AircraftClass(AircraftTypeClass* type, HouseClass* owner) : AircraftClass(fake_noinit_t{}) JMP_THIS(0x413D20);
};
static_assert(sizeof(AircraftClass) == AircraftClass::ClassSize);
