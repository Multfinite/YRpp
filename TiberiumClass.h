#pragma once

#include "AbstractTypeClass.h"
#include "PriorityQueueClass.h"

class AnimTypeClass;
class OverlayTypeClass;

/*!
* @brief Tiberiums are initialized by INI files.
*/
class __declspec(uuid("C53DD373-151E-11D2-8175-006008055BB5"))
NOVTABLE TiberiumClass : public AbstractTypeClass
{
public:
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
    ABSTRACTTYPE_ARRAY(TiberiumClass, 0xB0F4E8u);

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

    int SpreadCount;
    PriorityQueueClass<PriorityQueueClassNode>* SpreadQueue;
    bool* SpreadCellIndexesWithTiberium;
    PriorityQueueClassNode* SpreadNodes;
    CDTimerClass SpreadTimer;

    int GrowthCount;
    PriorityQueueClass<PriorityQueueClassNode>* GrowthQueue;
    bool* GrowthCellIndexesWithTiberium;
    PriorityQueueClassNode* GrowthNodes;
    CDTimerClass GrowthTimer;

public:
    virtual ~TiberiumClass() JMP_THIS(0x721880);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x721E40);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x721E80);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x7220D0);
    
    HRESULT GetSizeMax(ULARGE_INTEGER* pcbSize) override JMP_THIS(0x7220A0);
    
    void InvalidatePointer(AbstractClass* instance, bool all = true) override JMP_THIS(0x722140);
    RTTIType KindOf() const override JMP_THIS(0x7236F0);
    int SizeOf() const override JMP_THIS(0x7236E0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x721DC0);
    int GetArrayIndex() const override JMP_THIS(0x723700);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x721A50);

    void RegisterForGrowth(CellStruct* cell) JMP_THIS(0x7235A0);

/*
    void Delete_Growth_Data() JMP_THIS(0x723510);
    void Delete_Spread_Data() JMP_THIS(0x722A20);
    void Grow() JMP_THIS(0x722F00);
    void Init() JMP_THIS(0x7236D0);
    void Init_Growth_Data() JMP_THIS(0x723260);
    CellClass* Init_Spread_Data() JMP_THIS(0x722770);
    void Queue_Growth_At_Cell(Cell* a2) JMP_THIS(0x7235A0);
    void Queue_Spread_At_Cell(Cell* a2) JMP_THIS(0x722AF0);
    void Recalc_Growth_Data() JMP_THIS(0x7233A0);
    void Recalc_Spread_Data() JMP_THIS(0x7228B0);
    void Spread() JMP_THIS(0x722440);
*/

    static int FindIndex(int idxOverlayType) {
        SET_REG32(ecx, idxOverlayType);
        CALL(0x5FDD20);
    }

    static TiberiumClass* Find(int idxOverlayType) {
        int idx = FindIndex(idxOverlayType);
        return Array->GetItemOrDefault(idx);
    }

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline TiberiumClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{}) { }
public:
    TiberiumClass(const char* pID) : TiberiumClass(fake_noinit_t{}) JMP_THIS(0x7216C0);
};
static_assert(sizeof(TiberiumClass) == TiberiumClass::ClassSize);