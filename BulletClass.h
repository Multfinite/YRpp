#pragma once

#include "Timer.h"
#include "ObjectClass.h"
#include "BulletTypeClass.h"

class TechnoClass;
class ObjectClass;
class WarheadTypeClass;

struct BulletData
{
	CDTimerClass UnknownTimer;
	CDTimerClass ArmTimer;
	CoordStruct Location;
	int Distance;
};

// the velocities along the axes, or something like that
using BulletVelocity = Vector3D<double>;

/*!
* @brief Projectiles
*/
class NOVTABLE BulletClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7E46E4;
            this->IRTTITypeInfo = 0x7E46C8;
            this->INoticeSink = 0x7E46C0;
            this->INoticeSource = 0x7E46B8;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::Bullet;
    static constexpr uintptr_t AbsVTable = 0x7E46E4;
    static constexpr size_t ClassSize = 0x160;

public:
    static constexpr constant_ptr<DynamicVectorClass<BulletClass*>, 0xA8ED40u> const Array{};
    static constexpr reference<DynamicVectorClass<BulletClass*>, 0x89DE18u> const ScalableBullets{};

public:
    BulletTypeClass* Type;
    TechnoClass* Owner;
    bool IsInaccurate;
    BulletData Data;
    bool Bright;
    DWORD unknown_E4;
    BulletVelocity Velocity;
    DWORD unknown_100;
    bool unknown_104;
    bool CourseLock;
    int CourseLockCounter;
    AbstractClass* Target;
    int Speed;
    int InheritedColor;
    DWORD unknown_118;
    DWORD unknown_11C;
    double unknown_120;
    WarheadTypeClass* WH;
    byte AnimFrame;
    byte AnimRateCounter;
    WeaponTypeClass* WeaponType;
    CoordStruct SourceCoords;
    CoordStruct TargetCoords;
    CellStruct LastMapCoords;
    int DamageMultiplier;
    AnimClass* NextAnim;
    bool SpawnNextAnim;
    int Range;

public:
    virtual ~BulletClass() noexcept JMP_THIS(0x466560);

    ULONG AddRef() override JMP_THIS(0x46AFD0);
    ULONG Release() override JMP_THIS(0x46AFF0);
    
    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x46B560);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x46AE70);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x46AFB0);
    
    void Detach(AbstractClass* target, bool all = true) override JMP_THIS(0x4684E0);
    RTTIType KindOf() const override JMP_THIS(0x46B550);
    int SizeOf() const override JMP_THIS(0x46B540);
    void AI() override JMP_THIS(0x4666E0);
    
    Layer InWhichLayer() const override JMP_THIS(0x468B90);
    ObjectTypeClass* Type() const override JMP_THIS(0x46B5B0);
    CellStruct* OccupiedCells(bool placement) const override JMP_THIS(0x466660);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x468090);
    bool Mark(MarkType mark) override JMP_THIS(0x4666C0);

    virtual BYTE GetAnimFrame() const JMP_THIS(0x468000);
    virtual void SetTarget(AbstractClass* pTarget) JMP_THIS(0x46B5A0);
    virtual bool MoveTo(const CoordStruct& where, const BulletVelocity& velocity) JMP_THIS(0x468670);

    void Construct(BulletTypeClass* pType, AbstractClass* pTarget, TechnoClass* pOwner,
        int damage, WarheadTypeClass* pWarhead, int speed, bool bright) JMP_THIS(0x4664C0);
    void Explode(bool destroy = false) JMP_THIS(0x468D80);
    void Detonate(const CoordStruct& coords) JMP_THIS(0x4690B0);
    void Shrapnel() JMP_THIS(0x46A310);
    static void ApplyRadiationToCell(CellStruct cell, int radius, int amount) JMP_STD(0x46ADE0);
    void LoseTarget() JMP_THIS(0x468430);
    void InitScalable() JMP_THIS(0x46B280);
    void NukeMaker() JMP_THIS(0x46B310);

    bool IsHoming() const { return this->Type->ROT > 0; }
    void SetWeaponType(WeaponTypeClass* weapon) { this->WeaponType = weapon; }
    WeaponTypeClass* GetWeaponType() const { return this->WeaponType; }
    CoordStruct TargetCoord() const { return this->Target ? this->Target->Center() : this->Center(); }

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline BulletClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    BulletClass() noexcept : BulletClass(fake_noinit_t()) JMP_THIS(0x466380);
    BulletClass(noinit_t) noexcept : BulletClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(BulletClass) == BulletClass::ClassSize);