/*!
* @brief ScriptClass - handles AI team script execution
*/
#pragma once

#include "AbstractClass.h"
#include "ScriptTypeClass.h"

class __declspec(uuid("42F3A646-0789-11D2-ACA5-006008055BB5"))
NOVTABLE ScriptClass : public AbstractClass
{
public:
    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public AbstractClass::vtables_t
    {
        constexpr vtables_t() noexcept : AbstractClass::vtables_t()
        {
            this->IPersistStream = 0x7F0F78;
            this->IRTTITypeInfo = 0x7F0F5C;
            this->INoticeSink = 0x7F0F54;
            this->INoticeSource = 0x7F0F4C;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::Script;
    static constexpr uintptr_t AbsVTable = 0x7F0F78;
    static constexpr size_t ClassSize = 0x30;

public:
    ScriptTypeClass* Type;
    int field_28;
    int CurrentMission;

	DEFINE_REFERENCE(DynamicVectorClass<ScriptClass*>, Array, 0x8872B0u)
public:
    virtual ~ScriptClass() JMP_THIS(0x691460);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x6915F0);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x691630);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x691690);
    
    RTTIType WhatAmI() const override JMP_THIS(0x691EC0);
    int Size() const override JMP_THIS(0x691ED0);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x6914E0);

    ScriptActionNode* GetCurrentAction(ScriptActionNode* buffer) const JMP_THIS(0x691500);
    ScriptActionNode* GetNextAction(ScriptActionNode* buffer) const JMP_THIS(0x691540);
    bool ClearMission() JMP_THIS(0x691590);
    bool SetMission(int nLine) JMP_THIS(0x6915A0);
    bool HasNextMission() const JMP_THIS(0x6915B0);
    bool HasMissionsRemaining() JMP_THIS(0x6915D0);

    // Helper method
    bool NextMission() {
        ++this->CurrentMission;
        return this->HasNextMission();
    }

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ScriptClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
    ScriptClass(ScriptTypeClass* pType) : ScriptClass(fake_noinit_t{}) JMP_THIS(0x6913C0);
};
static_assert(sizeof(ScriptClass) == ScriptClass::ClassSize);
