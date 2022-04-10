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
    std::vector<String> commandWords = parseSerialInput(command);
    byte wordCount = commandWords.size();

    if (commandWords[0].compareTo("esp") == 0) {
        if (commandWords[1].compareTo("restart") == 0) {
            Serial.println("Restarting...");
            ESP.restart();
        }
        else {
            Serial.print("Argument \"");
            Serial.print(commandWords[1]);
            Serial.println("\" is not recognized for \"esp\" command.");
        }
    }
    else if (commandWords[0].compareTo("help") == 0) {
        Serial.println("ESP");
        Serial.println("\trestart - restarts ESP");
    }
    else {
        Serial.print("Command \"");
        Serial.print(commandWords[0]);
        Serial.println("\" is not recognized.");
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
