#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <vector>

enum class EepromResult
{
	SuccessValueWritten = 0,
	SuccessNoUpdateNeeded = 1,
	ErrorValueNegative = 2,
	ErrorAddressInvalid = 3,
	SuccessValueRead = 4
};

class EepromHandler
{
public:
	EepromHandler(int usedAddressesCount);

	// 0 - written and updated
	// 1 - values are the same, skipped overwriting
	// 2 - value is negative
	// 3 - address is invalid
	EepromResult Write(uint8_t address, int value);
	std::pair<uint8_t, EepromResult> Read(int address);
	std::vector<uint8_t> ReadAll();
	String DecodeResult(EepromResult result);
	String DecodeResult(int result);

private:
	int _usedAddressesCount;
};
