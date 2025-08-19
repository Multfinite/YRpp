/*
	ParticleSystems
*/

#pragma once

#include "ObjectClass.h"
#include "ParticleSystemTypeClass.h"
#include "ParticleClass.h"

class __declspec(uuid("0E272DC8-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE ParticleSystemClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<ParticleSystemClass*>, Array, 0xA80208u)
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EFB9C;
            this->IRTTITypeInfo = 0x7EFB80;
            this->INoticeSink = 0x7EFB78;
            this->INoticeSource = 0x7EFB70;
        }
    };
    static inline vtables_t vtables{};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;
    static constexpr AbstractType AbsID = AbstractType::ParticleSystem;
    static constexpr uintptr_t AbsVTable = 0x7EFB9C;
    static constexpr size_t ClassSize = 0x100;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParticleSystemClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;



	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleSystemClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	ParticleSystemTypeClass* Type;
	CoordStruct  SpawnDistanceToOwner;
	DECLARE_PROPERTY(DynamicVectorClass<ParticleClass*>, Particles);
	CoordStruct TargetCoords;
	ObjectClass* Owner;
	AbstractClass* Target; // CellClass or TechnoClass
	int          SpawnFrames; //from ParSysTypeClass
	int          Lifetime; //from ParSysTypeClass
	int          SparkSpawnFrames; //from ParSysTypeClass
	int          SpotlightRadius; //defaults to 29
	bool         TimeToDie;
	bool         unknown_bool_F9;
	HouseClass*  OwnerHouse;
    ParticleSystemClass(ParticleSystemTypeClass* pParticleSystemType, const CoordStruct& coords,
        AbstractClass* pTarget, ObjectClass* pOwner, const CoordStruct& targetCoords,
        HouseClass* pOwnerHouse) : ParticleSystemClass(fake_noinit_t{}) JMP_THIS(0x62DC50);
    ParticleSystemClass() : ParticleSystemClass(fake_noinit_t{}) JMP_THIS(0x62DC50);
    ParticleSystemClass(noinit_t)  noexcept : ParticleSystemClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(ParticleSystemClass) == ParticleSystemClass::ClassSize);
