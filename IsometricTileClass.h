#pragma once

#include "ObjectClass.h"

class IsometricTileTypeClass;

class __declspec(uuid("5AF2CE7A-0634-11D2-ACA4-006008055BB5"))
NOVTABLE IsometricTileClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EC258;
            this->IRTTITypeInfo = 0x7EC23C;
            this->INoticeSink = 0x7EC234;
            this->INoticeSource = 0x7EC22C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Isotile;
    static constexpr uintptr_t AbsVTable = 0x7EC258;
    static constexpr size_t ClassSize = 0xB0;

public:
    DEFINE_REFERENCE(DynamicVectorClass<IsometricTileClass*>, Array, 0x87F750u)

public:
    IsometricTileTypeClass* Type;

public:
    virtual ~IsometricTileClass() JMP_THIS(0x543880);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x543AB0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x543990);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x5439F0);
    
    RTTIType KindOf() const override JMP_THIS(0x543AA0);
    int SizeOf() const override JMP_THIS(0x543A90);
    
    ObjectTypeClass* ClassOf() const override JMP_THIS(0x543AF0);
    bool Limbo() override JMP_THIS(0x543A40);
    bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x543A10);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x543B00);
    bool Mark(MarkType mark) override JMP_THIS(0x543330);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline IsometricTileClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    IsometricTileClass(int idxType, CellStruct const& location) : IsometricTileClass(fake_noinit_t{}) JMP_THIS(0x543780);
    IsometricTileClass(noinit_t) noexcept : IsometricTileClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(IsometricTileClass) == IsometricTileClass::ClassSize);