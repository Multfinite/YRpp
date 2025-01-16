#pragma once

#include "AbstractTypeClass.h"
#include "FileSystem.h"

#include "Drawing.h"
#include "IndexClass.h"

//forward declarations
class TechnoTypeClass;
class HouseTypeClass;
class ObjectClass;
class BuildingClass;

/*!
	@brief ObjectType is type of object which can be placed on battle map.
*/
class NOVTABLE ObjectTypeClass : public AbstractTypeClass
{
public:
	static constexpr uintptr_t AbsVTable = 0x7EF2D8;

	static constexpr constant_ptr<DynamicVectorClass<ObjectTypeClass*>, 0xAC1418u> const Array{};
public:
	ColorStruct RadialColor;
	BYTE          unused_9B;
	Armor         Armor;
	int           MaxStrength;
	SHPStruct* Image;
	bool          ImageAllocated;
	PROTECTED_PROPERTY(BYTE, align_A9[3]);
	SHPStruct* AlphaImage;
	VoxelStruct MainVoxel;
	VoxelStruct TurretVoxel; //also used for WO voxels
	VoxelStruct BarrelVoxel;

	VoxelStruct ChargerTurrets[0x12];
	VoxelStruct ChargerBarrels[0x12];

	bool          NoSpawnAlt;
	PROTECTED_PROPERTY(BYTE, align_1E9[3]);
	int           MaxDimension;
	int           CrushSound; //index
	int           AmbientSound; //index

	char ImageFile[0x19];

	bool           HasAlternateArcticArt;
	bool           UseArcticGraphic; //not read from ini

	char AlphaImageFile[0x19];

	bool           Theater;
	bool           Crushable;
	bool           Bombable;
	bool           RadarInvisible;
	bool           Selectable;
	bool           LegalTarget;
	bool           Insignificant;
	bool           Immune;
	bool           IsLogic; // add objects to the logic vector
	bool           AllowCellContent;
	bool           Voxel;
	bool           NewTheater;
	bool           HasRadialIndicator;
	bool           IgnoresFirestorm;
	bool           UseLineTrail;
	ColorStruct    LineTrailColor;
	PROTECTED_PROPERTY(BYTE, align_23E[2]);
	int            LineTrailColorDecrement;

	IndexClass<MainVoxelIndexKey, VoxelCacheStruct*> VoxelMainCache;
	IndexClass<TurretWeaponVoxelIndexKey, VoxelCacheStruct*> VoxelTurretWeaponCache;
	IndexClass<ShadowVoxelIndexKey, VoxelCacheStruct*> VoxelShadowCache;
	IndexClass<TurretBarrelVoxelIndexKey, VoxelCacheStruct*> VoxelTurretBarrelCache;
public:
	HRESULT __stdcall Load(IStream* pStm) override JMP_THIS(0x5F9720);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x5F9950);
	HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) override JMP_THIS(0x5F9970);

	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x5F92D0);

	virtual ~ObjectTypeClass() JMP_THIS(0x5F7400);
	virtual CoordStruct FixupCoord(CoordStruct& coord) const JMP_THIS(0x41CF80);
	virtual DWORD Ownable() const JMP_THIS(0x428E40);
	virtual int MaxPips() const JMP_THIS(0x5F75B0);
	virtual Point3D PixelDimensions() const JMP_THIS(0x5F75C0);
	virtual Point3D LeptonDimensions() const JMP_THIS(0x5F75E0);
	virtual bool InstantiateAt(CellStruct& position, HouseClass* pOwner) = 0;
	virtual int CostOf(HouseClass* pHouse) const JMP_THIS(0x5F7610);
	virtual int TimeToBuild() const JMP_THIS(0x5F7620);
	virtual ObjectClass* Instantiate(HouseClass* pOwner) = 0;
	/*! @brief list of occypied cells. Foundation for buildings. placement was called includeBib */
	virtual CellStruct* OccupiedCells(bool placement) const JMP_THIS(0x5F7640);
	virtual BuildingClass* FindFactory(bool allowOccupied, bool requirePower, bool requireCanBuild, HouseClass const* pHouse) const JMP_THIS(0x5F7900);
	virtual SHPStruct* GetCameo() const JMP_THIS(0x5F7630);
	virtual SHPStruct* GetImage() const JMP_THIS(0x41CFA0);

	/*! @brief Return BuildCat for Buildings of BuildingTypes, otherwise - false*/
	inline static bool __fastcall GetBuildCategoryForStructures(RTTIType type, int index) JMP_STD(0x5004E0);
	inline static TechnoTypeClass* __fastcall GetTechnoType(RTTIType type, int idx) JMP_STD(0x48DCD0);
	/*! @brief strcmpi used */
	inline static ObjectTypeClass* FindByName(const char* name) JMP_THIS(0x5F9990);

	inline static void __fastcall DestroyAuxShapes() JMP_STD(0x5F77F0);
	inline static void __fastcall DestroyVoxelCaches() JMP_THIS(0x5F99E0);
	/*! @brief Executes one time per session for doing some static work. Usually it loads some static graphics. */
	inline static void __fastcall OneTime() JMP_THIS(0x5F76B0);

	inline void DestroyChargerTurretVoxels() JMP_THIS(0x5F8080);

	inline bool LoadChargerBarrelVoxel(char const* graphicName, int32_t turretIndex) JMP_THIS(0x5F7DB0);
	inline bool LoadChargerTurretVoxel(char const* graphicName, int32_t turretIndex) JMP_THIS(0x5F7A90);
	inline void LoadGraphics() JMP_THIS(0x5F9070);
	inline void LoadTurret() JMP_THIS(0x5F8CE0);
	inline void LoadVoxel() JMP_THIS(0x5F8110);

	inline static void SetGenericTheaterLetter() JMP_THIS(0x5F9710);
	inline static void SetTheaterLetter(TheaterType theater) JMP_THIS(0x5F96B0);
protected:
	explicit __forceinline ObjectTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{})
		, RadialColor{}, Armor{}, MainVoxel{}, TurretVoxel{}, BarrelVoxel{}, LineTrailColor{}
		, VoxelMainCache{}, VoxelTurretWeaponCache{}, VoxelShadowCache{}, VoxelTurretBarrelCache{}
	{ }
	ObjectTypeClass(noinit_t) : ObjectTypeClass(fake_noinit_t{}) JMP_THIS(0x5F7320);
	ObjectTypeClass(const char* pId) : ObjectTypeClass(fake_noinit_t{}) JMP_THIS(0x5F7090);
};
