#pragma once

#include "ObjectTypeClass.h"

class NOVTABLE ParticleSystemTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F00A8;
            this->IRTTITypeInfo = 0x7F008C;
            this->INoticeSink = 0x7F0084;
            this->INoticeSource = 0x7F007C;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::ParticleSystemType;
    static constexpr uintptr_t AbsVTable = 0;
    static constexpr size_t ClassSize = 0x310;

public:
    ABSTRACTTYPE_ARRAY(ParticleSystemTypeClass, 0xA83D68u);

public:
    int HoldsWhat; // ParticleType array index
    bool Spawns;
    int SpawnFrames;
    float Slowdown;
    int ParticleCap;
    int SpawnRadius;
    float SpawnCutoff;
    float SpawnTranslucencyCutoff;
    BehavesLike BehavesLike;
    int Lifetime;
    Vector3D<float> SpawnDirection;
    double ParticlesPerCoord;
    double SpiralDeltaPerCoord;
    double SpiralRadius;
    double PositionPerturbationCoefficient;
    double MovementPerturbationCoefficient;
    double VelocityPerturbationCoefficient;
    double SpawnSparkPercentage;
    int SparkSpawnFrames;
    int LightSize;
    ColorStruct LaserColor;
    bool Laser;
    bool OneFrameLight;

public:
    virtual ~ParticleSystemTypeClass() noexcept JMP_THIS(0x644250);

    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x6447A0);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x6447E0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x644830);
    
    RTTIType KindOf() const override JMP_THIS(0x644930);
    int SizeOf() const override JMP_THIS(0x644920);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x644700);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6442D0);
    bool InstantiateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x644940);
    ObjectClass* Instantiate(HouseClass* pOwner) override JMP_THIS(0x644950);

    static ParticleSystemTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x644890);

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleSystemTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    ParticleSystemTypeClass(const char* pID) noexcept : ParticleSystemTypeClass(fake_noinit_t{}) JMP_THIS(0x6440A0);
    ParticleSystemTypeClass(noinit_t) noexcept : ParticleSystemTypeClass(fake_noinit_t{}) JMP_THIS(0x644220);
};
static_assert(sizeof(ParticleSystemTypeClass) == ParticleSystemTypeClass::ClassSize);