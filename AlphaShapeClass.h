/*
	RadSites
*/

#pragma once

#include "FileSystem.h"
#include "AbstractClass.h"

class ObjectClass;

class __declspec(uuid("623C7584-74E7-11D2-B8F5-006008C809ED"))
NOVTABLE AlphaShapeClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E32A4;
			this->IRTTITypeInfo = 0x7E3288;
			this->INoticeSink = 0x7E3280;
			this->INoticeSource = 0x7E3278;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr AbstractType AbsID = AbstractType::AlphaShape;
	static constexpr uintptr_t AbsVTable = 0x7E32A4;
	static constexpr size_t ClassSize = 0x40;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<AlphaShapeClass*>, Array, 0x88A0F0u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~AlphaShapeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

	explicit __forceinline AlphaShapeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:

	ObjectClass* AttachedTo;	//To which object is this AlphaShape attached?
	RectangleStruct Rect;
	SHPStruct* AlphaImage;
	bool IsObjectGone;	//Set if AttachedTo is NULL.
	AlphaShapeClass() : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420AF0);
	AlphaShapeClass(noinit_t) noexcept : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420C50);
	AlphaShapeClass(ObjectClass* pObj, int nX, int nY) : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420960);
};
static_assert(sizeof(AlphaShapeClass) == AlphaShapeClass::ClassSize);
