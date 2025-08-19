/*
	Factories are responsible for producing units and buildings.
*/

#pragma once

#include "AbstractClass.h"
#include "StageClass.h"

class HouseClass;
class TechnoClass;
class TechnoTypeClass;

class __declspec(uuid("34ECD9A8-0AB0-11D2-ACA7-006008055BB5"))
NOVTABLE FactoryClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E88D0;
            this->IRTTITypeInfo = 0x7E88B4;
            this->INoticeSink = 0x7E88AC;
            this->INoticeSource = 0x7E88A4;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Factory;
    static constexpr uintptr_t AbsVTable = 0x7E88D0;
    static constexpr size_t ClassSize = 0x74;

	DEFINE_REFERENCE(DynamicVectorClass<FactoryClass*>, Array, 0xA83E30u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~FactoryClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//non-virtual

	// returns whether progress "IsDifferent" and resets the flag
	bool HasProgressChanged()
		{ JMP_THIS(0x4C9C60); }

	bool DemandProduction(TechnoTypeClass const* pType, HouseClass* pOwner, bool shouldQueue)
		{ JMP_THIS(0x4C9C70); }

	// aborts current product and puts the object in, completed and suspended
	void SetObject(TechnoClass* pObject)
		{ JMP_THIS(0x4C9E10); }

	bool Suspend(bool manual)
		{ JMP_THIS(0x4C9E60); }

	bool Unsuspend(bool manual)
		{ JMP_THIS(0x4C9EA0); }

	int GetBuildTimeFrames() const
		{ JMP_THIS(0x4C9FB0); }

	bool AbandonProduction()
		{ JMP_THIS(0x4C9FF0); }

	// returns Production.Value
	int GetProgress() const
		{ JMP_THIS(0x4CA120); }

	bool IsDone() const
		{ JMP_THIS(0x4CA130); }

	int GetCostPerStep() const
		{ JMP_THIS(0x4CA180); }

	// checks the progress and updates the state if done
	bool CompletedProduction()
		{ JMP_THIS(0x4CA1A0); }

	// builds an item from the queue
	void StartProduction()
		{ JMP_THIS(0x4CA5A0); }

	bool RemoveOneFromQueue(TechnoTypeClass const* pItem)
		{ JMP_THIS(0x4CA620); }

	// in queue and in production
	int CountTotal(TechnoTypeClass const* pType) const
		{ JMP_THIS(0x4CA670); }

	// whether at least one item is queued, not in production
	bool IsQueued(TechnoTypeClass const* pType) const
		{ JMP_THIS(0x4CA6B0); }

	static FactoryClass* FindByOwnerAndProduct(
		HouseClass const* const pHouse, TechnoTypeClass const* const pItem)
	{
		for(auto const& pFact : FactoryClass::Array) {
			if(pFact->Owner == pHouse) {
				if(pFact->CountTotal(pItem) > 0) {
					return pFact;
				}
			}
		}
		return nullptr;
	}


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

    /*! @brief FAKE CTOR */
    explicit __forceinline FactoryClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}
public:
	StageClass      Production; // hardcoded to be 54 steps (so cameo clock should be 54 frames)
	DynamicVectorClass<TechnoTypeClass*> QueuedObjects;
	TechnoClass*       Object;
	bool               OnHold; // paused when out of money, restored when funds available
	bool               IsDifferent;	// changed progress
	PROTECTED_PROPERTY(BYTE, align_5E[2]);
	int                Balance; // credits house still owes us for building this
	int                OriginalBalance;
	int                SpecialItem; // -1 = none, else Iron Curtain? (was EMPulse in TS)
	HouseClass*        Owner;
	bool               IsSuspended; //completed production, before next (or waiting to place)
	bool               IsManual; // whether the current suspension state was caused by the player
	PROTECTED_PROPERTY(BYTE, padding_72[2]);
    FactoryClass() : FactoryClass(fake_noinit_t{}) JMP_THIS(0x4C98B0);
    FactoryClass(noinit_t) noexcept : FactoryClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(FactoryClass) == FactoryClass::ClassSize);
