#pragma once

#include <Arduino.h>
#include <CommandDetails.h>
#include <vector>
#include <string>
#include <stdexcept>

class CommandParser
{
public:
	bool parse(String command, std::vector<CommandDetails> CommandDetailsList, CommandDetails& outputDetails);

private:
	bool findFirstMatch(std::vector<CommandDetails> commandDetails, std::vector<String> splitCommand, CommandDetails& outputDetails);
	bool tryMatchCurrentDetails(CommandDetails& commandDetails, std::vector<String> splitCommand, std::vector<int>& parameters);
	std::vector<String> split(String command);
};

