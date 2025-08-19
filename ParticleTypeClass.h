/*
	ParticleTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class WarheadTypeClass;
class RGBClass;

class __declspec(uuid("703E044B-0FB1-11D2-8172-006008055BB5"))
NOVTABLE ParticleTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F0188;
            this->IRTTITypeInfo = 0x7F016C;
            this->INoticeSink = 0x7F0164;
            this->INoticeSource = 0x7F015C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::ParticleType;
    static constexpr uintptr_t AbsVTable = 0x7F0188;
    static constexpr size_t ClassSize = 0x318;

	//Array
	ABSTRACTTYPE_ARRAY(ParticleTypeClass, 0xA83D98u);


public:
    virtual ~ParticleTypeClass() JMP_THIS(0x644E40);
    
    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x645620);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x645660);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6457A0);
    
    void PointerExpired(AbstractClass* instance, bool all = true) override JMP_THIS(0x6458B0);
    RTTIType WhatAmI() const override JMP_THIS(0x645920);
    int Size() const override JMP_THIS(0x645910);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6454E0);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x644F50);
    bool SpawnAtMapCoords(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x645930);
    ObjectClass* CreateObject(HouseClass* pOwner) override JMP_THIS(0x645940);

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	CoordStruct NextParticleOffset;
	int    XVelocity;
	int    YVelocity;
	int    MinZVelocity;
	int    ZVelocityRange;
	double ColorSpeed;
	TypeList<RGBClass*> ColorList;
	ColorStruct StartColor1;
	ColorStruct StartColor2;
	int    MaxDC;
	int    MaxEC;
	WarheadTypeClass* Warhead;
	int    Damage;
	int    StartFrame;
	int    NumLoopFrames;
	int    Translucency;
	int    WindEffect;
	float  Velocity;
	float  Deacc;
	int    Radius;
	bool   DeleteOnStateLimit;
	BYTE   EndStateAI;
	BYTE   StartStateAI;
	BYTE   StateAIAdvance;
	BYTE   FinalDamageState;
	BYTE   Translucent25State;
	BYTE   Translucent50State;
	bool   Normalized;
	ParticleTypeClass* NextParticle;
	BehavesLike BehavesLike;

    ParticleTypeClass(const char* pID) : ParticleTypeClass(fake_noinit_t{}) JMP_THIS(0x644BE0);
    ParticleTypeClass(noinit_t) noexcept : ParticleTypeClass(fake_noinit_t{}) JMP_THIS(0x644DD0);
};
static_assert(sizeof(ParticleTypeClass) == ParticleTypeClass::ClassSize);