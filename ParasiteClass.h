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
public:
	FootClass* Owner;
	FootClass* Victim;
	CDTimerClass    SuppressionTimer;
	CDTimerClass    DamageDeliveryTimer;
	AnimClass* GrappleAnim;
	ParasiteState   GrappleState;
	int             GrappleAnimFrame;
	int             GrappleAnimDelay;
	bool            GrappleAnimGotInvalid;
public:
	virtual ~ParasiteClass() JMP_THIS(0x6293E0);

	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6296D0);

	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6295B0);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6296B0);

	void InvalidatePointer(AbstractClass* instance, bool all = true) JMP_THIS(0x410480);
	RTTIType KindOf() const override JMP_THIS(0x62AF60);
	int SizeOf() const override JMP_THIS(0x62AF50);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6294D0);
	void AI() override JMP_THIS(0x629FD0);
public:
	/*!
	* @brief
	* @note original_name Can_Infect
	* @note address 0x62A8E0
	*/
	bool CanInfect(FootClass* pTarget) const JMP_THIS(0x62A8E0);

	/*!
	* @brief
	* @note original_name Infect
	* @note address 0x62A980
	*/
	void TryInfect(FootClass* pTarget) JMP_THIS(0x62A980);

	/*!
	* @brief
	* @note original_name Victims_Cell_Valid
	* @note address 0x62AB40
	*/
	bool CanExistOnVictimCell() const JMP_THIS(0x62AB40);

	/*!
	* @brief
	* @note original_name Grapple_AI
	* @note address 0x6297F0
	*/
	void UpdateSquid() JMP_THIS(0x6297F0);

	/*!
	* @brief
	* @note original_name Grapple_AI
	* @note address 0x629720
	*/
	bool UpdateGrapple() JMP_THIS(0x629720);

	/*!
	* @brief
	* @note original_name Uninfect
	* @note address 0x62A4A0
	*/
	void ExitUnit() JMP_THIS(0x62A4A0);

	/*!
	* @note original_name Detach_From_Victim
	* @note address 0x62AC30
	*/
	int32_t DetachFromVictim(int32_t arg0) JMP_THIS(0x62AC30);

	/*!
	* @note original_name Reset_Grapple
	* @note address 0x629710
	*/
	int32_t ResetGrapple() JMP_THIS(0x629710);

protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline ParasiteClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	ParasiteClass(noinit_t) noexcept : AbstractClass(fake_noinit_t{}) JMP_THIS(0x629210);
	ParasiteClass(FootClass* owner = nullptr) : ParasiteClass(fake_noinit_t{}) JMP_THIS(0x6292B0);
};
static_assert(sizeof(ParasiteClass) == ParasiteClass::ClassSize);