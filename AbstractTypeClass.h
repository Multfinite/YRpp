/*
	AbstractTypes are abstract template objects initialized by INI files
*/
#pragma once

#include "AbstractClass.h"
#include "Memory.h"

//forward declarations
class CCINIClass;

//Macro for the static Array of every AbstractTypeClass!
#define ABSTRACTTYPE_ARRAY(class_name, address)	public:\
	DEFINE_REFERENCE(DynamicVectorClass<class_name*>, Array, address)\
	static __declspec(noinline) class_name* __fastcall Find(const char* pID)\
	{\
		for(auto pItem : Array)\
			if(!_strcmpi(pItem->ID, pID))\
				return pItem;\
		return nullptr;\
	}\
	static __declspec(noinline) int __fastcall FindIndex(const char* pID)\
	{\
		for(int i = 0; i < Array.Count; ++i)\
			if(!_strcmpi(Array[i]->ID, pID))\
				return i;\
		return -1;\
	}
//---

class NOVTABLE AbstractTypeClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x07E2000;
			this->IRTTITypeInfo = 0x7E1FE4;
			this->INoticeSink = 0x7E1FDC;
			this->INoticeSource = 0x7E1FD4;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7E2000;
	static constexpr RTTIType AbsID = RTTIType::Abstract;
	static constexpr size_t ClassSize = 0x98;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<AbstractTypeClass*>, Array, 0xA8E968u)

	//Destructor
	virtual ~AbstractTypeClass() RX;

	//AbstractTypeClass
	virtual void LoadTheaterSpecificArt(TheaterType th_type) RX;
	virtual bool LoadFromINI(CCINIClass* pINI) R0;
	virtual bool SaveToINI(CCINIClass* pINI) R0;

	const char* get_ID() const {
		return this->ID;
	}


protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline AbstractTypeClass(fake_noinit_t) noexcept{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	char ID [0x18];
	PROTECTED_PROPERTY(BYTE, zero_3C);
	char UINameLabel [0x20];
	const wchar_t* UIName;
	char Name [0x31];
	AbstractTypeClass(noinit_t) : AbstractTypeClass(fake_noinit_t{}) JMP_THIS(0x410960);
	AbstractTypeClass(char* pId) : AbstractTypeClass(fake_noinit_t{}) JMP_THIS(0x410800);
};
static_assert(sizeof(AbstractTypeClass) == AbstractTypeClass::ClassSize);
