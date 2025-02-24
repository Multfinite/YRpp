/*
	Base class for buildable objects
*/

#pragma once

#include "Matrix3D.h"
#include "RadioClass.h"
#include "RadBeam.h"
#include "TechnoTypeClass.h"
#include "CaptureManagerClass.h"
#include "SlaveManagerClass.h"
#include "TeamClass.h"
#include "TemporalClass.h"
#include "LaserDrawClass.h"
#include "Helpers/Template.h"
#include "StageClass.h"
#include "PlanningTokenClass.h"
#include "GeneralStructures.h"
#include "Timer.h"

//forward declarations
class AirstrikeClass;
class AnimClass;
class BulletClass;
class BuildingClass;
class CellClass;
class HouseClass;
class FootClass;
class HouseClass;
class InfantryTypeClass;
class ObjectTypeClass;
class ParticleSystemClass;
class SpawnManagerClass;
class WaveClass;

class EventClass;

#include "TransitionTimer.h"

struct VeterancyStruct
{
	VeterancyStruct() = default;

	explicit VeterancyStruct(double value) noexcept
	{
		this->Add(value);
	}

	void Add(int ownerCost, int victimCost) noexcept
	{
		this->Add(static_cast<double>(victimCost)
			/ (ownerCost * RulesClass::Instance->VeteranRatio));
	}

	void Add(double value) noexcept
	{
		auto val = this->Veterancy + value;

		if (val > RulesClass::Instance->VeteranCap)
		{
			val = RulesClass::Instance->VeteranCap;
		}

		this->Veterancy = static_cast<float>(val);
	}

	Rank GetRemainingLevel() const noexcept
	{
		if (this->Veterancy >= 2.0f)
		{
			return Rank::Elite;
		}

		if (this->Veterancy >= 1.0f)
		{
			return Rank::Veteran;
		}

		return Rank::Rookie;
	}

	bool IsNegative() const noexcept
	{
		return this->Veterancy < 0.0f;
	}

	bool IsRookie() const noexcept
	{
		return this->Veterancy >= 0.0f && this->Veterancy < 1.0f;
	}

	bool IsVeteran() const noexcept
	{
		return this->Veterancy >= 1.0f && this->Veterancy < 2.0f;
	}

	bool IsElite() const noexcept
	{
		return this->Veterancy >= 2.0f;
	}

	void Reset() noexcept
	{
		this->Veterancy = 0.0f;
	}

	void SetRookie(bool notReally = true) noexcept
	{
		this->Veterancy = notReally ? -0.25f : 0.0f;
	}

	void SetVeteran(bool yesReally = true) noexcept
	{
		this->Veterancy = yesReally ? 1.0f : 0.0f;
	}

	void SetElite(bool yesReally = true) noexcept
	{
		this->Veterancy = yesReally ? 2.0f : 0.0f;
	}

	float Veterancy { 0.0f };
};

class PassengersClass
{
public:
	int NumPassengers;
	FootClass* FirstPassenger;

	void AddPassenger(FootClass* pPassenger)
	{ JMP_THIS(0x4733A0); }

	FootClass* GetFirstPassenger() const
	{ return this->FirstPassenger; }

	FootClass* RemoveFirstPassenger()
	{ JMP_THIS(0x473430); }

	int GetTotalSize() const
	{ JMP_THIS(0x473460); }

	int IndexOf(FootClass* candidate) const
	{ JMP_THIS(0x473500); }

	PassengersClass() : NumPassengers(0), FirstPassenger(nullptr) { };

	~PassengersClass() { };
};

struct FlashData
{
	int DurationRemaining;
	bool FlashingNow;

	bool AI()
	{ JMP_THIS(0x4CC770); }
};

struct RecoilData
{
	enum class RecoilState : unsigned int
	{
		Inactive = 0,
		Compressing = 1,
		Holding = 2,
		Recovering = 3,
	};

	TurretControl Turret;
	float TravelPerFrame;
	float TravelSoFar;
	RecoilState State;
	int TravelFramesLeft;

	void AI()
	{ JMP_THIS(0x70ED10); }

	void Fire()
	{ JMP_THIS(0x70ECE0); }
};

class NOVTABLE TechnoClass : public RadioClass
{
public:
	static const auto AbsDerivateID = AbstractFlags::Techno;

	static constexpr constant_ptr<DynamicVectorClass<TechnoClass*>, 0xA8EC78u> const Array {};

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TechnoClass() RX;

