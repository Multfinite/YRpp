#pragma once

#include "FootClass.h"
#include "InfantryTypeClass.h"

/*!
* @brief Infantry
*/
class NOVTABLE InfantryClass : public FootClass
{
public:
	static const AbstractType AbsID = AbstractType::Infantry;
	static constexpr uintptr_t AbsVTable = 0x7EB058;
	static constexpr size_t ClassSize = 0x6F0;

	static constexpr constant_ptr<DynamicVectorClass<InfantryClass*>, 0xA83DE8u> const Array{};
public:
	InfantryTypeClass* Type;
	//which is currently playing
	Sequence SequenceAnim;
	CDTimerClass CommentTimer;
	// set in ReceiveDamage on panicky units
	DWORD          PanicDurationLeft;
	// set by script action, not cleared anywhere
	bool           PermanentBerzerk;
	bool           IsTechnician;
	bool           IsStroked;
	bool           IsProne;
	bool           IsZoneCheat;
	bool           WasSelected;
	DWORD      unknown_6E0;
	bool           ShouldDeploy;
	int            OnLand;
	PROTECTED_PROPERTY(DWORD, unused_6EC);
public:
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_THIS(0x523300);

	//Destructor
	virtual ~InfantryClass() JMP_THIS(0x517D90);

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	//ObjectClass

	virtual Action MouseOverObject(ObjectClass const* pObject, bool ignoreForce = false) const override JMP_THIS(0x51E3B0);

	//TechnoClass
	virtual FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const override JMP_THIS(0x51C8B0);


	//InfantryClass
	virtual bool IsDeployed() const R0;
	virtual bool PlayAnim(Sequence index, bool force = false, bool randomStartFrame = false) R0;

	//Constructor
	InfantryClass(InfantryTypeClass* pType, HouseClass* pOwner) noexcept
		: InfantryClass(noinit_t())
	{ JMP_THIS(0x517A50); }

protected:
	explicit __forceinline InfantryClass(noinit_t) noexcept
		: FootClass(noinit_t())
	{ }
};
