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


public:
    virtual ~OverlayClass() JMP_THIS(0x5FC4D0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x5FDF10);
   
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x5FD8F0);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x5FD950);
   
    RTTIType WhatAmI() const override JMP_THIS(0x5FDF50);
    int Size() const override JMP_THIS(0x5FDF00);
   
    ObjectTypeClass* GetType() const override JMP_THIS(0x5FDDE0);
    bool Unlimbo(const Coordinate& coords, Dir256 dir) override JMP_THIS(0x5FD270);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x5FDF60);
    void DrawAgain(const Point2D& location, const RectangleStruct& bounds) const override JMP_THIS(0x5FD970);
    bool Mark(MarkType mark) override JMP_THIS(0x5FC570);

    static int __fastcall GetTiberiumType(int overlayTypeIndex) JMP_STD(0x5FDD20);

/*
    int32_t Read_INI() JMP_THIS(0x5FD2E0);
    void Write_INI(OverlayClass* pThis) JMP_THIS(0x5FD6A0);
*/

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
