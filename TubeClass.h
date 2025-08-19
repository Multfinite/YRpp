#pragma once

#include "AbstractClass.h"

class __declspec(uuid("0B4CA41C-B3A7-11D1-B457-006097C7A979"))
NOVTABLE TubeClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F59B0;
			this->IRTTITypeInfo = 0x7F5994;
			this->INoticeSink = 0x7F598C;
			this->INoticeSource = 0x7F5984;
		}
	};
	static inline vtables_t vtables {};
public:
	static constexpr uintptr_t AbsVTable = 0x7F59B0;
	static constexpr size_t ClassSize = 0x1C4;
	static constexpr AbstractType AbsID = AbstractType::Tube;

	DEFINE_REFERENCE(DynamicVectorClass<TubeClass*>, Array, 0x8B4138u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//Destructor
	virtual ~TubeClass() RX;


protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline TubeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t {}) { }

public:
	CellStruct EnterCell;
	CellStruct ExitCell;
	int ExitFace;
	int Faces[100];
	int FaceCount;
	TubeClass(CellStruct* cell, int32_t facing) noexcept : TubeClass(fake_noinit_t{}) JMP_THIS(0x727FD0);
	TubeClass(noinit_t) noexcept : TubeClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(TubeClass) == TubeClass::ClassSize);
