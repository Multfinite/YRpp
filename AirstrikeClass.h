#pragma once

#include "AbstractClass.h"

//forward declarations
class AircraftTypeClass;
class ObjectClass;
class TechnoClass;
class FootClass;

//The AirstrikeClass handles the airstrikes Boris calls in.
class NOVTABLE AirstrikeClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E29A8;
			this->IRTTITypeInfo = 0x7E298C;
			this->INoticeSink = 0x7E2984;
			this->INoticeSource = 0x7E297C;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7E29A8;
	static constexpr AbstractType AbsID = AbstractType::Airstrike;
	static constexpr size_t ClassSize = 0x60;
public:
	int AirstrikeTeam;			//As in the INI files.
	int EliteAirstrikeTeam;	//As in the INI files.
	int AirstrikeTeamTypeIndex;	//As in the INI files.
	int EliteAirstrikeTeamTypeIndex;	//As in the INI files.
	DWORD unknown_34;
	DWORD unknown_38;	//unused?
	bool IsOnMission;	//Is the Aircraft on its way?
	bool unknown_bool_3D;
	DWORD TeamDissolveFrame;	//when was the last time this team was invoked and subsequently dissolved
	int AirstrikeRechargeTime;	//As in the INI files.
	int EliteAirstrikeRechargeTime;	//As in the INI files.
	TechnoClass* Owner;		//The unit that called the Airstrike (usually Boris).
	ObjectClass* Target;	//The Airstrike's target.
	AircraftTypeClass* AirstrikeTeamType;	//As in the INI files.
	AircraftTypeClass* EliteAirstrikeTeamType;	//As in the INI files.
	// TeamPointer
	FootClass* FirstObject;
public:
	// scalar: 0x41DD50
	virtual ~AirstrikeClass() {}
	
	HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x41D7A0);
	
	HRESULT Load(IStream* pStm) override JMP_THIS(0x41D6F0);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x41D780);
	
	RTTIType KindOf() const override JMP_THIS(0x41DD40);
	int SizeOf() const override JMP_THIS(0x41DD30);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x41D6E0);
	void AI() override JMP_THIS(0x41DC50);

	//non-virtual
	void StartMission(ObjectClass* pTarget) JMP_THIS(0x41D830);

	/*
	bool Can_Strike(int32_t target) JMP_THIS(0x41D7E0);
	void Detach(TechnoClass* arg0) JMP_THIS(0x41D540);
	FootClass* Remove_Member(FootClass* a2) JMP_THIS(0x41DC80);
	void Reset_Target() JMP_THIS(0x41DB40);
	void Set_Target(TechnoClass* target) JMP_THIS(0x41DA20);
	void Setup(TechnoClass* target) JMP_THIS(0x41D860);
	void Setup_Target(TechnoClass* techno) JMP_THIS(0x41D830);
	*/

protected:
	explicit __forceinline AirstrikeClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	AirstrikeClass(noinit_t) : AirstrikeClass(fake_noinit_t{}) JMP_THIS(0x41D300);
	AirstrikeClass(TechnoClass* pOwner) : AirstrikeClass(fake_noinit_t{}) JMP_THIS(0x41D380);
};
static_assert(sizeof(AirstrikeClass) == AirstrikeClass::ClassSize);