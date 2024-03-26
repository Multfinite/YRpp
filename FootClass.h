/*
	Base class for units that can move (that have "feet")
*/

#pragma once

#include <TechnoClass.h>
#include <ParasiteClass.h>

//forward declarations
class LocomotionClass;
class TeamClass;

class NOVTABLE FootClass : public TechnoClass
{
public:
	static const auto AbsDerivateID = AbstractFlags::Foot;

	static constexpr constant_ptr<DynamicVectorClass<FootClass*>, 0x8B3DC0u> const Array{};

	//IPersistStream
	//Destructor
	virtual ~FootClass() RX;

	//AbstractClass
	//ObjectClass
	//MissionClass
	//TechnoClass
	virtual void Destroyed(ObjectClass *Killer) RX;
	virtual bool ForceCreate(CoordStruct& coord, DWORD dwUnk = 0) R0;

	//FootClass
	virtual void ReceiveGunner(FootClass* Gunner) RX;
	virtual void RemoveGunner(FootClass* Gunner) RX;
	virtual bool IsLeavingMap() const R0;
	virtual bool vt_entry_4E0() const R0;
	virtual bool CanDeployNow() const R0;
	virtual void AddSensorsAt(CellStruct cell) RX;
	virtual void RemoveSensorsAt(CellStruct cell) RX;
	virtual CoordStruct* vt_entry_4F0(CoordStruct* pCrd) R0;
	virtual void vt_entry_4F4() RX;
	virtual bool vt_entry_4F8() R0;
	virtual bool MoveTo(CoordStruct* pCrd) R0;
	virtual bool StopMoving() R0;
	virtual bool vt_entry_504() R0;
	virtual bool ChronoWarpTo(CoordStruct pDest) R0; // fsds... only implemented for one new YR map trigger, other chrono events repeat the code...
	virtual void Draw_A_SHP(
		SHPStruct *SHP, int idxFacing, Point2D * Coords, RectangleStruct *Rectangle,
		DWORD dwUnk5, DWORD dwUnk6, DWORD dwUnk7, ZGradient ZGradient,
		DWORD dwUnk9, int extraLight, DWORD dwUnk11, DWORD dwUnk12,
		DWORD dwUnk13, DWORD dwUnk14, DWORD dwUnk15, DWORD dwUnk16) RX;

	virtual void Draw_A_VXL(
		VoxelStruct *VXL, int HVAFrameIndex, int Flags, IndexClass<int, int> *Cache, RectangleStruct *Rectangle,
		Point2D *CenterPoint, Matrix3D *Matrix, DWORD dwUnk8, DWORD DrawFlags, DWORD dwUnk10) RX;

	virtual void GoBerzerk() RX;
	virtual void Panic() RX;
	virtual void UnPanic() RX; //never
	virtual void PlayIdleAnim(int nIdleAnimNumber) RX;
	virtual DWORD vt_entry_524() R0;
	virtual DWORD vt_entry_528(TypeList<BuildingTypeClass*>* bList, DWORD dwUnk2, DWORD dwUnk3) const R0;
	virtual BuildingClass* vt_entry_52C(BuildingTypeClass* bType, DWORD dwUnk2, DWORD dwUnk3, int* dwUnk4) const R0;
	virtual DWORD vt_entry_530(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3) const R0;
	virtual void vt_entry_534(DWORD dwUnk, DWORD dwUnk2) RX;
	virtual int GetCurrentSpeed() const R0;
	virtual DWORD vt_entry_53C(DWORD dwUnk) R0;
	virtual void vt_entry_540(DWORD dwUnk) RX;
	virtual void SetSpeedPercentage(double percentage) RX;
	virtual void vt_entry_548() RX;
	virtual void vt_entry_54C() RX;
	virtual bool vt_entry_550(DWORD dwUnk) R0;

	bool CanBeRecruited(HouseClass *ByWhom) const
		{ JMP_THIS(0x4DA230); }

	// non-virtual

	// only used by squid damage routines, normal wakes are created differently it seems
	// creates 3 wake animations behind the unit
	void CreateWakes(CoordStruct coords)
		{ JMP_THIS(0x629E90); }

	// can this jumpjet stay in this cell or not? (two jumpjets in one cell are not okay, locomotor kicks one of them out in the next frame)
	bool Jumpjet_LocationClear() const
		{ JMP_THIS(0x4135A0); }

	void Jumpjet_OccupyCell(CellStruct Cell)
		{ JMP_THIS(0x4E00B0); }

	// changes locomotor to the given one, Magnetron style
	// mind that this locks up the source too, Magnetron style
	void FootClass_ImbueLocomotor(FootClass *target, CLSID clsid)
		{ JMP_THIS(0x710000); }

	// var $this = this; $.each($this.Passengers, function(ix, p) { p.Location = $this.Location; });
	void UpdatePassengerCoords()
		{ JMP_THIS(0x7104F0); }

	void AbortMotion()
		{ JMP_THIS(0x4DF0D0); }

	bool UpdatePathfinding(CellStruct unkCell, CellStruct unkCell2, int unk3)
		{ JMP_THIS(0x4D3920); }

	// Removes the first passenger and updates the Gunner.
	FootClass* RemoveFirstPassenger()
		{ JMP_THIS(0x4DE710); }

