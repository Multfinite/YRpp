#pragma once

#include "ObjectClass.h"
#include "AnimTypeClass.h"
#include "BounceClass.h"
#include "StageClass.h"

class AnimTypeClass;
class BulletClass;
class HouseClass;
class LightConvertClass;

/*!
* @brief Animations
*/
class NOVTABLE AnimClass : public ObjectClass
{
public:
	using base_type = ObjectClass;
	struct __declspec(align(sizeof(uintptr_t))) vtables_t : public base_type::vtables_t
	{
		constexpr vtables_t() noexcept : base_type::vtables_t()
		{
			this->IPersistStream = 0x7E3354;
			this->IRTTITypeInfo = 0x7E3338;
			this->INoticeSink = 0x7E3330;
			this->INoticeSource = 0x7E3328;
		}
	};
	static inline vtables_t vtables{};
public:
	static const AbstractType AbsID = AbstractType::Anim;
	static constexpr uintptr_t AbsVTable = 0x7E3354;

	static constexpr constant_ptr<DynamicVectorClass<AnimClass*>, 0xA8E9A8u> const Array{};
public:
	DECLARE_PROPERTY(StageClass, Animation);
	AnimTypeClass* Type; //The AnimType.
	ObjectClass* OwnerObject; // set by AnimClass::SetOwnerObject (0x424B50)
	DWORD unknown_D0;
	LightConvertClass* LightConvert;	 //Palette?
	int LightConvertIndex; // assert( (*ColorScheme::Array)[this->LightConvertIndex] == this->LightConvert ;
	char PaletteName[0x20]; // filename set for destroy anims
	int TintColor;
	int ZAdjust;
	int YSortAdjust; // same as YSortAdjust from Type
	CoordStruct FlamingGuyCoords; // the destination the anim tries to reach
	int FlamingGuyRetries; // number of failed attemts to reach water. the random destination generator stops if >= 7
	bool IsBuildingAnim; // whether this anim will invalidate on buildings, and whether it's tintable
	bool UnderTemporal; // temporal'd building's active anims
	bool Paused; // if paused, does not advance anim, does not deliver damage
	bool Unpaused; // set when unpaused
	int PausedAnimFrame; // the animation value when paused
	bool Reverse; // anim is forced to be played from end to start
	DWORD unknown_124;
	DECLARE_PROPERTY(BounceClass, Bounce);
	BYTE TranslucencyLevel; // on a scale of 1 - 100
	bool TimeToDie; // or something to that effect, set just before UnInit
	BulletClass* AttachedBullet;
	HouseClass* Owner; //Used for remap (AltPalette).
	int LoopDelay; // randomized value, depending on RandomLoopDelay
	double Accum; // Stores accumulated fractional animation damage and gets added to Type->Damage if at least 1.0 or above. Defaults to 1.0.
	BlitterFlags AnimFlags; // argument that's 0x600 most of the time
	bool HasExtras; // enables IsMeteor and Bouncer special behavior (AnimExtras)
	byte RemainingIterations; // defaulted to deleteAfterIterations, when reaches zero, UnInit() is called
	byte unknown_196;
	byte unknown_197;
	bool IsInert; // Not official name, only set to true on TActionClass-created animations and prevents sounds, damage and TiberiumChainReaction from working.
	bool IsFogged;
	bool FlamingGuyExpire; // finish animation and remove
	bool UnableToContinue; // set when something prevents the anim from going on: cell occupied, veins destoyed or unit gone, ...
	bool SkipProcessOnce; // set in constructor, cleared during Update. skips damage, veins, tiberium chain reaction and animation progress
	bool Invisible; // don't draw, but Update state anyway
	bool PowerOff; // powered animation has no power
	PROTECTED_PROPERTY(BYTE, unused_19F);
	DECLARE_PROPERTY(AudioController, Audio3);
	DECLARE_PROPERTY(AudioController, Audio4);

public:
	virtual ~AnimClass() JMP_THIS(0x4228E0);

	HRESULT GetClassID(CLSID* pClassID) override JMP_THIS(0x426540);
	
