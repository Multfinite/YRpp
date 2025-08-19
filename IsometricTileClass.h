#pragma once

#include "ObjectClass.h"

class IsometricTileTypeClass;

class __declspec(uuid("5AF2CE7A-0634-11D2-ACA4-006008055BB5"))
NOVTABLE IsometricTileClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EC258;
            this->IRTTITypeInfo = 0x7EC23C;
            this->INoticeSink = 0x7EC234;
            this->INoticeSource = 0x7EC22C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Isotile;
    static constexpr uintptr_t AbsVTable = 0x7EC258;
    static constexpr size_t ClassSize = 0xB0;

	//Array
	DEFINE_REFERENCE(DynamicVectorClass<IsometricTileClass*>, Array, 0x87F750u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override R0;

	virtual HRESULT __stdcall Load(IStream* pStm) override R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override R0;

	//AbstractClass
	virtual AbstractType WhatAmI() const override RT(AbstractType);
	virtual int Size() const override R0;

	//ObjectClass
	virtual ObjectTypeClass* GetType() const override R0;
	virtual bool Limbo() override R0;
	virtual bool Unlimbo(const CoordStruct& Crd, DirType dFaceDir) override R0;
	virtual void Draw(Point2D* pLocation, RectangleStruct* pBounds) const override RX;

	//Destructor
	virtual ~IsometricTileClass() RX;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline IsometricTileClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
	IsometricTileTypeClass* Type;
    IsometricTileClass(int idxType, CellStruct const& location) : IsometricTileClass(fake_noinit_t{}) JMP_THIS(0x543780);
    IsometricTileClass(noinit_t) noexcept : IsometricTileClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(IsometricTileClass) == IsometricTileClass::ClassSize);