#include "ApiHandler.h"

ApiHandler::ApiHandler(int port)
	: _apiServer(port)
{
	this->prepareServerRouting();
}

void ApiHandler::startWebServer() {
    _apiServer.begin();
}

void ApiHandler::handleClients() {
    _apiServer.handleClient();
}

void ApiHandler::handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += _apiServer.uri();
    message += "\nMethod: ";
    message += (_apiServer.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += _apiServer.args();
    message += "\n";
    for (uint8_t i = 0; i < _apiServer.args(); i++) {
        message += " " + _apiServer.argName(i) + ": " + _apiServer.arg(i) + "\n";
    }
    _apiServer.send(404, "text/plain", message);
}

void ApiHandler::handleGetPinState() {
    Serial.println("Received GetPinState");
    Serial.println("Sending response...");
    _apiServer.send(200, "text/json", "{\"name\": \"handle get pin state\"}");
    Serial.println("Response to GetPinState sent!");
}

void ApiHandler::handleAddModule() {
    Serial.println("Received AddModule");
    Serial.println("Sending response...");
    _apiServer.send(200, "text/json", "{\"name\": \"handle add module\"}");
    Serial.println("Response to AddModule sent!");
}

void ApiHandler::prepareServerRouting() {
    _apiServer.on(F("/getPinState"), HTTP_GET, [this]() { handleGetPinState(); });
    _apiServer.on(F("/addModule"), HTTP_POST, [this]() { handleAddModule(); });
    _apiServer.onNotFound([this]() { handleNotFound(); });
}