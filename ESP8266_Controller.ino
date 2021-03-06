#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ApiHandler.h>
#include <Secrets.h>

// ********************
// **** CONSTANTS *****
// ********************
const char* MDNS_HOST_NAME = "esp8266";
const unsigned short WIFI_CONNECTION_ATTEMPTY_DELAY_MS = 1000;
const unsigned long BAUD_RATE = 115200;


// ********************
// ***** FIELDS *******
// ********************
ApiHandler apiServer(80);


// ********************
// **** PROTOTYPES ****
// ********************
void setupWiFiConnection();
void setupMdns();


// ********************
// ** MAIN FUNCTIONS **
// ********************
void setup(void) {
    setupWiFiConnection();
    setupMdns();
    apiServer.startWebServer();
}

void loop(void) {
    apiServer.handleClients();
    readSerial();
}


// ********************
// *** DEFINITIONS ****
// ********************
void readSerial() {
    String receivedSerialMsg;

    if (Serial.available()) {
        Serial.print("Serial <<< ");
        // read the incoming byte:
        while (Serial.available()) {
            receivedSerialMsg = Serial.read();
            Serial.print(receivedSerialMsg);
            if (!Serial.available()) delayMicroseconds(1200);
        }
        Serial.println();
    }
}

void setupWiFiConnection() {
    Serial.begin(BAUD_RATE);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, NET_PASS);

    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(WIFI_CONNECTION_ATTEMPTY_DELAY_MS);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("HTTP server started");
}

void setupMdns() {
    // Activate mDNS this is used to be able to connect to the server
    // with local DNS hostmane esp8266.local
    if (MDNS.begin(MDNS_HOST_NAME)) {
        Serial.println("MDNS responder started");
    }
}