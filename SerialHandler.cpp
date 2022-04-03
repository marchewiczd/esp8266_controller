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
        Serial.print("Serial <<< ");
        Serial.println(_serialData);

        _serialData.trim();
        handleCommand(_serialData);

        _serialData = "";
    }
}


void SerialHandler::handleCommand(String command)
{
    Serial.print("Serial >>> ");

    if (command.compareTo("test") == 0) {
        Serial.println("PASS");
    }
    else {
        Serial.println("bad command, try again");
    }
}
