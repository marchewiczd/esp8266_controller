#pragma once

#include <ESP8266WebServer.h>

class ApiHandler
{
public:
	// Initialize API handler
	// @port: specifies API server what port to run on
	ApiHandler(unsigned int port);

	void startWebServer();

	void handleClients();

private:
	ESP8266WebServer _apiServer;

	// handles not found request - HTTP 404
	void handleNotFound();

	// gets currents state of a pin
	void handleGetPinState();

	// hotplug a module
	// @pinNumber: pin number from which the module is supposed to work
	// @pinMode: 0x00 - INPUT, 0x01 - OUTPUT, 0x02 - INPUT_PULLUP
	void handleAddModule();

	// maps all routing to specific methods and endpoints
	void prepareServerRouting();
};

