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

    static constexpr AbstractType AbsID = AbstractType::Particle;
    static constexpr uintptr_t AbsVTable = 0x7EF954;
    static constexpr size_t ClassSize = 0x138;




public:
    virtual ~ParticleClass() JMP_THIS(0x62BCC0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x62D930);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x62D7A0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x62D810);
   
    RTTIType WhatAmI() const override JMP_THIS(0x62D980);
    int Size() const override JMP_THIS(0x62D970);
   
    Layer InWhichLayer() const override JMP_THIS(0x62D770);
    ObjectTypeClass* GetType() const override JMP_THIS(0x62D990);
    CellStruct* GetFoundationData(bool includeBib = false) const override JMP_THIS(0x62D710);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x62CEC0);
    bool Mark(MarkType mark) override JMP_THIS(0x62D6F0);
    
    virtual int ShapeNumber() const JMP_THIS(0x62D830);

/*
    void Update() JMP_THIS(0x62CE40);
    void Coord_AI() JMP_THIS(0x62D5E0);
    void Fire_AI() JMP_THIS(0x62CB10);
    int32_t Fire_Wind() JMP_THIS(0x62D510);
    int8_t Gas_AI() JMP_THIS(0x62BD50);
    void Gas_Wind() JMP_THIS(0x62D3F0);
    void ParticleClass() JMP_THIS(0x62BCC0);
    void Railgun_AI() JMP_THIS(0x62C3A0);
    void Smoke_AI() JMP_THIS(0x62C540);
    int32_t Smoke_Coord_Update() JMP_THIS(0x62D2A0);
    void Spark_AI() JMP_THIS(0x62C6E0);
*/

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
