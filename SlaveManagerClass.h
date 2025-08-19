#pragma once

#include "AbstractClass.h"

class HouseClass;
class InfantryClass;

enum class SlaveManagerStatus : unsigned int {
	Ready = 0,
	Scanning = 1,
	Travelling = 2,
	Deploying = 3,
	Working = 4,
	ScanningAgain = 5,
	PackingUp = 6
};

enum class SlaveControlStatus : unsigned int {
	Unknown = 0,
	ScanningForTiberium = 1,
	MovingToTiberium = 2,
	Harvesting = 3,
	BringingItBack = 4,
	Respawning = 5,
	Dead = 6
};

class __declspec(uuid("335AAFE4-2DA6-11D5-BE22-00104B62A16C"))
NOVTABLE SlaveManagerClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct SlaveControl {
        InfantryClass* Slave;
        SlaveControlStatus State;
        CDTimerClass RespawnTimer;
    };

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F31C8;
            this->IRTTITypeInfo = 0x7F31AC;
            this->INoticeSink = 0x7F31A4;
            this->INoticeSource = 0x7F319C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::SlaveManager;
    static constexpr uintptr_t AbsVTable = 0x7F31C8;
    static constexpr size_t ClassSize = 0x64;

	struct SlaveControl {
		InfantryClass* Slave;
		SlaveControlStatus State;
		CDTimerClass RespawnTimer;
	};

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<SlaveManagerClass*>, Array, 0xB0B5F0u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~SlaveManagerClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	// non-virtual
	void SetOwner(TechnoClass *NewOwner)
		{ JMP_THIS(0x6AF580); }

	void CreateSlave(SlaveControl *Node)
		{ JMP_THIS(0x6AF650); }

	void LostSlave(InfantryClass *Slave)
		{ JMP_THIS(0x6B0A20); }

	void Deploy2()
		{ JMP_THIS(0x6B0D60); }

	// switches the slaves to the killer house with cheers and hoorahs
	// note that this->Owner will be NULL once this function is done
	void Killed(TechnoClass *Killer, HouseClass * ForcedOwnerHouse = nullptr)
		{ JMP_THIS(0x6B0AE0); }

	bool ShouldWakeUpNow()
		{ JMP_THIS(0x6B1020); }

	// the slaves will become free citizens without any announcements or cheers, if you don't call Killed() beforehand
	void ZeroOutSlaves();

	// stops scanning, spawning slaves and driving around.
	void SuspendWork() {
		this->RespawnTimer.StartTime = -1;
		if(!this->RespawnTimer.TimeLeft) {
			this->RespawnTimer.TimeLeft = 1;
		}
	}

	// resumes to harvest automatically.
	void ResumeWork() {
		this->RespawnTimer.Resume();
	}


protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SlaveManagerClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

	TechnoClass* Owner;
	InfantryTypeClass* SlaveType;
	int SlaveCount;
	int RegenRate;
	int ReloadRate;
	DynamicVectorClass<SlaveControl*> SlaveNodes;
	CDTimerClass RespawnTimer;
	SlaveManagerStatus State;
	int LastScanFrame;
    SlaveManagerClass(TechnoClass* pOwner, InfantryTypeClass* pSlave, int num, int RegenRate, int ReloadRate) noexcept
        : SlaveManagerClass(fake_noinit_t{}) JMP_THIS(0x6AF1A0);
    SlaveManagerClass() : SlaveManagerClass(fake_noinit_t{}) JMP_THIS(0x6AF360);
    SlaveManagerClass(noinit_t) noexcept : SlaveManagerClass(fake_noinit_t{}) JMP_THIS(0x6AF440);
};
static_assert(sizeof(SlaveManagerClass) == SlaveManagerClass::ClassSize);
