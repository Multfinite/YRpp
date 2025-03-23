#pragma once

#include "FootClass.h"
#include "InfantryTypeClass.h"

/*!
* @brief Infantry
*/
class NOVTABLE InfantryClass : public FootClass
{
public:
	using base_type = FootClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EB058;
			this->IRTTITypeInfo = 0x7EB03C;
			this->INoticeSink = 0x7EB034;
			this->INoticeSource = 0x7EB02C;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::Infantry;
	static constexpr uintptr_t AbsVTable = 0x7EB058;
	static constexpr size_t ClassSize = 0x6F0;

	static constexpr constant_ptr<DynamicVectorClass<InfantryClass*>, 0xA83DE8u> const Array{};
public:
	InfantryTypeClass* Type;
	//IT IS MORE THAT JUST ANIMATION. IT IS INFANTRY STATE!
	InfantryState State;
	CDTimerClass CommentTimer;
	// set in ReceiveDamage on panicky units
	DWORD          PanicDurationLeft;
	// set by script action, not cleared anywhere
	bool           PermanentBerzerk;
	bool           IsTechnician;
	bool           IsStroked;
	bool           IsProne;
	bool           IsZoneCheat;
	bool           WasSelected;
	DWORD      unknown_6E0;
	bool           ShouldDeploy;
	int            OnLand;
	PROTECTED_PROPERTY(DWORD, unused_6EC);
public:
	virtual ~InfantryClass() JMP_THIS(0x517D90);

	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_THIS(0x523300);

	HRESULT STDMETHODCALLTYPE Load(__RPC__in_opt IStream* pStm) override JMP_THIS(0x521960);
	HRESULT STDMETHODCALLTYPE Save(__RPC__in_opt IStream* pStm, int32_t fClearDirty) override JMP_THIS(0x521B00);

	void Init() override JMP_THIS(0x517CC0);
	void Detach(AbstractClass* target, bool all) override JMP_THIS(0x51AA10);
	RTTIType KindOf() const override JMP_THIS(0x523340);
	int SizeOf() const override JMP_THIS(0x5232F0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x521C90);
	void AI() override JMP_THIS(0x51BAB0);

