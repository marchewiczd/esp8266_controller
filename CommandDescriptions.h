#pragma once

#include <CommandDetails.h>
#include <EnvironmentalVariables.h>

static std::vector<CommandDetails> AvailableCommands = {
	CommandDetails(ActionType::EspRestart, {"esp", "restart"}, 0, "- restart ESP"),
	CommandDetails(ActionType::Help, {"help"}, 0, "- print this message"),

#if ENABLE_DEBUG_COMMANDS == 1
	CommandDetails(ActionType::Debug_EepromRead, {"debug", "eeprom", "read"}, 1, "{address} - restart ESP"),
	CommandDetails(ActionType::Debug_EepromReadAll, {"debug", "eeprom", "readall"}, 0, "- print this message"),
	CommandDetails(ActionType::Debug_EepromWrite, {"debug", "eeprom", "write"}, 2, "{address} {value} - print this message"),
#endif // DEBUG

};