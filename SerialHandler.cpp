#include "SerialHandler.h"

SerialHandler::SerialHandler(unsigned int baudRate)
{
    Serial.begin(baudRate);
}

SerialHandler::SerialHandler(unsigned int baudRate, EepromHandler* eepromHandler)
{
    Serial.begin(baudRate);
    this->_eepromHandler = eepromHandler;
}

SerialHandler::~SerialHandler()
{
    delete this->_eepromHandler;
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
            printInvalidArgumentMessage(0, commandWords);
        }
    }
    else if (commandWords[0].compareTo("help") == 0) {
        printHelpMessage();
    }
#if DEBUG == 1
    else if (commandWords[0].compareTo("debug") == 0) {
        handleDebugCommands(commandWords);
    }
#endif // DEBUG
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

void SerialHandler::handleDebugCommands(std::vector<String> commandWords)
{
    if (commandWords[0].compareTo("debug") == 0) {
        if (commandWords[1].compareTo("eeprom") == 0) {
            if (commandWords[2].compareTo("write") == 0) {
                uint8_t address = atoi(commandWords[3].c_str());
                uint8_t value = atoi(commandWords[4].c_str());
                uint8_t writeResult = (int)_eepromHandler->Write(address, value);
                if (writeResult == 0) 
                    Serial.println("success");
                else
                    Serial.println("error");
            }
            else if (commandWords[2].compareTo("read") == 0) {
                uint8_t address = atoi(commandWords[3].c_str());
                uint8_t readResult = (int)_eepromHandler->Read(address);
                Serial.println(readResult);
                    
            }
            else if (commandWords[2].compareTo("readAll") == 0) {
                std::vector<uint8_t> readResult = _eepromHandler->ReadAll();
                for (int i = 0; i < readResult.size(); i++) {
                    Serial.print(readResult[i]);
                    Serial.print(" ");
                }
            }
            else {
                printInvalidArgumentMessage(1, commandWords);
            }
        }
        else {
            printInvalidArgumentMessage(0, commandWords);
        }
    }
}

void SerialHandler::printInvalidArgumentMessage(int parentIndex, std::vector<String> commandWords)
{
    Serial.print("Argument \"");
    Serial.print(commandWords[parentIndex + 1]);
    Serial.print("\" is not recognized for \"");
    Serial.print(commandWords[parentIndex]);
    Serial.println("\" command.");
}

void SerialHandler::printHelpMessage()
{
    Serial.println("ESP");
    Serial.println("\trestart - restarts ESP");
#if DEBUG == 1
    Serial.println("debug");
    Serial.println("\teeprom");
    Serial.println("\t\twrite {address} {value} - write specific value to a given address");
    Serial.println("\t\tread {address} - read value from a given address");
    Serial.println("\t\treadAll - read all values");
#endif // DEBUG
}