	HRESULT STDMETHODCALLTYPE Load(__RPC__in_opt IStream* pStm) override JMP_THIS(0x70BF50);
	HRESULT STDMETHODCALLTYPE Save(__RPC__in_opt IStream* pStm, int32_t fClearDirty) override JMP_THIS(0x70C250);
	void Init() override JMP_THIS(0x6F3F40);
	void Detach(AbstractClass* target, bool all = true) override JMP_THIS(0x7077C0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x70C270);
	int Owner() const override JMP_THIS(0x6F9DB0);
	HouseClass* OwningHouse() const override JMP_THIS(0x6F9DC0);
	void AI() override JMP_THIS(0x6F9E50);
	void DetachAnim(AnimClass* anim) override JMP_THIS(0x710410);
	bool IsSelectable() const override JMP_THIS(0x6F32D0);
	VisualType VisualCharacter(VARIANT_BOOL specificOwner, HouseClass* whoIsAsking) const override JMP_THIS(0x703860);
	Action MouseOverCell(CellStruct const* pCell, bool checkFog = false, bool ignoreForce = false) const override JMP_THIS(0x6FFEC0);
	Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x700600);
	TechnoTypeClass* TechnoType() const override JMP_THIS(0x6F3270);
	DWORD Ownable() const override JMP_THIS(0x708B30);
	bool Repairable() const override JMP_THIS(0x701140);
	bool IsActive() const override JMP_THIS(0x7010D0);
	bool IsControllable() const override JMP_THIS(0x700C40);
	CoordStruct FLH(int idxWeapon, CoordStruct BaseCoords) const override JMP_THIS(0x6F3AD0);
	bool IsDisguised() const override JMP_THIS(0x41C010);
	bool IsDisguisedAs(HouseClass* target) const override JMP_THIS(0x41C020);
	bool Limbo() override JMP_THIS(0x6F6AC0);
	bool Unlimbo(const CoordStruct& position, Dir256 dir) override JMP_THIS(0x6F6CA0);
	void RegisterKillByObject(ObjectClass const* destroyedBy) override JMP_THIS(0x702D40);
	void RegisterKillByHouse(HouseClass const* destroyedBy) override JMP_THIS(0x703230);
	void Reveal() override JMP_THIS(0x703850);
	KickOutResult KickOutUnit(TechnoClass* pTechno, CellStruct Cell) override JMP_THIS(0x7099D0);
	void DrawBehind(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x6F60D0);
	void DrawExtras(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x6F5190);
	void Undiscover() override JMP_THIS(0x6F4A40);
	void See(bool incremental, int32_t arg_4) override JMP_THIS(0x70ADC0);
	bool Mark(MarkType value) override JMP_THIS(0x6F4A70);
	bool CanBeSelectedNow() const override JMP_THIS(0x6FC030);
	void ClickedAsTarget(int duration) override JMP_THIS(0x6F9DD0);
	bool Select() override JMP_THIS(0x6FBFA0);
	DamageState IronCurtain(int nDuration, HouseClass* pSource, bool ForceShield) override JMP_THIS(0x70E2B0);
	void StopAirstrikeTimer() override JMP_THIS(0x70E340);
	void StartAirstrikeTimer(int duration) override JMP_THIS(0x70E300);
	bool IsIronCurtained() const override JMP_THIS(0x41BF40);
	bool InRange(Coordinate coord, int idxWeapon) const override JMP_THIS(0x6F7970);
	int WeaponRange(int idxWeapon) const override JMP_THIS(0x7012C0);
	DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) override JMP_THIS(0x701900);
	void Destroy() override JMP_THIS(0x710460);
	DWORD PointsValue() const override JMP_THIS(0x707DD0);
	void UpdatePosition(PCPType how) override JMP_THIS(0x6F5090);
	RadioCommand ReceiveCommand(TechnoClass* pSender, RadioCommand command, AbstractClass*& pInOut) override JMP_THIS(0x6F4AB0);
	bool DiscoveredBy(HouseClass* pHouse) override JMP_THIS(0x6F4960);
	bool IsBeingWarpedOut() const override JMP_THIS(0x70C5B0);
	bool IsWarpingIn() const override JMP_THIS(0x70C5C0);
	bool IsWarpingSomethingOut() const override JMP_THIS(0x70C5D0);
	bool IsNotWarping() const override JMP_THIS(0x70C5F0);
	LightConvertClass* RemapColor() const override JMP_THIS(0x705D70);
	void OverrideMission(Mission mission, AbstractClass* target, AbstractClass* destination) override JMP_THIS(0x7013A0);
	bool RestoreMission() override JMP_THIS(0x7013E0);

	/*!
	* @note original_name Is_Unit_Factory
	* @note vtable_index 161:0x284
	* @note address 0x41BEE0
	*/
	virtual bool IsUnitFactory() const JMP_THIS(0x41BEE0);

	/*!
	* @note original_name Is_Cloakable
	* @note vtable_index 162:0x288
	* @note address 0x70C5A0
	*/
	virtual bool IsCloakable() const JMP_THIS(0x70C5A0);

	/*!
	* @note original_name Can_Scatter
	* @note vtable_index 163:0x28C
	* @note address 0x6F3280
	*/
	virtual bool CanScatter() const JMP_THIS(0x6F3280);

	/*!
	* @note original_name Has_Team
	* @note vtable_index 164:0x290
	* @note address 0x459D80
	*/
	virtual bool BelongsToATeam() const JMP_THIS(0x459D80);

	/*!
	* @note original_name Can_Heal_Repair
	* @note vtable_index 165:0x294
	* @note address 0x70BE80
	*/
	virtual bool ShouldSelfHealOneStep() const JMP_THIS(0x70BE80);

	/*!
	* @note original_name Is_Voxel
	* @note vtable_index 166:0x298
	* @note address 0x6F9E10
	*/
	virtual bool IsVoxel() const JMP_THIS(0x6F9E10);

	/*!
	* @note original_name Is_Door_Closed
	* @note vtable_index 167:0x29C
	* @note address 0x41BEF0
	*/
	virtual bool IsDoorClosed() JMP_THIS(0x41BEF0);

	/*!
	* @note original_name Is_Ready_To_Cloak
	* @note vtable_index 168:0x2A0
	* @note address 0x6FBDC0
	*/
	virtual bool IsReadyToCloak() const JMP_THIS(0x6FBDC0);

	/*!
	* @note original_name Is_Allowed_To_Recloak
	* @note vtable_index 169:0x2A4
	* @note address 0x6FBC90
	*/
	virtual bool ShouldNotBeCloaked() const JMP_THIS(0x6FBC90);

	/*!
	* @note original_name Turret_Facing
	* @note vtable_index 170:0x2A8
	* @note address 0x4E0150
	*/
	virtual DirStruct TurretFacing() const JMP_THIS(0x4E0150);

	/*!
	* @note original_name Is_Weapon_Equipped
	* @note vtable_index 171:0x2AC
	* @note address 0x701120
	*/
	virtual bool IsArmed() const JMP_THIS(0x701120);

	/*!
	* @note original_name Is_On_Elevation
	* @note vtable_index 172:0x2B0
	* @note address 0x70C620
	*/
	virtual bool OnElevation() const JMP_THIS(0x70C620);

	/*!
	* @note original_name Tiberium_Load
	* @note vtable_index 173:0x2B4
	* @note address 0x708BC0
	*/
	virtual double GetStoragePercentage() const JMP_THIS(0x708BC0);

	/*!
	* @note original_name Pip_Count
	* @note vtable_index 174:0x2B8
	* @note address 0x708C30
	*/
	virtual int GetPipFillLevel() const JMP_THIS(0x708C30);

	/*!
	* @note original_name Refund_Amount
	* @note vtable_index 175:0x2BC
	* @note address 0x70ADA0
	*/
	virtual int GetRefund() const JMP_THIS(0x70ADA0);

	/*!
	* @note original_name Risk
	* @note vtable_index 176:0x2C0
	* @note address 0x708B40
	*/
	virtual int GetThreatValue() const JMP_THIS(0x708B40);

	/*!
	* @note original_name Is_In_Same_Zone_As
	* @note vtable_index 177:0x2C4
	* @note address 0x459D90
	*/
	virtual bool IsInSameZoneAs(AbstractClass* pTarget) JMP_THIS(0x459D90);

	/*!
	* @note original_name vthk_0x2C8_TechnoClass
	* @note vtable_index 178:0x2C8
	* @note address 0x6FDA00
	*/
	virtual DirStruct UnknownFireangle(TechnoClass* techno) JMP_THIS(0x6FDA00);

	/*!
	* @note original_name Is_In_Same_Zone
	* @note vtable_index 179:0x2CC
	* @note address 0x707F60
	*/
	virtual bool IsInSameZoneAsCoords(const CoordStruct& coord) JMP_THIS(0x707F60);

	/*!
	* @note original_name How_Many_Survivors
	* @note vtable_index 180:0x2D0
	* @note address 0x6F3950
	*/
	virtual int GetCrewCount() const JMP_THIS(0x6F3950);

	/*!
	* @note original_name Anti_Air
	* @note vtable_index 181:0x2D4
	* @note address 0x41BF00
	*/
	virtual int GetAntiAirValue() const JMP_THIS(0x41BF00);

	/*!
	* @note original_name Anti_Armor
	* @note vtable_index 182:0x2D8
	* @note address 0x41BF10
	*/
	virtual int GetAntiArmorValue() const JMP_THIS(0x41BF10);

	/*!
	* @note original_name Anti_Infantry
	* @note vtable_index 183:0x2DC
	* @note address 0x41BF20
	*/
	virtual int GetAntiInfantryValue() const JMP_THIS(0x41BF20);

	/*!
	* @note original_name Scatter_Incoming
	* @note vtable_index 184:0x2E0
	* @note address 0x70D980
	*/
	virtual void GotHijacked() JMP_THIS(0x70D980);

	/*!
	* @note original_name What_Weapon_Should_I_Use
	* @note vtable_index 185:0x2E4
	* @note address 0x6F3330
	*/
	virtual int SelectWeapon(AbstractClass* pTarget) const JMP_THIS(0x6F3330);

	/*!
	* @note original_name What_Weapon_Should_I_Use_Naval
	* @note vtable_index 186:0x2E8
	* @note address 0x6F3820
	*/
	virtual int SelectNavalTargeting(AbstractClass* pTarget) const JMP_THIS(0x6F3820);

	/*!
	* @note original_name Z_Adjust
	* @note vtable_index 187:0x2EC
	* @note address 0x704350
	*/
	virtual int GetZAdjustment() const JMP_THIS(0x704350);

	/*!
	* @note original_name Z_Gradient
	* @note vtable_index 188:0x2F0
	* @note address 0x459DA0
	*/
	virtual ZGradient GetZGradient() const JMP_THIS(0x459DA0);

	/*!
	* @note original_name Get_Last_Flight_Coord
	* @note vtable_index 189:0x2F4
	* @note address 0x459DB0
	*/
	virtual CellStruct GetLastFlightMapCoords() const JMP_THIS(0x459DB0);

	/*!
	* @note original_name Set_Last_Flight_Coord
	* @note vtable_index 190:0x2F8
	* @note address 0x459DC0
	*/
	virtual void SetLastFlightMapCoords(CellStruct coord) JMP_THIS(0x459DC0);

	/*!
	* @note original_name Find_Exit_Cell
	* @note vtable_index 191:0x2FC
	* @note address 0x70AD50
	*/
	virtual Cell FindExitCell() const JMP_THIS(0x70AD50);

	/*!
	* @note original_name Firing_Offset
	* @note vtable_index 192:0x300
	* @note address 0x6F3D60
	*/
	virtual CoordStruct FiringOffset() const JMP_THIS(0x6F3D60);

	/*!
	* @note original_name Desired_Load_Dir
	* @note vtable_index 193:0x304
	* @note address 0x708C10
	*/
	virtual FacingType DesiredLoadDir(ObjectClass const* object, Cell* cell) const JMP_THIS(0x708C10);

	/*!
	* @note original_name Fire_Direction
	* @note vtable_index 194:0x308
	* @note address 0x708D70
	*/
	virtual DirStruct GetRealFacing() const JMP_THIS(0x708D70);

	/*!
	* @note original_name Crew_Type
	* @note vtable_index 195:0x30C
	* @note address 0x707D20
	*/
	virtual InfantryTypeClass* GetCrew() const JMP_THIS(0x707D20);

	/*!
	* @note original_name Can_Render_Move_In_Tube
	* @note vtable_index 196:0x310
	* @note address 0x700D10
	*/
	virtual bool CanRenderMoveInTube() const JMP_THIS(0x700D10);

	/*!
	* @note original_name Can_Deploy
	* @note vtable_index 197:0x314
	* @note address 0x700D50
	*/
	virtual bool CanDeploySlashUnload() const JMP_THIS(0x700D50);

	/*!
	* @note original_name Rearm_Delay
	* @note vtable_index 198:0x318
	* @note address 0x6FCFA0
	*/
	virtual int GetROF(int nWeapon) const JMP_THIS(0x6FCFA0);

	/*!
	* @note original_name Threat_Range
	* @note vtable_index 199:0x31C
	* @note address 0x707E60
	*/
	virtual int GetGuardRange(int dwUnk) const JMP_THIS(0x707E60);

	/*!
	* @note original_name Is_Allowed_To_Leave_Map
	* @note vtable_index 200:0x320
	* @note address 0x459DD0
	*/
	virtual bool IsAllowedTo_Leave_Map() const JMP_THIS(0x459DD0);

	/*!
	* @note original_name Is_Visible_On_Radar
	* @note vtable_index 201:0x324
	* @note address 0x70D1D0
	*/
	virtual bool IsRadarVisible(int* pOutDetection) const JMP_THIS(0x70D1D0);

	/*!
	* @note original_name Is_Visible_On_Sensor
	* @note vtable_index 202:0x328
	* @note address 0x70D420
	*/
	virtual bool IsSensorVisibleToPlayer() const JMP_THIS(0x70D420);

	/*!
	* @note original_name Is_Visible_On_Sensor_House
	* @note vtable_index 203:0x32C
	* @note address 0x70D460
	*/
	virtual bool IsSensorVisibleToHouse(HouseClass* House) const JMP_THIS(0x70D460);

	/*!
	* @note original_name Is_Renovator
	* @note vtable_index 204:0x330
	* @note address 0x41BF30
	*/
	virtual bool IsEngineer() const JMP_THIS(0x41BF30);

	/*!
	* @note original_name Proceed_To_Next_Planning_Waypoint
	* @note vtable_index 205:0x334
	* @note address 0x459DE0
	*/
	virtual void ProceedToNextPlanningWaypoint() JMP_THIS(0x459DE0);

	/*!
	* @note original_name Scan_For_Tiberium
	* @note vtable_index 206:0x338
	* @note address 0x70F8F0
	*/
	virtual CellStruct* ScanForTiberium(CellStruct*, int range, DWORD dwUnk3) const JMP_THIS(0x70F8F0);

	/*!
	* @note original_name Try_Grinding
	* @note vtable_index 207:0x33C
	* @note address 0x459DF0
	*/
	virtual bool EnterGrinder() JMP_THIS(0x459DF0);

	/*!
	* @note original_name Try_Absorbing
	* @note vtable_index 208:0x340
	* @note address 0x459E00
	*/
	virtual bool EnterBioReactor() JMP_THIS(0x459E00);

	/*!
	* @note original_name Try_Bunkering
	* @note vtable_index 209:0x344
	* @note address 0x459E10
	*/
	virtual bool EnterTankBunker() JMP_THIS(0x459E10);

	/*!
	* @note original_name Try_To_Occupy
	* @note vtable_index 210:0x348
	* @note address 0x459E20
	*/
	virtual bool EnterBattleBunker() JMP_THIS(0x459E20);

	/*!
	* @note original_name Try_Garrisoning
	* @note vtable_index 211:0x34C
	* @note address 0x459E30
	*/
	virtual bool GarrisonStructure() JMP_THIS(0x459E30);

	/*!
	* @note original_name Is_Power_Online
	* @note vtable_index 212:0x350
	* @note address 0x701190
	*/
	virtual bool IsPowerOnline() const JMP_THIS(0x701190);

	/*!
	* @note original_name Queue_Voice
	* @note vtable_index 213:0x354
	* @note address 0x708D90
	*/
	virtual void QueueVoice(int idxVoc) JMP_THIS(0x708D90);

	/*!
	* @note original_name Response_Enter
	* @note vtable_index 214:0x358
	* @note address 0x709020
	*/
	virtual int VoiceEnter() JMP_THIS(0x709020);

	/*!
	* @note original_name Response_Harvest
	* @note vtable_index 215:0x35C
	* @note address 0x709060
	*/
	virtual int VoiceHarvest() JMP_THIS(0x709060);

	/*!
	* @note original_name Response_Select
	* @note vtable_index 216:0x360
	* @note address 0x708EB0
	*/
	virtual int VoiceSelect() JMP_THIS(0x708EB0);

	/*!
	* @note original_name Response_Capture
	* @note vtable_index 217:0x364
	* @note address 0x708DC0
	*/
	virtual int VoiceCapture() JMP_THIS(0x708DC0);

	/*!
	* @note original_name Response_Move
	* @note vtable_index 218:0x368
	* @note address 0x708FC0
	*/
	virtual int VoiceMove() JMP_THIS(0x708FC0);

	/*!
	* @note original_name Response_Deploy
	* @note vtable_index 219:0x36C
	* @note address 0x708E00
	*/
	virtual int VoiceDeploy() JMP_THIS(0x708E00);

	/*!
	* @note original_name Response_Attack
	* @note vtable_index 220:0x370
	* @note address 0x7090A0
	*/
	virtual int VoiceAttack(ObjectClass* pTarget) JMP_THIS(0x7090A0);

	/*!
	* @note original_name Clicked_Event
	* @note vtable_index 221:0x374
	* @note address 0x6FFE00
	*/
	virtual bool ClickedEvent(EventType event) JMP_THIS(0x6FFE00);

	/*!
	* @note original_name Player_Assign_Mission
	* @note vtable_index 222:0x378
	* @note address 0x6FFBE0
	*/
	virtual bool ClickedMission(Mission Mission, ObjectClass* pTarget, CellClass* TargetCell, CellClass* NearestTargetCellICanEnter) JMP_THIS(0x6FFBE0);

	/*!
	* @note original_name Cant_Move
	* @note vtable_index 223:0x37C
	* @note address 0x70EFD0
	*/
	virtual bool IsUnderEMP() const JMP_THIS(0x70EFD0);

	/*!
	* @note original_name Is_Paralyzed
	* @note vtable_index 224:0x380
	* @note address 0x459E40
	*/
	virtual bool IsParalyzed() const JMP_THIS(0x459E40);

	/*!
	* @note original_name Is_Idling
	* @note vtable_index 225:0x384
	* @note address 0x41BF80
	*/
	virtual bool CanCheer() const JMP_THIS(0x41BF80);

	/*!
	* @note original_name Cheer
	* @note vtable_index 226:0x388
	* @note address 0x41BF90
	*/
	virtual void Cheer(bool Force) JMP_THIS(0x41BF90);

	/*!
	* @note original_name Get_Max_Speed
	* @note vtable_index 227:0x38C
	* @note address 0x70EFE0
	*/
	virtual int GetDefaultSpeed() const JMP_THIS(0x70EFE0);

	/*!
	* @note original_name Reduce_Ammunition
	* @note vtable_index 228:0x390
	* @note address 0x70D670
	*/
	virtual void DecreaseAmmo() JMP_THIS(0x70D670);

	/*!
	* @note original_name Attach_Cargo
	* @note vtable_index 229:0x394
	* @note address 0x710670
	*/
	virtual void AddPassenger(FootClass* pPassenger) JMP_THIS(0x710670);

	/*!
	* @note original_name Can_Target_Terrain_Or_Disguise
	* @note vtable_index 230:0x398
	* @note address 0x70EF00
	*/
	virtual bool CanDisguiseAs(AbstractClass* pTarget) const JMP_THIS(0x70EF00);

	/*!
	* @note original_name Target_Something_Nearby
	* @note vtable_index 231:0x39C
	* @note address 0x709820
	*/
	virtual bool TargetAndEstimateDamage(CoordStruct& coord, ThreatType threat) JMP_THIS(0x709820);

	/*!
	* @note original_name Stun
	* @note vtable_index 232:0x3A0
	* @note address 0x6FCD40
	*/
	virtual void Stun() JMP_THIS(0x6FCD40);

	/*!
	* @note original_name vthk_0x3A4_TechnoClass
	* @note vtable_index 233:0x3A4
	* @note address 0x6F7660
	*/
	virtual bool TriggersCellInset(AbstractClass* pTarget) JMP_THIS(0x6F7660);

	/*!
	* @note original_name In_Range_Of
	* @note vtable_index 234:0x3A8
	* @note address 0x6F77B0
	*/
	virtual bool IsCloseEnough(AbstractClass* pTarget, int idxWeapon) const JMP_THIS(0x6F77B0);

	/*!
	* @note original_name In_Range_Of_Object
	* @note vtable_index 235:0x3AC
	* @note address 0x6F7780
	*/
	virtual bool IsCloseEnoughToAttack(AbstractClass* pTarget) const JMP_THIS(0x6F7780);

	/*!
	* @note original_name In_Range_Of_Cell
	* @note vtable_index 236:0x3B0
	* @note address 0x6F7930
	*/
	virtual bool IsCloseEnoughToAttackCoords(const CoordStruct& Coords) const JMP_THIS(0x6F7930);

	/*!
	* @note original_name In_Range1
	* @note vtable_index 237:0x3B4
	* @note address 0x6F78D0
	*/
	virtual bool InAuxiliarySearchRange(AbstractClass* pTarget) const JMP_THIS(0x6F78D0);

	/*!
	* @note original_name Death_Announcement
	* @note vtable_index 238:0x3BC
	* @note address 0x4C9150
	*/
	virtual void Destroyed(ObjectClass* Killer) = 0;

	/*!
	* @note original_name Can_Fire_With_Range
	* @note vtable_index 239:0x3BC
	* @note address 0x6FC090
	*/
	virtual FireError GetFireErrorWithoutRange(AbstractClass* pTarget, int nWeaponIndex) const JMP_THIS(0x6FC090);

	/*!
	* @note original_name Can_Fire
	* @note vtable_index 240:0x3C0
	* @note address 0x6FC0B0
	*/
	virtual FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const JMP_THIS(0x6FC0B0);

	/*!
	* @note original_name Greatest_Threat
	* @note vtable_index 241:0x3C4
	* @note address 0x6F8DF0
	*/
	virtual AbstractClass* GreatestThreat(ThreatType threat, CoordStruct* pCoord, bool onlyTargetHouseEnemy) JMP_THIS(0x6F8DF0);

	/*!
	* @note original_name Assign_Target
	* @note vtable_index 242:0x3C8
	* @note address 0x6FCDB0
	*/
	virtual void SetTarget(AbstractClass* pTarget) JMP_THIS(0x6FCDB0);

	/*!
	* @note original_name Fire_At
	* @note vtable_index 243:0x3CC
	* @note address 0x6FDD50
	*/
	virtual BulletClass* Fire(AbstractClass* pTarget, int nWeaponIndex) JMP_THIS(0x6FDD50);

	/*!
	* @note original_name Enter_Guard_Mode
	* @note vtable_index 244:0x3D0
	* @note address 0x70F850
	*/
	virtual void Guard() JMP_THIS(0x70F850);

	/*!
	* @note original_name Captured
	* @note vtable_index 245:0x3D4
	* @note address 0x7014A0
	*/
	virtual bool SetOwningHouse(HouseClass* pHouse, bool announce = true) JMP_THIS(0x7014A0);

	/*!
	* @note original_name Rock
	* @note vtable_index 246:0x3D8
	* @note address 0x70B280
	*/
	virtual void Rock(Coordinate& coord, float rockForwardMult, char rockForwardHalf) JMP_THIS(0x70B280);

	/*!
	* @note original_name On_Destroyed
	* @note vtable_index 247:0x3DC
	* @note address 0x459E50
	*/
	virtual bool Crash(ObjectClass* Killer) JMP_THIS(0x459E50);

	/*!
	* @note original_name Can_Area_Fire
	* @note vtable_index 248:0x3E0
	* @note address 0x70DD50
	*/
	virtual bool IsAreaFire() const JMP_THIS(0x70DD50);

	/*!
	* @note original_name Can_Not_Spray_Attack_1
	* @note vtable_index 249:0x3E4
	* @note address 0x70DD70
	*/
	virtual int IsNotSprayAttack() const JMP_THIS(0x70DD70);

	/*!
	* @note original_name vthk_0x3E8_TechnoClass
	* @note vtable_index 250:0x3E8
	* @note address 0x70DD90
	*/
	virtual int GetSecondaryWeaponIndex() const JMP_THIS(0x70DD90);

	/*!
	* @note original_name Can_Not_Spray_Attack_2
	* @note vtable_index 251:0x3EC
	* @note address 0x70DDA0
	*/
	virtual int IsNotSprayAttack2() const JMP_THIS(0x70DDA0);

	/*!
	* @note original_name Get_Current_Weapon
	* @note vtable_index 252:0x3F0
	* @note address 0x70E120
	*/
	virtual WeaponStruct* GetDeployWeapon() const JMP_THIS(0x70E120);

	/*!
	* @note original_name Get_Primary_Weapon
	* @note vtable_index 253:0x3F4
	* @note address 0x70E1A0
	*/
	virtual WeaponStruct* GetTurretWeapon() const JMP_THIS(0x70E1A0);

	/*!
	* @note original_name Get_Weapon
	* @note vtable_index 254:0x3F8
	* @note address 0x70E140
	*/
	virtual WeaponStruct* GetWeapon(int nWeaponIndex) const JMP_THIS(0x70E140);

	/*!
	* @note original_name Is_Turret_Equipped
	* @note vtable_index 255:0x3FC
	* @note address 0x41BFA0
	*/
	virtual bool HasTurret() const JMP_THIS(0x41BFA0);

	/*!
	* @note original_name Can_Occupy_Fire
	* @note vtable_index 256:0x400
	* @note address 0x41BFB0
	*/
	virtual bool CanOccupyFire() const JMP_THIS(0x41BFB0);

	/*!
	* @note original_name Get_Occupy_Weapon_Range_Bonus
	* @note vtable_index 257:0x404
	* @note address 0x41BFC0
	*/
	virtual int GetOccupyRangeBonus() const JMP_THIS(0x41BFC0);

	/*!
	* @note original_name Get_Occupant_Count
	* @note vtable_index 258:0x408
	* @note address 0x41BFD0
	*/
	virtual int GetOccupantCount() const JMP_THIS(0x41BFD0);

	/*!
	* @note original_name Renovate
	* @note vtable_index 259:0x40C
	* @note address 0x701410
	*/
	virtual void OnFinishRepair() JMP_THIS(0x701410);

	/*!
	* @note original_name Cloaking_AI
	* @note vtable_index 260:0x410
	* @note address 0x6FB740
	*/
	virtual void UpdateCloak(bool bUnk = 1) JMP_THIS(0x6FB740);

	/*!
	* @note original_name Create_Gap
	* @note vtable_index 261:0x414
	* @note address 0x6FB170
	*/
	virtual void CreateGap() JMP_THIS(0x6FB170);

	/*!
	* @note original_name Delete_Gap
	* @note vtable_index 262:0x418
	* @note address 0x6FB470
	*/
	virtual void DestroyGap() JMP_THIS(0x6FB470);

	/*!
	* @note original_name Rocking_AI
	* @note vtable_index 263:0x41C
	* @note address 0x70B570
	*/
	virtual void RockingAI() JMP_THIS(0x70B570);

	/*!
	* @note original_name Sensed
	* @note vtable_index 264:0x420
	* @note address 0x6F4EB0
	*/
	virtual void Sensed() JMP_THIS(0x6F4EB0);

	/*!
	* @note original_name Reload_Ammo_AI
	* @note vtable_index 265:0x424
	* @note address 0x6FB010
	*/
	virtual void Reload() JMP_THIS(0x6FB010);

	/*!
	* @note original_name Attack_Greatest_Threat
	* @note vtable_index 266:0x428
	* @note address 0x41BFE0
	*/
	virtual void AttackGreatestThreat() JMP_THIS(0x41BFE0);

	/*!
	* @note original_name Get_Attack_Coord
	* @note vtable_index 267:0x42C
	* @note address 0x705CA0
	*/
	virtual CoordStruct* GetAttackCoordinates(CoordStruct* pCrd) const JMP_THIS(0x705CA0);

	/*!
	* @note original_name Is_Not_Warping_Out
	* @note vtable_index 268:0x430
	* @note address 0x705D50
	*/
	virtual bool IsNotWarpingIn() const JMP_THIS(0x705D50);

	/*!
	* @note original_name vthk_0x434_TechnoClass
	* @note vtable_index 269:0x434
	* @note address 0x41BFF0
	*/
	virtual bool vt_entry_434() const JMP_THIS(0x41BFF0);

	/*!
	* @note original_name Draw_Action_Lines
	* @note vtable_index 270:0x438
	* @note address 0x459E60
	*/
	virtual void DrawActionLines(bool Force, DWORD dwUnk2) JMP_THIS(0x459E60);

	/*!
	* @note original_name Disguise_Blit_Flags
	* @note vtable_index 271:0x43C
	* @note address 0x70ED80
	*/
	virtual DWORD GetDisguiseFlags(DWORD existingFlags) const JMP_THIS(0x70ED80);

	/*!
	* @note original_name Disguise_Been_Seen
	* @note vtable_index 272:0x440
	* @note address 0x70EE30
	*/
	virtual bool IsClearlyVisibleTo(HouseClass* House) const JMP_THIS(0x70EE30);

	/*!
	* @note original_name Draw_Voxel
	* @note vtable_index 273:0x444
	* @note address 0x706640
	*/
	virtual void DrawVoxel(VoxelStruct const& voxel, DWORD dwUnk2, short /*FacingType*/ facing,
		IndexClass<int, int> const& voxelIndex, RectangleStruct const& rect, Point2D const& location,
		Matrix3D const& Matrix, int Intensity, DWORD dwUnk9, DWORD dwUnk10) JMP_THIS(0x706640);

	/*!
	* @note original_name Draw_Health_Bar_Unselected
	* @note vtable_index 274:0x448
	* @note address 0x6F60C0
	*/
	virtual void DrawHealthBarUnselected(int x, int y) JMP_THIS(0x6F60C0);

	/*!
	* @note original_name Draw_Health_Bar_Selected
	* @note vtable_index 275:0x44C
	* @note address 0x6F64A0
	*/
	virtual void DrawHealthBar(Point2D* pLocation, RectangleStruct* pBounds, bool bUnk3) const JMP_THIS(0x6F64A0);

	/*!
	* @note original_name Draw_Pips
	* @note vtable_index 276:0x450
	* @note address 0x709A90
	*/
	virtual void DrawPipScalePips(Point2D* pLocation, Point2D* pOriginalLocation, RectangleStruct* pBounds) const JMP_THIS(0x709A90);

	/*!
	* @note original_name Draw_Veterancy_Pips
	* @note vtable_index 277:0x454
	* @note address 0x70A990
	*/
	virtual void DrawVeterancyPips(Point2D* pLocation, RectangleStruct* pBounds) const JMP_THIS(0x70A990);

	/*!
	* @note original_name Draw_Selected_Overlay
	* @note vtable_index 278:0x458
	* @note address 0x70AA60
	*/
	virtual void DrawExtraInfo(Point2D const& location, Point2D const& originalLocation, RectangleStruct const& bounds) const JMP_THIS(0x70AA60);

	/*!
	* @note original_name Do_Uncloak
	* @note vtable_index 279:0x45C
	* @note address 0x7036C0
	*/
	virtual void Uncloak(bool bPlaySound) JMP_THIS(0x7036C0);

	/*!
	* @note original_name Do_Cloak
	* @note vtable_index 280:0x460
	* @note address 0x703770
	*/
	virtual void Cloak(bool bPlaySound) JMP_THIS(0x703770);

	/*!
	* @note original_name Flash_Tint_Stage
	* @note vtable_index 281:0x464
	* @note address 0x70D190
	*/
	virtual int32_t FlashTintStage(int32_t tintStage) const JMP_THIS(0x70D190);

	/*!
	* @note original_name Init_Particles
	* @note vtable_index 282:0x468
	* @note address 0x41C000
	*/
	virtual void UpdateRefinerySmokeSystems() JMP_THIS(0x41C000);

	/*!
	* @note original_name Disguise_As
	* @note vtable_index 283:0x46C
	* @note address 0x70E280
	*/
	virtual void DisguiseAs(AbstractClass* target) JMP_THIS(0x70E280);

	/*!
	* @note original_name Clear_Disguise
	* @note vtable_index 284:0x470
	* @note address 0x41C030
	*/
	virtual InfantryTypeClass* ClearDisguise() JMP_THIS(0x41C030);

	/*!
	* @note original_name Is_Ready_To_Random_Animate
	* @note vtable_index 285:0x474
	* @note address 0x7099E0
	*/
	virtual bool IsReadyToRandomAnimate() JMP_THIS(0x7099E0);

	/*!
	* @note original_name Random_Animate
	* @note vtable_index 286:0x478
	* @note address 0x41C040
	*/
	virtual bool RandomAnimate() JMP_THIS(0x41C040);

	/*!
	* @note original_name FootClass_4D94A0
	* @note vtable_index 287:0x47C
	* @note address 0x709A20
	*/
	virtual void vt_entry_47C(DWORD dwUnk) JMP_THIS(0x709A20);

	/*!
	* @note original_name Assign_Destination
	* @note vtable_index 288:0x480
	* @note address 0x709A30
	*/
	virtual void SetDestination(AbstractClass* target, bool a2) JMP_THIS(0x709A30);

	/*!
	* @note original_name Enter_Idle_Mode
	* @note vtable_index 289:0x484
	* @note address 0x709A40
	*/
	virtual bool EnterIdleMode(bool initial, bool a2) JMP_THIS(0x709A40);

	/*!
	* @note original_name Reveal_In_Range
	* @note vtable_index 290:0x488
	* @note address 0x70AF50
	*/
	virtual void UpdateSight(DWORD dwUnk, DWORD dwUnk2, bool toOtherHouse, HouseClass* otherHouse, int sightRange) JMP_THIS(0x70AF50);

	/*!
	* @note original_name Reveal
	* @note vtable_index 291:0x48C
	* @note address 0x70B1D0
	*/
	virtual void Reveal(bool incremental, int unused, bool toOtherHouse, HouseClass* otherHouse) JMP_THIS(0x70B1D0);

	/*!
	* @note original_name Force_Create
	* @note vtable_index 292:0x490
	* @note address 0x0
	*/
	virtual bool ForceCreate(CoordStruct& coord, DWORD dwUnk = 0) = 0;

	/*!
	* @note original_name Radar_Track_Object
	* @note vtable_index 293:0x494
	* @note address 0x70CC90
	*/
	virtual int RadarTrackingStart() JMP_THIS(0x70CC90);

	/*!
	* @note original_name Radar_Untrack_Object
	* @note vtable_index 294:0x498
	* @note address 0x70CCC0
	*/
	virtual int RadarTrackingStop() JMP_THIS(0x70CCC0);

	/*!
	* @note original_name Radar_Tracking_Flash
	* @note vtable_index 295:0x49C
	* @note address 0x70CCF0
	*/
	virtual void RadarTrackingFlash() JMP_THIS(0x70CCF0);

	/*!
	* @note original_name Radar_Tracking_AI
	* @note vtable_index 296:0x4A0
	* @note address 0x70D990
	*/
	virtual void RadarTrackingUpdate(bool forced) JMP_THIS(0x70D990);

	/*!
	* @note original_name Targeting_70F000
	* @note vtable_index 297:0x4A4
	* @note address 0x70F000
	*/
	virtual int RespondMegaEventMission(EventClass* pRespondTo) JMP_THIS(0x70F000);

	/*!
	* @note original_name Targeting_70F010
	* @note vtable_index 298:0x4A8
	* @note address 0x70F010
	*/
	virtual void ClearMegaMissionData() JMP_THIS(0x70F010);

	/*!
	* @note original_name Targeting_70F020
	* @note vtable_index 299:0x4AC
	* @note address 0x70F020
	*/
	virtual bool HaveMegaMission() const JMP_THIS(0x70F020);

	/*!
	* @note original_name Targeting_70F030
	* @note vtable_index 300:0x4B0
	* @note address 0x70F030
	*/
	virtual bool HaveAttackMoveTarget() const JMP_THIS(0x70F030);

	/*!
	* @note original_name Targeting_70F040
	* @note vtable_index 301:0x4B4
	* @note address 0x70F040
	*/
	virtual Mission GetMegaMission() const JMP_THIS(0x70F040);

	/*!
	* @note original_name Get_Target_Coord
	* @note vtable_index 302:0x4B8
	* @note address 0x70F050
	*/
	virtual Coordinate* GetAttackMoveCoords(void* retstr) JMP_THIS(0x70F050);

	/*!
	* @note original_name Can_Use_Waypoint
	* @note vtable_index 303:0x4BC
	* @note address 0x70F070
	*/
	virtual bool CanUseWaypoint() const JMP_THIS(0x70F070);

	/*!
	* @note original_name Can_Attack_Move
	* @note vtable_index 304:0x4C0
	* @note address 0x70F090
	*/
	virtual bool CanAttackOnTheMove() const JMP_THIS(0x70F090);

	/*!
	* @note original_name Targeting_70F0E0
	* @note vtable_index 305:0x4C4
	* @note address 0x70F0E0
	*/
	virtual bool MegaMissionIsAttackMove() const JMP_THIS(0x70F0E0);

	/*!
	* @note original_name Targeting_70F0F0
	* @note vtable_index 306:0x4C8
	* @note address 0x70F0F0
	*/
	virtual bool ContinueMegaMission() JMP_THIS(0x70F0F0);

	/*!
	* @note original_name Targeting_70F100
	* @note vtable_index 307:0x4CC
	* @note address 0x70F100
	*/
	virtual void UpdateAttackMove() JMP_THIS(0x70F100);

	/*!
	* @note original_name Targeting_70F110
	* @note vtable_index 308:0x4D0
	* @note address 0x70F110
	*/
	virtual bool RefreshMegaMission() JMP_THIS(0x70F110);

	//non-virtual

	// (re-)starts the reload timer
	void StartReloading()
	{ JMP_THIS(0x6FB080); }

	bool ShouldSuppress(CellStruct* coords) const
	{ JMP_THIS(0x6F79A0); }

	// smooth operator
	const char* get_ID() const
	{
		auto const pType = this->Type();
		return pType ? pType->get_ID() : nullptr;
	}

	int TimeToBuild() const
	{ JMP_THIS(0x6F47A0); }

	bool IsMindControlled() const
	{ JMP_THIS(0x7105E0); }

	bool CanBePermaMindControlled() const
	{ JMP_THIS(0x53C450); }

	LaserDrawClass* CreateLaser(ObjectClass* pTarget, int idxWeapon, WeaponTypeClass* pWeapon, const CoordStruct& Coords)
	{ JMP_THIS(0x6FD210); }

	/*
	 *  Cell->AddThreat(this->Owner, -this->ThreatPosed);
	 *  this->ThreatPosed = 0;
	 *  int Threat = this->CalculateThreat(); // this is another gem of a function, to be revealed another time...
	 *  this->ThreatPosed = Threat;
	 *  Cell->AddThreat(this->Owner, Threat);
	 */
	void UpdateThreatInCell(CellClass* Cell)
	{ JMP_THIS(0x70F6E0); }

	// CanTargetWhatAmI is a bitfield, if(!(CanTargetWhatAmI & (1 << tgt->WhatAmI())) { fail; }

	// slave of the next one
	bool CanAutoTargetObject(
		ThreatType targetFlags,
		int canTargetWhatAmI,
		int wantedDistance,
		TechnoClass* pTarget,
		int* pThreatPosed,
		DWORD dwUnk,
		CoordStruct* pSourceCoords) const
	{
		JMP_THIS(0x6F7CA0);
	}

	// called by AITeam Attack Target Type and autoscan
	bool TryAutoTargetObject(
		ThreatType targetFlags,
		int canTargetWhatAmI,
		CellStruct* pCoords,
		DWORD dwUnk1,
		DWORD* dwUnk2,
		int* pThreatPosed,
		DWORD dwUnk3)
	{
		JMP_THIS(0x6F8960);
	}

	void Reactivate()
	{ JMP_THIS(0x70FBE0); }

	void Deactivate()
	{ JMP_THIS(0x70FC90); }


	// this should be the transport, but it's unused
	// marks passenger as "InOpenTopped" for targeting, range scanning and other purposes
	void EnteredOpenTopped(TechnoClass* pWho)
	{ JMP_THIS(0x710470); }

	// this should be the transport, but it's unused
	// reverses the above
	void ExitedOpenTopped(TechnoClass* pWho)
	{ JMP_THIS(0x7104A0); }

	// called when the source unit dies - passengers are about to get kicked out, this basically calls ->ExitedOpenTransport on each passenger
	void MarkPassengersAsExited()
	{ JMP_THIS(0x7104C0); }

	// for gattlings
	void SetCurrentWeaponStage(int idx)
	{ JMP_THIS(0x70DDD0); }

	void SetArchiveTarget(AbstractClass* pTarget)
	{ JMP_THIS(0x70C610); }

	void DrawVoxelShadow(VoxelStruct* vxl, int shadow_index, VoxelIndexKey vxl_index_key, IndexClass<ShadowVoxelIndexKey, VoxelCacheStruct*>* shadow_cache,
		RectangleStruct* bound, Point2D* a3, Matrix3D* matrix, bool again, Surface* surface, Point2D shadow_point)
	{
		JMP_THIS(0x706BD0);
	}

	void DrawObject(SHPStruct* pSHP, int nFrame, Point2D* pLocation, RectangleStruct* pBounds,
		int, int, int nZAdjust, ZGradient eZGradientDescIdx, int, int nBrightness, int TintColor,
		SHPStruct* pZShape, int nZFrame, int nZOffsetX, int nZOffsetY, int);

	int sub_70DE00(int State)
	{ JMP_THIS(0x70DE00); }

	int __fastcall ClearPlanningTokens(EventClass* pEvent)
	{ JMP_STD(0x6386E0); }

	void SetTargetForPassengers(AbstractClass* pTarget)
	{ JMP_THIS(0x710550); }

	void KillPassengers(TechnoClass* pSource)
	{ JMP_THIS(0x707CB0); }

	// returns the house that created this object (factoring in Mind Control)
	HouseClass* GetOriginalOwner() const
	{ JMP_THIS(0x70F820); }

	void FireDeathWeapon(int additionalDamage)
	{ JMP_THIS(0x70D690); }

	bool HasAbility(Ability ability) const
	{ JMP_THIS(0x70D0D0); }

	void ClearSidebarTabObject() const
	{ JMP_THIS(0x734270); }

	LightConvertClass* GetDrawer() const
	{ JMP_THIS(0x705D70); }

	int GetEffectTintIntensity(int currentIntensity)
	{ JMP_THIS(0x70E360); }

	int GetInvulnerabilityTintIntensity(int currentIntensity)
	{ JMP_THIS(0x70E380); }

	int GetAirstrikeTintIntensity(int currentIntensity)
	{ JMP_THIS(0x70E4B0); }

	int CombatDamage(int nWeaponIndex) const
	{ JMP_THIS(0x6F3970); }

	WeaponStruct* GetPrimaryWeapon() const
	{ JMP_THIS(0x70E1A0); }

	bool TryNextPlanningTokenNode()
	{ JMP_THIS(0x6385C0); }

	int GetIonCannonValue(AIDifficulty difficulty) const;

	int GetIonCannonValue(AIDifficulty difficulty, int maxStrength) const
	{
		// what TS does
		if (maxStrength > 0 && this->Strength > maxStrength)
		{
			return (this->KindOf() == AbstractType::Building) ? 3 : 1;
		}

		return this->GetIonCannonValue(difficulty);
	}

	// Invokes AI response on their 'base' being attacked. Used by buildings, ToProtect=true technos and Whiner=true team members.
	void BaseIsAttacked(TechnoClass* pEnemy)
	{ JMP_THIS(0x708080); }

	//Constructor
	TechnoClass(HouseClass* pOwner) noexcept
		: TechnoClass(noinit_t())
	{
		JMP_THIS(0x6F2B40);
	}

