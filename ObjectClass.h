#pragma once

#include "AbstractClass.h"
#include "Audio.h"
#include "ObjectTypeClass.h"
#include "TagClass.h"

#include "Helpers/Template.h"

struct SHPStruct;
class LightConvertClass;

//forward declarations
class AnimClass;
class BombClass;
class BuildingTypeClass;
class CellClass;
class InfantryTypeClass;
class TechnoClass;
class TechnoTypeClass;
class WarheadTypeClass;
class UnitClass;

class HouseTypeClass;

class LineTrail;
struct WeaponStruct;

/*!
* @brief Base class for all game objects.
*/
class NOVTABLE ObjectClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EF060;
			this->IRTTITypeInfo = 0x7EF044;
			this->INoticeSink = 0x7EF03C;
			this->INoticeSource = 0x7EF034;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7EF060;
	static constexpr auto AbsDerivateID = AbstractFlags::Object;
	static constexpr size_t ClassSize = 0xAC;

	static constexpr reference<DynamicVectorClass<ObjectClass*>, 0xA8ECB8u> const CurrentObjects{};
	static constexpr reference<DynamicVectorClass<ObjectClass*>, 0xA8E360u> const Array{};

public:
	DWORD              unknown_24;
	DWORD              unknown_28;
	int                FallRate;     // how fast is it falling down? only works if FallingDown is set below, and actually positive numbers will move the thing UPWARDS
	ObjectClass* NextObject;   // Next Object in the same cell or transport. This is a linked list of Objects.
	TagClass* AttachedTag;  // Should be TagClass , TODO: change when implemented
	BombClass* AttachedBomb; // Ivan's little friends.
	DECLARE_PROPERTY(AudioController, AmbientSoundController); // the "mofo" struct, evil evil stuff
	DECLARE_PROPERTY(AudioController, CustomSoundController);  // the "mofo" struct, evil evil stuff
	int                CustomSound;
	bool               BombVisible;    // In range of player's bomb seeing units, so should draw it
	PROTECTED_PROPERTY(BYTE, align_69[0x3]);
	int                Strength;         // The current Health.
	int                EstimatedStrength;// used for auto-targeting threat estimation
	bool               IsOnMap;        // has this object been placed on the map?
	PROTECTED_PROPERTY(BYTE, align_75[0x3]);
	DWORD              unknown_78;
	DWORD              unknown_7C;
	bool               NeedsRedraw;
	bool               InLimbo;        // act as if it doesn't exist - e.g., post mortem state before being deleted
	bool               InOpenToppedTransport;
	bool               IsSelected;     // Has the player selected this Object?
	bool               HasParachute;   // Is this Object parachuting?
	PROTECTED_PROPERTY(BYTE, align_85[0x3]);
	AnimClass* Parachute;      // Current parachute Anim.
	bool               OnBridge;
	bool               IsFallingDown;
	bool               WasFallingDown; // last falling state when FootClass::Update executed. used to find out whether it changed.
	bool               IsToExplode;        // if set, will explode after FallingDown brings it to contact with the ground
	bool               IsActive;        // Self-explanatory.
	PROTECTED_PROPERTY(BYTE, align_91[0x3]);
	Layer              LastLayer;
	bool               IsInLogic;      // has this object been added to the logic collection?
	bool               IsVisible;      // was this object in viewport when drawn?
	PROTECTED_PROPERTY(BYTE, align_99[0x2]);
	Coordinate        Location;       // Absolute current 3D location (in leptons)
	LineTrail* LineTrailer;
