#pragma once

#include "ObjectTypeClass.h"

class AnimTypeClass;
class BulletClass;
class ColorScheme;
class CellClass;
class TechnoClass;
class WeaponTypeClass;
class WarheadTypeClass;

class NOVTABLE BulletTypeClass : public ObjectTypeClass
{
public:
	using base_type = AbstractTypeClass;
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
	static const AbstractType AbsID = AbstractType::BulletType;

	static constexpr uintptr_t AbsVTable = 0x7E4948;

	ABSTRACTTYPE_ARRAY(BulletTypeClass, 0xA83C80u);
	static BulletTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x46C790);
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
	// actually has opposite meaning of Rotates. false means Rotates=yes.
	bool NoRotate;
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
public:
	virtual ~BulletTypeClass() JMP_THIS(0x46BE10);

	HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x46C750);
	
	HRESULT Load(IStream* pStm) override JMP_THIS(0x46C6A0);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x46C730);
	
	void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x46C820);
	RTTIType KindOf() const override JMP_THIS(0x46C850);
	int SizeOf() const override JMP_THIS(0x46C860);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x46C560);
	
	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x46BEE0);
	CoordStruct FixupCoord(CoordStruct& coord) const override JMP_THIS(0x46C4F0);
	bool InstantiateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x46C870);
	ObjectClass* Instantiate(HouseClass* pOwner) override JMP_THIS(0x46C880);

	bool Rotates() const { return !this->NoRotate; }

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
		bool Bright) JMP_STD(0x46B050);

/*
		int32_t From_Name() JMP_THIS(0x46C440);
		int8_t * Name_From() JMP_THIS(0x46C4D0);
		void Set_Scaled_Spawn_Delay(int32_t scaled_spawn_delay) JMP_THIS(0x46C840);
*/

protected:
	explicit __forceinline BulletTypeClass(fake_noinit_t) noexcept : ObjectTypeClass(fake_noinit_t{}) {}
public:
	BulletTypeClass(noinit_t) : BulletTypeClass(fake_noinit_t{}) JMP_THIS(0x46BDE0);
	BulletTypeClass(const char* pId) : BulletTypeClass(fake_noinit_t{}) JMP_THIS(0x46BBC0);
};
