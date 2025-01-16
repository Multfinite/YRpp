#pragma once

#include "AbstractClass.h"
#include "Memory.h"

//forward declarations
class CCINIClass;

//Macro for the static Array of every AbstractTypeClass!
#define ABSTRACTTYPE_ARRAY(class_name, address)	public:\
	static constexpr constant_ptr<DynamicVectorClass<class_name*>, address> const Array{};\
	static __declspec(noinline) class_name* __fastcall Find(const char* pID)\
	{\
		for(auto pItem : *Array)\
			if(!_strcmpi(pItem->ID, pID))\
				return pItem;\
		return nullptr;\
	}\
	static __declspec(noinline) int __fastcall FindIndex(const char* pID)\
	{\
		for(int i = 0; i < Array->Count; ++i)\
			if(!_strcmpi(Array->Items[i]->ID, pID))\
				return i;\
		return -1;\
	}

/*!
* @brief AbstractType is abstract template objects initialized by INI files.
*/
class NOVTABLE AbstractTypeClass : public AbstractClass
{
public:
	static constexpr uintptr_t AbsVTable = 0x7E2000;
	static constexpr AbstractType AbsID = AbstractType::Abstract;

	static constexpr constant_ptr<DynamicVectorClass<AbstractTypeClass*>, 0xA8E968u> const Array{};
public:
	char ID[0x19-1];
	/*! @brief Nullterminator of ID (some cursed string handler class do this) */
	PROTECTED_PROPERTY(BYTE, __ID_ZERO);
	char UINameLabel[0x20-1];
	/*! @brief Nullterminator of ID (some cursed string handler class do this) */
	PROTECTED_PROPERTY(BYTE, __UINameLabel_ZERO);
	const wchar_t* UIName;
	char Name[0x31];
public:
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x410BE0);

	virtual ~AbstractTypeClass() JMP_THIS(0x4109C0);
	/*!
	* @brief It's commonly empty. Only AnimClass override this.
	* @note vtable_index 24:0x60
	*/
	virtual void LoadTheaterSpecificArt(TheaterType th_type) JMP_THIS(0x410C20);
	/*25:0x64*/virtual bool LoadFromINI(CCINIClass* pINI) JMP_THIS(0x410A60);
	/*26:0x68*/virtual bool SaveToINI(CCINIClass* pINI) JMP_THIS(0x410B90);

	const char* get_ID() const { return this->ID; }

protected:
	explicit __forceinline AbstractTypeClass(fake_noinit_t) noexcept{ }
	AbstractTypeClass(noinit_t) : AbstractTypeClass(fake_noinit_t{}) JMP_THIS(0x410960);
	AbstractTypeClass(char* pId) : AbstractTypeClass(fake_noinit_t{}) JMP_THIS(0x410800);
};
