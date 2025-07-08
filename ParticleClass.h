#pragma once

#include "ObjectClass.h"
#include "ParticleTypeClass.h"

class ParticleSystemClass;

class NOVTABLE ParticleClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7EF954;
            this->IRTTITypeInfo = 0x7EF938;
            this->INoticeSink = 0x7EF930;
            this->INoticeSource = 0x7EF928;
        }
    };
    static inline vtables_t vtables{};

    static const AbstractType AbsID = AbstractType::Particle;
    static constexpr uintptr_t AbsVTable = 0x7EF954;
    static constexpr size_t ClassSize = 0x138;

public:
    static constexpr constant_ptr<DynamicVectorClass<ParticleClass*>, 0xA83DC8u> const Array{};

public:
    ParticleTypeClass* Type;
    RGBClass unknown_color_B0;
    DWORD RefCount;
    DWORD unknown_B8;
    DWORD unknown_BC;
    Coordinate Velocity;
    DWORD unknown_CC;
    double unknown_double_D0;
    DWORD unknown_D8;
    DWORD unknown_DC;
    DWORD unknown_E0;
    float Speed;
    Coordinate unknown_coords_E8;
    Coordinate unknown_coords_F4;
    Coordinate unknown_coords_100;
    Vector3D<float> unknown_vector3d_10C;
    Vector3D<float> unknown_vector3d_118;
    ParticleSystemClass* ParticleSystem;
    WORD RemainingEC;
    WORD RemainingDC;
    BYTE StateAIAdvance; // bool ?
    BYTE unknown_12D;
    BYTE StartStateAI; // bool ?
    BYTE Translucency;
    BYTE unknown_130;
    BYTE HasRemaining; // bool?
    PROTECTED_PROPERTY(DWORD, unused_134);

/*
    ParticleTypeClass* Type;
    RGBClass byteB0;
    uint64_t RefCount;
    double doubleB8;
    Coordinate Gas_AI_C0;
    float floatCC;
    float floatD0;
    float floatD4;
    uint64_t dwordD8;
    uint64_t dwordDC;
    uint64_t dwordE0;
    float Velocity;
    Coordinate gapE8;
    Coordinate dwordF4;
    Coordinate dword100;
    Vector3D vector3_10C;
    float float118;
    float float11C;
    float float120;
    ParticleSystemClass* ParticleSystem;
    int16_t RemainingEC;
    int16_t RemainingDC;
    uint8_t StateAIAdvance;
    uint8_t byte12D;
    uint8_t StartStateAI;
    uint8_t Translucency;
    uint8_t byte130;
    uint8_t hasremaining;
    int8_t field_132;
    int8_t field_133;
    int8_t field_134;
    int8_t field_135;
    int8_t field_136;
    int8_t field_137;
*/

public:
    virtual ~ParticleClass() noexcept JMP_THIS(0x62BCC0);

    HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x62D930);
    
    HRESULT Load(IStream* pStm) override JMP_THIS(0x62D7A0);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x62D810);
   
    RTTIType KindOf() const override JMP_THIS(0x62D980);
    int SizeOf() const override JMP_THIS(0x62D970);
   
    Layer InWhichLayer() const override JMP_THIS(0x62D770);
    ObjectTypeClass* Type() const override JMP_THIS(0x62D990);
    CellStruct* OccupiedCells(bool includeBib = false) const override JMP_THIS(0x62D710);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x62CEC0);
    bool Mark(MarkType mark) override JMP_THIS(0x62D6F0);
    
    virtual int ShapeNumber() const JMP_THIS(0x62D830);

/*
    void AI() JMP_THIS(0x62CE40);
    void Coord_AI() JMP_THIS(0x62D5E0);
    void Fire_AI() JMP_THIS(0x62CB10);
    int32_t Fire_Wind() JMP_THIS(0x62D510);
    int8_t Gas_AI() JMP_THIS(0x62BD50);
    void Gas_Wind() JMP_THIS(0x62D3F0);
    void ParticleClass() JMP_THIS(0x62BCC0);
    void Railgun_AI() JMP_THIS(0x62C3A0);
    void Smoke_AI() JMP_THIS(0x62C540);
    int32_t Smoke_Coord_AI() JMP_THIS(0x62D2A0);
    void Spark_AI() JMP_THIS(0x62C6E0);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ParticleClass(fake_noinit_t) noexcept : base_type(fake_noinit_t()) {}

public:
    ParticleClass(ParticleTypeClass* pParticleType, Coordinate* pCrd1,
        Coordinate* pCrd2, ParticleSystemClass* pParticleSystem) noexcept
        : ParticleClass(fake_noinit_t()) JMP_THIS(0x62B5E0);
    ParticleClass() noexcept : ParticleClass(fake_noinit_t()) JMP_THIS(0x62BB20);
    ParticleClass(noinit_t) noexcept : ParticleClass(fake_noinit_t{}) { vtables.init(this); }
};

static_assert(sizeof(ParticleClass) == ParticleClass::ClassSize);