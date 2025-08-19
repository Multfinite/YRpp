/*
	Trees
*/

#pragma once

#include "ObjectClass.h"
#include "TerrainTypeClass.h"
#include "StageClass.h"

class __declspec(uuid("0E272DCE-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE TerrainClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

	//global array
	DEFINE_REFERENCE(DynamicVectorClass<TerrainClass*>, Array, 0xA8E988u)
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F522C;
            this->IRTTITypeInfo = 0x7F5224;
            this->INoticeSink = 0x7F521C;
            this->INoticeSource = 0x7F5200;
        }
    };
    static inline vtables_t vtables{};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;
    static constexpr AbstractType AbsID = AbstractType::Terrain;
    static constexpr uintptr_t AbsVTable = 0x7F522C;
    static constexpr size_t ClassSize = 0xE0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TerrainClass() RX;

	//identification
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;



	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TerrainClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}

public:

	StageClass Animation;
	TerrainTypeClass* Type;
	bool IsBurning; // this terrain object has been ignited
	bool IsCrumbling; // finish the animation and uninit
	RectangleStruct unknown_rect_D0;

    TerrainClass(TerrainTypeClass* tt, CellStruct coords) : TerrainClass(fake_noinit_t{})
        JMP_THIS(0x71BB90);
    TerrainClass() : TerrainClass(fake_noinit_t{})
        JMP_THIS(0x71BDF0);
};
static_assert(sizeof(TerrainClass) == TerrainClass::ClassSize);
