/*
	Base class for units that can move (that have "feet")
*/

#pragma once

#include "TechnoClass.h"
#include "ParasiteClass.h"

//forward declarations
class LocomotionClass;
class TeamClass;

class NOVTABLE FootClass : public TechnoClass
{
public:
	static constexpr uintptr_t AbsVTable = 0x7E8C94;
	static constexpr auto AbsDerivateID = AbstractFlags::Foot;
	static constexpr size_t ClassSize = 0x6C0;

	static constexpr constant_ptr<DynamicVectorClass<FootClass*>, 0x8B3DC0u> const Array{};
public:
	int             PlanningPathIdx; // which planning path am I following?
	::Cell      WaypointNearbyAccessibleCellDelta; // add to WaypointCell to get Nearby_Cell for this foot
	::Cell      WaypointCell; // current waypoint cell
	DWORD           __gap_52C;
	double           ThreatAvoidanceCoefficient;
	int				WalkedFramesSoFar;
	bool            IsMoveSoundPlaying;
	int             MoveSoundDelay;

	DECLARE_PROPERTY(AudioController, MoveSoundAudioController);

	::Cell      CurrentMapCoords;
	::Cell      LastMapCoords; // ::UpdatePosition uses this to remove threat from last occupied cell, etc
	::Cell      LastFlightMapCoords; // which cell was I occupying previously? only for AircraftTracker-tracked stuff
	::Cell      CurrentJumpjetMapCoords; // unconfirmed, which cell am I occupying? only for jumpjets
	Coordinate     Sqrt_ed_val_568;
	PROTECTED_PROPERTY(DWORD, unused_574);
	double          SpeedPercentage;
	double          SpeedMultiplier;
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, NavQueue2);
	AbstractClass* FollowingMaybe_5A0;
	// NavCom
	// possibly other objects as well
	AbstractClass* Destination;
	// SuspendedNavCom
	AbstractClass* LastDestination;
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, NavQueue); // Stores sequence of movement destinations
	Mission         MegaMission; // only Mission::AttackMove or Mission::None
	AbstractClass* MegaDestination; // when AttackMove target is a cell
	AbstractClass* MegaTarget; // when AttackMove target is an object
	BYTE            __gap_5D0;	//unused?
	bool            HaveAttackMoveTarget; // fighting an enemy on the way
	TeamClass* Team;
	FootClass* NextTeamMember;        //next unit in team
	CellClass*           SomeCell_5DC;
	int             PathDirections[24]; // list of directions to move in next, like tube directions
	DECLARE_PROPERTY(CDTimerClass, PathDelayTimer);
	int             TryTryAgain;
	DECLARE_PROPERTY(CDTimerClass, BaseAttackTimer);
	DECLARE_PROPERTY(CDTimerClass, SightTimer);
	DECLARE_PROPERTY(CDTimerClass, BlockagePathTimer);
	DECLARE_PROPERTY(ILocomotionPtr, Locomotor);
	Coordinate       HeadTo;
	uint8_t      CurrentTubeIndex;
	uint8_t              CurrentDirectionInTube;
	uint8_t       WaypointIndex; // which waypoint in my planning path am I following?
	bool              IsToScatter;
	bool              IsScanLimited;
	bool              IsInitiated; // Is a fully joined member of a team, used for regroup etc. checks
	// IsNewNavCom
	bool              ShouldScanForTarget;
	bool              IsPlanningToLook;
	bool              IsDeploying;
	bool              IsFiring;
	bool              AssignNewThreat;
	bool              ShouldEnterAbsorber; // orders the unit to enter the closest bio reactor
	bool              ShouldEnterOccupiable; // orders the unit to enter the closest battle bunker
	bool              ShouldGarrisonStructure; // orders the unit to enter the closest neutral building
	FootClass* ParasiteEatingMe; // the tdrone/squid that's eating me
	int               LastBeParasitedStartFrame;
	ParasiteClass* ParasiteImUsing;	// my parasitic half, nonzero for, eg, terror drone or squiddy
	DECLARE_PROPERTY(CDTimerClass, ParalysisTimer); // for squid victims
	bool              unknown_bool_6AC;
	bool              IsAttackedByLocomotor; // the unit's locomotor is jammed by a magnetron
	bool              IsLetGoByLocomotor; // a magnetron attacked this unit and let it go. falling, landing, or sitting on the ground
	bool              IsRotating;
	bool              IsUnloading;
	bool              IsNavQueueLoop;
	bool              IsScattering;
	bool              IsIdle_6B3;
	bool              HeightSubtract_6B4;
	bool              IsCrusher_6B5;
	// also called aircraft state - from db
	// frozen in first frame of the proper facing - when magnetron'd or warping
	bool              FrozenStill;
	bool              blockage_6B7;
	bool              Removed;
	PROTECTED_PROPERTY(DWORD, unused_6BC);	//???
