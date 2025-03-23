#pragma once

#include "MissionClass.h"

//forward declarations
class TechnoClass;

/*!
* Base class for any object that can respobd via radio
*/
class NOVTABLE RadioClass : public MissionClass
{
public:
	using base_type = MissionClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7F0508;
			this->IRTTITypeInfo = 0x7F04EC;
			this->INoticeSink = 0x7F04E4;
			this->INoticeSource = 0x7F04DC;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7F0508;
	static constexpr size_t ClassSize = 0xF0;
public:
	// new command updates these
	RadioCommand LastCommands[3];
	// Docked units etc
	DECLARE_PROPERTY(VectorClass<TechnoClass*>, RadioLinks);
public:
	// 0x65AEB0 SDTOR
	virtual ~RadioClass() RX;

	HRESULT __stdcall Load(IStream* pStm) override JMP_THIS(0x65AB80);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x65AC40);

	void Detach(AbstractClass* target, bool all) override JMP_THIS(0x65AAC0);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x65AB10);
	bool Limbo() override JMP_THIS(0x65AA80);

	// these are oogly, westwood themselves admitted it, so it's probably even more of a wtf than the rest

	/*!
	* @note original_name Transmit_Message_To_First
	* @note vtable_index 157:0x274
	* @note address 0x65ACB0
	*/
	virtual RadioCommand SendToFirstLink(RadioCommand command) JMP_THIS(0x65ACB0);
	
	/*!
	* @note original_name Transmit_Message
	* @note vtable_index 158:0x278
	* @note address 0x65AAA0
	*/
	virtual RadioCommand SendCommand(RadioCommand command, TechnoClass* pRecipient) JMP_THIS(0x65AAA0);
	
	/*!
	* @note original_name Transmit_Message_Param
	* @note vtable_index 159:0x27C
	* @note address 0x65A970
	*/
	virtual RadioCommand SendCommandWithData(RadioCommand command, AbstractClass* &pInOut, TechnoClass* pRecipient) JMP_THIS(0x65A970);
	
	/*!
	* @note original_name Transmit_Message_To_All
	* @note vtable_index 160:0x280
	* @note address 0x65ACE0
	*/
	virtual void SendToEachLink(RadioCommand command) JMP_THIS(0x65ACE0);

	/*!
	* @note original_name Contact_With_Whom
	* @brief get specific link
	* @note address 0x65AD30
	*/
	constexpr TechnoClass* const& GetNthLink(int idx = 0) const { return this->RadioLinks[idx]; }

	/*!
	* @note original_name Contact_With_Whom_Building
	* @brief get specific link
	* @note address 0x65AD40
	*/
	constexpr BuildingClass* const& GetNthLinkAsBuilding(int idx = 0) const JMP_THIS(0x65AD40);

	/*!
	* @note original_name Has_Contact_Index
	* @note address 0x65AD50
	* @brief whether any link is pLink
	*/
	constexpr bool ContainsLink(TechnoClass const* pLink) const JMP_THIS(0x65AD50);

	/*!
	* @note original_name Has_Contact_Index
	* @note address 0x65AD90
	* @brief null pointers will always return -1
	*/
	constexpr int FindLinkIndex(TechnoClass const* pLink) const JMP_THIS(0x65AD90);

	/*!
	* @note original_name Has_Free_Slots
	* @note address 0x65ADC0
	* @brief iow: not full
	*/
	constexpr bool HasFreeLink() const JMP_THIS(0x65ADC0);

	/*!
	* @note original_name In_Radio_Contact
	* @note address 0x65ADF0
	* @brief iow: iow: not full; consider pIgnore's link empty
	*/
	constexpr bool HasFreeLink(TechnoClass const* pIgnore) const JMP_THIS(0x65ADF0);

	/*!
	* @note original_name Is_In_Radio_Contact
	* @note address 0x65AE30
	* @brief iow. at least one link used
	*/
	constexpr bool HasAnyLink() const JMP_THIS(0x65AE30);

	/*!
	* @note original_name Set_Radio_Count
	* @note address 0x65AE60
	* @brief resizes the vector and nulls the new elements
	*/
	constexpr void SetLinkCount(int count) JMP_THIS(0x65AE60);

protected:

	/*! @brief FAKE CTOR */
	explicit __forceinline RadioClass(fake_noinit_t) noexcept : MissionClass(fake_noinit_t{}) {}
	RadioClass(noinit_t) : MissionClass(fake_noinit_t{}) JMP_THIS(0x65A7E0);
	RadioClass() : RadioClass(fake_noinit_t{}) JMP_THIS(0x65A750);
};
static_assert(sizeof(RadioClass) == RadioClass::ClassSize);