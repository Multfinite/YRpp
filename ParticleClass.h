/*
	Particles
*/

#pragma once

#include "ObjectClass.h"
#include "ParticleTypeClass.h"

class ParticleSystemClass;

class __declspec(uuid("0E272DCC-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE ParticleClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<ParticleClass*>, Array, 0xA83DC8u)
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EF954;
            this->IRTTITypeInfo = 0x7EF938;
            this->INoticeSink = 0x7EF930;
            this->INoticeSource = 0x7EF928;
        }
    };
    static inline vtables_t vtables{};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;
    static constexpr AbstractType AbsID = AbstractType::Particle;
    static constexpr uintptr_t AbsVTable = 0x7EF954;
    static constexpr size_t ClassSize = 0x138;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParticleClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ParticleClass
	virtual int vt_entry_1E8() R0;



	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	ParticleTypeClass* Type;
	BYTE   unknown_B0;
	BYTE   unknown_B1;
	BYTE   unknown_B2;
	DWORD  unknown_B4;
	DWORD  unknown_B8;
	DWORD  unknown_BC;
	CoordStruct Velocity;
	DWORD  unknown_CC;
	double unknown_double_D0;
	DWORD  unknown_D8;
	DWORD  unknown_DC;
	DWORD  unknown_E0;
	float  Speed;
	CoordStruct unknown_coords_E8; //Crd2 in CTOR
	CoordStruct unknown_coords_F4; //Crd1 in CTOR
	CoordStruct unknown_coords_100; //{ 0, 0, 0} in CTOR
	Vector3D<float> unknown_vector3d_10C;
	Vector3D<float> unknown_vector3d_118;
	ParticleSystemClass*   ParticleSystem;
	WORD   RemainingEC;
	WORD   RemainingDC;
	BYTE   StateAIAdvance;
	BYTE   unknown_12D;
	BYTE   StartStateAI;
	BYTE   Translucency;
	BYTE   unknown_130;
	BYTE   unknown_131;
	PROTECTED_PROPERTY(DWORD,        unused_134); //??
    ParticleClass(ParticleTypeClass* pParticleType, Coordinate* pCrd1,
        Coordinate* pCrd2, ParticleSystemClass* pParticleSystem)
        : ParticleClass(fake_noinit_t{}) JMP_THIS(0x62B5E0);
    ParticleClass() : ParticleClass(fake_noinit_t{}) JMP_THIS(0x62BB20);
    ParticleClass(noinit_t) noexcept : ParticleClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(ParticleClass) == ParticleClass::ClassSize);
