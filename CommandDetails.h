#pragma once

#include <Arduino.h>
#include <ActionType.h>
#include <vector>


struct CommandDetails
{
	CommandDetails();
	CommandDetails(ActionType type, std::vector<String> commandWords, int parameterCount, String description);

	ActionType type;
	std::vector<String> commandWords;
	int parameterCount;
	std::vector<int> parameters;
	String description;
};

