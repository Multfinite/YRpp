#pragma once

#include "AbstractClass.h"

class AnimClass;
class FootClass;

class __declspec(uuid("1D016B81-B24B-11D3-BE16-00104B62A16C"))
NOVTABLE ParasiteClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EF890;
			this->IRTTITypeInfo = 0x7EF874;
			this->INoticeSink = 0x7EF86C;
			this->INoticeSource = 0x7EF864;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7EF890;
	static constexpr AbstractType AbsID = AbstractType::Parasite;
	static constexpr size_t ClassSize = 0x58;

	DEFINE_REFERENCE(DynamicVectorClass<ParasiteClass*>, Array, 0xAC4910u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParasiteClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//non-virtual
	void UpdateSquid()
		{ JMP_THIS(0x6297F0); }

	bool UpdateGrapple()
		{ JMP_THIS(0x629720); }

	void ExitUnit()
		{ JMP_THIS(0x62A4A0); }

	bool CanInfect(FootClass *pTarget) const
		{ JMP_THIS(0x62A8E0); }

	void TryInfect(FootClass *pTarget)
		{ JMP_THIS(0x62A980); }

	bool CanExistOnVictimCell() const
		{ JMP_THIS(0x62AB40); }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	FootClass*      Owner;
	FootClass*      Victim;
	CDTimerClass    SuppressionTimer;
	CDTimerClass    DamageDeliveryTimer;
	AnimClass*      GrappleAnim;
	ParasiteState   GrappleState;
	int             GrappleAnimFrame;
	int             GrappleAnimDelay;
	bool            GrappleAnimGotInvalid;
protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline ParasiteClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	ParasiteClass(noinit_t) noexcept : AbstractClass(fake_noinit_t{}) JMP_THIS(0x629210);
	ParasiteClass(FootClass* owner = nullptr) : ParasiteClass(fake_noinit_t{}) JMP_THIS(0x6292B0);
};
static_assert(sizeof(ParasiteClass) == ParasiteClass::ClassSize);
