#pragma once

#include <Arduino.h>
#include <CommandParser.h>
#include <CommandDescriptions.h>
#include <Action.h>
#include <vector>

class SerialHandler
{
public:
	SerialHandler(unsigned int baudRate);
	void handleClientWrite();


private:
	String _serialData = "";
	CommandParser _commandParser;

	void handleCommand(String command);
	std::vector<String> parseSerialInput(String command);
};



