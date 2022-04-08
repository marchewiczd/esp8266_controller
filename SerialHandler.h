#pragma once

#include <Arduino.h>
#include <vector>

class SerialHandler
{
public:
	SerialHandler(unsigned int baudRate);

	void handleClientWrite();


private:
	String _serialData = "";

	void handleCommand(String command);
	std::vector<String> parseSerialInput(String command);
};

