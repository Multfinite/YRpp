#pragma once

#include "AbstractTypeClass.h"

struct ScriptActionNode
{
	int Action;
	int Argument;
};

class TechnoTypeClass;

class __declspec(uuid("42F3A647-0789-11D2-ACA5-006008055BB5"))
NOVTABLE ScriptTypeClass : public AbstractTypeClass
{
public:
    using base_type = AbstractTypeClass;

    struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
    {
        constexpr vtables_t() noexcept : base_type::vtables_t()
        {
            this->IPersistStream = 0x7F1008;
            this->IRTTITypeInfo = 0x7F0FEC;
            this->INoticeSink = 0x7F0FE4;
            this->INoticeSource = 0x7F0FDC;
        }
    };
    static inline vtables_t vtables{};

    static constexpr AbstractType AbsID = AbstractType::ScriptType;
    static constexpr uintptr_t AbsVTable = 0x7F1008;
    static constexpr size_t ClassSize = 0x234;

public:
    ABSTRACTTYPE_ARRAY(ScriptTypeClass, 0x8B41C8u);

public:
    int ArrayIndex;
    bool IsGlobal;
    int ActionsCount;
    ScriptActionNode ScriptActions[50];

public:
    virtual ~ScriptTypeClass() noexcept JMP_THIS(0x691770);

    HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x691D50);
    
    HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x691D90);
    HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x691DE0);
    
    void PointerExpired(AbstractClass* instance, bool all = true) override JMP_THIS(0x691E30);
    RTTIType WhatAmI() const override JMP_THIS(0x691F70);
    int Size() const override JMP_THIS(0x691F80);
    void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x691E00);
    int GetArrayIndex() const override JMP_THIS(0x691F90);
    
    bool LoadFromINI(CCINIClass* pINI) override JMP_THIS(0x6918A0);
    bool SaveToINI(CCINIClass* pINI) override JMP_THIS(0x6917F0);

    static ScriptTypeClass* __fastcall FindOrAllocate(const char* id) JMP_STD(0x691C00);
    static bool LoadFromINIList(CCINIClass* pINI, bool IsGlobal) JMP_STD(0x691970);

/*
    void Write_Scenario_INI(int32_t a2) JMP_THIS(0x691B30);
*/

protected:
    /*! @brief FAKE CTOR */
    explicit __forceinline ScriptTypeClass(fake_noinit_t) noexcept : base_type(fake_noinit_t{}) {}

public:
    ScriptTypeClass(const char* pID) noexcept : ScriptTypeClass(fake_noinit_t{}) JMP_THIS(0x6916B0);
};
static_assert(sizeof(ScriptTypeClass) == ScriptTypeClass::ClassSize);
