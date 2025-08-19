/*
	OverlayTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class AnimTypeClass;

class __declspec(uuid("5AF2CE79-0634-11D2-ACA4-006008055BB5"))
NOVTABLE OverlayTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EF600;
            this->IRTTITypeInfo = 0x7EF5E4;
            this->INoticeSink = 0x7EF5DC;
            this->INoticeSource = 0x7EF5D4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::OverlayType;
    static constexpr uintptr_t AbsVTable = 0x7EF600;
    static constexpr size_t ClassSize = 0x2BC;

	//Array
	ABSTRACTTYPE_ARRAY(OverlayTypeClass, 0xA83D80u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~OverlayTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ObjectTypeClass
	virtual CoordStruct* vt_entry_6C(CoordStruct* pDest,CoordStruct* pSrc) const R0;

	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords,HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//OverlayTypeClass
	virtual void Draw(Point2D* pClientCoords, RectangleStruct* pClipRect, int nFrame) RX;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline OverlayTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	int                ArrayIndex;
	LandType           LandType;
	AnimTypeClass*     CellAnim;
	int                DamageLevels;
	int                Strength;
	bool               Wall;
	bool               Tiberium;
	bool               Crate;
	bool               CrateTrigger;
	bool               NoUseTileLandType;
	bool               IsVeinholeMonster;
	bool               IsVeins;
	bool               ImageLoaded;	//not INI
	bool               Explodes;
	bool               ChainReaction;
	bool               Overrides;
	bool               DrawFlat;
	bool               IsRubble;
	bool               IsARock;
	ColorStruct RadarColor;

    OverlayTypeClass(const char* pID) : OverlayTypeClass(fake_noinit_t{}) JMP_THIS(0x5FE250);
    OverlayTypeClass(noinit_t) noexcept : OverlayTypeClass(fake_noinit_t{}) JMP_THIS(0x5FE3C0);
};
static_assert(sizeof(OverlayTypeClass) == OverlayTypeClass::ClassSize);
