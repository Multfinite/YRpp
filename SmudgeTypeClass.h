#pragma once

#include "ObjectTypeClass.h"

class __declspec(uuid("5AF2CE78-0634-11D2-ACA4-006008055BB5"))
NOVTABLE SmudgeTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F3528;
            this->IRTTITypeInfo = 0x7F350C;
            this->INoticeSink = 0x7F3504;
            this->INoticeSource = 0x7F34FC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::SmudgeType;
    static constexpr uintptr_t AbsVTable = 0x7F3528;
    static constexpr size_t ClassSize = 0x2A4;

public:
    ABSTRACTTYPE_ARRAY(SmudgeTypeClass, 0xA8EC18u);

public:
    int ArrayIndex;
    int Width;
    int Height;
    bool Crater;
    bool Burn;

public:
    virtual ~SmudgeTypeClass() JMP_THIS(0x6B53A0);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x6B58D0);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x6B5850);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6B58B0);
   
    RTTIType KindOf() const override JMP_THIS(0x6B6130);
    int SizeOf() const override JMP_THIS(0x6B6140);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6B57F0);
    int GetArrayIndex() const override JMP_THIS(0x6B6150);
   
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6B56D0);
    bool CreateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x6B5550);
    ObjectClass* Create(HouseClass* pOwner) override JMP_THIS(0x6B55C0);
    
    virtual void DrawIt(const Point2D& Point, const RectangleStruct& Rect, int SmudgeData, int Height, const CellStruct& MapCoords) JMP_THIS(0x6B55F0);

    static void __fastcall LoadFromIniList(int idxTheatre) JMP_STD(0x6B5490);

/*
    int8_t Can_Place(Cell* cell, bool ignore_buildings) JMP_THIS(0x6B5F80);
    SmudgeTypeClass* Find_Or_Make() JMP_THIS(0x6B5910);
    int32_t From_Name() JMP_THIS(0x6B5440);
    int32_t Init() JMP_THIS(0x6B5490);
    void Place(Cell* a2) JMP_THIS(0x6B6080);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SmudgeTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    SmudgeTypeClass(const char* pID) noexcept : SmudgeTypeClass(fake_noinit_t{}) JMP_THIS(0x6B5260);
    SmudgeTypeClass(noinit_t) : SmudgeTypeClass(fake_noinit_t{}) JMP_THIS(0x6B5370);
};

static_assert(sizeof(SmudgeTypeClass) == SmudgeTypeClass::ClassSize);