	HRESULT Load(IStream* pStm) override JMP_THIS(0x425280);
	HRESULT Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x4253B0);
	
	void Detach(AbstractClass* instance, bool all = true) override JMP_THIS(0x425150);
	RTTIType KindOf() const override JMP_THIS(0x426580);
	int SizeOf() const override JMP_THIS(0x426530);
	void ComputeCRC(CRCEngine& crc) const override JMP_THIS(0x425410);
	Coordinate Center() const override JMP_THIS(0x422BE0);
	void AI() override JMP_THIS(0x423AC0);

	Layer InWhichLayer() const override JMP_THIS(0x424CB0);
	ObjectTypeClass* Type() const override JMP_THIS(0x425520);
	int YSort() const override JMP_THIS(0x422BC0);
	 bool Limbo() override JMP_THIS(0x425530);
	void MarkAllOccupationBits(Coordinate const& coords) override JMP_THIS(0x426270);
	void UnmarkAllOccupationBits(Coordinate const& coords) override JMP_THIS(0x426300);
	void UnInit() override JMP_THIS(0x4255B0);
	bool DrawIfVisible(RectangleStruct* pBounds, bool EvenIfCloaked, DWORD dwUnk3) const override JMP_THIS(0x422C70);
	CellStruct const* OccupiedCells(bool includeBib = false) const override JMP_THIS(0x4238D0);
	void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x422CA0);
	bool Mark(MarkType value) override JMP_THIS(0x4238B0);
	int Z() const override JMP_THIS(0x425630);

	/*!
	* @note original_name BounceAI
	* @note vtable_index 122:0x1E8
	* @note address 0x423930
	*/
	virtual int BounceAI() JMP_THIS(0x423930);
	/*!
	* @note original_name GetEnd
	* @note vtable_index 123:0x1EC
	* @note address 0x425510
	*/
	virtual int GetEndFrame() JMP_THIS(0x425510);

	void SetOwnerObject(ObjectClass *pOwner) JMP_THIS(0x424B50);

	void Pause() {
		this->Paused = true;
		this->Unpaused = false;
		this->PausedAnimFrame = this->Animation.Value;
	}

	void Unpause() {
		this->Paused = false;
		this->Unpaused = true;
	}

	// Anim start logic: sound event handling, tiberium chain reaction etc.
	void Start() const JMP_THIS(0x424CE0);

	// Anim midpoint logic: particle spawning, smudges etc.
	bool Middle() const JMP_THIS(0x424F00);

/*
	void Attach_To(ObjectClass * obj) JMP_THIS(0x424B50);
	void Do_Atom_Damage(Cell * cell) JMP_THIS(0x4251F0);
	void Flaming_Guy_AI() JMP_THIS(0x425670);
	bool Flaming_Guy_Allowed(Cell * a2) JMP_THIS(0x4260F0);
	int32_t Flaming_Guy_Coords(Coordinate * a2) JMP_THIS(0x425D10);
	int32_t Init() JMP_THIS(0x4261D0);
	void Middle() JMP_THIS(0x424F00);
	void Power_Off() JMP_THIS(0x425260);
	void Power_On() JMP_THIS(0x425270);
	void Set_House(int32_t house) JMP_THIS(0x424CA0);
	void Set_Projectile(int32_t a2) JMP_THIS(0x424C90);
	void Start() JMP_THIS(0x424CE0);
	void Stop_Attached_Anim() JMP_THIS(0x422B80);
*/

protected:
	explicit __forceinline AnimClass(fake_noinit_t) noexcept : ObjectClass(fake_noinit_t{}) {}
public:
	AnimClass(noinit_t) : AnimClass(fake_noinit_t{}) JMP_THIS(0x422720);
	AnimClass(AnimTypeClass* pAnimType, const CoordStruct& Location, int LoopDelay = 0,
		int LoopCount = 1, DWORD flags = 0x600, int ForceZAdjust = 0, bool reverse = false) noexcept
		: AnimClass(noinit_t())
	JMP_THIS(0x421EA0);
};
