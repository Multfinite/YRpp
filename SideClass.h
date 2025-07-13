#pragma once

#include "AbstractTypeClass.h"

class __declspec(uuid("C53DD372-151E-11D2-8175-006008055BB5"))
NOVTABLE SideClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F2EC0;
            this->IRTTITypeInfo = 0x7F2EA4;
            this->INoticeSink = 0x7F2E9C;
            this->INoticeSource = 0x7F2E94;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Side;
    static constexpr uintptr_t AbsVTable = 0x7F2EC0;
    static constexpr size_t ClassSize = 0xB4;

public:
    ABSTRACTTYPE_ARRAY(SideClass, 0x8B4120u);

public:
    /*! @brief Indexes */
    TypeList<int> HouseTypes;

public:
    virtual ~SideClass() JMP_THIS(0x6A4610);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6A4740);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x6A4780);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x6A48A0);
    
    RTTIType KindOf() const override JMP_THIS(0x6A4920);
    int SizeOf() const override JMP_THIS(0x6A4910);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6A4710);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline SideClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    SideClass(const char* pID) : SideClass(fake_noinit_t{}) JMP_THIS(0x6A4550);
    SideClass(noinit_t) noexcept : SideClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(SideClass) == SideClass::ClassSize);