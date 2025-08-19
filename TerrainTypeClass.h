/*
	TerrainTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class __declspec(uuid("5AF2CE7B-0634-11D2-ACA4-006008055BB5"))
NOVTABLE TerrainTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

	//Array
	ABSTRACTTYPE_ARRAY(TerrainTypeClass, 0xA8E318u);
	static TerrainTypeClass* __fastcall FindOrAllocate(const char* id)
	{ JMP_STD(0x71E2A0); }
	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F5458;
            this->IRTTITypeInfo = 0x7F543C;
            this->INoticeSink = 0x7F5434;
            this->INoticeSource = 0x7F542C;
        }
    };
    static inline vtables_t vtables{};

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;
    static constexpr AbstractType AbsID = AbstractType::TerrainType;
    static constexpr uintptr_t AbsVTable = 0x7F5458;
    static constexpr size_t ClassSize = 0x2BC;

	//Destructor
	virtual ~TerrainTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords,HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* owner) R0;



	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	int Foundation;
	ColorStruct RadarColor;
	int AnimationRate;
	float AnimationProbability;
	int TemperateOccupationBits;
	int SnowOccupationBits;
	bool WaterBound;
	bool SpawnsTiberium;
	bool IsFlammable;
	bool IsAnimated;
	bool IsVeinhole;
	CellStruct* FoundationData;
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TerrainTypeClass(fake_noinit_t) noexcept
        : ObjectTypeClass(fake_noinit_t{})
    {}

public:
    TerrainTypeClass(const char* pID) : TerrainTypeClass(fake_noinit_t{})
        JMP_THIS(0x71DA80);
    TerrainTypeClass(noinit_t) noexcept : TerrainTypeClass(fake_noinit_t{})
        JMP_THIS(0x71DBD0);
};
static_assert(sizeof(TerrainTypeClass) == TerrainTypeClass::ClassSize);