public:
	virtual ~ObjectClass() JMP_THIS(0x5F3B80);

	HRESULT __stdcall Load(IStream* pStm) override JMP_THIS(0x5F5E80);

	void Detach(AbstractClass* target, bool all) override JMP_THIS(0x5F5230);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x5F6250);
	bool IsInactive() const override JMP_THIS(0x5F6690);
	Coordinate Center() const override JMP_THIS(0x5F65A0);	
	bool OnGround() const override JMP_THIS(0x5F6B60);
	bool InAir() const override JMP_THIS(0x5F6B90);
	void AI() override JMP_THIS(0x5F3E70);

	/*!
	* @note original_name Detach_Anim
	* @note vtable_index 24:0x60
	* @note address 0x5F6DA0
	*/
	virtual void DetachAnim(AnimClass* pAnim) JMP_THIS(0x5F6DA0);

	/*!
	* @brief Determines if this object is part of the player's army.
	* @brief The player's army is considered to be all those mobile units that can be selected and controlled by the player (they may or may not have weapons in the traditional sense).
	* @note original_name Is_Players_Army
	* @note vtable_index 25:0x64
	* @note address 0x426390
	*/
	virtual bool IsSelectable() const JMP_THIS(0x426390);

	/*!
	* @note original_name Visual_Character
	* @note vtable_index 26:0x68
	* @note address 0x4263A0
	*/
	virtual VisualType VisualCharacter(VARIANT_BOOL specificOwner, HouseClass* whoIsAsking) const JMP_THIS(0x4263A0);

	/*!
	* @note original_name Get_Image_Data
	* @note vtable_index 27:0x6C
	* @note address 0x5F3E30
	*/
	virtual SHPStruct* GetImage() const JMP_THIS(0x5F3E30);

	/*!
	* @note original_name What_Action_Cell
	* @note vtable_index 28:0x70
	* @note address 0x5F4250
	*/
	virtual Action MouseOverCell(::Cell const* pCell, bool checkFog = false, bool ignoreForce = false) const JMP_THIS(0x5F4250);

	/*!
	* @note original_name What_Action_Object
	* @note vtable_index 29:0x74
	* @note address 0x5F4240
	*/
	virtual Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const JMP_THIS(0x5F4240);

	/*!
	* @note original_name In_Which_Layer
	* @note vtable_index 30:0x78
	* @note address 0x5F4260
	*/
	virtual Layer InWhichLayer() const JMP_THIS(0x5F4260);

	/*!
	* @brief Object on surface. Opposed to being submerged.
	* @brief returns (Height() > -20)
	* @note original_name Is_Surfaced
	* @note vtable_index 31:0x7C
	* @note address 0x5F6C10
	*/
	virtual bool IsSurfaced() JMP_THIS(0x5F6C10);

	/*!
	* @brief BuildingClass returns if it is 1x1 and has UndeploysInto
	* @brief InfantryClass returns 0
	* @brief UnitClass returns !NonVehicle
	* @brief AircraftClass returns IsOnFloor()
	* @brief
	* @brief users include:
	* @brief 452656 - is this building click-repairable
	* @brief 440C26 - should this building get considered in BaseSpacing
	* @brief 445A8E - -""-
	* @brief 51E7D1 - can a VehicleThief be clicked to steal this unit
	* @brief 51E4D9 - can an engi be clicked to enter this to fix/takeover
	* @brief 51F0D3 - -""-
	* @brief 51EA06 - can this building be C4'd?
	* @brief 51E243 - can a VehicleThief steal this on his own decision
	* @brief 4F93F3 - should this building's damage raise a BaseUnderAttack?
	* @brief 442286 - -""-
	* @brief 44296A - -""-
	* @brief 741117 - can this be healed by a vehicle?
	* @brief 6F8242 - can this aircraft be auto-target
	* @brief 6F85BE - can this aircraft be auto-attacked
	* @note original_name Is_Vehicle_Can_Undeploy
	* @note vtable_index 32:0x80
	* @note address 0x4263B0
	*/
	virtual bool IsStrange() const JMP_THIS(0x4263B0);

	/*!
	* @note original_name Techno_Class_Of
	* @note vtable_index 33:0x84
	* @note address 0x5F6BC0
	*/
	virtual TechnoTypeClass* TechnoType() const JMP_THIS(0x5F6BC0);

	/*!
	* @note original_name Class_Of
	* @note vtable_index 34:0x88
	* @note address 0x4E0130
	*/
	virtual ObjectTypeClass* Type() const JMP_THIS(0x4E0130);

	/*!
	* @brief Returns the data for IndexBitfield<HouseTypeClass*>
	* @note original_name Get_Ownable
	* @note vtable_index 35:0x8C
	* @note address 0x5F42A0
	*/
	virtual DWORD Ownable() const JMP_THIS(0x5F42A0);

	/*!
	* @note original_name Full_Name
	* @note vtable_index 36:0x90
	* @note address 0x4263C0
	*/
	virtual const wchar_t* FullName() const JMP_THIS(0x4263C0);

	/*!
	* @note original_name Can_Repair
	* @note vtable_index 37:0x94
	* @note address 0x5F42B0
	*/
	virtual bool Repairable() const JMP_THIS(0x5F42B0);

	/*!
	* @note original_name Can_Demolish
	* @note vtable_index 38:0x98
	* @note address 0x5F42C0
	*/
	virtual bool Soldable() const JMP_THIS(0x5F42C0);

	/*!
	* @note original_name Can_Player_Fire
	* @note vtable_index 39:0x9C
	* @note address 0x5F42D0
	*/
	virtual bool CanPlayerFire() const JMP_THIS(0x5F42D0);

	/*!
	* @note original_name Can_Player_Move
	* @brief Can the current player control this unit? (owned by him, not paralyzed, not spawned, not warping, not slaved...)
	* @note vtable_index 40:0xA0
	* @note address 0x5F42E0
	*/
	virtual bool IsControllable() const JMP_THIS(0x5F42E0);

	/*!
	* @note original_name Target_Coord
	* @brief On non-buildings this is same as Center(), on buildings it returns the target coordinate that is affected by TargetCoordOffset.
	* @note vtable_index 41:0xA4
	* @note address 0x41BDD0
	*/
	virtual Coordinate TargetCoord() const JMP_THIS(0x41BDD0);

	/*!
	* @note original_name Docking_Coord
	* @brief Gets a building's free dock coordinates for a unit. falls back to Destination(pCrd);
	* @note vtable_index 42:0xA8
	* @note address 0x5F6C80
	*/
	virtual Coordinate DockingCoord(TechnoClass* docker) const JMP_THIS(0x5F6C80);

	/*!
	* @note original_name Render_Coord
	* @note vtable_index 43:0xAC
	* @note address 0x41BE00
	*/
	virtual Coordinate RenderCoord() const JMP_THIS(0x41BE00);

	/*!
	* @note original_name Fire_Coord
	* @note vtable_index 44:0xB0
	* @note address 0x4263D0
	*/
	virtual Coordinate FLH(int idxWeapon, Coordinate BaseCoords) const JMP_THIS(0x4263D0);

	/*!
	* @note original_name Exit_Coord
	* @note vtable_index 45:0xB4
	* @note address 0x41BE30
	*/
	virtual Coordinate ExitCoord() const JMP_THIS(0x41BE30);

	/*!
	* @note vtable_index 46:0xB8
	* @note address 0x5F6BD0
	*/
	virtual int YSort() const JMP_THIS(0x5F6BD0);

	/*!
	* @brief pDocker is passed to Destination
	* @note vtable_index 47:0xBC
	* @note address 0x5F6A70
	*/
	virtual bool IsOnBridge(TechnoClass* pDocker = nullptr) const JMP_THIS(0x5F6A70);

	/*!
	* @note vtable_index 48:0xC0
	* @note address 0x426410
	*/
	virtual bool IsStandingStill() const JMP_THIS(0x426410);

	/*!
	* @note vtable_index 49:0xC4
	* @note address 0x426420
	*/
	virtual bool IsDisguised() const JMP_THIS(0x426420);

	/*!
	* @brief Only works correctly on infantry!
	* @note vtable_index 50:0xC8
	* @note address 0x426430
	*/
	virtual bool IsDisguisedAs(HouseClass* target) const JMP_THIS(0x426430);

	/*!
	* @note vtable_index 51:0xCC
	* @note address 0x41BE60
	*/
	virtual ObjectTypeClass* Disguise(bool disguisedAgainstAllies) const JMP_THIS(0x41BE60);

	/*!
	* @note vtable_index 52:0xD0
	* @note address 0x41BE70
	*/
	virtual HouseClass* DisguiseHouse(bool disguisedAgainstAllies) const JMP_THIS(0x41BE70);

	/*!
	* @brief Remove object from the map
	* @note vtable_index 53:0xD4
	* @note address 0x5F4D30
	*/
	virtual bool Limbo() JMP_THIS(0x5F4D30);

	/*!
	* @brief Place the object on the map
	* @note vtable_index 54:0xD8
	* @note address 0x5F4EC0
	*/
	virtual bool Unlimbo(const Coordinate& position, Dir256 dir) JMP_THIS(0x5F4EC0);

	/*!
	* @brief Cleanup things (lose line trail, deselect, etc). Permanently: destroyed/removed/gone opposed to just going out of sight.
	* @note original_name Detach_All
	* @note vtable_index 55:0xDC
	* @note address 0x5F5280
	*/
	virtual void DetachAll(bool permanently) JMP_THIS(0x5F5280);

	/*!
	* @note original_name Record_The_Kill_Object
	* @note vtable_index 56:0xE0
	* @note address 0x5F42F0
	*/
	virtual void RegisterKillByObject(ObjectClass const* destroyedBy) JMP_THIS(0x5F42F0);

	/*!
	* @brief maybe Object instead of Techno? Raises Map Events, grants veterancy, increments house kill counters
	* @brief ++destroyer's kill counters , etc
	* @note original_name Record_The_Kill_House
	* @note vtable_index 57:0xE4
	* @note address 0x5F4300
	*/
	virtual void RegisterKillByHouse(HouseClass const* destroyedBy) JMP_THIS(0x5F4300);

	/*!
	* @note original_name Paradrop
	* @note vtable_index 58:0xE8
	* @note address 0x5F5940
	*/
	virtual bool SpawnParachuted(Coordinate const& coords) JMP_THIS(0x5F5940);

	/*!
	* @note original_name Drop_As_Bomb
	* @note vtable_index 59:0xEC
	* @note address 0x5F4160
	*/
	virtual void DropAsBomb() JMP_THIS(0x5F4160);

	/*!
	* @note original_name Set_Occupy_Bit
	* @note vtable_index 60:0xF0
	* @note address 0x5F60A0
	*/
	virtual void MarkAllOccupationBits(Coordinate const& coords) JMP_THIS(0x5F60A0);

	/*!
	* @note original_name Clear_Occupy_Bit
	* @note vtable_index 61:0xF4
	* @note address 0x5F6120
	*/
	virtual void UnmarkAllOccupationBits(Coordinate const& coords) JMP_THIS(0x5F6120);

	/*!
	* @note original_name Remove_This
	* @note vtable_index 62:0xF8
	* @note address 0x5F65F0
	*/
	virtual void UnInit() JMP_THIS(0x5F65F0);

	/*!
	* @brief uncloak when object is bumped, damaged, detected, ...
	* @note original_name Do_Shimmer
	* @note vtable_index 63:0xFC
	* @note address 0x5F4310
	*/
	virtual void Reveal() JMP_THIS(0x5F4310);

	/*!
	* @note original_name Exit_Object
	* @note vtable_index 64:0x100
	* @note address 0x5F4320
	*/
	virtual KickOutResult KickOutUnit(TechnoClass* pTechno, ::Cell Cell) JMP_THIS(0x5F4320);

	/*!
	* @note original_name Render
	* @note vtable_index 65:0x104
	* @note address 0x5F4B10
	*/
	virtual bool DrawIfVisible(RectangleStruct* pBounds, bool EvenIfCloaked, DWORD dwUnk3) const JMP_THIS(0x5F4B10);

	/*!
	* @note original_name Occupy_List
	* @note vtable_index 66:0x108
	* @note address 0x5F5B90
	*/
	virtual ::Cell const* OccupiedCells(bool includeBib = false) const JMP_THIS(0x5F5B90);

	/*!
	* @note original_name Draw_Lines_On_Buildings
	* @note vtable_index 67:0x10C
	* @note address 0x426440
	*/
	virtual void DrawBehind(Point2D* pLocation, RectangleStruct* pBounds) const JMP_THIS(0x426440);

	/*!
	* @brief draws ivan bomb, health bar, talk bubble, etc
	* @note original_name Draw_Extras
	* @note vtable_index 68:0x110
	* @note address 0x426450
	*/
	virtual void DrawExtras(Point2D* pLocation, RectangleStruct* pBounds) const JMP_THIS(0x426450);

	/*!
	* @note original_name Draw_It
	* @note vtable_index 69:0x114
	* @note address 0x5B3A50
	*/
	virtual void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const JMP_THIS(0x5B3A50);

	/*!
	* @brief just forwards the call to Draw
	* @note original_name Placement_Draw_It
	* @note vtable_index 70:0x118
	* @note address 0x5F65D0
	*/
	virtual void DrawAgain(const Point2D& location, const RectangleStruct& bounds) const JMP_THIS(0x5F65D0);

	/*!
	* @note original_name Hidden
	* @note vtable_index 71:0x11C
	* @note address 0x5F4330
	*/
	virtual void Undiscover() JMP_THIS(0x5F4330);

	/*!
	* @note original_name Look
	* @note vtable_index 72:0x120
	* @note address 0x5F4340
	*/
	virtual void See(bool incremental, int32_t arg_4) JMP_THIS(0x5F4340);

	/*!
	* @note original_name Mark
	* @note vtable_index 73:0x124
	* @note address 0x5F5850
	*/
	virtual bool Mark(MarkType value) JMP_THIS(0x5F5850);

	/*!
	* @note original_name Get_Dimensions
	* @note vtable_index 74:0x128
	* @note address 0x5F4730
	*/
	virtual RectangleStruct* GetDimensions(RectangleStruct* pRect) const JMP_THIS(0x5F4730);

	/*!
	* @note original_name Get_Render_Dimensions
	* @note vtable_index 75:0x12C
	* @note address 0x5F4870
	*/
	virtual RectangleStruct* GetRenderDimensions(RectangleStruct* pRect) JMP_THIS(0x5F4870);

	/*!
	* @note original_name Draw_Radial_Indicator
	* @note vtable_index 76:0x130
	* @note address 0x41BE80
	*/
	virtual void DrawRadialIndicator(DWORD dwUnk) JMP_THIS(0x41BE80);

	/*!
	* @note original_name Mark_For_Redraw
	* @note vtable_index 77:0x134
	* @note address 0x5F4D10
	*/
	virtual void MarkForRedraw() JMP_THIS(0x5F4D10);

	/*!
	* @note original_name Is_Selectable
	* @note vtable_index 78:0x138
	* @note address 0x5F6C30
	*/
	virtual bool CanBeSelected() const JMP_THIS(0x5F6C30);

	/*!
	* @note original_name Can_Select
	* @note vtable_index 79:0x13C
	* @note address 0x5F6C70
	*/
	virtual bool CanBeSelectedNow() const JMP_THIS(0x5F6C70);

	/*!
	* @note original_name Active_Click_With_Object
	* @note vtable_index 80:0x140
	* @note address 0x5F4360
	*/
	virtual bool ObjectClickedAction(Action action, ObjectClass* pTarget, bool bUnk) JMP_THIS(0x5F4360);

	/*!
	* @note original_name Active_Click_With_Cell
	* @note vtable_index 81:0x144
	* @note address 0x5F4350
	*/
	virtual bool CellClickedAction(Action action, ::Cell* pCell, ::Cell* pCell1, bool bUnk) JMP_THIS(0x5F4350);

	/*!
	* @note original_name Clicked_As_Target
	* @note vtable_index 82:0x148
	* @note address 0x5F4370
	*/
	virtual void ClickedAsTarget(int duration) JMP_THIS(0x5F4370);

	/*!
	* @note original_name Select
	* @note vtable_index 83:0x14C
	* @note address 0x5F4520
	*/
	virtual bool Select() JMP_THIS(0x5F4520);

	/*!
	* @note original_name Unselect
	* @note vtable_index 84:0x150
	* @note address 0x5F44A0
	*/
	virtual void Deselect() { JMP_THIS(0x5F44A0); }

	/*!
	* @note original_name Iron_Curtain
	* @note vtable_index 85:0x154
	* @note address 0x426460
	*/
	virtual DamageState IronCurtain(int nDuration, HouseClass* pSource, bool ForceShield) JMP_THIS(0x426460);

	/*!
	* @note original_name Stop_Airstrike_Timer
	* @note vtable_index 86:0x158
	* @note address 0x426470
	*/
	virtual void StopAirstrikeTimer() JMP_THIS(0x426470);

	/*!
	* @note original_name Start_Airstrike_Timer
	* @note vtable_index 87:0x15C
	* @note address 0x426480
	*/
	virtual void StartAirstrikeTimer(int duration) JMP_THIS(0x426480);

	/*!
	* @note original_name Is_Iron_Curtained
	* @note vtable_index 88:0x160
	* @note address 0x426490
	*/
	virtual bool IsIronCurtained() const JMP_THIS(0x426490);

	/*!
	* @note original_name In_Range
	* @note vtable_index 89:0x164
	* @note address 0x5F4380
	*/
	virtual bool InRange(Coordinate coord, int idxWeapon) const JMP_THIS(0x5F4380);

	/*!
	* @note original_name Weapon_Range
	* @note vtable_index 90:0x168
	* @note address 0x5F4390
	*/
	virtual int WeaponRange(int idxWeapon) const JMP_THIS(0x5F4390);

	/*!
	* @note original_name Take_Damage
	* @note vtable_index 91:0x16C
	* @note address 0x5F5390
	*/
	virtual DamageState ReceiveDamage(int* pDamage, int distanceFromEpicenter, WarheadTypeClass* pWH, ObjectClass* source, bool ignoreDefenses, bool preventPassengerEscape, HouseClass* attacker) JMP_THIS(0x5F5390);

	/*!
	* @note original_name Destroy
	* @note vtable_index 92:0x170
	* @note address 0x4264A0
	*/
	virtual void Destroy() JMP_THIS(0x4264A0);

	/*!
	* @note original_name Scatter
	* @note vtable_index 93:0x174
	* @note address 0x5F43A0
	*/
	virtual void Scatter(const Coordinate& crd, bool ignoreMission, bool ignoreDestination) JMP_THIS(0x5F43A0);

	/*!
	* @note original_name Catch_Fire
	* @note vtable_index 94:0x178
	* @note address 0x5F43B0
	*/
	virtual bool Ignite() JMP_THIS(0x5F43B0);

	/*!
	* @note original_name Fire_Out
	* @note vtable_index 95:0x17C
	* @note address 0x5F43C0
	*/
	virtual void Extinguish() JMP_THIS(0x5F43C0);

	/*!
	* @note original_name Value
	* @note vtable_index 96:0x180
	* @note address 0x5F43D0
	*/
	virtual DWORD PointsValue() const JMP_THIS(0x5F43D0);

	/*!
	* @note original_name Get_Mission
	* @note vtable_index 97:0x184
	* @note address 0x5F43E0
	*/
	virtual Mission CurrentMission() const JMP_THIS(0x5F43E0);

	/*!
	* @note original_name Assign_Mission
	* @note vtable_index 98:0x188
	* @note address 0x41BE90
	*/
	virtual void RestoreMission(Mission mission) JMP_THIS(0x41BE90);

	/*!
	* @note original_name Per_Cell_Process
	* @note vtable_index 99:0x18C
	* @note address 0x4264B0
	*/
	virtual void UpdatePosition(PCPType how) JMP_THIS(0x4264B0);

	/*!
	* @note original_name Who_Can_Build_Me
	* @note vtable_index 100:0x190
	* @note address 0x5F5C20
	*/
	virtual BuildingClass* FindFactory(bool allowOccupied, bool requirePower) const JMP_THIS(0x5F5C20);

	/*!
	* @note original_name Receive_Message
	* @note vtable_index 101:0x194
	* @note address 0x5F5320
	*/
	virtual RadioCommand ReceiveCommand(TechnoClass* pSender, RadioCommand command, AbstractClass*& pInOut) JMP_THIS(0x5F5320);

	/*!
	* @note original_name Revealed
	* @note vtable_index 102:0x198
	* @note address 0x5F5930
	*/
	virtual bool DiscoveredBy(HouseClass* pHouse) JMP_THIS(0x5F5930);

	/*!
	* @param state 0 - off, 1 - on, -1 - toggle
	* @note original_name Repair
	* @note vtable_index 103:0x19C
	* @note address 0x5F43F0
	*/
	virtual void SetRepairState(int state) JMP_THIS(0x5F43F0);

	/*!
	* @note original_name Sell_Back
	* @note vtable_index 104:0x1A0
	* @note address 0x5F4400
	*/
	virtual void Sell(DWORD control) JMP_THIS(0x5F4400);

	/*!
	* @note original_name Assign_Planning_Path
	* @note vtable_index 105:0x1A4
	* @note address 0x5F6B50
	*/
	virtual void AssignPlanningPath(signed int idxPath, signed char idxWP) JMP_THIS(0x5F6B50);

	/*!
	* @brief Vestigial, never called by the game.
	* @brief UPDATE: RA remaster says that is map editor feature function.
	* @note original_name Move
	* @note vtable_index 106:0x1A8
	* @note address 0x5F4410
	*/
	virtual void MoveToDirection(FacingType facing) JMP_THIS(0x5F4410);

	/*!
	* @note original_name Can_Enter_Cell
	* @note vtable_index 107:0x1AC
	* @note address 0x4264C0
	*/
	virtual Move CanEnterCell(CellClass* pDestCell, FacingType facing, int level, CellClass* pSourceCell, bool alt) const JMP_THIS(0x4264C0);

	/*!
	* @note original_name Can_Change_Level
	* @note vtable_index 108:0x1B0
	* @note address 0x4264D0
	*/
	virtual DWORD CanChangeLevel(CellClass* cell, Dir256 dir, int* targetLevel, bool* useAltObject, Cell targetCoord) JMP_THIS(0x4264D0);

	/*!
	* @note original_name Set_Coord
	* @note vtable_index 109:0x1B4
	* @note address 0x5F6940
	*/
	virtual void SetLocation(const Coordinate& crd) JMP_THIS(0x5F6940);

	/*!
	* @note original_name Coord_Cell
	* @note vtable_index 110:0x1B8
	* @note address 0x41BEA0
	*/
	virtual ::Cell Coord() const JMP_THIS(0x41BEA0);

	/*!
	* @note original_name Coord_Cell_Ptr
	* @note vtable_index 111:0x1BC
	* @note address 0x5F6960
	*/
	virtual CellClass* Cell() const JMP_THIS(0x5F6960);

	/*!
	* @note original_name Coord_Target_Cell
	* @note vtable_index 112:0x1C0
	* @note address 0x5F69C0
	*/
	virtual ::Cell DestinationCoord() const JMP_THIS(0x5F69C0);

	/*!
	* @note original_name Coord_Target_Cell_Ptr
	* @note vtable_index 113:0x1C4
	* @note address 0x5F6A10
	*/
	virtual CellClass* DestinationCell() const JMP_THIS(0x5F6A10);

	/*!
	* @note original_name Get_Height
	* @note vtable_index 114:0x1C8
	* @note address 0x5F5F40
	*/
	virtual int Height() const JMP_THIS(0x5F5F40);

	/*!
	* @note original_name Set_Height
	* @note vtable_index 115:0x1CC
	* @note address 0x5F5FA0
	*/
	virtual void SetHeight(DWORD dwUnk) JMP_THIS(0x5F5FA0);

	/*!
	* @note original_name Get_Z_Coord
	* @note vtable_index 116:0x1D0
	* @note address 0x5F5F30
	*/
	virtual int Z() const JMP_THIS(0x5F5F30);

	/*!
	* @note original_name Is_Being_Warped_Away
	* @note vtable_index 117:0x1D4
	* @note address 0x4264E0
	*/
	virtual bool IsBeingWarpedOut() const JMP_THIS(0x4264E0);

	/*!
	* @note original_name Is_Warping_In
	* @note vtable_index 118:0x1D8
	* @note address 0x4264F0
	*/
	virtual bool IsWarpingIn() const JMP_THIS(0x4264F0);

	/*!
	* @note original_name Is_Warping_Something_Out
	* @note vtable_index 119:0x1DC
	* @note address 0x426500
	*/
	virtual bool IsWarpingSomethingOut() const JMP_THIS(0x426500);

	/*!
	* @note original_name Is_Not_Warping
	* @note vtable_index 120:0x1E0
	* @note address 0x426510
	*/
	virtual bool IsNotWarping() const JMP_THIS(0x426510);

	/*!
	* @note original_name Get_Remap_Color
	* @note vtable_index 121:0x1E4
	* @note address 0x426520
	*/
	virtual LightConvertClass* RemapColor() const JMP_THIS(0x426520);

	// technically it takes an ecx<this> , but it's not used and ecx is immediately overwritten on entry
	// draws the mind control line when unit is selected
	constexpr static void DrawALinkTo(int src_X, int src_Y, int src_Z, int dst_X, int dst_Y, int dst_Z, ColorStruct color)
		{ PUSH_VAR32(color); PUSH_VAR32(dst_Z); PUSH_VAR32(dst_Y); PUSH_VAR32(dst_X);
			PUSH_VAR32(src_Z); PUSH_VAR32(src_Y); PUSH_VAR32(src_X); CALL(0x704E40); }

	constexpr void AttachSound(int32_t customSound) JMP_THIS(0x5F6CB0);
	constexpr bool AttachTrigger(TagClass* pTag) JMP_THIS(0x5F5B50);
	constexpr static RectangleStruct BoundingBoxOf(DynamicVectorClass<ObjectClass>& vector) JMP_THIS(0x5F66A0);
	constexpr static Coordinate AveragePointOf(DynamicVectorClass<ObjectClass>& vector) JMP_THIS(0x5F6790);
	constexpr static ObjectClass* FindNearestOf(Coordinate& coord) JMP_THIS(0x5F6810);
	constexpr HealthState HealthStatus() const JMP_THIS(0x5F5DD0);
	constexpr void DestroyLinetrail() JMP_THIS(0x5F3D90);
	/*!
	* @brief Direction from this object to target object.
	* @note in EXE this is method of ObjectClass, but it can be used with any Abstract.
	*/
	constexpr DirStruct Direction(AbstractClass* pTarget) const JMP_THIS(0x5F3DB0);
	/*!
	* @note in EXE this is method of ObjectClass, but it can be used with any Abstract.
	*/
	constexpr int DistanceFrom(AbstractClass* that) const JMP_THIS(0x5F6440);
	/*!
	* @note in EXE this is method of ObjectClass, but it can be used with any Abstract.
	*/
	constexpr int DistanceFrom3D(AbstractClass* that) const JMP_THIS(0x5F6360);
	constexpr int32_t DistanceFrom3DSquared(AbstractClass* target) JMP_THIS(0x5F6500);
	constexpr int32_t DistanceSquared(Coordinate coord) JMP_THIS(0x5F6560);	
	constexpr float HealthRatio() JMP_THIS(0x5F5C60);
	constexpr double HealthPercentage() const { return static_cast<double>(this->Strength) / this->Type()->MaxStrength; }
	constexpr bool IsRedHP() const JMP_THIS(0x5F5CD0);
	constexpr bool IsYellowHP() const JMP_THIS(0x5F5D20);
	constexpr bool IsGreenHP() const JMP_THIS(0x5F5D90);
	constexpr int32_t CellLevel() JMP_THIS(0x5F5F00);
	constexpr bool SameName(int8_t* name) JMP_THIS(0x5F3E50);
	constexpr void SetHealthPercentage(double percentage) JMP_THIS(0x5F5C80);
	constexpr void SetZ(int32_t z) JMP_THIS(0x5F6060);
	constexpr bool IsCrushableBy(TechnoClass* pCrusher) JMP_THIS(0x5F6CD0);
	constexpr void BecomeUntargetable() JMP_THIS(0x70D4A0);

	constexpr bool operator>(ObjectClass* other) JMP_THIS(0x5F6220);
	constexpr bool operator<(ObjectClass* other) JMP_THIS(0x5F61F0);

protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline ObjectClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
	ObjectClass(noinit_t) : ObjectClass(fake_noinit_t{}) JMP_THIS(0x5F3B50);
	ObjectClass() : ObjectClass(fake_noinit_t{}) JMP_THIS(0x5F3900);
};
static_assert(sizeof(ObjectClass) == ObjectClass::ClassSize);
