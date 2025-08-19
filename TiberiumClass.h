/*
	Tiberiums are initialized by INI files.
*/

#pragma once

#include "AbstractTypeClass.h"
#include "PriorityQueueClass.h"

class AnimTypeClass;
class OverlayTypeClass;

class TiberiumLogic
class __declspec(uuid("C53DD373-151E-11D2-8175-006008055BB5"))
NOVTABLE TiberiumClass : public AbstractTypeClass
{
public:
	void Construct(int nCount = PriorityQueueClassNode::SurfaceDataCount())
	{
		Nodes = (PriorityQueueClassNode*)YRMemory::Allocate(sizeof(PriorityQueueClassNode) * nCount);
		CellIndexesWithTiberium = (bool*)YRMemory::Allocate(sizeof(bool) * nCount);

		Queue = GameCreate<PriorityQueueClass<PriorityQueueClassNode>>(nCount);
	}

	void Destruct()
	{
		GameDelete(Queue);
		Queue = nullptr;

		if (Nodes)
		{
			YRMemory::Deallocate(Nodes);
			Nodes = nullptr;
		}

		if (CellIndexesWithTiberium)
		{
			YRMemory::Deallocate(CellIndexesWithTiberium);
			CellIndexesWithTiberium = nullptr;
		}
	}

	int Count;
	PriorityQueueClass<PriorityQueueClassNode>* Queue;
	bool* CellIndexesWithTiberium;
	PriorityQueueClassNode* Nodes;
	CDTimerClass Timer;
};
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream =0x7F5728;
            this->IRTTITypeInfo = 0x7F570C;
            this->INoticeSink = 0x7F5704;
            this->INoticeSource = 0x7F56FC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Tiberium;
    static constexpr uintptr_t AbsVTable = 0x7F5728;
    static constexpr size_t ClassSize = 0x128;

public:

	//Array
	ABSTRACTTYPE_ARRAY(TiberiumClass, 0xB0F4E8u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;
	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) R0;

	//Destructor
	virtual ~TiberiumClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//TiberiumClass

	void RegisterForGrowth(CellStruct* cell)
		{ JMP_THIS(0x7235A0); }

	//Static helpers

	static int FindIndex(int idxOverlayType) {
		SET_REG32(ecx, idxOverlayType);
		CALL(0x5FDD20);
	}

	static TiberiumClass* Find(int idxOverlayType) {
		int idx = FindIndex(idxOverlayType);
		return Array.GetItemOrDefault(idx);
	}


protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

    /*! @brief FAKE CTOR */
    explicit __forceinline TiberiumClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) { }
public:

	int ArrayIndex;
	int Spread;
	double SpreadPercentage;
	int Growth;
	double GrowthPercentage;
	int Value;
	int Power;
	int Color;
	DECLARE_PROPERTY(TypeList<AnimTypeClass*>, Debris);
	OverlayTypeClass* Image;
	int NumFrames;
	int NumImages;
	int NumSlopes;
	DECLARE_PROPERTY(TiberiumLogic, SpreadLogic);
	DECLARE_PROPERTY(TiberiumLogic, GrowthLogic);
    TiberiumClass(const char* pID) : TiberiumClass(fake_noinit_t{}) JMP_THIS(0x7216C0);
};
static_assert(sizeof(TiberiumClass) == TiberiumClass::ClassSize);
