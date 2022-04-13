#pragma once

#include <Arduino.h>
#include <EepromHandler.h>
#include <vector>

#define DEBUG 1

class SerialHandler
{
public:
	SerialHandler(unsigned int baudRate);
	SerialHandler(unsigned int baudRate, EepromHandler* eepromHandler);
	~SerialHandler();
	void handleClientWrite();


private:
	String _serialData = "";
	EepromHandler* _eepromHandler = nullptr;

	void handleCommand(String command);
	std::vector<String> parseSerialInput(String command);
	void handleDebugCommands(std::vector<String> commandWords);
	void printInvalidArgumentMessage(int parentIndex, std::vector<String> commandWords);
	void printHelpMessage();
};



