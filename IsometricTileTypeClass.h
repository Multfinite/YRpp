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

	//Array
	DEFINE_REFERENCE(DynamicVectorClass<IsometricTileTypeClass*>, Array, 0xA8ED28u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//AbstractClass
	virtual void PointerExpired(AbstractClass* pAbstract, bool removed) RX;
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;
	virtual void ComputeCRC(CRCEngine& crc) const RX;

	virtual int GetArrayIndex() const R0;

	//ObjectTypeClass
	virtual CoordStruct* vt_entry_6C(CoordStruct* pDest, CoordStruct* pSrc) const R0;

	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;

	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;
	virtual void vt_entry_90(DWORD dwUnk) RX;

	virtual SHPStruct* GetImage() const R0;

	//Destructor
	virtual ~IsometricTileTypeClass() RX;

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

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
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline IsometricTileTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    IsometricTileTypeClass(int ArrayIndex, int Minus65, int Zero1,
        const char* pName, int Zero2) noexcept : IsometricTileTypeClass(fake_noinit_t{}) JMP_THIS(0x5447C0);
	IsometricTileTypeClass(noinit_t) noexcept : IsometricTileTypeClass(fake_noinit_t{}) JMP_THIS(0x544A00);
};
static_assert(sizeof(IsometricTileTypeClass) == IsometricTileTypeClass::ClassSize);
