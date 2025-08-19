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
	using base_type = AbstractTypeClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7EF2D8;
			this->IRTTITypeInfo = 0x7EF2BC;
			this->INoticeSink = 0xEF2B4;
			this->INoticeSource = 0x7EF2AC;
		}
	};
	static inline vtables_t vtables{};
public:
	static constexpr uintptr_t AbsVTable = 0x7EF2D8;

	DEFINE_REFERENCE(DynamicVectorClass<ObjectTypeClass*>, Array, 0xAC1418u)
public:
	ColorStruct RadialColor;
	BYTE          unused_9B;
	Armor         Armor;
	int           Strength;
	SHPStruct*    Image;
	bool          ImageAllocated;
	PROTECTED_PROPERTY(BYTE, align_A9[3]);
	SHPStruct*    AlphaImage;
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

	bool           AlternateArcticArt;
	bool           ArcticArtInUse; //not read from ini

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
	virtual ~ObjectTypeClass() JMP_THIS(0x5F7400);
	
	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x5F9720);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x5F9950);
	HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) override JMP_STD(0x5F9970);

	bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x5F92D0);

	/*!
	* @brief
	* @note original_name Coord_Fixup
	* @note vtable_index 27:0x6C
	* @note address 0x41CF80
	*/
	virtual Coordinate* __FixupCoord(Coordinate& retstr, Coordinate& coord) const JMP_THIS(0x41CF80);
	__forceinline Coordinate FixupCoord(Coordinate& coord) const
	{
		Coordinate ret;
		__FixupCoord(ret, coord);
		return ret;
	}

	/*!
	* @brief
	* @note original_name Get_Ownable
	* @note vtable_index 28:0x70
	* @note address 0x428E40
	*/
	virtual DWORD GetOwners() const JMP_THIS(0x428E40);

	/*!
	* @brief
	* @note original_name Max_Pips
	* @note vtable_index 29:0x74
	* @note address 0x5F75B0
	*/
	virtual int GetPipMax() const JMP_THIS(0x5F75B0);

	/*!
	* @brief
	* @note original_name Pixel_Dimensions
	* @note vtable_index 30:0x78
	* @note address 0x5F75C0
	*/
	virtual Point3D* __PixelDimensions(Point3D& retstr) const JMP_THIS(0x5F75C0);
	__forceinline Point3D PixelDimensions() const
	{
		Point3D ret;
		__PixelDimensions(ret);
		return ret;
	}

	/*!
	* @brief
	* @note original_name Lepton_Dimensions
	* @note vtable_index 31:0x7C
	* @note address 0x5F75E0
	*/
	virtual Point3D* __LeptonDimensions(Point3D& retstr) const JMP_THIS(0x5F75E0);
	__forceinline Point3D LeptonDimensions() const
	{
		Point3D ret;
		__LeptonDimensions(ret);
		return ret;
	}

	/*!
	* @brief
	* @note original_name Create_And_Place
	* @note vtable_index 32:0x80
	* @note address 0x4C9150
	*/
	virtual bool SpawnAtMapCoords(CellStruct& position, HouseClass* pOwner) = 0;

	/*!
	* @brief
	* @note original_name Cost_Of
	* @note vtable_index 33:0x84
	* @note address 0x5F7610
	*/
	virtual int GetActualCost(HouseClass* pHouse) const JMP_THIS(0x5F7610);

	/*!
	* @brief
	* @note original_name Time_To_Build
	* @note vtable_index 34:0x88
	* @note address 0x5F7620
	*/
	virtual int GetBuildSpeed() const JMP_THIS(0x5F7620);

	/*!
	* @brief
	* @note original_name Create_One_Of
	* @note vtable_index 35:0x8C
	* @note address 0x4C9150
	*/
	virtual ObjectClass* CreateObject(HouseClass* pOwner) = 0;

	/*!
	* @brief list of occypied cells. Foundation for buildings. placement was called includeBib
	* @note original_name Occupy_List
	* @note vtable_index 36:0x90
	* @note address 0x5F7640
	*/
	virtual CellStruct* GetFoundationData(bool placement) const JMP_THIS(0x5F7640);

	/*!
	* @brief
	* @note original_name Who_Can_Build_Me
	* @note vtable_index 37:0x94
	* @note address 0x5F7900
	*/
	virtual BuildingClass* FindFactory(bool allowOccupied, bool requirePower, bool requireCanBuild, HouseClass const* pHouse) const JMP_THIS(0x5F7900);

	/*!
	* @brief
	* @note original_name Get_Cameo_Data
	* @note vtable_index 38:0x98
	* @note address 0x5F7630
	*/
	virtual SHPStruct* GetCameo() const JMP_THIS(0x5F7630);

	/*!
	* @brief
	* @note original_name Get_Image_Data
	* @note vtable_index 39:0x9C
	* @note address 0x41CFA0
	*/
	virtual SHPStruct* GetImage() const JMP_THIS(0x41CFA0);

	/*! @brief Return BuildCat for Buildings of BuildingTypes, otherwise - false*/
	static bool __fastcall GetBuildCategoryForStructures(RTTIType type, int index) JMP_STD(0x5004E0);
	static TechnoTypeClass* __fastcall GetTechnoType(RTTIType type, int idx) JMP_STD(0x48DCD0);
	/*! @brief strcmpi used */
	static ObjectTypeClass* FindByName(const char* name) JMP_THIS(0x5F9990);

	static void __fastcall DestroyAuxShapes() JMP_STD(0x5F77F0);
	static void __fastcall DestroyVoxelCaches() JMP_THIS(0x5F99E0);
	/*! @brief Executes one time per session for doing some static work. Usually it loads some static graphics. */
	static void __fastcall OneTime() JMP_THIS(0x5F76B0);

	void DestroyChargerTurretVoxels() JMP_THIS(0x5F8080);

	bool LoadChargerBarrelVoxel(char const* graphicName, int32_t turretIndex) JMP_THIS(0x5F7DB0);
	bool LoadChargerTurretVoxel(char const* graphicName, int32_t turretIndex) JMP_THIS(0x5F7A90);
	void LoadGraphics() JMP_THIS(0x5F9070);
	void LoadTurret() JMP_THIS(0x5F8CE0);
	void LoadVoxel() JMP_THIS(0x5F8110);

	static void SetGenericTheaterLetter() JMP_THIS(0x5F9710);
	static void SetTheaterLetter(TheaterType theater) JMP_THIS(0x5F96B0);
protected:
	explicit __forceinline ObjectTypeClass(fake_noinit_t) noexcept : AbstractTypeClass(fake_noinit_t{})
		, RadialColor{}, Armor{}, MainVoxel{}, TurretVoxel{}, BarrelVoxel{}, LineTrailColor{}
		, VoxelMainCache{}, VoxelTurretWeaponCache{}, VoxelShadowCache{}, VoxelTurretBarrelCache{}
	{ }

	ObjectTypeClass(noinit_t) noexcept : ObjectTypeClass(fake_noinit_t{}) JMP_THIS(0x5F7320);
	ObjectTypeClass(const char* pId) : ObjectTypeClass(fake_noinit_t{}) JMP_THIS(0x5F7090);
};
