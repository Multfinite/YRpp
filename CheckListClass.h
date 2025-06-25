#pragma once

#include "ListClass.h"

class NOVTABLE CheckListClass : public ListClass
{
public:
	bool IsReadOnly;
protected:
	explicit __forceinline CheckListClass(noinit_t)  noexcept
		: ListClass(noinit_t())
	{}
public:
	CheckListClass(unsigned int nID, int nX, int nY, int nWidth, int nHeight, TextPrintType eFlag, SHPStruct* UpSHP, SHPStruct* DownSHP) noexcept
		: CheckListClass(noinit_t())
		JMP_THIS(0x488280);
};
