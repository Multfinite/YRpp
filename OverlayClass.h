/*
	Overlays (mainly Ore and Gems)
*/

#pragma once

/*

;GEF in case it wasn't intuitively obvious from the above, this list mirrors an object enumeration
;in overlay.hh. If you want to add something to this list, make sure you add to the enumeration
;or get a programmer to do it for you

 * Ironically, the list they had in overlay.hh doesn't seem to have been updated that much since TS.

 */

#define OVERLAY_GASAND 0x00
#define OVERLAY_GAWALL 0x02
#define OVERLAY_NAWALL 0x1A

#define OVERLAY_VEINS 0x7E
#define OVERLAY_VEINHOLE 0xA7
#define OVERLAY_VEINHOLEDUMMY 0xB2

#define OVERLAY_BRIDGEHEAD11 0x18
#define OVERLAY_BRIDGEHEAD12 0x19

#define OVERLAY_BRIDGEHEAD21 0xED
#define OVERLAY_BRIDGEHEAD22 0xEE

#define OVERLAY_LOBRIDGE1 0x7A
#define OVERLAY_LOBRIDGE2 0x7B
#define OVERLAY_LOBRIDGE3 0x7C
#define OVERLAY_LOBRIDGE4 0x7D

#include "ObjectClass.h"
#include "OverlayTypeClass.h"

class __declspec(uuid("0E272DC7-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE OverlayClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EF3D4;
            this->IRTTITypeInfo = 0x7EF3CC;
            this->INoticeSink = 0x7EF3B0;
            this->INoticeSource = 0x7EF3A8;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Overlay;
    static constexpr uintptr_t AbsVTable = 0x7EF3D4;
    static constexpr size_t ClassSize = 0xB0;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<OverlayClass*>, Array, 0xA8EC50u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~OverlayClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	// Gets overlay's tiberium type
	static int __fastcall GetTiberiumType(int overlayTypeIndex)
		{ JMP_THIS(0x5FDD20); }


	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline OverlayClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	OverlayTypeClass* Type;
    OverlayClass(OverlayTypeClass* pType, CellStruct const& mapCoord, int houseId) : OverlayClass(fake_noinit_t{}) JMP_THIS(0x5FC380);
    OverlayClass(noinit_t) noexcept : OverlayClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(OverlayClass) == OverlayClass::ClassSize);
