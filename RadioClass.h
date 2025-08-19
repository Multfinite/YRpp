/*
	Base class for WHAT?? I DUNNO =(
*/

#pragma once

#include "MissionClass.h"

//forward declarations
class TechnoClass;

class NOVTABLE RadioClass : public MissionClass
{
public:
	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
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
	virtual ~RadioClass() RX;

	//RadioClass

	// these are oogly, westwood themselves admitted it, so it's probably even more of a wtf than the rest
	virtual RadioCommand SendToFirstLink(RadioCommand command) RT(RadioCommand);
	virtual RadioCommand SendCommand(RadioCommand command, TechnoClass* pRecipient) RT(RadioCommand);
	virtual RadioCommand SendCommandWithData(RadioCommand command, AbstractClass* &pInOut, TechnoClass* pRecipient) RT(RadioCommand);
	virtual void SendToEachLink(RadioCommand command) RX;

	// get specific link
	TechnoClass* const& GetNthLink(int idx = 0) const {
		return this->RadioLinks[idx];
	}

	// whether any link is pLink
	bool ContainsLink(TechnoClass const* pLink) const
		{ JMP_THIS(0x65AD50); }

	// note: null pointers will always return -1
	int FindLinkIndex(TechnoClass const* pLink) const
		{ JMP_THIS(0x65AD90); }

	// iow: not full
	bool HasFreeLink() const
		{ JMP_THIS(0x65ADC0); }

	// iow: not full; consider pIgnore's link empty
	bool HasFreeLink(TechnoClass const* pIgnore) const
		{ JMP_THIS(0x65ADF0); }

	// iow. at least one link used
	bool HasAnyLink() const
		{ JMP_THIS(0x65AE30); }

	// resizes the vector and nulls the new elements
	void SetLinkCount(int count)
		{ JMP_THIS(0x65AE60); }


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	RadioCommand LastCommands[3]; // new command updates these
	DECLARE_PROPERTY(VectorClass<TechnoClass*>, RadioLinks);	//Docked units etc
	/*! @brief FAKE CTOR */
	explicit __forceinline RadioClass(fake_noinit_t) noexcept : MissionClass(fake_noinit_t{}) {}
	RadioClass(noinit_t) : MissionClass(fake_noinit_t{}) JMP_THIS(0x65A7E0);
	RadioClass() : RadioClass(fake_noinit_t{}) JMP_THIS(0x65A750);
};
static_assert(sizeof(RadioClass) == RadioClass::ClassSize);
