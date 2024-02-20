#pragma once

#include <PriorityQueueClass.h>

enum MoveType
{
	MOVE_OK = 0x0,
	MOVE_CLOAK = 0x1,
	MOVE_MOVING_BLOCK = 0x2,
	MOVE_CLOSED_GATE = 0x3,
	MOVE_FRIENDLY_DESTROYABLE = 0x4,
	MOVE_DESTROYABLE = 0x5,
	MOVE_TEMP = 0x6,
	MOVE_NO = 0x7,
	MOVE_COUNT = 0x8,
};

enum MZoneType : __int32
{
	MZONE_NONE = -1, //18446744073709551615,
	MZONE_NORMAL = 0,
	MZONE_CRUSHER = 1,
	MZONE_DESTROYER = 2,
	MZONE_AMPH_DESTROYER = 3,
	MZONE_AMPH_CRUSHER = 4,
	MZONE_AMPH = 5,
	MZONE_SUBTERRANEAN = 6,
	MZONE_INFANTRY = 7,
	MZONE_INFANTRY_DESTROYER = 8,
	MZONE_FLY = 9,
	MZONE_WATER = 10,
	MZONE_WATERBEACH = 11,
	MZONE_CRUSHER_ALL = 12,
	MZONE_COUNT = 13,
};

enum AStarPostProcessType
{
	ASTAR_PASS_0 = 0x0,
	ASTAR_PASS_1 = 0x1,
	ASTAR_PASS_2 = 0x2,
};

struct CellLevelPassabilityStruct
{
	char CellPassability;
	char CellLevel;
	unsigned short ZoneArrayIndex;
};

struct LevelAndPassabilityStruct2
{
	__int16 word_0[4];
	char CellLevel;
	char field_9;
};

//ZoneConnectionClass - Holding zone connection info from tubes or bridges (probably used for pathfinding)
struct ZoneConnectionClass
{
	CellStruct	FromMapCoords;
	CellStruct	ToMapCoords;
	bool		unknown_bool_08;
	CellClass* Cell;

	//need to define a == operator so it can be used in array classes
	bool operator==(const ZoneConnectionClass& other) const
	{
		return (FromMapCoords == other.FromMapCoords
			&& ToMapCoords == other.ToMapCoords
			&& unknown_bool_08 == other.unknown_bool_08
			&& Cell == other.Cell);
	}
};

struct AStarQueueNodeHierarchical;
struct SubzoneConnectionStruct
{
	//DWORD unknown_dword_0;
	AStarQueueNodeHierarchical* queueBuffer;
	BYTE unknown_byte_4;

	//need to define a == operator so it can be used in array classes
	bool operator==(const SubzoneConnectionStruct& other) const
	{
		return (queueBuffer == other.queueBuffer
			&& unknown_byte_4 == other.unknown_byte_4);
	}
};

struct SubzoneTrackingStruct
{
public:
	DynamicVectorClass<SubzoneConnectionStruct> SubzoneConnections;
	WORD unknown_word_18;
	DWORD unknown_dword_1C;
	DWORD unknown_dword_20;

	//need to define a == operator so it can be used in array classes
	bool operator==(const SubzoneTrackingStruct& other) const
	{
		return (unknown_word_18 != other.unknown_word_18
			&& unknown_dword_1C == other.unknown_dword_1C
			&& unknown_dword_20 == other.unknown_dword_20);
	}
};

struct __declspec(align(4)) AStarQueueNodeHierarchical
{
	int BufferDelta;
	DWORD Index;
	float Score;
	int Number;
};

struct AStarWorkPathStructNode
{
	CellClass** Cells;
	int CellLevel;
	AStarWorkPathStructNode* Prev;
};


struct __declspec(align(8)) AStarWorkPathStruct
{
	AStarWorkPathStructNode* Data;
	float MovementCost;
	float PathCost;
	int PathLength;
};


struct __unaligned __declspec(align(4)) AStarWorkPathStructHeap
{
	AStarWorkPathStruct Nodes[65536];
	unsigned __int32 Count;
};


struct __declspec(align(4)) AStarWorkPathStructDataHeap
{
	AStarWorkPathStructNode Nodes[131072];
	unsigned __int32 Count;
};

struct __declspec(align(4)) PathType
{
	CellStruct Start;
	int Cost;
	int Length;
	FacingType* Command;
	int field_10;
	int* Overlap;
	CellStruct LastOverlap;
	CellStruct LastFixup;
};

inline int __fastcall AStarHelperFacing(CellStruct* a1, CellStruct* a2)
{ JMP_STD(0x42AA40); }
inline CellStruct* __fastcall AStar_FindAdjacentCell0(CellStruct* a1, CellStruct* a2, int a3)
{ JMP_STD(0x42D490); }
inline CellStruct* __fastcall Find_Some_Cell(CellStruct* retstr, CellStruct* cell, int count, int* path)
{ JMP_STD(0x429780); }

