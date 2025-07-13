#pragma once

#include "GeneralStructures.h"
#include "ObjectClass.h"

class __declspec(uuid("54822258-D8A8-11D1-B462-006097C6A979"))
NOVTABLE BuildingLightClass : public ObjectClass
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
	static constexpr AbstractType AbsID = AbstractType::BuildingLight;
	static constexpr uintptr_t AbsVTable = 0x7E3AD0;
	static constexpr size_t ClassSize = 0xE8;
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
	
	HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_STD(0x436910);
	
	HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x436950);
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x4369C0);
	
	void InvalidatePointer(AbstractClass* instance, bool all = true) override JMP_THIS(0x436A00);
	RTTIType KindOf() const override JMP_THIS(0x4370B0);
	int SizeOf() const override JMP_THIS(0x436900);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x436F40);
	void AI() override JMP_THIS(0x4361D0);
	
	Layer InWhichLayer() const override JMP_THIS(0x4369F0);
	ObjectTypeClass* Type() const override JMP_THIS(0x4369E0);
	bool Limbo() override JMP_THIS(0x437030);
	bool Unlimbo(const Coordinate& position, Dir256 dir) override JMP_THIS(0x437050);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x435BE0);

	void SetBehaviour(SpotlightBehaviour mode) JMP_THIS(0x436BE0);
	int32_t MovementRadius() JMP_THIS(0x436E80);
	int32_t SpotlightRadius() JMP_THIS(0x436DA0);

protected:
	explicit __forceinline BuildingLightClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}
public:
	BuildingLightClass(noinit_t) noexcept : BuildingLightClass(fake_noinit_t{}) { vtables.init(this); }
	BuildingLightClass(ObjectClass* pOwner) : BuildingLightClass(fake_noinit_t{}) JMP_THIS(0x435820);
};
static_assert(sizeof(BuildingLightClass) == BuildingLightClass::ClassSize);