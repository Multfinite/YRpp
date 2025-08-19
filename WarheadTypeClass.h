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

	static WarheadTypeClass* __fastcall FindOrAllocate(const char* id)
	{ JMP_STD(0x75E3B0); }

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;
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

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~WarheadTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//AbstractTypeClass


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