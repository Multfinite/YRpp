#pragma once

#include "FileSystem.h"
#include "AbstractClass.h"

class ObjectClass;

/*!
* @brief RadSites
*/
class NOVTABLE AlphaShapeClass : public AbstractClass
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
	static const AbstractType AbsID = AbstractType::AlphaShape;
	static constexpr uintptr_t AbsVTable = 0x7E32A4;

	static constexpr constant_ptr<DynamicVectorClass<AlphaShapeClass*>, 0x88A0F0u> const Array{};
public:
	ObjectClass* AttachedTo;	//To which object is this AlphaShape attached?
	RectangleStruct Rect;
	SHPStruct* AlphaImage;
	bool IsObjectGone;	//Set if AttachedTo is NULL.
public:
	// scalar: 0x421730
	virtual ~AlphaShapeClass() {}

	HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x420D40);
	
	HRESULT Load(IStream* pStm) override JMP_THIS(0x420DE0);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x420E40);
	
	void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x420E70);
	RTTIType KindOf() const override JMP_THIS(0x420D80);
	int SizeOf() const override JMP_THIS(0x420D90);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x420DA0);

	/*
	void AI() JMP_THIS(0x420E90);
	int32_t Blit(tagRECT* edx0) JMP_THIS(0x420F40);
	int32_t Blit_Rect() JMP_THIS(0x421350);
	uint32_t Init_Array() JMP_THIS(0x4216C0);
	*/
protected:
	explicit __forceinline AlphaShapeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	AlphaShapeClass(noinit_t) : AlphaShapeClass(fake_noinit_t{}) { vtables.init(this); }
	AlphaShapeClass(ObjectClass* pObj, int nX, int nY) : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420960);
};
