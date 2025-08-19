#pragma once



#include "GeneralDefinitions.h"
#include "CCINIClass.h"
#include "AbstractTypeClass.h"

class __declspec(uuid("FFDAC848-1517-11D2-8175-006008055BB5"))
NOVTABLE CampaignClass : public AbstractTypeClass
{
public:
	static void __fastcall CreateFromINIList(CCINIClass *pINI)
		{ JMP_STD(0x46CE10); }
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractTypeClass::vtables_t
	{
		constexpr vtables_t() noexcept : AbstractTypeClass::vtables_t()
		{
			this->IPersistStream = 0x7E4A28;
			this->IRTTITypeInfo = 0x7E4A0C;
			this->INoticeSink = 0x7E4A04;
			this->INoticeSource = 0x7E49FC;
		}
	};
	static inline vtables_t vtables{};

	static signed int __fastcall FindIndex(const char* name)
		{ JMP_STD(0x46CC90); }
	static constexpr AbstractType AbsID = AbstractType::Campaign;
	static constexpr uintptr_t AbsVTable = 0x7E4A28;
	static constexpr size_t ClassSize = 0x3A0;

public:
	int idxCD;
	char Scenario[512];
	int FinalMovie;
	wchar_t Description[128];
protected:
	/*! @brief FAKE CTOR */
	explicit __forceinline CampaignClass(fake_noinit_t) noexcept
		: AbstractTypeClass(fake_noinit_t{}) { }

public:
	CampaignClass(noinit_t) noexcept : CampaignClass(fake_noinit_t{}) { vtables.init(this); }
	CampaignClass(const char* name) : CampaignClass(fake_noinit_t{})
		JMP_THIS(0x46CB60);
};
static_assert(sizeof(CampaignClass) == CampaignClass::ClassSize);