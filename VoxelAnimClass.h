#pragma once

#include "ObjectClass.h"
#include "VoxelAnimTypeClass.h"
#include "BounceClass.h"

class HouseClass;
class ParticleSystemClass;

/*!
* @brief Voxel Animations
*/
class __declspec(uuid("0E272DC1-9C0F-11D1-B709-00A024DDAFD1"))
NOVTABLE VoxelAnimClass : public ObjectClass
{
public:
    using base_type = ObjectClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F6318;
            this->IRTTITypeInfo = 0x7F62FC;
            this->INoticeSink = 0x7F62F4;
            this->INoticeSource = 0x7F62EC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::VoxelAnim;
    static constexpr uintptr_t AbsVTable = 0x7F6318;
    static constexpr size_t ClassSize = 0x148;

public:
    static constexpr constant_ptr<DynamicVectorClass<VoxelAnimClass*>, 0x887388u> const Array{};

public:
    PROTECTED_PROPERTY(DWORD, unused_AC);
    DECLARE_PROPERTY(BounceClass, Bounce);
    int unknown_int_100;
    VoxelAnimTypeClass* Type;
    ParticleSystemClass* AttachedSystem;
    HouseClass* OwnerHouse;
    bool TimeToDie;
    PROTECTED_PROPERTY(BYTE, unused_111[3]);
    DECLARE_PROPERTY(AudioController, Audio3);
    DECLARE_PROPERTY(AudioController, Audio4);
    bool Invisible;
    PROTECTED_PROPERTY(BYTE, unused_13D[3]);
    int Duration;
    PROTECTED_PROPERTY(DWORD, unused_144);

public:
    virtual ~VoxelAnimClass() JMP_THIS(0x7499F0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x74AAD0);
    
    HRESULT __stdcall Load(IStream* pStm) JMP_STD JMP_THIS(0x74A970);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) JMP_STD JMP_THIS(0x74AA10);
   
    RTTIType KindOf() const override JMP_THIS(0x74AB20);
    int SizeOf() const override JMP_THIS(0x74AB10);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x74AA30);
    
    void AI() override JMP_THIS(0x749F30);
    Layer InWhichLayer() const override JMP_THIS(0x74A960);
    ObjectTypeClass* Type() const override JMP_THIS(0x74AB30);
    bool DrawIfVisible(RectangleStruct* pBounds, bool EvenIfCloaked, DWORD dwUnk3) const override JMP_THIS(0x749B20);
    CellStruct const* OccupiedCells(bool includeBib = false) const override JMP_THIS(0x74AB40);
    void DrawIt(Point2D* location, RectangleStruct* bounds) const override JMP_THIS(0x749B70);

/*
    int32_t Init_Clear() JMP_THIS(0x749F00);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline VoxelAnimClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}

public:
    VoxelAnimClass(VoxelAnimTypeClass* pVoxelAnimType, CoordStruct* pLocation, HouseClass* pOwnerHouse)
        : VoxelAnimClass(fake_noinit_t{})
        JMP_THIS(0x7493B0);
    VoxelAnimClass() : VoxelAnimClass(fake_noinit_t{}) JMP_THIS(0x7498D0);
};
static_assert(sizeof(VoxelAnimClass) == VoxelAnimClass::ClassSize);