/*
	Warheads
*/

#pragma once

#include "AbstractTypeClass.h"

class AnimTypeClass;
class ParticleTypeClass;
class VoxelAnimTypeClass;

struct WarheadFlags {
	bool ForceFire;
	bool Retaliate;
	bool PassiveAcquire;

	WarheadFlags(bool FF = true, bool Retal = true, bool Acquire = true) : ForceFire(FF), Retaliate(Retal), PassiveAcquire(Acquire) {};
};

class NOVTABLE WarheadTypeClass : public AbstractTypeClass
{
public:

	//Array
	ABSTRACTTYPE_ARRAY(WarheadTypeClass, 0x8874C0u);
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractTypeClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractTypeClass::vtables_t()
        {
            this->IPersistStream = 0x7F6B30;
            this->IRTTITypeInfo = 0x7F6B14;
            this->INoticeSink = 0x7F6B0C;
            this->INoticeSource = 0x7F6B04;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::WarheadType;
    static constexpr uintptr_t AbsVTable = 0x7F6B30;
    static constexpr size_t ClassSize = 0x1D0;


	//AbstractTypeClass

public:
    virtual ~WarheadTypeClass() JMP_THIS(0x75D230);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x75E080);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x75E0C0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x75E2C0);
    
    void PointerExpired(AbstractClass* instance, bool all = true) override JMP_THIS(0x75E440);
    RTTIType WhatAmI() const override JMP_THIS(0x75E500);
    int Size() const override JMP_THIS(0x75E4F0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x75DEC0);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x75D3A0);

    static WarheadTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x75E3B0);
/*
    WarheadTypeClass * Find_Or_Make_0() JMP_THIS(0x75E3B0);
    int32_t From_Name() JMP_THIS(0x75E4A0);
*/

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline WarheadTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) {}

public:

	double  Deform;

	double Verses [0xB];

	double  ProneDamage;
	int     DeformTreshold;

	TypeList<AnimTypeClass*> AnimList;

	InfDeath InfDeath;
	float   CellSpread;
	float   CellInset;
	float   PercentAtMax;
	bool    CausesDelayKill;
	int     DelayKillFrames;
	float   DelayKillAtMax;
	float   CombatLightSize;
	ParticleTypeClass* Particle;
	bool    Wall;
	bool    WallAbsoluteDestroyer;
	bool    PenetratesBunker;
	bool    Wood;
	bool    Tiberium;
	bool    unknown_bool_149;
	bool    Sparky;
	bool    Sonic;
	bool    Fire;
	bool    Conventional;
	bool    Rocker;
	bool    DirectRocker;
	bool    Bright;
	bool    CLDisableRed;
	bool    CLDisableGreen;
	bool    CLDisableBlue;
	bool    EMEffect;
	bool    MindControl;
	bool    Poison;
	bool    IvanBomb;
	bool    ElectricAssault;
	bool    Parasite;
	bool    Temporal;
	bool    IsLocomotor;
	_GUID   Locomotor;
	bool    Airstrike;
	bool    Psychedelic;
	bool    BombDisarm;
	int     Paralyzes;
	bool    Culling;
	bool    MakesDisguise;
	bool    NukeMaker;
	bool    Radiation;
	bool    PsychicDamage;
	bool    AffectsAllies;
	bool    Bullets;
	bool    Veinhole;
	int     ShakeXlo;
	int     ShakeXhi;
	int     ShakeYlo;
	int     ShakeYhi;

	TypeList<VoxelAnimTypeClass*> DebrisTypes;
	TypeList<int> DebrisMaximums;

	int     MaxDebris;
	int     MinDebris;
	PROTECTED_PROPERTY(DWORD, unused_1CC); //???
    WarheadTypeClass(const char* pID) : WarheadTypeClass(fake_noinit_t{})
        JMP_THIS(0x75CEC0);
    WarheadTypeClass(noinit_t) noexcept : WarheadTypeClass(fake_noinit_t{})
        JMP_THIS(0x75D1B0);
};
static_assert(sizeof(WarheadTypeClass) == WarheadTypeClass::ClassSize);