	virtual SHPStruct* GetImage() const override JMP_THIS(0x5216C0);
	Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x51F800);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x51E3B0);
	ObjectTypeClass* Type() const override JMP_THIS(0x51FAF0);
	const wchar_t* FullName() const override JMP_THIS(0x51F2C0);
	Coordinate FLH(int idxWeapon, Coordinate BaseCoords) const override JMP_THIS(0x523250);
	bool IsDisguisedAs(HouseClass* target) const override JMP_THIS(0x5227F0);
	ObjectTypeClass* Disguise(bool disguisedAgainstAllies) const override JMP_THIS(0x522640);
	HouseClass* DisguiseHouse(bool disguisedAgainstAllies) const override JMP_THIS(0x5226C0);
	bool Limbo() override JMP_THIS(0x51DF10);
	bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x51DFF0);
	bool SpawnParachuted(Coordinate const& coords) override JMP_THIS(0x521760);
	void MarkAllOccupationBits(Coordinate const& coords) override JMP_THIS(0x5217C0);
	void UnmarkAllOccupationBits(Coordinate const& coords) override JMP_THIS(0x521850);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x518F90);
	bool ObjectClickedAction(Action action, ObjectClass* pTarget, bool bUnk) override JMP_THIS(0x51F250);
	bool CellClickedAction(Action action, ::Cell* pCell, ::Cell* pCell1, bool bUnk) override JMP_THIS(0x51F190);
	DamageState IronCurtain(int nDuration, HouseClass* pSource, bool ForceShield) override JMP_THIS(0x522600);
	DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x517FA0);
	void Scatter(const Coordinate& crd, bool ignoreMission, bool ignoreDestination) override JMP_THIS(0x51D0D0);
	void UpdatePosition(PCPType how) override JMP_THIS(0x519630);
	Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const override JMP_THIS(0x51BF90);
	
	bool IsReadyToCommence() override JMP_THIS(0x521B60);
	int MissionAttack() override JMP_THIS(0x51F3E0);
	int MissionGuard() override JMP_THIS(0x51F620);
	int MissionGuardArea() override JMP_THIS(0x51F640);
	int MissionHarvest() override JMP_THIS(0x522E70);
	int MissionHunt() override JMP_THIS(0x51F540);
	int MissionMove() override JMP_THIS(0x51F660);
	int MissionUnload() override JMP_THIS(0x51F6E0);
	
	int SelectWeapon(AbstractClass* pTarget) const override JMP_THIS(0x5218E0);
	Coordinate FiringOffset() const override JMP_THIS(0x521D30);
	bool IsEngineer() const override JMP_THIS(0x5224D0);
	bool CanCheer() const override JMP_THIS(0x522BC0);
	void Cheer(bool Force) override JMP_THIS(0x522C00);
	FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const override JMP_THIS(0x51C8B0);
	AbstractClass* GreatestThreat(ThreatType threat, Coordinate* pCoord, bool onlyTargetHouseEnemy) override JMP_THIS(0x51E140);
	void SetTarget(AbstractClass* pTarget) override JMP_THIS(0x51B1F0);
	BulletClass* Fire(AbstractClass* pTarget, int nWeaponIndex) override JMP_THIS(0x51DF60);
	void AttackGreatestThreat() override JMP_THIS(0x51F330);
	void DisguiseAs(AbstractClass* target) override JMP_THIS(0x522700);
	InfantryTypeClass* ClearDisguise() override JMP_THIS(0x522780);
	bool IsReadyToRandomAnimate() override JMP_THIS(0x5216D0);
	bool RandomAnimate() override JMP_THIS(0x51CDB0);
	void SetDestination(AbstractClass* target, bool a2) override JMP_THIS(0x51AA40);
	bool EnterIdleMode(bool initial, bool a2) override JMP_THIS(0x51CBA0);
	bool CanUseWaypoint() const override JMP_THIS(0x5228B0);
	bool CanAttackOnTheMove() const override JMP_THIS(0x5228C0);
	
	void StopHunting() override JMP_THIS(0x521DD0);
	virtual bool JumpJet_UnknownMovement() override JMP_THIS(0x521EB0);
	bool MoveTo(Coordinate* crd) override JMP_THIS(0x51DBD0);
	bool StopDriver() override JMP_THIS(0x51DAF0);
	bool ChronoWarpTo(Coordinate dest) override JMP_THIS(0x522FE0);
	void GoBerzerk() override JMP_THIS(0x5220F0);
	void Panic() override JMP_THIS(0x521C10);
	void UnPanic() override JMP_THIS(0x521C40);
	void PlayIdleAnim(int nIdleAnimNumber) override JMP_THIS(0x521C60);
	int GetCurrentSpeed() const override JMP_THIS(0x521D80);
	AbstractClass* ApproachTarget(bool assign) override JMP_THIS(0x522340);
	void StopMoving() override JMP_THIS(0x521B20);
	void ForceDeploy() override JMP_THIS(0x521B40);

	/*!
	* @brief Object: IsDeployed is true and currently it's sequince in any form of deploy
	* @note original_name Is_Deployed
	* @note vtable_index 341:0x554
	* @note address 0x5228D0
	*/
	virtual int32_t IsDeployed() JMP_THIS(0x5228D0);

	/*!
	* @brief Object: Change current unit state and test against state machine avaliable transitions
	* @note original_name Do_Action
	* @note vtable_index 342:0x558
	* @note address 0x51D6F0
	*/
	virtual bool TryChangeState(Sequence index, bool force = false, bool randomStartFrame = false) JMP_THIS(0x51D6F0);

	bool IsDeployer() const JMP_THIS(0x5224E0);
	bool InDeployTansition() const JMP_THIS(0x522510);
	int Deploy() JMP_THIS(0x522550);
	bool DeployFire() const JMP_THIS(0x522540);

	void UpdateTube() JMP_THIS(0x51B350);
	void UpdateMovement() JMP_THIS(0x520F40);
	bool UpdateEdgeOfWorld() JMP_THIS(0x520260);
	void UpdateFiring() JMP_THIS(0x5206B0);
	int UpdateStateMachine() JMP_THIS(0x520AE0);
	void UpdateFear() JMP_THIS(0x5200B0);	
	bool UpdateThief() JMP_THIS(0x5202F0);	
	int UpdateStorage(TechnoClass* techno) JMP_THIS(0x522D50);

	// Shape_Number
	int32_t ShapeIndex() const JMP_THIS(0x518D80);

	void ForceGuard() JMP_THIS(0x522D20);
	void ForceHarvest() JMP_THIS(0x522D00);
	void InfantryEnteredThing(FootClass* foot) JMP_THIS(0x522910);

	bool IsDying() const JMP_THIS(0x522CB0);

	bool HasTiberiumLoad() JMP_THIS(0x522D30);
	bool HasUndeployDelay() JMP_THIS(0x5224F0);
	bool Harvesting() JMP_THIS(0x522FC0);
	
	static void __fastcall ReadINI(CCINIClass* pINI) JMP_STD(0x51FB00);
	static void __fastcall WriteINI(CCINIClass* pINI) JMP_STD(0x51FEF0);
protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline InfantryClass(fake_noinit_t) noexcept : FootClass(fake_noinit_t{}) {}

public:
	InfantryClass(noinit_t) : FootClass(fake_noinit_t{}) { vtables.init(this); };
	InfantryClass(InfantryTypeClass* pType, HouseClass* pOwner) noexcept : InfantryClass(fake_noinit_t()) JMP_THIS(0x517A50);
};
