#pragma once

#include <Arduino.h>
#include <EepromHandler.h>
#include <CommandDescriptions.h>
#include <ActionType.h>
#include <vector>


class Action {
private:
	static EepromHandler _eepromHandler;

	static void RestartEsp();
	static void PrintHelp();
	static void DebugEepromWrite(std::vector<int> parameters);
	static uint8_t DebugEepromRead(std::vector<int> parameters);
	static std::vector<uint8_t> DebugEepromReadAll();

public:
	static void Perform(ActionType type, std::vector<int> parameters = {});
	static void InitializeEeprom(EepromHandler& eepromHandler);
};
