#include "EepromHandler.h"


EepromHandler::EepromHandler(int usedAddressesCount)
{
	EEPROM.begin(usedAddressesCount);
	_usedAddressesCount = usedAddressesCount;
}

EepromResult EepromHandler::Write(uint8_t address, int value)
{
	if (address >= _usedAddressesCount)
		return EepromResult::ErrorAddressInvalid;

	if (value < 0)
		return EepromResult::ErrorValueNegative;

	uint8_t currentValue = EEPROM.read(address);
	EEPROM.commit();
	if (currentValue == value)
		return EepromResult::SuccessNoUpdateNeeded;

	EEPROM.write(address, value);
	return EepromResult::SuccessValueWritten;
}

std::pair<uint8_t, EepromResult> EepromHandler::Read(int address)
{
	if (address > _usedAddressesCount || address < 0)
		return std::make_pair<uint8_t, EepromResult>(0, EepromResult::ErrorAddressInvalid);

	return std::make_pair(EEPROM.read(address), EepromResult::SuccessValueRead);
}

std::vector<uint8_t> EepromHandler::ReadAll() 
{
	std::vector<uint8_t> readValues(_usedAddressesCount);

	for (int currentReadAddress = 0; currentReadAddress < _usedAddressesCount; currentReadAddress++)
		readValues[currentReadAddress] = EEPROM.read(currentReadAddress);

	return readValues;
}

String EepromHandler::DecodeResult(EepromResult result) 
{
	return DecodeResult((int)result);
}

String EepromHandler::DecodeResult(int result)
{
	switch (result)
	{
		case 0:
			return "Success: value written.";
		case 1:
			return "Success: no value update needed.";
		case 2:
			return "Error: negative input.";
		case 3:
			return "Error: invalid address.";
		case 4:
			return "Success: value read.";
	}

	String msg = "Error: unrecognized. Received result code: ";
	msg.concat(result);
	return msg;
}