	// Removes a specific passenger and updates the Gunner.
	FootClass* RemovePassenger(FootClass* pPassenger)
		{ JMP_THIS(0x4DE670); }

	// Adds a specific passenger and updates the Gunner.
	void EnterAsPassenger(FootClass* pPassenger)
		{ JMP_THIS(0x4DE630); }

	// Clears NavQueue
	void ClearNavQueue()
		{ JMP_THIS(0x4DA1C0); }

	// searches cell, sets destination, and returns whether unit is on that cell
	bool MoveToTiberium(int radius, bool scanClose = false)
		{ JMP_THIS(0x4DCFE0); }

	// searches cell, sets destination, and returns whether unit is on that cell
	bool MoveToWeed(int radius)
		{ JMP_THIS(0x4DDB90); }

	double GetThreatAvoidance() { JMP_THIS(0x4DC760); }

	//Constructor
	FootClass(HouseClass* pOwner) noexcept : FootClass(noinit_t())
		{ JMP_THIS(0x4D31E0); }

protected:
	explicit __forceinline FootClass(noinit_t) noexcept
		: TechnoClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int					PlanningPathIdx; // which planning path am I following?
	CellStruct      WaypointNearbyAccessibleCellDelta; // add to WaypointCell to get Nearby_Cell for this foot
	CellStruct      WaypointCell; // current waypoint cell
	DWORD        unknown_52C;	//unused?
	double			ThreatAvoidanceCoefficient;
	DWORD         WalkedFramesSoFar;
	int					PlayingMovingSound; // WalkedFramesSoFar;
	DWORD         MovingSoundDelay;

	DECLARE_PROPERTY(AudioController, Audio7);

	CellStruct      CurrentMapCoords;
	CellStruct      LastMapCoords; // ::UpdatePosition uses this to remove threat from last occupied cell, etc
	CellStruct      LastFlightMapCoords; // which cell was I occupying previously? only for AircraftTracker-tracked stuff
	CellStruct      CurrentJumpjetMapCoords; // unconfirmed, which cell am I occupying? only for jumpjets
	CoordStruct     Sqrt_ed_val_568;
	double          SpeedPercentage;
	double          SpeedMultiplier;
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, NavQueue2);
	AbstractClass* someabstract_5A0_followingmaybe;
	AbstractClass* NavCom; // possibly other objects as well
	AbstractClass* SuspendedNavCom;
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, NavQueue); // Stores sequence of movement destinations
	int             state5C4;
	FootClass*           target5C8_CandidateTarget;
	FootClass* CandidateTarget;
	BYTE            unknown_5D0;	//unused?
	bool            newtargetassigned_5D1;
	TeamClass*      Team;
	FootClass*      NextTeamMember;        //next unit in team
	CellClass*           cellptr5DC;
	FacingType             Path[24]; // list of directions to move in next, like tube directions
	DECLARE_PROPERTY(CDTimerClass, PathDelayTimer);
	int             TryTryAgain;
	DECLARE_PROPERTY(CDTimerClass, BaseAttackTimer);
	DECLARE_PROPERTY(CDTimerClass, SightTimer);
	DECLARE_PROPERTY(CDTimerClass, BlockagePathTimer);
	DECLARE_PROPERTY(ILocomotionPtr, Locomotor);
	CoordStruct       HeadTo;
	byte       CurrentTube;	//I'm in this tunnel
	byte              CurrentDirectionInTube;
	byte       WaypointIndex; // which waypoint in my planning path am I following?
	bool              IsToScatter;
	bool              IsScanLimited;
	bool              IsInitiated; // Is a fully joined member of a team, used for regroup etc. checks
	bool              IsNewNavCom; // ShouldScanForTarget;
	bool              IsPlanningToLook;
	bool              IsDeploying;
	bool              IsFiring;
	bool              AssignNewThreat;
	bool              ShouldEnterAbsorber; // orders the unit to enter the closest bio reactor
	bool              ShouldEnterOccupiable; // orders the unit to enter the closest battle bunker
	bool              ShouldGarrisonStructure; // orders the unit to enter the closest neutral building
	WORD			unknown_692; // unused ?
	FootClass*        ParasiteEatingMe; // the tdrone/squid that's eating me
	DWORD             ParasiteFireBlock;
	ParasiteClass*    ParasiteImUsing;	// my parasitic half, nonzero for, eg, terror drone or squiddy
	DECLARE_PROPERTY(CDTimerClass, ParalysisTimer); // for squid victims
	bool              unknown_bool_6AC;
	bool              IsAttackedByLocomotor; // the unit's locomotor is jammed by a magnetron
	bool              IsLetGoByLocomotor; // a magnetron attacked this unit and let it go. falling, landing, or sitting on the ground
	bool              IsRotating;
	bool              IsUnloading;
	bool              IsNavQueueLoop;
	bool              IsScattering;
	bool              isidle_6B3;
	bool              height_subtract_6B4;
	bool              iscrusher_6B5;
	bool              FrozenStill; // frozen in first frame of the proper facing - when magnetron'd or warping
	bool              blockage6B7;
	bool              removed;
	char field_6B9;
	char field_6BA;
	char field_6BB;
	char field_6BC;
	char field_6BD;
	char field_6BE;
	char field_6BF;
};

static constexpr size_t FootClassSize = sizeof(FootClass);
static_assert(FootClassSize == 0x6C0);
