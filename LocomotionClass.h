#pragma once

#include "Interfaces.h"
#include "FootClass.h"
#include "Unsorted.h"
#include "YRCom.h"
#include "Drawing.h"
#include "Helpers/CompileTime.h"
#include "Helpers/VTable.h"

class LocomotionClass : public IPersistStream, public ILocomotion
{
public:
	/*!
	* @brief use only for setting virtual tables in missing noinit ctors
	*/
	struct __declspec(align(sizeof(uintptr_t))) vtables_t
	{
		uintptr_t IPersistStream;
		uintptr_t ILocomotion;

		constexpr vtables_t() noexcept :
			IPersistStream(0x7EAEC0)
			, ILocomotion(0x7EADF4)
		{}

		__forceinline void init(LocomotionClass* instance) { memcpy(instance, this, sizeof(vtables_t)); }
	};
	static inline vtables_t vtables{};

	static constexpr size_t ClassSize = 0x18;
public:
	class CLSIDs
	{
	public:
		DEFINE_REFERENCE(CLSID const, Drive, 0x7E9A30u)
		DEFINE_REFERENCE(CLSID const, Hover, 0x7E9A40u)
		DEFINE_REFERENCE(CLSID const, Tunnel, 0x7E9A50u)
		DEFINE_REFERENCE(CLSID const, Walk, 0x7E9A60u)
		DEFINE_REFERENCE(CLSID const, Droppod, 0x7E9A70u)
		DEFINE_REFERENCE(CLSID const, Fly, 0x7E9A80u)
		DEFINE_REFERENCE(CLSID const, Teleport, 0x7E9A90u)
		DEFINE_REFERENCE(CLSID const, Mech, 0x7E9AA0u)
		DEFINE_REFERENCE(CLSID const, Ship, 0x7E9AB0u)
		DEFINE_REFERENCE(CLSID const, Jumpjet, 0x7E9AC0u)
		DEFINE_REFERENCE(CLSID const, Rocket, 0x7E9AD0u)
	};
public:
	FootClass* Owner;
	FootClass* LinkedTo;
	bool Powered;
	bool Dirty;
	int RefCount;
public:

	HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* ppvObject) JMP_STD(0x55A9B0);
	ULONG __stdcall AddRef() JMP_STD(0x55A950);
	ULONG __stdcall Release() JMP_STD(0x55A970);

	HRESULT __stdcall GetClassID(CLSID* pClassID) = 0;

	HRESULT __stdcall IsDirty() JMP_STD(0x4B4C30);
	HRESULT __stdcall Load(IStream* pStm) JMP_STD(0x55AAC0); // for some reason was 0x4C9150 aka purecall
	HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) JMP_STD(0x55AA60);

	HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) JMP_STD(0x55AB40);

	virtual ~LocomotionClass() = default;
	virtual int SizeOf() const = 0;

	// ILocomotion
	// virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) JMP_STD(0x4D0510);
	// virtual ULONG __stdcall AddRef() JMP_STD(0x4D0520);
	// virtual ULONG __stdcall Release() JMP_STD(0x4D0530);
	/*3:0xC*/virtual HRESULT __stdcall Link_To_Object(void* pointer) JMP_STD(0x55A710);
	/*4:0x10*/virtual bool __stdcall Is_Moving() JMP_STD(0x55ACD0);
	/*5:0x14*/virtual CoordStruct __stdcall Destination() JMP_STD(0x55AC70);
	/*6:0x18*/virtual CoordStruct __stdcall Head_To_Coord() JMP_STD(0x55ACA0);
	/*7:0x1C*/virtual Move __stdcall Can_Enter_Cell(CellStruct cell) JMP_STD(0x55ABF0);
	/*8:0x20*/virtual bool __stdcall Is_To_Have_Shadow() JMP_STD(0x55ABE0);
	/*9:0x24*/virtual Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) JMP_STD(0x55A730);
	/*10:0x28*/virtual Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) JMP_STD(0x55A7D0);
	/*11:0x2C*/virtual Point2D __stdcall Draw_Point() JMP_STD(0x55ABD0);
	/*12:0x30*/virtual Point2D __stdcall Shadow_Point() JMP_STD(0x55A8C0);
	/*13:0x34*/virtual VisualType __stdcall Visual_Character(bool raw) JMP_STD(0x55ABC0);
	/*14:0x38*/virtual int __stdcall Z_Adjust() JMP_STD(0x55ABA0);
	/*15:0x3C*/virtual ZGradient __stdcall Z_Gradient() JMP_STD(0x55ABB0);
	/*16:0x40*/virtual bool __stdcall Process() JMP_STD(0x55AC60);
	/*17:0x44*/virtual void __stdcall Move_To(CoordStruct to) JMP_STD(0x55AC50);
	/*18:0x48*/virtual void __stdcall Stop_Moving() JMP_STD(0x55AC40);
	/*19:0x4C*/virtual void __stdcall Do_Turn(DirStruct coord) JMP_STD(0x55AC30);
	/*20:0x50*/virtual void __stdcall Unlimbo() JMP_STD(0x55AC20);
	/*21:0x54*/virtual void __stdcall Tilt_Pitch_AI() JMP_STD(0x55AB90);
	/*22:0x58*/virtual bool __stdcall Power_On() JMP_STD(0x55A8F0);
	/*23:0x5C*/virtual bool __stdcall Power_Off() JMP_STD(0x55A910);
	/*24:0x60*/virtual bool __stdcall Is_Powered() JMP_STD(0x55A930);
	/*25:0x64*/virtual bool __stdcall Is_Ion_Sensitive() JMP_STD(0x55A940);
	/*26:0x68*/virtual bool __stdcall Push(DirStruct dir) JMP_STD(0x55AB70);
	/*27:0x6C*/virtual bool __stdcall Shove(DirStruct dir) JMP_STD(0x55AB80);
	/*28:0x70*/virtual void __stdcall Force_Track(int track, CoordStruct coord) JMP_STD(0x55AC10);
	/*29:0x74*/virtual Layer __stdcall In_Which_Layer() = 0;
	/*30:0x78*/virtual void __stdcall Force_Immediate_Destination(CoordStruct coord) JMP_STD(0x55AC00);
	/*31:0x7C*/virtual void __stdcall Force_New_Slope(int ramp) JMP_STD(0x55ACE0);
	/*32:0x80*/virtual bool __stdcall Is_Moving_Now() JMP_STD(0x4B6610);
	/*33:0x84*/virtual int __stdcall Apparent_Speed() JMP_STD(0x55AD10);
	/*34:0x88*/virtual int __stdcall Drawing_Code() JMP_STD(0x55ACF0);
	/*35:0x8C*/virtual FireError __stdcall Can_Fire() JMP_STD(0x55AD00);
	/*36:0x90*/virtual int __stdcall Get_Status() JMP_STD(0x4B4C60);
	/*37:0x94*/virtual void __stdcall Acquire_Hunter_Seeker_Target() JMP_STD(0x4B4C70);
	/*38:0x98*/virtual bool __stdcall Is_Surfacing() JMP_STD(0x4B4C80);
	/*39:0x9C*/virtual void __stdcall Mark_All_Occupation_Bits(MarkType mark) JMP_STD(0x4B6620);
	/*40:0xA0*/virtual bool __stdcall Is_Moving_Here(CoordStruct to) JMP_STD(0x4B6630);
	/*41:0xA4*/virtual bool __stdcall Will_Jump_Tracks() JMP_STD(0x4B6640);
	/*42:0xA8*/virtual bool __stdcall Is_Really_Moving_Now() JMP_STD(0x4B4C50);
	/*43:0xAC*/virtual void __stdcall Stop_Movement_Animation() JMP_STD(0x4B4C90);
	/*44:0xB0*/virtual void __stdcall Limbo() JMP_STD(0x4B4CA0);
	/*45:0xB4*/virtual void __stdcall Lock() JMP_STD(0x4B6650);
	/*46:0xB8*/virtual void __stdcall Unlock() JMP_STD(0x4B6660);
	/*47:0xBC*/virtual int __stdcall Get_Track_Number() JMP_STD(0x4B6670);
	/*48:0xC0*/virtual int __stdcall Get_Track_Index() JMP_STD(0x4B6680);
	/*49:0xC4*/virtual int __stdcall Get_Speed_Accum() JMP_STD(0x4B6690);

	// Non virtuals
	static HRESULT TryPiggyback(IPiggyback** Piggy, ILocomotion** Loco)
	{ PUSH_VAR32(Loco); SET_REG32(ECX, Piggy); CALL(0x45AF20); }

	static HRESULT CreateInstance(ILocomotion** ppv, const CLSID* rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext)
	{ PUSH_VAR32(dwClsContext); PUSH_VAR32(pUnkOuter); PUSH_VAR32(rclsid); SET_REG32(ECX, ppv); CALL(0x41C250); }

	// these two are identical, why do they both exist...
	static void AddRef1(LocomotionClass** Loco)
	{ SET_REG32(ECX, Loco); CALL(0x45A170); }

	static void AddRef2(LocomotionClass** Loco)
	{ SET_REG32(ECX, Loco); CALL(0x6CE270); }

	static void ChangeLocomotorTo(FootClass* Object, const CLSID& clsid)
	{
		// remember the current one
		ILocomotionPtr Original(Object->Locomotor);

		// create a new locomotor and link it
		auto NewLoco = CreateInstance(clsid);
		NewLoco->Link_To_Object(Object);

		// get piggy interface and piggy original
		IPiggybackPtr Piggy(NewLoco);
		Piggy->Begin_Piggyback(Original);

		// replace the current locomotor
		Object->Locomotor = NewLoco;
	}

	// creates a new instance by class ID. returns a pointer to ILocomotion
	static ILocomotionPtr CreateInstance(const CLSID& rclsid)
	{
		return ILocomotionPtr(rclsid, nullptr,
			CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER);
	}

	// finds out whether a locomotor is currently piggybacking and restores
	// the original locomotor. this function ignores Is_Ok_To_End().
	static bool End_Piggyback(ILocomotionPtr& pLoco)
	{
		if (!pLoco)
			_com_issue_error(E_POINTER);

		if (IPiggybackPtr pPiggy = pLoco)
		{
			if (pPiggy->Is_Piggybacking())
			{
				// _com_ptr_t releases the old pointer automatically,
				// so we just use it without resetting it
				auto res = pPiggy->End_Piggyback(&pLoco);
				if (FAILED(res))
					_com_issue_error(res);

				return (res == S_OK);
			}
		}

		return false;
	}