public:
	virtual ~FootClass() JMP_THIS(0x4D3590); // i am not sure about the address

	HRESULT STDMETHODCALLTYPE Load(__RPC__in_opt IStream* pStm) override JMP_THIS(0x4DB3C0);
	HRESULT STDMETHODCALLTYPE Save(__RPC__in_opt IStream* pStm, int32_t fClearDirty) override JMP_THIS(0x4DB690);

	void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x4D9960);
	void ComputeCRC(CRCEngine & crc) const override JMP_THIS(0x4DBAD0);
	Coordinate Destination(TechnoClass* pDocker = nullptr) const override JMP_THIS(0x4DBDF0);
	bool InAir() const override JMP_THIS(0x4DE620);
	void AI() override JMP_THIS(0x4DA530);
	
	VisualType VisualCharacter(VARIANT_BOOL specificOwner, HouseClass* whoIsAsking) const override JMP_THIS(0x4DA4E0);
	SHPStruct* GetImage() const override JMP_THIS(0x4DED70);
	Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x4DDDE0);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x4DDED0);
	Layer InWhichLayer() const override JMP_THIS(0x4DB7E0);
	bool Soldable() const override JMP_THIS(0x4D9E70);
	bool IsOnBridge(TechnoClass* pDocker = nullptr) const override JMP_THIS(0x4DDC40);
	bool IsStandingStill() const override JMP_THIS(0x41C070);
	bool Limbo() override JMP_THIS(0x4DB260);
	bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x4D7170);
	void DetachAll(bool permanently) override JMP_THIS(0x4D9720);
	void UnInit() override JMP_THIS(0x4DE5D0);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x4DB250);
	bool Mark(MarkType value) override JMP_THIS(0x4D3780);
	bool CanBeSelected() const override JMP_THIS(0x4DFA50);
	bool ObjectClickedAction(Action action, ObjectClass * pTarget, bool bUnk) override JMP_THIS(0x4D7D50);
	bool CellClickedAction(Action action, ::Cell* pCell, ::Cell* pCell1, bool bUnk) override JMP_THIS(0x4D74E0);
	DamageState IronCurtain(int nDuration, HouseClass* pSource, bool ForceShield) override JMP_THIS(0x4DEAE0);
	DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x4D7330);
	void UpdatePosition(PCPType how) override JMP_THIS(0x4D85D0);
	RadioCommand ReceiveCommand(TechnoClass* pSender, RadioCommand command, AbstractClass*& pInOut) override JMP_THIS(0x4D8FB0);
	void Sell(DWORD control) override JMP_THIS(0x4D9F70);
	void AssignPlanningPath(signed int idxPath, signed char idxWP) override JMP_THIS(0x4DC810);
	Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const override JMP_THIS(0x4D9C10);
	DWORD CanChangeLevel(CellClass* cell, Dir256 dir, int* targetLevel, bool* useAltObject, ::Cell targetCoord) override JMP_THIS(0x4D9C60);
	void SetLocation(const Coordinate& crd)override JMP_THIS(0x4DB810);
	
	void OverrideMission(Mission mission, AbstractClass* target, AbstractClass* destination) override JMP_THIS(0x4D8F40);
	bool RestoreMission() override JMP_THIS(0x4D8F80);
	int32_t MissionAttack() override JMP_THIS(0x4D4DC0);
	int32_t MissionCapture() override JMP_THIS(0x4D4B20);
	int32_t MissionEaten() override JMP_THIS(0x4D4CB0);
	int32_t MissionGuard() override JMP_THIS(0x4D5070);
	int32_t MissionGuardArea() override JMP_THIS(0x4D6AA0);
	int32_t MissionHunt() override JMP_THIS(0x4D5350);
	int32_t MissionMove() override JMP_THIS(0x4D4200);
	int32_t MissionRetreat() override JMP_THIS(0x4DA2C0);
	int32_t MissionUnload() override JMP_THIS(0x4DA2B0);
	int32_t MissionEnter() override JMP_THIS(0x4D9290);
	int32_t MissionRescue() override JMP_THIS(0x4DDF90);
	int32_t MissionPatrol() override JMP_THIS(0x4D4280);

	bool IsCloakable() const override JMP_THIS(0x4DBDA0);
	bool BelongsToATeam() const override JMP_THIS(0x41C050);
	bool IsInSameZoneAs(AbstractClass* pTarget) override JMP_THIS(0x4DBA50);
	bool IsInSameZoneAsCoords(const Coordinate& coord) override JMP_THIS(0x4D3810);
	int GetZAdjustment() const override JMP_THIS(0x4DAFC0);
	ZGradient GetZGradient() const override JMP_THIS(0x4DB0A0);
	::Cell GetLastFlightMapCoords() const override JMP_THIS(0x41C150);
	void SetLastFlightMapCoords(::Cell coord) override JMP_THIS(0x41C160);
	bool IsAllowedToLeaveMap() const override JMP_THIS(0x4DA1D0);
	void ProceedToNextPlanningWaypoint() override JMP_THIS(0x4DE580);
	::Cell ScanForTiberium(int range) const override JMP_THIS(0x4DD0A0);
	bool EnterGrinder() override JMP_THIS(0x4DFA70);
	bool EnterBioReactor() override JMP_THIS(0x4DFB70);
	bool EnterTankBunker() override JMP_THIS(0x4DFF40);
	bool EnterBattleBunker() override JMP_THIS(0x4DFCB0);
	bool GarrisonStructure() override JMP_THIS(0x4DFE00);
	bool IsParalyzed() const override JMP_THIS(0x4DE770);
	void AttachCargo(FootClass* cargo) override JMP_THIS(0x4DE630);
	void Stun() override JMP_THIS(0x4D5660);
	void Destroyed(ObjectClass* Killer) override JMP_THIS(0x4D98C0);
	AbstractClass* GreatestThreat(ThreatType threat, Coordinate* pCoord, bool onlyTargetHouseEnemy) override JMP_THIS(0x4D9920);
	bool SetOwningHouse(HouseClass* pHouse, bool announce = true) override JMP_THIS(0x4DBED0);
	bool Crash(ObjectClass* killer) override JMP_THIS(0x4DEBB0);
	virtual Coordinate GetAttackCoordinates() const override JMP_THIS(0x4D8560);
	void DrawActionLines(bool force, DWORD unkColorComponent) override JMP_THIS(0x4DC060);
	void vt_entry_47C(DWORD dwUnk) override JMP_THIS(0x4D94A0);
	void SetDestination(AbstractClass* target, bool a2) override JMP_THIS(0x4D94B0);
	bool EnterIdleMode(bool initial, bool a2) override JMP_THIS(0x4D82B0);
	bool ForceCreate(Coordinate& coord, DWORD dwUnk = 0) override JMP_THIS(0x4DF510);
	int RespondMegaEventMission(EventClass* pRespondTo) override JMP_THIS(0x4DF0E0);
	void ClearMegaMissionData() override JMP_THIS(0x4DF1A0);
	bool HaveMegaMission() const override JMP_THIS(0x4DF1C0);
	bool HaveAttackMoveTarget() const override JMP_THIS(0x4DF1D0);
	Mission GetMegaMission() const override JMP_THIS(0x4DF1E0);
	Coordinate GetAttackMoveCoords() const override JMP_THIS(0x4DF1F0);
	bool MegaMissionIsAttackMove() const override JMP_THIS(0x4DF310);
	bool ContinueMegaMission() override JMP_THIS(0x4DF320);
	void UpdateAttackMove() override JMP_THIS(0x4DF3A0);
	bool RefreshMegaMission() override JMP_THIS(0x4DF4B0);

	/*!
	* @brief
	* @note original_name vthk_0x4D4_FootClass
	* @note vtable_index 309:0x4D4
	* @note address 0x4DE750
	*/
	virtual void ReceiveGunner(FootClass* Gunner) JMP_THIS(0x4DE750);

	/*!
	* @brief
	* @note original_name vthk_0x4D8_FootClass
	* @note vtable_index 310:0x4D8
	* @note address 0x4DE760
	*/
	virtual void RemoveGunner(FootClass* Gunner) JMP_THIS(0x4DE760);

	/*!
	* @brief
	* @note original_name FootClass_traincrap
	* @note vtable_index 311:0x4DC
	* @note address 0x4DC790
	*/
	virtual bool IsLeavingMap() const JMP_THIS(0x4DC790);

	/*!
	* @brief
	* @note original_name someallow
	* @note vtable_index 312:0x4E0
	* @note address 0x4DBFD0
	*/
	virtual bool vt_entry_4E0() const JMP_THIS(0x4DBFD0);

	/*!
	* @brief
	* @note original_name TechnoClasssub_41C060
	* @note vtable_index 313:0x4E4
	* @note address 0x41C060
	*/
	virtual bool CanDeployNow() const JMP_THIS(0x41C060);

	/*!
	* @brief
	* @note original_name FootClass_SensorsSight_0
	* @note vtable_index 314:0x4E8
	* @note address 0x4DE7B0
	*/
	virtual void AddSensorsAt(::Cell cell) JMP_THIS(0x4DE7B0);

	/*!
	* @brief
	* @note original_name FootClass_SensorsSight
	* @note vtable_index 315:0x4EC
	* @note address 0x4DE940
	*/
	virtual void RemoveSensorsAt(::Cell cell) JMP_THIS(0x4DE940);

	/*!
	* @brief
	* @note original_name vthk_0x4F0_FootClass
	* @note vtable_index 316:0x4F0
	* @note address 0x4D9FF0
	*/
	virtual Coordinate* vt_entry_4F0(Coordinate* pCrd) JMP_THIS(0x4D9FF0);

	/*!
	* @brief
	* @note original_name Stop_Hunting
	* @note vtable_index 317:0x4F4
	* @note address 0x4DC030
	*/
	virtual void StopHunting() JMP_THIS(0x4DC030);

	/*!
	* @brief
	* @note original_name vthk_0x4F8_FootClass
	* @note vtable_index 318:0x4F8
	* @note address 0x41C080
	*/
	virtual bool vt_entry_4F8() JMP_THIS(0x41C080);

	/*!
	* @brief
	* @note original_name Start_Driver
	* @note vtable_index 319:0x4FC
	* @note address 0x4D55F0
	*/
	virtual bool MoveTo(Coordinate* pCrd) JMP_THIS(0x4D55F0);

	/*!
	* @brief
	* @note original_name Stop_Driver
	* @note vtable_index 320:0x500
	* @note address 0x4D55C0
	*/
	virtual bool StopDriver() JMP_THIS(0x4D55C0);

	/*!
	* @brief
	* @note original_name FootClass_4DB9B0
	* @note vtable_index 321:0x504
	* @note address 0x4DB9B0
	*/
	virtual bool vt_entry_504() JMP_THIS(0x4DB9B0);

	/*!
	* @brief
	* @note original_name vthk_0x508_FootClass
	* @note vtable_index 322:0x508
	* @note address 0x4DF7F0
	*/
	virtual bool ChronoWarpTo(Coordinate pDest) JMP_THIS(0x4DF7F0);

	/*!
	* @brief
	* @note original_name Techno_Draw_Object2
	* @note vtable_index 323:0x50C
	* @note address 0x41C090
	*/
	virtual void DrawShape(
		SHPStruct* SHP, int idxFacing, Point2D* Coords, RectangleStruct* Rectangle,
		DWORD dwUnk5, DWORD dwUnk6, DWORD dwUnk7, ZGradient ZGradient,
		DWORD dwUnk9, int extraLight, DWORD dwUnk11, DWORD dwUnk12,
		DWORD dwUnk13, DWORD dwUnk14, DWORD dwUnk15, DWORD dwUnk16) JMP_THIS(0x41C090);

	/*!
	* @brief
	* @note original_name Draw_Voxel
	* @note vtable_index 324:0x510
	* @note address 0x4DAF10
	*/
	virtual void DrawVoxel(
		VoxelStruct* VXL, int HVAFrameIndex, int Flags, IndexClass<int, int>* Cache, RectangleStruct* Rectangle,
		Point2D* CenterPoint, Matrix3D* Matrix, DWORD dwUnk8, DWORD DrawFlags, DWORD dwUnk10) JMP_THIS(0x4DAF10);

	/*!
	* @brief
	* @note original_name Make_Bezerk_Permanent
	* @note vtable_index 325:0x514
	* @note address 0x41C0F0
	*/
	virtual void GoBerzerk() JMP_THIS(0x41C0F0);

	/*!
	* @brief
	* @note original_name Make_Afraid
	* @note vtable_index 326:0x518
	* @note address 0x41C100
	*/
	virtual void Panic() JMP_THIS(0x41C100);

	/*!
	* @brief
	* @note original_name Make_Calm
	* @note vtable_index 327:0x51C
	* @note address 0x41C110
	*/
	virtual void UnPanic() JMP_THIS(0x41C110);

	/*!
	* @brief
	* @note original_name Make_Go_Idle
	* @note vtable_index 328:0x520
	* @note address 0x41C120
	*/
	virtual void PlayIdleAnim(int nIdleAnimNumber) JMP_THIS(0x41C120);

	/*!
	* @brief
	* @note original_name Offload_Tiberium_Bail
	* @note vtable_index 329:0x524
	* @note address 0x4D9C00
	*/
	virtual DWORD OffloadTiberiumBail() JMP_THIS(0x4D9C00);

	/*!
	* @brief
	* @note original_name Find_Docking_Bay_In_Vector
	* @note vtable_index 330:0x528
	* @note address 0x4DF040
	*/
	virtual BuildingClass* TryNearestDockBuilding(TypeList<BuildingTypeClass*>* bList, DWORD dwUnk2, DWORD dwUnk3) const JMP_THIS(0x4DF040);

	/*!
	* @brief
	* @note original_name Find_Docking_Bay_By_Type
	* @note vtable_index 331:0x52C
	* @note address 0x4DEE80
	*/
	virtual BuildingClass* FindCloserDockBuilding(BuildingTypeClass* bType, DWORD dwUnk2, DWORD dwUnk3, int* pDistance) const JMP_THIS(0x4DEE80);

	/*!
	* @brief
	* @note original_name Find_Docking_Bay
	* @note vtable_index 332:0x530
	* @note address 0x4DEE50
	*/
	virtual BuildingClass* FindNearestDockBuilding(BuildingTypeClass* bType, DWORD dwUnk2, DWORD dwUnk3) const JMP_THIS(0x4DEE50);

	/*!
	* @brief
	* @note original_name Overrun_Square
	* @note vtable_index 333:0x534
	* @note address 0x41C130
	*/
	virtual void OverrunSquare(volatile ::Cell* a2, ::Cell a3) JMP_THIS(0x41C130);

	/*!
	* @brief
	* @note original_name Get_Movement_Speed
	* @note vtable_index 334:0x538
	* @note address 0x4DB1A0
	*/
	virtual int GetCurrentSpeed() const JMP_THIS(0x4DB1A0);

	/*!
	* @brief
	* @note original_name Approach_Target
	* @note vtable_index 335:0x53C
	* @note address 0x4D5690
	*/
	virtual AbstractClass* ApproachTarget(bool assign) JMP_THIS(0x4D5690);

	/*!
	* @brief
	* @note original_name Fixup_Path
	* @note vtable_index 336:0x540
	* @note address 0x41C140
	*/
	virtual void FixupPath(PathType& path) JMP_THIS(0x41C140);

	/*!
	* @brief
	* @note original_name vthk_0x544_FootClass
	* @note vtable_index 337:0x544
	* @note address 0x4D3710
	*/
	virtual void SetSpeedPercentage(double percentage) JMP_THIS(0x4D3710);

	/*!
	* @brief
	* @note original_name Stop_Moving
	* @note vtable_index 338:0x548
	* @note address 0x4DBA30
	*/
	virtual void StopMoving() JMP_THIS(0x4DBA30);

	/*!
	* @brief
	* @note original_name Force_Deploy
	* @note vtable_index 339:0x54C
	* @note address 0x4DBA40
	*/
	virtual void ForceDeploy() JMP_THIS(0x4DBA40);

	/*!
	* @brief
	* @note original_name FootClass_Is_LZ_Clear_4DDC60
	* @note vtable_index 340:0x550
	* @note address 0x4DDC60
	*/
	virtual bool IsLandZoneClear(AbstractClass* pDestination) JMP_THIS(0x4DDC60);

	/*!
	* @brief Some team related stuff
	* @note original_name Is_Recruitable
	* @note address 0x4DA230
	*/
	constexpr bool CanBeRecruited(HouseClass *byWhom) const JMP_THIS(0x4DA230);

	/*!
	* @brief only used by squid damage routines, normal wakes are created differently it seems
	* @brief creates 3 wake animations behind the unit
	* @note original_name Wake_Anim
	* @note address 0x629E90
	*/
	constexpr void CreateWakes(Coordinate coords) JMP_THIS(0x629E90);

	/*!
	* @brief can this jumpjet stay in this cell or not? 
	* @brief (two jumpjets in one cell are not okay, locomotor kicks one of them out in the next frame)
	* @note original_name Jumpjet_LocationClear
	* @note address 0x4135A0
	*/
	constexpr bool JumpjetsIsColliding() const JMP_THIS(0x4135A0);

	/*!
	* @note original_name JumpjetOccupyCell
	* @note address 0x4E00B0
	*/
	constexpr void JumpjetOccupyCell(::Cell Cell) JMP_THIS(0x4E00B0);

	/*!
	* @brief Changes locomotor to the given one, Magnetron style
	* @brief Mind that this locks up the source too, Magnetron style
	* @note original_name FootClass_ImbueLocomotor
	* @note address 0x710000
	*/
	constexpr void ImbueLocomotor(FootClass *target, CLSID clsid) JMP_THIS(0x710000);

	/*!
	* @brief var $this = this; $.each($this.Passengers, function(ix, p) { p.Location = $this.Location; });
	* @note original_name Set_Cargo_Coords
	* @note address 0x7104F0
	*/
	constexpr void UpdateCargoCoords() JMP_THIS(0x7104F0);

	/*!
	* @note original_name Abort_Motion
	* @note address 0x4DF0D0
	*/
	constexpr void AbortMotion() JMP_THIS(0x4DF0D0);

	/*!
	* @note original_name Basic_Path
	* @note address 0x4D3920
	*/
	constexpr bool UpdatePathfinding(::Cell unkCell, ::Cell unkCell2, int unk3) JMP_THIS(0x4D3920);

	/*!
	* @brief Removes the first passenger and updates the Gunner.
	* @note original_name Kick_Out_Passenger
	* @note address 0x4DE710
	*/
	constexpr FootClass* LeaveTransport() JMP_THIS(0x4DE710);

	/*!
	* @brief Removes a specific passenger and updates the Gunner.
	* @note original_name Leave_Transport
	* @note address 0x4DE670
	*/
	constexpr FootClass* LeaveTransport(FootClass* pPassenger) JMP_THIS(0x4DE670);

	/*!
	* @brief Adds a specific passenger and updates the Gunner.
	* @note original_name Leave_Transport
	* @note address 0x4DE630
	*/
	constexpr void EnterTransport(FootClass* pPassenger) JMP_THIS(0x4DE630);

	/*!
	* @brief Clears NavQueue
	* @note original_name Clear_Navigation_List
	* @note address 0x4DA1C0
	*/
	constexpr void ClearNavQueue() JMP_THIS(0x4DA1C0);

	/*!
	* @brief searches cell, sets destination, and returns whether unit is on that 
	* @note original_name Assign_Tiberium_As_Destination
	* @note address 0x4DCFE0
	*/
	constexpr bool MoveToTiberium(int radius, bool scanClose = false) JMP_THIS(0x4DCFE0);

	/*!
	* @brief  searches cell, sets destination, and returns whether unit is on that cell
	* @note original_name Assign_Weed_As_Destination
	* @note address 0x4DDB90
	*/
	constexpr bool MoveToWeed(int radius) JMP_THIS(0x4DDB90);

protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline FootClass(fake_noinit_t) noexcept : TechnoClass(fake_noinit_t{}) {}
	FootClass(noinit_t) : TechnoClass(fake_noinit_t{}) JMP_THIS(0x4D3540);
	FootClass(HouseClass* house) : FootClass(fake_noinit_t{}) JMP_THIS(0x4D31E0);
};
static_assert(sizeof(FootClass) == FootClass::ClassSize);
