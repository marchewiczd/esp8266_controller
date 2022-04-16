#include "Action.h"


EepromHandler Action::_eepromHandler(EEPROM_USED_SIZE);

void Action::Perform(ActionType type, std::vector<int> parameters)
{
	switch (type) {
		case ActionType::EspRestart:
			Action::RestartEsp();
			break;
		case ActionType::Help:
			Action::PrintHelp();
			break;
		case ActionType::Debug_EepromRead:
			Action::DebugEepromRead(parameters);
			break;
		case ActionType::Debug_EepromReadAll:
			Action::DebugEepromReadAll();
			break;
		case ActionType::Debug_EepromWrite:
			Action::DebugEepromWrite(parameters);
			break;
	}
}

void Action::InitializeEeprom(EepromHandler& handler)
{
	Action::_eepromHandler = handler;
}

void Action::RestartEsp()
{
	Serial.println("Restarting...");
	ESP.restart();
}

void Action::PrintHelp()
{
	String previousCmd = "";

	Serial.println("Available commands:");
	for (int i = 0; i < AvailableCommands.size(); i++) {
		// separate different commands with empty line
		if (previousCmd != AvailableCommands[i].commandWords[0] && previousCmd != "")
			Serial.print("\n");

		Serial.print("\t");
		for (int j = 0; j < AvailableCommands[i].commandWords.size(); j++) {
			Serial.print(AvailableCommands[i].commandWords[j]);
			Serial.print(" ");
		}
		Serial.println(AvailableCommands[i].description);

		previousCmd = AvailableCommands[i].commandWords[0];
	}
}

void Action::DebugEepromWrite(std::vector<int> parameters)
{
	uint8_t writeResult = (int)Action::_eepromHandler.Write(parameters[0], parameters[1]);
	Serial.println(Action::_eepromHandler.DecodeResult(writeResult));
}

uint8_t Action::DebugEepromRead(std::vector<int> parameters)
{
	uint8_t value = Action::_eepromHandler.Read(parameters[0]);

	if (value == UINT8_MAX)
		Serial.println(Action::_eepromHandler.DecodeResult(value));

	return value;
}

std::vector<uint8_t> Action::DebugEepromReadAll()
{
	return Action::_eepromHandler.ReadAll();
}
