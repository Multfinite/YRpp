#pragma once

#include "LocomotionClass.h"

class __declspec(uuid("4A582745-9839-11d1-B709-00A024DDAFD1"))
NOVTABLE DropPodLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	virtual ULONG __stdcall AddRef() R0;
	virtual ULONG __stdcall Release() R0;

	//IPiggyback
	virtual HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) R0;
	virtual HRESULT __stdcall End_Piggyback(ILocomotion** pointer) R0;
	virtual bool __stdcall Is_Ok_To_End() R0;
	virtual HRESULT __stdcall Piggyback_CLSID(GUID* classid) R0;
	virtual bool __stdcall Is_Piggybacking() R0;

	//ILocomotion
	virtual bool __stdcall Is_Moving() R0;
	virtual CoordStruct* __stdcall Destination(CoordStruct* pcoord) R0;
	virtual bool __stdcall Process() R0;
	virtual void __stdcall Move_To(CoordStruct to) RX;
	virtual void __stdcall Stop_Moving() RX;
	virtual int __stdcall Drawing_Code() R0;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~DropPodLocomotionClass() RX;

	//LocomotionClass
	virtual	int Size() R0;

	using base_type = LocomotionClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		JMP_THIS(0x4B5AB0);
	}
		uintptr_t IPiggyBack;

		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E8344;
			this->ILocomotion = 0x7E8278;
			this->IPiggyBack = 0x7E8254;
		}

		__forceinline void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t ILocoVTable = 0x7E8278;
	static constexpr size_t ClassSize = 0x30;
public:
	bool OutOfMap;
	CoordStruct DestinationCoords;
	ILocomotionPtr Piggybackee;
};

protected:
	explicit __forceinline DropPodLocomotionClass(noinit_t) : LocomotionClass(noinit_t{}) {}
public:
	DropPodLocomotionClass() : DropPodLocomotionClass(noinit_t{}) JMP_THIS(0x4B5AB0);

};
static_assert(sizeof(DropPodLocomotionClass) == DropPodLocomotionClass::ClassSize);
