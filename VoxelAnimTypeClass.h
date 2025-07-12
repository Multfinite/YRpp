#pragma once

#include "ObjectTypeClass.h"

class AnimTypeClass;
class ParticleSystemTypeClass;
class WarheadTypeClass;

/*!
* @brief VoxelAnimTypes are initialized by INI files.
*/
class __declspec(uuid("2EBB6D66-0D4D-11D2-8172-006008055BB5"))
NOVTABLE VoxelAnimTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F6548;
            this->IRTTITypeInfo = 0x7F652C;
            this->INoticeSink = 0x7F6524;
            this->INoticeSource = 0x7F651C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::VoxelAnimType;
    static constexpr uintptr_t AbsVTable = 0x7F6548;
    static constexpr size_t ClassSize = 0x308;

public:
    ABSTRACTTYPE_ARRAY(VoxelAnimTypeClass, 0xA8EB28u);

public:
    bool Normalized;
    bool Translucent;
    bool SourceShared;
    PROTECTED_PROPERTY(BYTE, unused_297);
    int VoxelIndex;
    int Duration;
    double Elasticity;
    double MinAngularVelocity;
    double MaxAngularVelocity;
    double MinZVel;
    double MaxZVel;
    double MaxXYVel;
    bool IsMeteor;
    PROTECTED_PROPERTY(BYTE, unused_2D1[3]);
    VoxelAnimTypeClass* Spawns;
    int SpawnCount;
    int StartSound;
    int StopSound;
    AnimTypeClass* BounceAnim;
    AnimTypeClass* ExpireAnim;
    AnimTypeClass* TrailerAnim;
    int Damage;
    int DamageRadius;
    WarheadTypeClass* Warhead;
    ParticleSystemTypeClass* AttachedSystem;
    bool IsTiberium;
    PROTECTED_PROPERTY(BYTE, unused_301[3]);

public:
    virtual ~VoxelAnimTypeClass() JMP_THIS(0x74AF70);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x74B7D0);
    
    HRESULT Load(IStream* pStm) override JMP_STD(0x74B810);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x74B8D0);
    
    void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x74B8F0);
    RTTIType KindOf() const override JMP_THIS(0x74B9F0);
    int SizeOf() const override JMP_THIS(0x74BA00);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x74B690);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x74B050);
    bool CreateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x74BA10);
    ObjectClass* Create(HouseClass* pOwner) override JMP_THIS(0x74BA20);

/*
    VoxelAnimTypeClass * Find_Or_Make() JMP_THIS(0x74B960);
    VoxelAnimTypeClass * Find_Or_Make_0(DynamicVectorClass * a2) JMP_THIS(0x74BB20);
    int32_t From_Name() JMP_THIS(0x74B640);
    int8_t * Get_Name() JMP_THIS(0x74B620);
*/
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline VoxelAnimTypeClass(fake_noinit_t) noexcept
        : ObjectTypeClass(fake_noinit_t{})
    {}

public:
    VoxelAnimTypeClass(const char* pID) : VoxelAnimTypeClass(fake_noinit_t{}) JMP_THIS(0x74AD80);
    VoxelAnimTypeClass() : VoxelAnimTypeClass(fake_noinit_t{}) JMP_THIS(0x74AF70);
};
static_assert(sizeof(VoxelAnimTypeClass) == VoxelAnimTypeClass::ClassSize);