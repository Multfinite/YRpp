/*
	SmudgeTypes are initialized by INI files.
*/

#pragma once

#include "ObjectTypeClass.h"

class __declspec(uuid("5AF2CE78-0634-11D2-ACA4-006008055BB5"))
NOVTABLE SmudgeTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F3528;
            this->IRTTITypeInfo = 0x7F350C;
            this->INoticeSink = 0x7F3504;
            this->INoticeSource = 0x7F34FC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::SmudgeType;
    static constexpr uintptr_t AbsVTable = 0x7F3528;
    static constexpr size_t ClassSize = 0x2A4;

	//Array
	ABSTRACTTYPE_ARRAY(SmudgeTypeClass, 0xA8EC18u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~SmudgeTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//SmudgeTypeClass
	virtual void DrawIt(const Point2D& Point, const RectangleStruct& Rect, int SmudgeData, int Height, const CellStruct& MapCoords) RX;

	static void __fastcall LoadFromIniList(int idxTheatre)
		{ JMP_STD(0x6B5490); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline SmudgeTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	int ArrayIndex;
	int Width;
	int Height;
	bool Crater;
	bool Burn;
    SmudgeTypeClass(const char* pID) noexcept : SmudgeTypeClass(fake_noinit_t{}) JMP_THIS(0x6B5260);
    SmudgeTypeClass(noinit_t) : SmudgeTypeClass(fake_noinit_t{}) JMP_THIS(0x6B5370);
};

static_assert(sizeof(SmudgeTypeClass) == SmudgeTypeClass::ClassSize);
