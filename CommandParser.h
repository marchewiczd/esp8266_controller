#pragma once

#include <Arduino.h>
#include <vector>
#include <string>
#include <stdexcept>


enum CmdType {
	Placeholder_A,
	Placeholder_B,
	Placeholder_C
};

struct CmdDetails {
	CmdDetails();
	CmdDetails(CmdType type, std::vector<String> commandWords, int parameterCount);

	CmdType type;
	std::vector<String> commandWords;
	int parameterCount;
	std::vector<int> parameters;
};

class CommandParser
{
public:
	bool parse(String command, std::vector<CmdDetails> cmdDetailsList, CmdDetails& outputDetails);

private:
	std::vector<CmdDetails> findAllMatches(std::vector<CmdDetails> commandDetails, String firstCommandWord, size_t commandWordCount);
	bool findFirstMatch(std::vector<CmdDetails> commandDetails, std::vector<String> splitCommand, CmdDetails& outputDetails);
	bool tryMatchCurrentDetails(CmdDetails& commandDetails, std::vector<String> splitCommand, std::vector<int>& parameters);
	std::vector<String> split(String command);
};

