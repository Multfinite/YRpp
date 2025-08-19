/*
	Ground & Naval Vehicles
*/

#pragma once

#include "FootClass.h"
#include "UnitTypeClass.h"

class EBolt;

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

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~UnitClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ObjectClass

	virtual Action MouseOverCell(CellStruct const* pCell, bool checkFog = false, bool ignoreForce = false) const override { JMP_THIS(0x7404B0) };
	virtual Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override { JMP_THIS(0x73FD50) };

	virtual void MarkAllOccupationBits(const CoordStruct& coords) override { JMP_THIS(0x7441B0) };
	virtual void UnmarkAllOccupationBits(const CoordStruct& coords) override { JMP_THIS(0x744210) };
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
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

	/*! @brief FAKE CTOR */
	explicit __forceinline UnitClass(fake_noinit_t) noexcept : FootClass(fake_noinit_t{}) {}
public:

	int CurrentFiringFrame;
	UnitTypeClass* Type;
	UnitClass* FollowerCar; // groovy - link defined in the map's [Units] section, looked up on startup
	int FlagHouseIndex; // Carrying the flag of this House
	bool IsFollowerCar; // This vehicle is another vehicle's FollowerCar (such as a train car following train).
	bool Unloading;
	bool IsHarvesting;
	bool TerrainPalette;
	int unknown_int_6D4;
	int DeathFrameCounter;
	EBolt* ElectricBolt; //Unit is the owner of this
	bool Deployed;
	bool Deploying;
	bool Undeploying;
	int NonPassengerCount; // Set when unloading passengers. Units with TurretCount>0 will not unload the gunner.

	wchar_t ToolTipText[0x100];
	UnitClass(noinit_t) noexcept : FootClass(fake_noinit_t{}) { vtables.init(this); };
	UnitClass(UnitTypeClass* type, HouseClass* house) : UnitClass(fake_noinit_t{}) JMP_THIS(0x7353C0);
};
static_assert(sizeof(UnitClass) == UnitClass::ClassSize);