protected:
	explicit __forceinline TechnoClass(noinit_t) noexcept
		: RadioClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
public:
	DECLARE_PROPERTY(FlashData, Flashing);
	DECLARE_PROPERTY(StageClass, Animation); // how the unit animates
	DECLARE_PROPERTY(PassengersClass, Passengers);
	TechnoClass*     Transporter; // unit carrying me
	int              LastFireBulletFrame;
	int              CurrentTurretNumber; // for IFV/gattling/charge turrets
	int              unknown_int_128;
	AnimClass*       BehindAnim;
	AnimClass*       DeployAnim;
	bool             InAir;
	int              CurrentWeaponNumber; // for IFV/gattling
	Rank             CurrentRanking; // only used for promotion detection
	int              CurrentGattlingStage;
	int              GattlingValue; // sum of RateUps and RateDowns
	int              TurretAnimFrame;
	HouseClass* InitialOwner; // only set in ctor
	DECLARE_PROPERTY(VeterancyStruct, Veterancy);
	DWORD            align_154;
	double           ArmorMultiplier;
	double           FirepowerMultiplier;
	DECLARE_PROPERTY(CDTimerClass, IdleActionTimer); // MOO
	DECLARE_PROPERTY(CDTimerClass, RadarFlashTimer);
	DECLARE_PROPERTY(CDTimerClass, TargetingTimer); //Duration = 45 on init!
	DECLARE_PROPERTY(CDTimerClass, IronCurtainTimer);
	DECLARE_PROPERTY(CDTimerClass, IronTintTimer); // how often to alternate the effect color
	int              IronTintStage; // ^
	DECLARE_PROPERTY(CDTimerClass, AirstrikeTimer);
	DECLARE_PROPERTY(CDTimerClass, AirstrikeTintTimer); // tracks alternation of the effect color
	DWORD            AirstrikeTintStage; //  ^
	int              ForceShielded;	//0 or 1, NOT a bool - is this under ForceShield as opposed to IC?
	bool             Deactivated; //Robot Tanks without power for instance
	TechnoClass*     DrainTarget; // eg Disk -> PowerPlant, this points to PowerPlant
	TechnoClass*     DrainingMe;  // eg Disk -> PowerPlant, this points to Disk
	AnimClass*       DrainAnim;
	bool             Disguised;
	DWORD            DisguiseCreationFrame;
	DECLARE_PROPERTY(CDTimerClass, InfantryBlinkTimer); // Rules->InfantryBlinkDisguiseTime , detects mirage firing per description
	DECLARE_PROPERTY(CDTimerClass, DisguiseBlinkTimer); // disguise disruption timer
	bool             UnlimboingInfantry;
	DECLARE_PROPERTY(CDTimerClass, ReloadTimer);
	Point2D          RadarPosition;

	// WARNING! this is actually an index of HouseTypeClass es, but it's being changed to fix typical WW bugs.
	DECLARE_PROPERTY(IndexBitfield<HouseClass*>, DisplayProductionTo); // each bit corresponds to one player on the map, telling us whether that player has (1) or hasn't (0) spied this building, and the game should display what's being produced inside it to that player. The bits are arranged by player ID, i.e. bit 0 refers to house #0 in HouseClass::Array, 1 to 1, etc.; query like ((1 << somePlayer->ArrayIndex) & someFactory->DisplayProductionToHouses) != 0

	int              Group; //0-9, assigned by CTRL+Number, these kinds // also set by aimd TeamType->Group !
	AbstractClass*   ArchiveTarget; // Set when told to guard a unit or such, or to distinguish undeploy and selling. Also used by rally points as well as harvesters for remembering ore fields etc.
	HouseClass*      Owner;
	CloakState       CloakState;
	DECLARE_PROPERTY(StageClass, CloakProgress); // phase from [opaque] -> [fading] -> [transparent] , [General]CloakingStages= long
	DECLARE_PROPERTY(CDTimerClass, CloakDelayTimer); // delay before cloaking again
	float            WarpFactor; // don't ask! set to 0 in CTOR, never modified, only used as ((this->Fetch_ID) + this->WarpFactor) % 400 for something in cloak ripple
	bool             unknown_bool_250;
	CoordStruct      LastSightCoords;
	int              LastSightRange;
	int              LastSightHeight;
	bool             GapSuperCharged; // GapGenerator, when SuperGapRadiusInCells != GapRadiusInCells, you can deploy the gap to boost radius
	bool             GeneratingGap; // is currently generating gap
	int              GapRadius;
	bool             BeingWarpedOut; // is being warped by CLEG
	bool             WarpingOut; // phasing in after chrono-jump
	bool             unknown_bool_272;
	BYTE             unused_273;
	TemporalClass*   TemporalImUsing; // CLEG attacking Power Plant : CLEG's this
	TemporalClass*   TemporalTargetingMe; 	// CLEG attacking Power Plant : PowerPlant's this
	bool             IsImmobilized; // by chrono aftereffects
	DWORD            unknown_280;
	int              ChronoLockRemaining; // countdown after chronosphere warps things around
	CoordStruct      ChronoDestCoords; // teleport loco and chsphere set this
	AirstrikeClass*  Airstrike; //Boris
	bool             Berzerk;
	DWORD            BerzerkDurationLeft;
	DWORD            SprayOffsetIndex; // hardcoded array of xyz offsets for sprayattack, 0 - 7, see 6FE0AD
	bool             Uncrushable; // DeployedCrushable fiddles this, otherwise all 0

	// unless source is Pushy=
	// abs_Infantry source links with abs_Unit target and vice versa - can't attack others until current target flips
	// no checking whether source is Infantry, but no update for other types either
	// old Brute hack
	FootClass*       DirectRockerLinkedUnit;
	FootClass*       LocomotorTarget; // mag->LocoTarget = victim
	FootClass*       LocomotorSource; // victim->LocoSource = mag
	AbstractClass*   Target; //if attacking
	AbstractClass*   LastTarget;
	CaptureManagerClass* CaptureManager; //for Yuris
	TechnoClass*     MindControlledBy;
	bool             MindControlledByAUnit;
	AnimClass*       MindControlRingAnim;
	HouseClass*      MindControlledByHouse; //used for a TAction
	SpawnManagerClass* SpawnManager;
	TechnoClass*     SpawnOwner; // on DMISL , points to DRED and such
	SlaveManagerClass*   SlaveManager;
	TechnoClass*     SlaveOwner; // on SLAV, points to YAREFN
	HouseClass*      OriginallyOwnedByHouse; //used for mind control

	// units point to the Building bunkering them, building points to Foot contained within
	TechnoClass*     BunkerLinkedItem;

	float            PitchAngle; // not exactly, and it doesn't affect the drawing, only internal state of a dropship
	DECLARE_PROPERTY(CDTimerClass, RearmTimer); // Originally named Arm in RA1, but this is more descriptive name.
	int              ChargeTurretDelay;         // Set to same duration (frames) as RearmTimer when weapon is fired. Only used by IsChargeTurret to calculate timespan during which to display turret animation.
	int              Ammo;
	int              Value; // set to actual cost when this gets queued in factory, updated only in building's 42C

	ParticleSystemClass* FireParticleSystem;
	ParticleSystemClass* SparkParticleSystem;
	ParticleSystemClass* NaturalParticleSystem;
	ParticleSystemClass* DamageParticleSystem;
	ParticleSystemClass* RailgunParticleSystem;
	ParticleSystemClass* unk1ParticleSystem;
	ParticleSystemClass* unk2ParticleSystem;
	ParticleSystemClass* FiringParticleSystem;

	WaveClass* Wave; //Beams


	// rocking effect
	float            AngleRotatedSideways; // in this frame, in radians - if abs() exceeds pi/2, it dies
	float            AngleRotatedForwards; // same

	// set these and leave the previous two alone!
	// if these are set, the unit will roll up to pi/4, by this step each frame, and balance back
	float            RockingSidewaysPerFrame; // left to right - positive pushes left side up
	float            RockingForwardsPerFrame; // back to front - positive pushes ass up

	int              HijackerInfantryType; // mutant hijacker

	DECLARE_PROPERTY(StorageClass, Tiberium);
	DWORD            unknown_34C;

	DECLARE_PROPERTY(TransitionTimer, UnloadTimer); // times the deploy, unload, etc. cycles

	DECLARE_PROPERTY(FacingClass, BarrelFacing);
	DECLARE_PROPERTY(FacingClass, PrimaryFacing);
	DECLARE_PROPERTY(FacingClass, SecondaryFacing);
	int              CurrentBurstIndex;
	DECLARE_PROPERTY(CDTimerClass, TargetLaserTimer);
	short            unknown_short_3C8;
	WORD             unknown_3CA;
	bool             CountedAsOwned; // is this techno contained in OwningPlayer->Owned... counts?
	bool             IsSinking;
	bool             WasSinkingAlready; // if(IsSinking && !WasSinkingAlready) { play SinkingSound; WasSinkingAlready = 1; }
	bool             unknown_bool_3CF;
	bool             unknown_bool_3D0;
	bool             HasBeenAttacked; // ReceiveDamage when not HouseClass_IsAlly
	bool             Cloakable;
	bool             IsPrimaryFactory; // doubleclicking a warfac/barracks sets it as primary
	bool             Spawned;
	bool             IsInPlayfield;
	DECLARE_PROPERTY(RecoilData, TurretRecoil);
	DECLARE_PROPERTY(RecoilData, BarrelRecoil);
	bool             IsTether;
	bool             IsAlternativeTether;
	bool             IsOwnedByCurrentPlayer; // Returns true if owned by the player on this computer
	bool             DiscoveredByCurrentPlayer;
	bool             DiscoveredByComputer;
	bool             unknown_bool_41D;
	bool             unknown_bool_41E;
	bool             unknown_bool_41F;
	char             SightIncrease; // used for LeptonsPerSightIncrease
	bool             RecruitableA; // these two are like Lenny and Carl, weird purpose and never seen separate
	bool             RecruitableB; // they're usually set on preplaced objects in maps
	bool             IsRadarTracked;
	bool             IsOnCarryall;
	bool             IsCrashing;
	bool             WasCrashingAlready;
	bool             IsBeingManipulated;
	TechnoClass*     BeingManipulatedBy; // set when something is being molested by a locomotor such as magnetron
	// the pointee will be marked as the killer of whatever the victim falls onto
	HouseClass*      ChronoWarpedByHouse;
	bool             unknown_bool_430;
	bool             IsMouseHovering;
	bool             ShouldBeReselectOnUnlimbo;
	TeamClass*       OldTeam;
	bool             CountedAsOwnedSpecial; // for absorbers, infantry uses this to manually control OwnedInfantry count
	bool             Absorbed; // in UnitAbsorb/InfantryAbsorb or smth, lousy memory
	bool             unknown_bool_43A;
	DWORD            unknown_43C;
	DECLARE_PROPERTY(DynamicVectorClass<int>, CurrentTargetThreatValues);
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, CurrentTargets);

	// if DistributedFire=yes, this is used to determine which possible targets should be ignored in the latest threat scan
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, AttackedTargets);

	DECLARE_PROPERTY(AudioController, Audio3);

	BOOL            unknown_BOOL_49C; // Turret is moving?
	BOOL            TurretIsRotating;

	DECLARE_PROPERTY(AudioController, Audio4);

	bool             unknown_bool_4B8;
	DWORD            unknown_4BC;

	DECLARE_PROPERTY(AudioController, Audio5);

	bool             unknown_bool_4D4;
	DWORD            unknown_4D8;

	DECLARE_PROPERTY(AudioController, Audio6);

	DWORD            QueuedVoiceIndex;
	DWORD            unknown_4F4;
	bool             unknown_bool_4F8;
	DWORD            unknown_4FC;	//gets initialized with the current Frame, but this is NOT a TimerStruct!
	TechnoClass*     QueueUpToEnter;
	DWORD            EMPLockRemaining;
	DWORD            ThreatPosed; // calculated to include cargo etc
	DWORD            ShouldLoseTargetNow;
	RadBeam*         FiringRadBeam;
	PlanningTokenClass* PlanningToken;
	ObjectTypeClass* Disguise;
	HouseClass*      DisguisedAsHouse;
};
