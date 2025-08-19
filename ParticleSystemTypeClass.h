/*
	ParticleSystemTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class __declspec(uuid("703E044A-0FB1-11D2-8172-006008055BB5"))
NOVTABLE ParticleSystemTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

	//Array
	ABSTRACTTYPE_ARRAY(ParticleSystemTypeClass, 0xA83D68u);
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F00A8;
            this->IRTTITypeInfo = 0x7F008C;
            this->INoticeSink = 0x7F0084;
            this->INoticeSource = 0x7F007C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::ParticleSystemType;
    static constexpr uintptr_t AbsVTable = 0x7F00A8;
    static constexpr size_t ClassSize = 0x310;



public:
    virtual ~ParticleSystemTypeClass() JMP_THIS(0x644250);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6447A0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6447E0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x644830);
    
    RTTIType WhatAmI() const override JMP_THIS(0x644930);
    int Size() const override JMP_THIS(0x644920);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x644700);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6442D0);
    bool SpawnAtMapCoords(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x644940);
    ObjectClass* CreateObject(HouseClass* pOwner) override JMP_THIS(0x644950);

    static ParticleSystemTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x644890);

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleSystemTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	int      HoldsWhat; //ParticleType Array index
	bool     Spawns;
	int      SpawnFrames;
	float    Slowdown;
	int      ParticleCap;
	int      SpawnRadius;
	float    SpawnCutoff;
	float    SpawnTranslucencyCutoff;
	BehavesLike BehavesLike;
	int      Lifetime;
	Vector3D<float> SpawnDirection;
	double   ParticlesPerCoord;
	double   SpiralDeltaPerCoord;
	double   SpiralRadius;
	double   PositionPerturbationCoefficient;
	double   MovementPerturbationCoefficient;
	double   VelocityPerturbationCoefficient;
	double   SpawnSparkPercentage;
	int      SparkSpawnFrames;
	int      LightSize;
	ColorStruct LaserColor;
	bool     Laser;
	bool     OneFrameLight;
    ParticleSystemTypeClass(const char* pID) : ParticleSystemTypeClass(fake_noinit_t{}) JMP_THIS(0x6440A0);
    ParticleSystemTypeClass(noinit_t) noexcept : ParticleSystemTypeClass(fake_noinit_t{}) JMP_THIS(0x644220);
};
static_assert(sizeof(ParticleSystemTypeClass) == ParticleSystemTypeClass::ClassSize);