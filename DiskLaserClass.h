/*
	DiskLasers are the floating disks' purple lasers.
*/

#pragma once

#include "AbstractClass.h"

class LaserDrawClass;
class TechnoClass;
class WeaponTypeClass;

class __declspec(uuid("5230C9A8-846A-47EC-BDA2-7E95445E1D49"))
NOVTABLE DiskLaserClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7E5FB8;
            this->IRTTITypeInfo = 0x7E5F9C;
            this->INoticeSink = 0x7E5F94;
            this->INoticeSource = 0x7E5F8C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::DiskLaser;
    static constexpr uintptr_t AbsVTable = 0x7E5FB8;
    static constexpr size_t ClassSize = 0x40;

	// static
	DEFINE_REFERENCE(DynamicVectorClass<DiskLaserClass*>, Array, 0x8A0208u)

	static constexpr auto Radius = 240;
	DEFINE_ARRAY_REFERENCE(Point2D, [16], DrawCoords, 0x8A0180u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~DiskLaserClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//non-virtual
	void Fire(TechnoClass* pOwner, TechnoClass* pTarget, WeaponTypeClass* pWeapon, int nDamage)
		{ JMP_THIS(0x4A71A0); }

	void PointerGotInvalid(AbstractClass* pInvalid)
		{ JMP_THIS(0x4A7900); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

    /*! @brief FAKE CTOR */
    explicit __forceinline DiskLaserClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) { }
public:

	TechnoClass* Owner;
	TechnoClass* Target;
	WeaponTypeClass* Weapon;
	DWORD unknown_30;
	DWORD unknown_34;
	DWORD unknown_38;
	int Damage;
    DiskLaserClass() : DiskLaserClass(fake_noinit_t{}) JMP_THIS(0x4A7A30);
    DiskLaserClass(noinit_t) noexcept : DiskLaserClass(fake_noinit_t{}) JMP_THIS(0x4A7AD0);
};
static_assert(sizeof(DiskLaserClass) == DiskLaserClass::ClassSize);
