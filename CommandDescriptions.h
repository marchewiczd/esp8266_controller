#pragma once

#include <CommandDetails.h>

static std::vector<CommandDetails> AvailableCommands = {
	CommandDetails(ActionType::EspRestart, {"esp", "restart"}, 0, "restart ESP"),
	CommandDetails(ActionType::Help, {"help"}, 0, "print this message"),
};