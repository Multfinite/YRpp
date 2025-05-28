#pragma once

#include "AbstractClass.h"
#include "Audio.h"

class ObjectClass;
class TechnoClass;
class HouseClass;

class NOVTABLE BombClass : public AbstractClass
{
public:
	using base_type = AbstractClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E3D10;
			this->IRTTITypeInfo = 0x7E3CF4;
			this->INoticeSink = 0x7E3CEC;
			this->INoticeSource = 0x7E3CE4;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::Bomb;
	static constexpr uintptr_t AbsVTable = 0x7E3D10;
public:
	TechnoClass* Owner;		//Most likely Ivan.
	HouseClass* OwnerHouse;
	ObjectClass* Target; // attaching to objects is possible, but it will never detonate
	BOOL DeathBomb; // unused - if so, [General]CanDetonateDeathBomb applies instead of CanDetonateTimeBomb
	int PlantingFrame;
	int DetonationFrame;
	AudioController Audio;
	int TickSound;
	BOOL ShouldPlayTickingSound; // seems so
	bool Harmless; // (mostly) set to 0 on plant, 1 on detonation/removal ?
public:
	virtual ~BombClass() JMP_THIS(0x438670);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//AbstractClass
	virtual RTTIType KindOf() const RT(AbstractType);
	virtual int	SizeOf() const R0;

	void Detonate() JMP_THIS(0x438720); 
	void Disarm() JMP_THIS(0x4389B0); 
	BOOL IsDeathBomb() const JMP_THIS(0x4389F0);
	/*! @brief which frame of the ticking bomb to draw */
	int GetCurrentFlickerFrame() const JMP_THIS(0x438A00);
	bool TimeToExplode() const JMP_THIS(0x438A70);

protected:
	explicit __forceinline BombClass(fake_noinit_t) noexcept : AbstractClass(fake_noinit_t{}) {}
public:
	BombClass(noinit_t) : BombClass(fake_noinit_t{}) JMP_THIS(0x4386F0);
	BombClass() : BombClass(fake_noinit_t{}) JMP_THIS(0x4385D0);	
};
