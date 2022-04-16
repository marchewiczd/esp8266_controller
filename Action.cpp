#include "Action.h"


void Action::Perform(ActionType type, std::vector<int> parameters)
{
	switch (type) {
		case ActionType::EspRestart:
			Action::RestartEsp();
			break;

		case ActionType::Help:
			Action::PrintHelp();
			break;
	}
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
		Serial.print("- ");
		Serial.println(AvailableCommands[i].description);

		previousCmd = AvailableCommands[i].commandWords[0];
	}
}
