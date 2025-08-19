#pragma once

#include "AbstractClass.h"

// this refers to the "planning mode" waypoints you place with your mouse, not mapping waypoints
class WaypointClass
{
public:
	//need to define a == operator so it can be used in array classes
	bool operator == (const WaypointClass& tWaypoint) const
	{
		return (Coords == tWaypoint.Coords && unknown == tWaypoint.unknown);
	}

	//Properties
	CellStruct Coords;
	DWORD       unknown;
};

class NOVTABLE WaypointPathClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7F6E70;
            this->IRTTITypeInfo = 0x7F6E54;
            this->INoticeSink = 0x7F6E4C;
            this->INoticeSource = 0x7F6E44;
        }
    };
    static inline vtables_t vtables{};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~WaypointPathClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	WaypointClass * GetWaypoint(int idx) const
		{ JMP_THIS(0x763980); }
	WaypointClass * GetWaypointAfter(int idx) const
		{ JMP_THIS(0x763BA0); }
	bool WaypointExistsAt(WaypointClass *wpt) const
		{ JMP_THIS(0x763A50); }

	// Constructor
	WaypointPathClass(int idx)
		: WaypointPathClass(noinit_t())
	{ JMP_THIS(0x763810); }

protected:

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
    /*! @brief FAKE CTOR */
    explicit __forceinline WaypointPathClass(fake_noinit_t) noexcept
        : AbstractClass(fake_noinit_t{})
    {}

public:

	int  CurrentWaypointIndex; //seems that way
	DynamicVectorClass<WaypointClass> Waypoints; // actual path waypoints, no *
    WaypointPathClass(int idx) noexcept : WaypointPathClass(fake_noinit_t{})
        JMP_THIS(0x763810);
    WaypointPathClass() noexcept : WaypointPathClass(fake_noinit_t{})
        JMP_THIS(0x763730);
};
static_assert(sizeof(WaypointPathClass) == WaypointPathClass::ClassSize);