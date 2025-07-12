#pragma once

#include "ObjectClass.h"
#include "SmudgeTypeClass.h"

class NOVTABLE SmudgeClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F32FC;
            this->IRTTITypeInfo = 0x7F32F4;
            this->INoticeSink = 0x7F32D8;
            this->INoticeSource = 0x7F32D0;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::Smudge;
    static constexpr uintptr_t AbsVTable = 0x7F32FC;
    static constexpr size_t ClassSize = 0xB0;

public:
    static constexpr constant_ptr<DynamicVectorClass<SmudgeClass*>, 0xA8B1E0u> const Array{};

public:
    SmudgeTypeClass* Type;

public:
    virtual ~SmudgeClass() noexcept JMP_THIS(0x6B4B40);
   
    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x6B4F50);
   
    HRESULT Load(IStream* pStm) override JMP_THIS(0x6B4EA0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x6B4F00);
    
    RTTIType KindOf() const override JMP_THIS(0x6B4F40);
    int SizeOf() const override JMP_THIS(0x6B4F30);
    ObjectTypeClass* Type() const override JMP_THIS(0x6B4F20);
    
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x6B4F90);
    bool Mark(MarkType value) override JMP_THIS(0x6B4BE0);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SmudgeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    SmudgeClass(SmudgeTypeClass const* pType, Coordinate const& pos, int houseId) noexcept : SmudgeClass(fake_noinit_t()) JMP_THIS(0x6B4A50);
    SmudgeClass(noinit_t) noexcept : SmudgeClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(SmudgeClass) == SmudgeClass::ClassSize);