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

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

protected:
	explicit __forceinline AlphaShapeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	AlphaShapeClass(noinit_t) : AlphaShapeClass(fake_noinit_t{}) { vtables.init(this); }
	AlphaShapeClass(ObjectClass* pObj, int nX, int nY) : AlphaShapeClass(fake_noinit_t{}) JMP_THIS(0x420960);
};
