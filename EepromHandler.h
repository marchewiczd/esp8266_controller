#pragma once

#include <EEPROM.h>
#include <vector>

enum class WriteResult 
{ 
	SuccessValueWritten = 0, 
	SuccessNoUpdateNeeded = 0, 
	ErrorAddressInvalid = 1 
};

class EepromHandler
{
public:
	EepromHandler(int usedAddressesCount);

	// 0 - written and updated
	// 1 - values are the same, skipped overwriting
	WriteResult Write(uint8_t address, uint8_t value);
	uint8_t Read(uint8_t address);
	std::vector<uint8_t> ReadAll();

private:
	int _usedAddressesCount;
};
