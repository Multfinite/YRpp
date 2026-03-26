#pragma once

#include "FileSystem.h"
#include "AbstractClass.h"

class ObjectClass;

/*!
* @brief RadSites
*/
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

	DEFINE_REFERENCE(DynamicVectorClass<AlphaShapeClass*>, Array, 0x88A0F0u)
	DEFINE_REFERENCE(char, IsArrayInitialized, 0x89A134)
public:
	//To which object is this AlphaShape attached?
	ObjectClass* AttachedTo;
	RectangleStruct Rect;
	SHPStruct* AlphaImage;
	//Set if AttachedTo is NULL.
	bool IsObjectGone;
	char field_3D;
public:
	virtual ~AlphaShapeClass() JMP_THIS(0x420C80);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x420D40);
	
	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x420DE0);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x420E40);
	
	void PointerExpired(AbstractClass* instance, bool removed = true) override JMP_THIS(0x420E70);
	RTTIType WhatAmI() const override JMP_THIS(0x420D80);
	int Size() const override JMP_THIS(0x420D90);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x420DA0);

/*
	void Update() JMP_THIS(0x420E90);
	int32_t Blit(tagRECT* edx0) JMP_THIS(0x420F40);
	int32_t Blit_Rect() JMP_THIS(0x421350);
	uint32_t Init_Array() JMP_THIS(0x4216C0);
*/

protected:
	explicit __forceinline AlphaShapeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	AlphaShapeClass() : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420AF0);
	AlphaShapeClass(noinit_t) noexcept : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420C50);
	AlphaShapeClass(ObjectClass* pObj, int nX, int nY) : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420960);
};
static_assert(sizeof(AlphaShapeClass) == AlphaShapeClass::ClassSize);
