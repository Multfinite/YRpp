/*!
* @brief WaypointPathClass - handles path planning waypoints
*/
#pragma once

#include "AbstractClass.h"

// This refers to the "planning mode" waypoints you place with your mouse, not mapping waypoints
class WaypointClass
{
public:
    // Need to define a == operator so it can be used in array classes
    bool operator == (const WaypointClass& tWaypoint) const
    {
        return (Coords == tWaypoint.Coords && unknown == tWaypoint.unknown);
    }

    // Properties
    ::Cell Coords;
    DWORD unknown;
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

    static constexpr AbstractType AbsID = AbstractType::Waypoint;
    static constexpr uintptr_t AbsVTable = 0x7F6E70;
    static constexpr size_t ClassSize = 0x40;

public:
    int CurrentWaypointIndex;
    DynamicVectorClass<WaypointClass> Waypoints;

public:
    virtual ~WaypointPathClass() JMP_THIS(0x7638C0);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_THIS(0x763C30);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_THIS(0x763C70);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x763D90);
    
    RTTIType WhatAmI() const override JMP_THIS(0x763E10);
    int Size() const override JMP_THIS(0x763E00);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x763C00);

    WaypointClass* GetWaypoint(int idx) const JMP_THIS(0x763980);
    WaypointClass* GetWaypointAfter(int idx) const JMP_THIS(0x763BA0);
    bool WaypointExistsAt(WaypointClass* wpt) const JMP_THIS(0x763A50);
    void Clear() JMP_THIS(0x763BE0);
/*
    WaypointClass* Get_WP(int32_t index, WaypointClass* retval) JMP_THIS(0x763AF0);
    bool Set(Coordinate* a2) JMP_THIS(0x7639A0);
*/
protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline WaypointPathClass(fake_noinit_t) noexcept
        : AbstractClass(fake_noinit_t{})
    {}

public:
    WaypointPathClass(int idx) noexcept : WaypointPathClass(fake_noinit_t{})
        JMP_THIS(0x763810);
    WaypointPathClass() noexcept : WaypointPathClass(fake_noinit_t{})
        JMP_THIS(0x763730);
};
static_assert(sizeof(WaypointPathClass) == WaypointPathClass::ClassSize);