class FootClass;
class NOVTABLE __declspec(align(4)) AStarClass
{
public:
	static constexpr reference<AStarClass, 0x87E8B8> const Instance {};
	static constexpr reference<DynamicVectorClass<SubzoneTrackingStruct*>, 0x87F874> const SubzoneTracking {};

	char bool_0;
	bool ScaleMovementCost;
	char bool_2;
	char __DoPostProcess;
	float MovementCostScaler;
	char CheckLocomotor;
	AStarWorkPathStructDataHeap* WorkingNodesBuffer;
	AStarWorkPathStructHeap* WorkingNodes;
	PriorityQueueClass<AStarQueueNodeHierarchical>* OpenNodes;
	int* celllevel_costarray2_alt;
	int* celllevel_costarray1;
	float* MovementCosts;
	float* MovementCostsAlt;
	DWORD initedcount;
	DWORD ObjectSpeed;
	int CurrentCellLevel;
	int DestCellLevel;
	bool boolpathfind_38;
	AStarPostProcessType __Blockage;
	int* ints_40_costs[3];
	int* ints_4C_costs[3];
	float* HierarchicalCosts[3];
	AStarQueueNodeHierarchical* HierarchicalOpenNodesBuffer;
	PriorityQueueClass<AStarQueueNodeHierarchical>* HierarchicalOpenNodes;
	int CellsProcessed;
	CellStruct CurrentCell;
	DynamicVectorClass<DWORD> CellIndexesVector[3];
	unsigned __int16 somearray_BC[1500];
	int counts_for_subzones_field_C74[3];

	double GetMovementCost(
		  CellClass** from, CellClass** to
		, bool useAlt, MoveType move
		, FootClass* object
	)	{ JMP_THIS(0x429830); }
	PathType* FindPathRegular(
		  CellStruct* from, CellStruct* to
		, FootClass* object, FacingType* moves
		, signed int maxLoops, AStarPostProcessType postProcess
	) { JMP_THIS(0x429A90); }
	AStarWorkPathStruct* CreateNode(
		AStarWorkPathStructNode** pathNodes
		, CellClass** a3, CellStruct* a4
		, float movementCost
	) { JMP_THIS(0x42A460); }
	void Cleanup() { JMP_THIS(0x42A5B0); }
	bool IsSameCostCommon(int a2, char a3, int a4) { JMP_THIS(0x42A690); }
	AStarClass() { JMP_THIS(0x42A6D0); }
	~AStarClass() { JMP_THIS(0x42A900); }
	PathType* BuildFinalPathRegular(	AStarWorkPathStruct* workPath, FacingType* moves)
	{ JMP_THIS(0x42AA90); }
	void ReinitCostArrays(RectangleStruct* where) { JMP_THIS(0x42AC00); }
	char PostProcessCells(FootClass* object) { JMP_THIS(0x42ACF0); }
	FootClass* GetOccupierRegular(CellStruct* pos, int level) { JMP_THIS(0x42B080); };
	void ProcessFinalPathRegular(PathType* path, FootClass* object) { JMP_THIS(0x42B210); }
	int FixupFinalPathRegular(int a2, CellStruct a3, int a4, int a5, int a6, int a7)
	{ JMP_THIS(0x42B420); }
	void OptimizeFinalPath(PathType* path, FootClass* object) { JMP_THIS(0x42B7F0); }
	void AdjacentCellRegular(FacingType* moves, int a3, int a4, int a5, CellStruct* cellOut)
	{ JMP_THIS(0x42BCA0); }
	bool PlotStraightLineRegular(
		  FacingType* moves, int arg4
		, CellStruct* a4, CellStruct* a5
		, FootClass* object, int* overlap, int a8)
	{ JMP_THIS(0x42BE20); };
	DWORD* ClearPointers() { JMP_THIS(0x42C1C0); }
	bool FindPathHierarchical(
		  CellStruct* from, CellStruct* to
		, MZoneType zoneType, FootClass* object)
	{ JMP_THIS(0x42C290); }
	PathType* FindPath(
		CellStruct* from, CellStruct* to
		, FootClass* object
		, FacingType* moves, int maxLoop, MZoneType zoneType, AStarPostProcessType postProcess)
	{ JMP_THIS(0x42C900); }
	void InitCellIndexSets(int a2) { JMP_THIS(0x42CCD0); }
	bool IsCellIndexSetRegistered(int xPos, int yPos, int vectorNum) { JMP_THIS(0x42CEB0); }
	void RegisterCellIndexSet(unsigned int xPos, unsigned int yPos, int vectorNum)
	{ JMP_THIS(0x42CF10); }
	void RegisterCellIndexSets(SubzoneTrackingStruct* tracking, AStarPostProcessType postProcess)
	{ JMP_THIS(0x42CF80); }
	unsigned int TestCellWalk(CellStruct* a2, CellStruct* a3, FootClass* object, bool bridge1, int bridge2, MZoneType zoneType)
	{ JMP_THIS(0x42D170); }
};

constexpr size_t AStarClassSize = sizeof(AStarClass);
static_assert(AStarClassSize == 0xC80, "AStarClass size must be C80h (3200d)!");
