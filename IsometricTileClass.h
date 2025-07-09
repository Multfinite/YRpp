#pragma once

#include "ObjectClass.h"

class IsometricTileTypeClass;

class NOVTABLE IsometricTileClass : public ObjectClass
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

    static const AbstractType AbsID = AbstractType::Isotile;
    static constexpr uintptr_t AbsVTable = 0x7EC258;
    static constexpr size_t ClassSize = 0xB0;

public:
    static constexpr constant_ptr<DynamicVectorClass<IsometricTileClass*>, 0x87F750u> const Array{};

public:
    IsometricTileTypeClass* Type;

public:
    virtual ~IsometricTileClass() noexcept JMP_THIS(0x543880);

    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x543AB0);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x543990);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x5439F0);
    
    RTTIType KindOf() const override JMP_THIS(0x543AA0);
    int SizeOf() const override JMP_THIS(0x543A90);
    
    ObjectTypeClass* Type() const override JMP_THIS(0x543AF0);
    bool Limbo() override JMP_THIS(0x543A40);
    bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x543A10);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x543B00);
    bool Mark(MarkType mark) override JMP_THIS(0x543330);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline IsometricTileClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    IsometricTileClass(int idxType, CellStruct const& location) noexcept : IsometricTileClass(fake_noinit_t()) JMP_THIS(0x543780);
    IsometricTileClass(noinit_t) noexcept : IsometricTileClass(fake_noinit_t()) { vtables.init(this); }
};
static_assert(sizeof(IsometricTileClass) == IsometricTileClass::ClassSize);