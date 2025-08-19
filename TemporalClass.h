#pragma once

#include "AbstractClass.h"

class SuperClass;
class TechnoClass;

//The AirstrikeClass handles the airstrikes Boris calls in.
class __declspec(uuid("94112424-E403-11D3-8E6E-005004AAB2FB"))
NOVTABLE TemporalClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F5180;
            this->IRTTITypeInfo = 0x7F5164;
            this->INoticeSink = 0x7F515C;
            this->INoticeSource = 0x7F5154;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Temporal;
    static constexpr uintptr_t AbsVTable = 0x7F5180;
    static constexpr size_t ClassSize = 0x50;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<TemporalClass*>, Array, 0xB0EC60u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~TemporalClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//non-virtual
	void Fire(TechnoClass* pTarget)
		{ JMP_THIS(0x71AF20); }
	bool CanWarpTarget(TechnoClass* pTarget) const
		{ JMP_THIS(0x71AE50); }

	// hardcoded to accumulate only up to 50 helpers
	int GetWarpPerStep( int nHelperCount = 0 ) const
		{ JMP_THIS(0x71AB10); }

	void LetGo()
		{ JMP_THIS(0x71ABC0); }
	void JustLetGo()
		{ JMP_THIS(0x71AD40); }
	void Detach()
		{ JMP_THIS(0x71ADE0); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline TemporalClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	TechnoClass*       Owner;
	TechnoClass*       Target;
	CDTimerClass       LifeTimer;
	void*              unknown_pointer_38;
	SuperClass*        SourceSW;

	TemporalClass*     NextTemporal;
	TemporalClass*     PrevTemporal;

	int                WarpRemaining;
	int                WarpPerStep;
    TemporalClass() : TemporalClass(fake_noinit_t{}) JMP_THIS(0x71A450);
    TemporalClass(noinit_t) noexcept : TemporalClass(fake_noinit_t{}) JMP_THIS(0x71A5A0);
    TemporalClass(TechnoClass* pOwnerUnit) : TemporalClass(fake_noinit_t{}) JMP_THIS(0x71A4E0);
};
static_assert(sizeof(TemporalClass) == TemporalClass::ClassSize);
