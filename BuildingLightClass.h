#pragma once

#include "GeneralStructures.h"
#include "ObjectClass.h"

class NOVTABLE BuildingLightClass : public ObjectClass
{
public:
	using base_type = ObjectClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E3AD0;
			this->IRTTITypeInfo = 0x7E3AB4;
			this->INoticeSink = 0x7E3AAC;
			this->INoticeSource = 0x7E3AA4;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::BuildingLight;
	static constexpr uintptr_t AbsVTable = 0x7E3AD0;
public:
	static constexpr constant_ptr<DynamicVectorClass<BuildingLightClass*>, 0x8B4190u> const Array{};
public:
	double Speed;
	CoordStruct field_B8;
	CoordStruct field_C4;
	double Acceleration;
	bool Direction;
	SpotlightBehaviour BehaviourMode;
	ObjectClass* FollowingObject;
	TechnoClass* OwnerObject;
public:
	virtual ~BuildingLightClass() JMP_THIS(0x435B50);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	// non-virtual
	void SetBehaviour(SpotlightBehaviour mode) JMP_THIS(0x436BE0);

protected:
	explicit __forceinline BuildingLightClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}
public:
	BuildingLightClass(noinit_t) : BuildingLightClass(fake_noinit_t{}) { vtables.init(this); }
	BuildingLightClass(ObjectClass* pOwner) : BuildingLightClass(fake_noinit_t{}) JMP_THIS(0x435820);
};
