/*
	Projectiles
*/

#pragma once

#include "ObjectTypeClass.h"

class AnimTypeClass;
class BulletClass;
class ColorScheme;
class CellClass;
class TechnoClass;
class WeaponTypeClass;
class WarheadTypeClass;

class __declspec(uuid("5AF2CE77-0634-11D2-ACA4-006008055BB5"))
NOVTABLE BulletTypeClass : public ObjectTypeClass
{
public:
	using base_type = ObjectTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E4948;
			this->IRTTITypeInfo = 0x7E492C;
			this->INoticeSink = 0x7E4924;
			this->INoticeSource = 0x7E491C;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::BulletType;
	static constexpr uintptr_t AbsVTable = 0x7E4948;
	static constexpr size_t ClassSize = 0x2F8;

	//Array
	ABSTRACTTYPE_ARRAY(BulletTypeClass, 0xA83C80u);
	static BulletTypeClass* __fastcall FindOrAllocate(const char* id)
	{ JMP_STD(0x46C790); }
	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//Destructor
	virtual ~BulletTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//AbstractTypeClass
	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords,HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* owner) R0;

	bool Rotates() const {
		return !this->NoRotate;
	}

	void SetScaledSpawnDelay(int delay) {
		// JMP_THIS(0x46C840);
		this->ScaledSpawnDelay = delay;
	}

	BulletClass* __fastcall CreateBullet(
		AbstractClass* Target,
		TechnoClass* Owner,
		int Damage,
		WarheadTypeClass *WH,
		int Speed,
		bool Bright)
		{ JMP_STD(0x46B050); }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	bool Airburst;
	bool Floater;
	bool SubjectToCliffs;
	bool SubjectToElevation;
	bool SubjectToWalls;
	bool VeryHigh;
	bool Shadow;
	bool Arcing;
	bool Dropping;
	bool Level;
	bool Inviso;
	bool Proximity;
	bool Ranged;
	bool NoRotate; // actually has opposite meaning of Rotates. false means Rotates=yes.
	bool Inaccurate;
	bool FlakScatter;
	bool AA;
	bool AG;
	bool Degenerates;
	bool Bouncy;
	bool AnimPalette;
	bool FirersPalette;
	int Cluster;
	WeaponTypeClass* AirburstWeapon;
	WeaponTypeClass* ShrapnelWeapon;
	int ShrapnelCount;
	int DetonationAltitude;
	bool Vertical;
	double Elasticity;
	int Acceleration;
	ColorScheme* Color;
	AnimTypeClass* Trailer;
	int ROT;
	int CourseLockDuration;
	int SpawnDelay;
	int ScaledSpawnDelay;
	bool Scalable;
	int Arm;
	byte AnimLow;
	byte AnimHigh;
	byte AnimRate;
	bool Flat;
protected:
	explicit __forceinline BulletTypeClass(fake_noinit_t) noexcept : ObjectTypeClass(fake_noinit_t{}) {}
public:
	BulletTypeClass(noinit_t) noexcept : BulletTypeClass(fake_noinit_t{}) JMP_THIS(0x46BDE0);
	BulletTypeClass(const char* pId) : BulletTypeClass(fake_noinit_t{}) JMP_THIS(0x46BBC0);
};
static_assert(sizeof(BulletTypeClass) == BulletTypeClass::ClassSize);
