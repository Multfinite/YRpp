#pragma once

#include "AbstractTypeClass.h"

class AnimTypeClass;
class BulletTypeClass;
class ParticleSystemTypeClass;
class WarheadTypeClass;

class __declspec(uuid("0CF2BCE7-36E4-11D2-B8D8-006008C809ED"))
NOVTABLE WeaponTypeClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F73B8;
            this->IRTTITypeInfo = 0x7F739C;
            this->INoticeSink = 0x7F7394;
            this->INoticeSource = 0x7F738C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::WeaponType;
    static constexpr uintptr_t AbsVTable = 0x7F73B8;
    static constexpr size_t ClassSize = 0x160;

public:
    ABSTRACTTYPE_ARRAY(WeaponTypeClass, 0x887568u);

public:
    int AmbientDamage;
    int Burst;
    BulletTypeClass* Projectile;
    int Damage;
    int Speed;
    WarheadTypeClass* Warhead;
    int ROF;
    int Range;
    int MinimumRange;
    DECLARE_PROPERTY(TypeList<int>, Report);
    DECLARE_PROPERTY(TypeList<int>, DownReport);
    DECLARE_PROPERTY(TypeList<AnimTypeClass*>, Anim);
    AnimTypeClass* OccupantAnim;
    AnimTypeClass* AssaultAnim;
    AnimTypeClass* OpenToppedAnim;
    ParticleSystemTypeClass* AttachedParticleSystem;
    ColorStruct LaserInnerColor;
    ColorStruct LaserOuterColor;
    ColorStruct LaserOuterSpread;
    bool UseFireParticles;
    bool UseSparkParticles;
    bool OmniFire;
    bool DistributedWeaponFire;
    bool IsRailgun;
    bool Lobber;
    bool Bright;
    bool IsSonic;
    bool Spawner;
    bool LimboLaunch;
    bool DecloakToFire;
    bool CellRangefinding;
    bool FireOnce;
    bool NeverUse;
    bool RevealOnFire;
    bool TerrainFire;
    bool SabotageCursor;
    bool MigAttackCursor;
    bool DisguiseFireOnly;
    int DisguiseFakeBlinkTime;
    bool InfiniteMindControl;
    bool FireWhileMoving;
    bool DrainWeapon;
    bool FireInTransport;
    bool Suicide;
    bool TurboBoost;
    bool Supress;
    bool Camera;
    bool Charges;
    bool IsLaser;
    bool DiskLaser;
    bool IsLine;
    bool IsBigLaser;
    bool IsHouseColor;
    char LaserDuration;
    bool IonSensitive;
    bool AreaFire;
    bool IsElectricBolt;
    bool DrawBoltAsLaser;
    bool IsAlternateColor;
    bool IsRadBeam;
    bool IsRadEruption;
    int RadLevel;
    bool IsMagBeam;

public:
    virtual ~WeaponTypeClass() JMP_THIS(0x771F50);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x772C90);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x772CD0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x772EB0);
    
    RTTIType KindOf() const override JMP_THIS(0x7730E0);
    int SizeOf() const override JMP_THIS(0x7730D0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x772AE0);
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x772080);

    void CalculateSpeed() JMP_THIS(0x7729F0);
    ThreatType AllowedThreats() JMP_THIS(0x772A90);

    static WeaponTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x772FA0);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline WeaponTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    WeaponTypeClass(const char* pID = nullptr) noexcept : WeaponTypeClass(fake_noinit_t{}) JMP_THIS(0x771C70);
    WeaponTypeClass(noinit_t) noexcept : WeaponTypeClass(fake_noinit_t{}) JMP_THIS(0x771F00);
};

static_assert(sizeof(WeaponTypeClass) == WeaponTypeClass::ClassSize);