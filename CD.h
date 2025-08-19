#pragma once

#include "YRPPCore.h"

class CDDriveManagerClass
{
public:
	//Static
	static CDDriveManagerClass* Global() { return *((CDDriveManagerClass**)0x89E414); }
public:
	int CDDriveNames[26]; //int + 'A' would be the drive's name
	int NumCDDrives;
	DWORD unknown_6C;
protected:
	CDDriveManagerClass() JMP_THIS(0x4E6070);
public:
	/*!
	* @brief Retrieves the number of the currently inserted disc
	* @brief 0 = RA2 Allied,
	* @brief 1 = RA2 Soviet,
	* @brief 2 = YR
	*/
	int GetCDNumber() JMP_THIS(0x4A80D0);
};

class CD
{
public:
	DWORD unknown_04;
public:
	virtual bool ForceAvailable(int nCDNumber) R0;
	virtual bool InsertCDDialog() R0;
	virtual void SwapToDisk() RX;
protected:
	CD() {}
};
