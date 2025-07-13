#pragma once

#include "ObjectClass.h"
#include "ParticleSystemTypeClass.h"
#include "ParticleClass.h"

class __declspec(uuid("0E272DC8-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE ParticleSystemClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EFB9C;
            this->IRTTITypeInfo = 0x7EFB80;
            this->INoticeSink = 0x7EFB78;
            this->INoticeSource = 0x7EFB70;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::ParticleSystem;
    static constexpr uintptr_t AbsVTable = 0x7EFB9C;
    static constexpr size_t ClassSize = 0x100;

public:
    static constexpr constant_ptr<DynamicVectorClass<ParticleSystemClass*>, 0xA80208u> const Array{};

public:
    ParticleSystemTypeClass* Type;
    CoordStruct SpawnDistanceToOwner;
    DECLARE_PROPERTY(DynamicVectorClass<ParticleClass*>, Particles);
    CoordStruct TargetCoords;
    ObjectClass* Owner;
    /*! @brief CellClass or TechnoClass */
	AbstractClass* Target;
	int SpawnFrames; //from ParSysTypeClass
	int Lifetime; //from ParSysTypeClass
	int SparkSpawnFrames; //from ParSysTypeClass
	int SpotlightRadius; //defaults to 29
    bool TimeToDie;
    bool unknown_bool_F9;
    HouseClass* OwnerHouse;

public:
    virtual ~ParticleSystemClass() JMP_THIS(0x62E070);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6301A0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x62FF20);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x630090);
    
    void InvalidatePointer(AbstractClass* target, bool all = true) override JMP_THIS(0x62FE90);
    RTTIType KindOf() const override JMP_THIS(0x630210);
    int SizeOf() const override JMP_THIS(0x630200);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x630100);
    bool IsInactive() const override JMP_THIS(0x62FE60);
    void AI() override JMP_THIS(0x62FD60);
    
    Layer InWhichLayer() const override JMP_THIS(0x62FE80);
    ObjectTypeClass* ClassOf() const override JMP_THIS(0x630220);
    void UnInit() override JMP_THIS(0x6301E0);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x62E280);

/*
    ParticleClass* addtovector(ParticleTypeClass*, Coordinate*) JMP_THIS(0x62E430);
    ParticleClass* addtovector_0(Coordinate*, Coordinate*, int32_t arg8) JMP_THIS(0x62E4C0);
    int8_t Fire_AI() JMP_THIS(0x62F9A0);
    void Gas_AI() JMP_THIS(0x62E6D0);
    int8_t Railgun_AI() JMP_THIS(0x62F230);
    int8_t removefromvector(int32_t a2) JMP_THIS(0x62E5D0);
    void removefromvector_0() JMP_THIS(0x62E650);
    void set_lifetime(int32_t a2) JMP_THIS(0x6301F0);
    void Smoke_AI() JMP_THIS(0x62ED40);
    int8_t Spark_AI() JMP_THIS(0x62E840);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleSystemClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    ParticleSystemClass(ParticleSystemTypeClass* pParticleSystemType, const CoordStruct& coords,
        AbstractClass* pTarget, ObjectClass* pOwner, const CoordStruct& targetCoords,
        HouseClass* pOwnerHouse) : ParticleSystemClass(fake_noinit_t{}) JMP_THIS(0x62DC50);
    ParticleSystemClass() : ParticleSystemClass(fake_noinit_t{}) JMP_THIS(0x62DC50);
    ParticleSystemClass(noinit_t)  noexcept : ParticleSystemClass(fake_noinit_t{}) { vtables.init(this); }
};
static_assert(sizeof(ParticleSystemClass) == ParticleSystemClass::ClassSize);