#include "EepromHandler.h"


EepromHandler::EepromHandler(int usedAddressesCount)
{
	EEPROM.begin(usedAddressesCount);
	_usedAddressesCount = usedAddressesCount;
}

WriteResult EepromHandler::Write(uint8_t address, uint8_t value)
{
	if (address >= _usedAddressesCount)
		return WriteResult::ErrorAddressInvalid;

	uint8_t currentValue = EEPROM.read(address);
	EEPROM.commit();
	if (currentValue == value)
		return WriteResult::SuccessNoUpdateNeeded;

	EEPROM.write(address, value);
	return WriteResult::SuccessValueWritten;
}

uint8_t EepromHandler::Read(uint8_t address)
{
	if (address > _usedAddressesCount)
		return UINT8_MAX;

	return EEPROM.read(address);
}

std::vector<uint8_t> EepromHandler::ReadAll() 
{
	std::vector<uint8_t> readValues(_usedAddressesCount);

	for (int currentReadAddress = 0; currentReadAddress < _usedAddressesCount; currentReadAddress++)
		readValues[currentReadAddress] = EEPROM.read(currentReadAddress);

	return readValues;
}

String EepromHandler::DecodeResult(int result)
{
	switch (result)
	{
		case 0:
			return "Success: value written.";
		case 1:
			return "Success: no value update needed.";
		case UINT8_MAX:
			return "Error: invalid address.";
	}

	String msg = "Error: unrecognized. Received result code: ";
	msg.concat(result);
	return msg;
}
