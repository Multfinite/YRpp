/*
	VoxelAnimTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class AnimTypeClass;
class ParticleSystemTypeClass;
class WarheadTypeClass;

class __declspec(uuid("2EBB6D66-0D4D-11D2-8172-006008055BB5"))
NOVTABLE VoxelAnimTypeClass : public ObjectTypeClass
{
public:
	//Array
	ABSTRACTTYPE_ARRAY(VoxelAnimTypeClass, 0xA8EB28u);
    using base_type = ObjectTypeClass;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F6548;
            this->IRTTITypeInfo = 0x7F652C;
            this->INoticeSink = 0x7F6524;
            this->INoticeSource = 0x7F651C;
        }
    };
    static inline vtables_t vtables{};

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;
    static constexpr AbstractType AbsID = AbstractType::VoxelAnimType;
    static constexpr uintptr_t AbsVTable = 0x7F6548;
    static constexpr size_t ClassSize = 0x308;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* owner) R0; // ! this just returns NULL instead of creating the anim, fucking slackers

	//VoxelAnimTypeClass

	//Destructor
	virtual ~VoxelAnimTypeClass() RX;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline VoxelAnimTypeClass(fake_noinit_t) noexcept
        : ObjectTypeClass(fake_noinit_t{})
    {}

public:

	bool Normalized;
	bool Translucent;
	bool SourceShared;
	PROTECTED_PROPERTY(BYTE, unused_297);
	int VoxelIndex;
	int Duration;
	double Elasticity;
	double MinAngularVelocity;
	double MaxAngularVelocity;
	double MinZVel;
	double MaxZVel;
	double MaxXYVel;
	bool IsMeteor;
	PROTECTED_PROPERTY(BYTE, unused_2D1[3]);
	VoxelAnimTypeClass* Spawns;
	int SpawnCount;
	int StartSound;
	int StopSound;
	AnimTypeClass* BounceAnim;
	AnimTypeClass* ExpireAnim;
	AnimTypeClass* TrailerAnim;
	int Damage;
	int DamageRadius;
	WarheadTypeClass* Warhead;
	ParticleSystemTypeClass* AttachedSystem;
	bool IsTiberium;
	PROTECTED_PROPERTY(BYTE, unused_301[3]);
    VoxelAnimTypeClass(const char* pID) : VoxelAnimTypeClass(fake_noinit_t{}) JMP_THIS(0x74AD80);
    VoxelAnimTypeClass() : VoxelAnimTypeClass(fake_noinit_t{}) JMP_THIS(0x74AF70);
};
static_assert(sizeof(VoxelAnimTypeClass) == VoxelAnimTypeClass::ClassSize);