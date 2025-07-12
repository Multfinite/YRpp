#pragma once

#include "ObjectTypeClass.h"

class __declspec(uuid("5AF2CE7A-0634-11D2-ACA4-006008055BB5"))
NOVTABLE IsometricTileTypeClass : public ObjectTypeClass
{
public:
    using base_type = ObjectTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7ECC48;
            this->IRTTITypeInfo = 0x7ECC2C;
            this->INoticeSink = 0x7ECC24;
            this->INoticeSource = 0x7ECC1C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::IsotileType;
    static constexpr uintptr_t AbsVTable = 0x7ECC48;
    static constexpr size_t ClassSize = 0x30C;

public:
    static constexpr constant_ptr<DynamicVectorClass<IsometricTileTypeClass*>, 0xA8ED28u> const Array{};

public:
	int ArrayIndex;
	int MarbleMadnessTile;
	int NonMarbleMadnessTile;
	DWORD unk_2A0;
	DynamicVectorClass<Color16Struct*> unk_2A4;
	DWORD unk_2BC;
	int ToSnowTheater;
	int ToTemperateTheater;
	int TileAnimIndex; //Tile%02dAnim, actually an AnimTypeClass array index...
	int TileXOffset; //Tile%02dXOffset
	int TileYOffset; //Tile%02dYOffset
	int TileAttachesTo; //Tile%02dAttachesTo, iso tile index?
	int TileZAdjust; //Tile%02dZAdjust
	DWORD unk_2DC; //0xBF
	bool Morphable;
	bool ShadowCaster;
	bool AllowToPlace; //default true
	bool RequiredByRMG;
	DWORD unk_2E4;
	DWORD unk_2E8;
	DWORD unk_2EC;
	int unk_2F0; //default 1, no idea
	bool unk_2F4; //like always true
	char FileName[0xE]; // WARNING! Westwood strncpy's 0xE bytes into this buffer without NULL terminating it.
	bool AllowBurrowing;
	bool AllowTiberium;
	DWORD unk_308;

public:
    virtual ~IsometricTileTypeClass() JMP_THIS(0x544A70);

    HRESULT GetClassID(CLSID* pClassID) override JMP_STD(0x549D90);
   
    HRESULT Load(IStream* pStm) override JMP_STD(0x549C80);
    HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x549D70);
   
    void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x549DD0);
    RTTIType KindOf() const override JMP_THIS(0x54A140);
    int SizeOf() const override JMP_THIS(0x54A150);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x549B70);
    int ArrayIndex() const override JMP_THIS(0x54A160);
   
    CoordStruct FixupCoord(CoordStruct& coord) const override JMP_THIS(0x549B50);
    bool CreateAt(CellStruct& position, HouseClass* pOwner) override JMP_THIS(0x549AA0);
    ObjectClass* Create(HouseClass* pOwner) override JMP_THIS(0x549AE0);
    CellStruct* OccupiedCells(bool includeBib = false) const override JMP_THIS(0x544D30);
    SHPStruct* GetImage() const override JMP_THIS(0x544CB0);

/*
	bool Check_Tile(int32_t tile, bool loadimage) JMP_THIS(0x544C20);
	bool Determine_Offsets(int8_t tile, uint32_t* xoffset, uint32_t* yoffset) JMP_THIS(0x547150);
	void Draw_Shadow_Cast(int32_t a2, int32_t a1, int32_t a5, int32_t argC, int32_t a6, int32_t a7, int32_t a8, int32_t a9, int32_t a10) JMP_THIS(0x547230);
	void Draw_Tile(LightConvertClass* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9, int32_t a10, int32_t a11, int32_t a12, int8_t a13, int32_t a14, int8_t a15, int8_t a16, int8_t a17, int32_t a18) JMP_THIS(0x547CF0);
	IsometricTileTypeClass* fetch_tile_from_ptr(int32_t modval) JMP_THIS(0x544E00);
	int8_t Fetch_Tile_To_Buffer(int32_t sizemod, char** data, int32_t size1, int32_t size2) JMP_THIS(0x549830);
	int32_t From_Name() JMP_THIS(0x544CE0);
	RadarImageStruct* Get_Radar_ImageData(uint8_t tile, int8_t level) JMP_THIS(0x549E50);
	Cell* Get_ShadowCaster_list() JMP_THIS(0x547370);
	int32_t get_tile() JMP_THIS(0x544E30);
	int32_t Get_Y_Offset(int32_t a2) JMP_THIS(0x549A60);
	LightConvertClass* Init_Drawer(int32_t green, int32_t blue) JMP_THIS(0x544E70);
	void Init_Drawers() JMP_THIS(0x545000);
	LandType Land_Type(uint8_t tile) JMP_THIS(0x544BE0);
	bool Load_Tile() JMP_THIS(0x544C80);
	int32_t Load_Tile_0() JMP_THIS(0x547020);
	void Make_Radar_Image() JMP_THIS(0x549E90);
	RampType Ramp_Type(uint8_t tile) JMP_THIS(0x5471B0);
	void Read_INI(int8_t reloadtile) JMP_THIS(0x545150);
*/
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline IsometricTileTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    IsometricTileTypeClass(int ArrayIndex, int Minus65, int Zero1,
        const char* pName, int Zero2) noexcept : IsometricTileTypeClass(fake_noinit_t{}) JMP_THIS(0x5447C0);
	IsometricTileTypeClass(noinit_t) noexcept : IsometricTileTypeClass(fake_noinit_t{}) JMP_THIS(0x544A00);
};
static_assert(sizeof(IsometricTileTypeClass) == IsometricTileTypeClass::ClassSize);