protected:
	explicit __forceinline LocomotionClass(noinit_t) noexcept { }
public:
	LocomotionClass() JMP_THIS(0x55A6C0);
};
static_assert(sizeof(LocomotionClass) == LocomotionClass::ClassSize);

namespace detail
{
	template<typename Base>
	concept LocoHasILocoVtbl = std::derived_from<Base, LocomotionClass> && !std::is_same_v<LocomotionClass, Base> && requires
	{
		{ Base::ILocoVTable }->std::convertible_to<const uintptr_t>;
	};
}

template<typename T>
concept LocoCastEligible = std::is_pointer_v<T> && detail::LocoHasILocoVtbl<std::remove_cvref_t<std::remove_const_t<std::remove_pointer_t<T>>>>;


template <LocoCastEligible T>
__forceinline T locomotion_cast(ILocomotion* iLoco)
{
	using Base = std::remove_cvref_t<std::remove_const_t<std::remove_pointer_t<T>>>;
	return VTable::Get(iLoco) == Base::ILocoVTable ? static_cast<T>(iLoco) : nullptr;
}

template<LocoCastEligible T>
__forceinline T locomotion_cast(ILocomotionPtr& comLoco)
{
	return locomotion_cast<T>(comLoco.GetInterfacePtr());
/*
//	IPersistPtr comPersist = comLoco;
//	CLSID clsid;
//	if (SUCCEEDED(comPersist->GetClassID(&clsid)) && clsid == __uuidof(Base))
//		return static_cast<T>(comLoco.GetInterfacePtr());
*/
}
