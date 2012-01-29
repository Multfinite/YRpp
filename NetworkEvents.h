#ifndef NETWORKEVENTS_H_
#define NETWORKEVENTS_H_

#include <GeneralDefinitions.h>
#include <Unsorted.h>

class BuildingClass;
class AircraftClass;
class UnitClass;
class InfantryClass;
class CellClass;
class TeamClass;
class AnimClass;
class BulletClass;
class TerrainClass;
class TeamTypeClass;
class TriggerTypeClass;
class TechnoTypeClass;
class HouseClass;
class TriggerClass;
class FootClass;
class ObjectClass;
class TechnoClass;
class AbstractClass;
class TagClass;
class TagTypeClass;
class AbstractTypeClass;

#pragma pack(push, 8)
#pragma pack(1)
struct NetworkEvent {
	byte Kind;
	byte Unused;
	byte HouseIndex;
	DWORD Timestamp;
	byte ExtraData[0x68];

	NetworkEvent() {
		memset(this, 0, sizeof(*this));
	}

	NetworkEvent * FillEvent_ProduceAbandonSuspend(int PlayerNumber, eNetworkEvents eventKind, int abstractId, int idx, int isNaval)
		{ JMP_THIS(0x4C6970); }

	NetworkEvent * FillEvent_SellCell(int dwUnk, eNetworkEvents eventKind, CellStruct *Coords)
		{ JMP_THIS(0x4C6650); }

	NetworkEvent * FillEvent_Noopt(int PlayerNumber, eNetworkEvents eventKind)
		{ JMP_THIS(0x4C66C0); }

	NetworkEvent * FillEvent_PlayerBased(int a2, eNetworkEvents eventKind, int a4)
		{ JMP_THIS(0x4C6720); }

	NetworkEvent * FillEvent_Waypoints(int PlayerNumber, eNetworkEvents eventKind, int a4, char a5, int a6, char a7)
		{ JMP_THIS(0x4C6780); }

	NetworkEvent * FillEvent_Animation(int PlayerNumber, eNetworkEvents eventKind, int a4, int a5)
		{ JMP_THIS(0x4C6800); }

	NetworkEvent * FillEvent_Place(int a2, eNetworkEvents eventKind, int a4, int a5, int a6, CellStruct *loc)
		{ JMP_THIS(0x4C6AE0); }

	NetworkEvent * FillEvent_SWPlace(int PlayerNumber, eNetworkEvents eventKind, int swTypeIdx, CellStruct *loc)
		{ JMP_THIS(0x4C6B60); }
};

struct NetID {
	DWORD RTTI_ID;
	byte WhatAmI;

	NetID() {
		this->RTTI_ID = this->WhatAmI = 0;
	}

#define UNPACK(T, addr) \
	T ## Class* Unpack ## T () { JMP_THIS(addr); }

	UNPACK(Building, 0x6E7A80);
	UNPACK(Aircraft, 0x6E7B50);
	UNPACK(Unit, 0x6E79B0);
	UNPACK(Infantry, 0x6E78E0);

	UNPACK(Cell, 0x6E7C20);
	UNPACK(Team, 0x6E7810);
	UNPACK(Anim, 0x6E7740);
	UNPACK(Bullet, 0x6E7670);
	UNPACK(Terrain, 0x6E75A0);
	UNPACK(TeamType, 0x6E74D0);
	UNPACK(TriggerType, 0x6E7400);
	UNPACK(TechnoType, 0x6E7330);
	UNPACK(House, 0x6E7260);
	UNPACK(Trigger, 0x6E7190);
	UNPACK(Foot, 0x6E70C0);
	UNPACK(Object, 0x6E6FF0);
	UNPACK(Techno, 0x6E6F20);
	UNPACK(Abstract, 0x6E6E20);
	UNPACK(Tag, 0x6E6C80);
	UNPACK(TagType, 0x6E6D50);
	UNPACK(AbstractType, 0x6E6BB0);

	NetID * Pack(AbstractClass * toPack)
		{ JMP_THIS(0x6E6AB0); }

	NetID * Pack(CellStruct * toPack)
		{ JMP_THIS(0x6E6B20); }

	NetID * Pack(Point2D * toPack)
		{ JMP_THIS(0x6E6B70); }
};
#pragma pack(pop)

class Networking {
public:
	static int &LastEventIndex;
	static int &NextPacketIndex;
	static NetworkEvent *QueuedEvents; // these are really 128 length arrays
	static int *QueuedEventTimestamps; // these are really 128 length arrays

	// custom helper for Ares logics
	static bool AddEvent(NetworkEvent *event) {
		event->Timestamp = Unsorted::CurrentFrame;
		if(LastEventIndex >= 128) {
			return false;
		}
		memcpy(&QueuedEvents[NextPacketIndex], event, sizeof(*event));
		QueuedEventTimestamps[NextPacketIndex] = Imports::TimeGetTime();
		NextPacketIndex = (NextPacketIndex + 1) & 0x7F;
		++LastEventIndex;
		return true;
	}

	// existing functions from Westwood

	/**
	 * dam girl, you crazy
	 *
	 * this gets called when you click-command your objects
	 * from inside TechnoClass::ClickedMission, where this is the selected object
	 *
	 * selfID and selfWhatAmI are results of Pack(this)
	 * PackedTarget and PackedTargetCell are pointers to the Pack()ed versions of the Target and TargetCell of ClickedMission
	 */
	static bool __fastcall CreateClickedMissionEvent
			(eMission Mission, NetID *PackedTarget, int selfID, char selfWhatAmI, NetID *PackedTargetCell)
		{ JMP_STD(0x646E90); }


};

#endif
