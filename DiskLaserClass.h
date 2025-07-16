#pragma once

#include "AbstractClass.h"

class LaserDrawClass;
class TechnoClass;
class WeaponTypeClass;

/*!
* @brief DiskLasers are the floating disks' purple lasers.
*/
class __declspec(uuid("5230C9A8-846A-47EC-BDA2-7E95445E1D49"))
NOVTABLE DiskLaserClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7E5FB8;
            this->IRTTITypeInfo = 0x7E5F9C;
            this->INoticeSink = 0x7E5F94;
            this->INoticeSource = 0x7E5F8C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::DiskLaser;
    static constexpr uintptr_t AbsVTable = 0x7E5FB8;
    static constexpr size_t ClassSize = 0x40;

public:
    DEFINE_POINTER(DynamicVectorClass<DiskLaserClass*>, Array, 0x8A0208u)
    static constexpr auto Radius = 240;
    DEFINE_ARRAY_REFERENCE(Point2D, [16], DrawCoords, 0x8A0180u)

public:
    TechnoClass* Owner;
    TechnoClass* Target;
    WeaponTypeClass* Weapon;
    DWORD LogicState;
    DWORD drawoffset34;
    DWORD drawoffset38;
    int Damage;

public:
    virtual ~DiskLaserClass() JMP_THIS(0x4A7B00);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x4A7C30);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x4A7B90);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4A7C10);
   
    RTTIType KindOf() const override JMP_THIS(0x4A7C80);
    int SizeOf() const override JMP_THIS(0x4A7C70);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x4A7B80);
    void AI() override JMP_THIS(0x4A7340);

    void Fire(TechnoClass* pOwner, TechnoClass* pTarget, WeaponTypeClass* pWeapon, int nDamage) JMP_THIS(0x4A71A0);
    void PointerGotInvalid(AbstractClass* pInvalid) JMP_THIS(0x4A7900);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline DiskLaserClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) { }
public:
    DiskLaserClass() : DiskLaserClass(fake_noinit_t{}) JMP_THIS(0x4A7A30);
    DiskLaserClass(noinit_t) noexcept : DiskLaserClass(fake_noinit_t{}) JMP_THIS(0x4A7AD0);
};
static_assert(sizeof(DiskLaserClass) == DiskLaserClass::ClassSize);
