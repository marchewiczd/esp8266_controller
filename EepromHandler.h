#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <vector>

enum class WriteResult 
{ 
	SuccessValueWritten = 0, 
	SuccessNoUpdateNeeded = 1, 
	ErrorAddressInvalid = UINT8_MAX
};

class EepromHandler
{
public:
	EepromHandler(int usedAddressesCount);

	// 0 - written and updated
	// 1 - values are the same, skipped overwriting
	// 255 - address is invalid
	WriteResult Write(uint8_t address, uint8_t value);
	uint8_t Read(uint8_t address);
	std::vector<uint8_t> ReadAll();
	String DecodeResult(int result);

private:
	int _usedAddressesCount;
};
