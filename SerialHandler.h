#pragma once

#include <Arduino.h>

class SerialHandler
{
public:
	SerialHandler(unsigned int baudRate);

	void handleClientWrite();


private:
	String _serialData = "";
	void handleCommand(String command);
};

