#pragma once

#include "AbstractClass.h"
#include "ObjectTypeClass.h"
#include "TerrainClass.h"

class __declspec(uuid("1C470B0E-69D7-11D2-B8F2-006008C809ED"))
NOVTABLE FoggedObjectClass : public AbstractClass
{
public:
    using base_type = AbstractClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E8B38;
            this->IRTTITypeInfo = 0x7E8B1C;
            this->INoticeSink = 0x7E8B14;
            this->INoticeSource = 0x7E8B0C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::FoggedObject;
    static constexpr uintptr_t AbsVTable = 0x7E8B38;
    static constexpr size_t ClassSize = 0x78;
public:
    struct DrawRecord
    {
        ObjectTypeClass* TypeClass;
        int Frame;
        int HeightAdjust;
        int ZAdjust;
    };

    OverlayType Overlay;
    HouseClass* Owner;
    int OverlayData;
    RTTIType RTTI;
    Coordinate Coord;
    RectangleStruct BoundingRect;
    int CellLevel;
    SmudgeType Smudge;
    int SmudgeData;
    DynamicVectorClass<DrawRecord*> Records;
    bool ToDraw;
public:
    virtual ~FoggedObjectClass() JMP_THIS(0x4D1650);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x4D27D0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4D2510);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4D24A0);
    
    RTTIType WhatAmI() const override JMP_THIS(0x4D27B0);
    int Size() const override JMP_THIS(0x4D27C0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x4D2810);

    virtual ::Cell Get_Cell() const JMP_THIS(0x4D28D0);
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline FoggedObjectClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}
public:
    FoggedObjectClass() noexcept : FoggedObjectClass(fake_noinit_t{}) JMP_THIS(0x4D08B0);
    FoggedObjectClass(Coordinate& coord, OverlayType overlay, int overlayData) noexcept : FoggedObjectClass(fake_noinit_t{}) JMP_THIS(0x4D0980);
    FoggedObjectClass(Coordinate& coord, SmudgeType smudge, int smudgeData) noexcept : FoggedObjectClass(fake_noinit_t{}) JMP_THIS(0x4D0C40);
    FoggedObjectClass(BuildingClass const* building, bool toDraw = false) noexcept : FoggedObjectClass(fake_noinit_t{}) JMP_THIS(0x4D0EF0);
    FoggedObjectClass(TerrainClass const* terrain) noexcept : FoggedObjectClass(fake_noinit_t{}) JMP_THIS(0x4D1370);
    FoggedObjectClass(noinit_t noinit) noexcept : FoggedObjectClass(fake_noinit_t{}) JMP_THIS(0x4D0860);
};
static_assert(sizeof(FoggedObjectClass) == FoggedObjectClass::ClassSize);
