#include "SerialHandler.h"

SerialHandler::SerialHandler(unsigned int baudRate)
{
    Serial.begin(baudRate);
}

void SerialHandler::handleClientWrite()
{
    byte ch;

    if (Serial.available()) {
        while (Serial.available()) {
            ch = Serial.read();

            // skip junk data on connection via serial
            if (ch == 254)
                return;

            _serialData += (char)ch;

            if (!Serial.available())
                delayMicroseconds(1200);
        }

        Serial.print("> ");
        Serial.println(_serialData);

        _serialData.trim();
        handleCommand(_serialData);

        _serialData = "";
    }
}

void SerialHandler::handleCommand(String command)
{
    CommandDetails cmdDetails;
    if (_commandParser.parse(command, AvailableCommands, cmdDetails)) {
        Action::Perform(cmdDetails.type);
    }
    else {
        Serial.print("Command \"");
        Serial.print(command);
        Serial.println("\" is not recognized. Type help for available commands.");
    }
}

std::vector<String> SerialHandler::parseSerialInput(String command)
{
    std::vector<String> commandWords(1);
    int currentListPosition = 0;

    for (int i = 0; i < command.length(); i++) {

        if (command[i] == ' ') {
            currentListPosition++;
            commandWords.push_back("");
        }
        else
            commandWords[currentListPosition] += command[i];
    }

    return commandWords;
}
